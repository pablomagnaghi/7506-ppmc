#ifndef __delta_h__
#define __delta_h__

void delta_encode(int  number, int* delta_value, int* delta_len );

int delta_decode(int number);

#endif /* __delta_h__ */
