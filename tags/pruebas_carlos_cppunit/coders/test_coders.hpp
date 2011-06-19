#ifndef __test_coders_h__
#define __test_coders_h__

void test_decode(int start, int stop, int (*f)(int));

void test_encode(int start, int stop, void (*f)(int,int*,int*));
#endif /* __test_coders_h__ */
