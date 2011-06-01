/*
 * PPMCUncompressor.h
 *
 *  Created on: Jun 1, 2011
 *      Author: luispaniagua
 */

#ifndef PPMCUNCOMPRESSOR_H_
#define PPMCUNCOMPRESSOR_H_

#include "Uncompressor.h"
#include "FrequencyTable.h"

using namespace ppmc;

class PPMCUncompressor: public Uncompressor {
private:
	FrequencyTable table;
	bool first_character;
public:
	PPMCUncompressor(char *, char *);
	bool process (char a);
	virtual ~PPMCUncompressor();
};

#endif /* PPMCUNCOMPRESSOR_H_ */
