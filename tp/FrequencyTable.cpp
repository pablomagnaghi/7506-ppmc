#include "FrequencyTable.h"

using namespace ppmc;
using namespace std;

FrequencyTable::FrequencyTable(){

}

void FrequencyTable::compressEof(Query &q){
	Probability p;
	p.skip  = calculateSkipEof(q);
	p.total = calculateTotal(q) + 1;
	
	if (freq.size() == 0) {
		p.width = 1;
		p.total = 1;
	} else {
		p.width = freq.size();
	}
	
	q.setProbability(p);
	q.setFound(false);
}

void FrequencyTable::compress(Query & q){
	Probability p;
	probabilityType escWidth;
	escWidth = calculateEscWidth(q);
	p.skip   = calculateSkip(q);
	p.total  = calculateTotal(q);
	p.width  = calculateWidth(q.getTerm());
	q.setFound(p.width != 0);
	
	if( !q.isFound() ) {
		if (escWidth == 0) {
			p.width = 1;
			p.total = 1;
		} else {
			p.width = escWidth ;
			p.total += escWidth;
		}
		insert(q.getTerm());
	} else {
		if (escWidth == 0) {
			p.total += 2;
		} else {
			p.total += escWidth;
		}
	}
	q.setProbability(p);

	updateExclusion(q);
}

/**
 * Calculate the values of the included elements before the term
 */
probabilityType FrequencyTable::calculateSkip(Query& q) {
	map<char,size_t>::iterator iter;
	probabilityType skip=0;
	for( iter = freq.begin(); iter != freq.end(); ++iter ) {
		if (!q.isExcluded(iter->first) ) {
			if ( iter->first != q.getTerm() ) {
				skip+=iter->second;
			} else {
				break;
			}
		}
	}
	return skip;
}

/**
 * Calculate the count of all the excluded elements
 */
probabilityType FrequencyTable::calculateEscWidth(Query& q) {
	map<char,size_t>::iterator iter;
	probabilityType skipped=0;
	for( iter = freq.begin(); iter != freq.end(); ++iter ) {
		if (q.isExcluded(iter->first) ) {
			skipped++;
		}
	}
	return freq.size() - skipped;
}

/**
 * Calculate the values of all the included elements up to EOF
 */
probabilityType FrequencyTable::calculateSkipEof(Query& q) {
	return calculateTotal(q);
}

/**
 * Calculate the values of all the included elements
 */
probabilityType FrequencyTable::calculateTotal(Query& q){
	probabilityType total = 0;
	map<char,size_t>::iterator iter;
	for( iter = freq.begin(); iter != freq.end(); ++iter ) {
		if (!q.isExcluded(iter->first)) {
			total+= iter->second;
		}
	}
	return total;
}

void FrequencyTable::updateExclusion(Query& q) {
	std::map<char,size_t>::iterator it;
	for(it = freq.begin(); it != freq.end(); it++) {
		if (it->first == q.getTerm() ) {
			if( ! q.isFound() ) {
				q.addExclusion(it->first);
			}
		} else {
			q.addExclusion(it->first);
		}
	}
}

void FrequencyTable::insert(char c) {
	map<char,size_t>::iterator iter = freq.find(c);
	if (iter != freq.end()) {
		throw 1;
	}
	freq.insert(make_pair(c,1));
}
/**
 * Calculates the width of the searched term
 */
probabilityType FrequencyTable::calculateWidth(char c){
	map<char,size_t>::iterator iter = freq.find(c);
	probabilityType width = 0;
	if (iter != freq.end()) {
		width = iter->second; 
		iter->second++;
	}
	return width;
}

