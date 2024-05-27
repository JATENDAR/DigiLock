#ifndef __LOCK
#define __LOCK

#include <REG2051.H>

#define lockpin P1_3
#define FALSE 0
#define TRUE 1
#define RETRY 2
#define EXIT 3
#define LOCK 0
#define UNLOCK 1
#define EX 2
#define OK 3

bit check(unsigned char *,unsigned char *,unsigned char);
void setulock();
char getinput(unsigned char);
void store_code();

#endif