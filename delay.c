#include "delay.h"

void delayus(unsigned char delay){
	while(delay--);
}

void delayms(unsigned char delay){
	while(delay--)
		delayus(149);
}
