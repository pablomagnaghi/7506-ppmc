#include "FrequencyTable.h"

using namespace ppmc;
using namespace std;

FrequencyTable::FrequencyTable(){

}

void FrequencyTable::compressEof(Query &q){
	Probability p;
	probabilityType escWidth;
	escWidth = calculateEscWidth(q);
	p.skip   = calculateSkipEof(q);

if (1) {
	p.total  = calculateTotal(q);
} else {
	probabilityType total = 0;
	map<char,size_t>::iterator iter;
	for( iter = freq.begin(); iter != freq.end(); ++iter ) {
		if (!q.isExcluded(iter->first)) {
			cerr << "including " << iter->first << " with value: " << iter->second << endl;
			p.total+= iter->second;
		} else {
			cerr << "excluding " << iter->first << endl;
		}
	}
}

	cout << "escWidth: " << escWidth << " width: " << p.width << " total: " << p.total << endl;
	if (escWidth == 0) {
		p.width = 1;
		p.total = 1;
	} else {
		p.width = escWidth;
		p.total+= escWidth;
		
	}

	updateExclusion(q);
	q.setProbability(p);
}

void FrequencyTable::compress(Query & q){
	calculateAll(q);

	Probability p = q.getProbability();
	q.setFound(p.width != 0);
	
	if( !q.isFound() ) {
		if (p.escWidth == 0) {
			p.width = 1;
			p.total = 1;
		} else {
			p.width = p.escWidth ;
			p.total += p.escWidth;
		}
		insert(q.getTerm());
	} else {
		if (p.escWidth == 0) {
			p.total += 2;
		} else {
			p.total += p.escWidth;
		}
	}
	
	q.setProbability(p);
	updateExclusion(q);

}

/**
 * Calculate all the values and update frequency in a single loop
 * 
 *   calculateAll(q);
 *   Probability p = q.getProbability();
 *
 * is the same as
 *
 *   escWidth = calculateEscWidth(q);
 *   p.skip   = calculateSkip(q);
 *   p.total  = calculateTotal(q);
 *   p.width  = calculateAndUpdateWidth(q.getTerm());
 *
 */
void FrequencyTable::calculateAll(Query& q) {
	map<char,size_t>::iterator iter;
	Probability p;
	p.skip=0;
	p.total=0;
	bool skipping = true;
	for( iter = freq.begin(); iter != freq.end(); ++iter ) {
		if (!q.isExcluded(iter->first)) {
			p.total+= iter->second;
		}
		if ( iter->first == q.getTerm() ) {
			p.width = iter->second;
			iter->second++;
			skipping = false;
		}
		if (skipping && !q.isExcluded(iter->first) ) {
			p.skip+=iter->second;
		} 
	}
	p.escWidth = freq.size();
	q.setProbability(p);
}

/**
 * Calculate the value to skip as the sum of the 
 * frequencies of the included elements before the term
 */
probabilityType FrequencyTable::calculateSkip(Query& q) {
	map<char,size_t>::iterator iter;
	probabilityType skip=0;
	for( iter = freq.begin(); iter != freq.end(); ++iter ) {
		if ( iter->first == q.getTerm() ) {
			break;
		}
		if (!q.isExcluded(iter->first) ) {
			skip+=iter->second;
		} 
	}
	return skip;
}

/**
 * Calculate the width of ESC as the count of the known terms 
 * minus the count of the excluded elements
 */
probabilityType FrequencyTable::calculateEscWidth(Query& q) {
	return freq.size();
}

/**
 * Calculate the values of all the included elements up to EOF
 */
probabilityType FrequencyTable::calculateSkipEof(Query& q) {
	return calculateTotal(q);
}

/**
 * Calculate the total as the sum of the frequencies 
 * of all the included elements
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
	for(it = freq.begin(); it != freq.end(); ++it) {
		if (it->first != q.getTerm() ) {
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
probabilityType FrequencyTable::calculateAndUpdateWidth(char c){
	map<char,size_t>::iterator iter = freq.find(c);
	probabilityType width = 0;
	if (iter != freq.end()) {
		width = iter->second; 
		iter->second++;
	}
	return width;
}


std::string FrequencyTable::show() {
	stringstream result;
	
	std::map<char,size_t>::iterator it;
	for(it = freq.begin(); it != freq.end(); ++it) {
		result << "caracter ";
		result << it->first;
		result << " |  frecuencia ";
		result << it->second;
		result << endl;
	}
	result << "caracter esc  | " << " frecuencia " << freq.size() << endl;
	return result.str();
}