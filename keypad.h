#ifndef __KEYPAD_
#define __KEYPAD_

#include <REG2051.H>

#define keyport P1
#define col1 P1_0
#define col2 P1_1
#define col3 P1_2
#define TRUE 1
#define FALSE 0

void keypad_init();
unsigned char getkey();
unsigned char translate(unsigned char);

#endif