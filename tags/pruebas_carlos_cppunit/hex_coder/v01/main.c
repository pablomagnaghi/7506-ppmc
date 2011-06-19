#include <stdio.h>
#include <string.h>

int main( int argc ,  char * argv[] ) {
	char * decode="50 4B 03 04 14 00 03 00 00 00 AF 68 9A 2E 23 8B 7D 5D 45 00 00 00 39 00 00 00 08 00 00 00 69 6E 66 6F 2E 74 78 74 29 C9 5D 22 4D 80 A8 4E 65 E5 58 E3 A2 A5 7C 96 BA DA 42 21 F4 04 6F DA 24 FF 68 51 F9 2A 8F E8 C0 AB 2A 3D 40 5B E0 37 55 6E 91 1D A6 0A F1 25 D5 D5 B6 27 2C 56 85 25 2F 2D AF 5E DB A1 CA D6 48 0B 5A 82 6A 50 4B 01 02 14 00 14 00 03 00 00 00 AF 68 9A 2E 23 8B 7D 5D 45 00 00 00 39 00 00 00 08 00 00 00 00 00 00 00 01 00 20 00 B6 81 00 00 00 00 69 6E 66 6F 2E 74 78 74 50 4B 05 06 00 00 00 00 01 00 01 00 36 00 00 00 6B 00 00 00 00 00 ";
	char * end=decode + strlen(decode);
	while ( decode < end) {
		char digit = 0;
		if (decode[0] >= '0' && decode[0] <= '9') {
			digit = (decode[0]-'0') * 16;
                } else if (decode[0] >='a' && decode[0] <= 'f') {
                        digit = (decode[0]-'a') * 16;
		} else if (decode[0] >='A' && decode[0] <= 'F') {
			digit = (decode[0]-'A') * 16;
		}
		if (decode[1] >= '0' && decode[1] <= '9') {
			digit += decode[1]-'0';
		} else {
			digit += decode[1]-55;
		}

		decode += 3;
		printf("%c",digit);
	}
	return 0;



}
