#include <stdio.h>
#include <string.h>
int map_digit(char digit, char min, char max,int offset){
  if ( digit >= min && digit <= max) {
    return (digit - min + offset);
  }
  return -1;
}
int decode_digit(char digit) {
  int res;
  res=map_digit(digit,'0','9',0);
  if (res != -1) {
    return res;
  }
  res=map_digit(digit,'a','f',10);
  if (res != -1) {
    return res;
  }
  return map_digit(digit,'A','F',10);
}


int main( int argc ,  char * argv[] ) {

  char * decode="50 4B 03 04 14 00 03 00 00 00 AF 68 9A 2E 23 8B 7D 5D 45 00 00 00 39 00 00 00 08 00 00 00 69 6E 66 6F 2E 74 78 74 29 C9 5D 22 4D 80 A8 4E 65 E5 58 E3 A2 A5 7C 96 BA DA 42 21 F4 04 6F DA 24 FF 68 51 F9 2A 8F E8 C0 AB 2A 3D 40 5B E0 37 55 6E 91 1D A6 0A F1 25 D5 D5 B6 27 2C 56 85 25 2F 2D AF 5E DB A1 CA D6 48 0B 5A 82 6A 50 4B 01 02 14 00 14 00 03 00 00 00 AF 68 9A 2E 23 8B 7D 5D 45 00 00 00 39 00 00 00 08 00 00 00 00 00 00 00 01 00 20 00 B6 81 00 00 00 00 69 6E 66 6F 2E 74 78 74 50 4B 05 06 00 00 00 00 01 00 01 00 36 00 00 00 6B 00 00 00 00 00 ";
  int delta=3;
  if (decode[2]!=' ') {
    delta=2;
  }  
  char * end=decode + strlen(decode);
  while ( decode < end) {
    int digit = 0;
    int tmp = decode_digit(decode[0]);
    if (tmp == -1) {
      return 1;
    } 
    digit = tmp * 16;

    tmp = decode_digit(decode[1]);
    if (tmp == -1) {
      return 1;
    }
    digit += tmp;

    decode += delta;
    printf("%c",digit);
  }
  return 0;



}
