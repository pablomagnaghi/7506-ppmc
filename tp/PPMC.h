#ifndef _ppmc_h_
#define _ppmc_h_

#include <iostream>
#include <cstdlib>

namespace ppmc {
	const size_t max_models = 15;
	typedef u_int32_t baseType;
	typedef size_t probabilityType;
	//const baseType TOP = 0xFFFFFFFF;
	//const baseType BOTTOM = 0x00000000;
	//const baseType EMPTY_BUFFER = 0x00000000;
	const baseType BYTE_128 = 0x80000000;
	const baseType BYTE_127 = 0x7FFFFFFF;
	const size_t   MAX_BIT = ( sizeof(baseType) * 8 ) - 1;
}

#endif  // _ppmc_h_