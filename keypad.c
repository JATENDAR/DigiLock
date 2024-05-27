#include "keypad.h"
#include "delay.h"

bit keystatus = FALSE;

void keypad_init(){
	keyport &=0x0F;
}
			   
unsigned char getkey(){
	unsigned char i,j,k,key=0,temp;
	k=1;
	for(i=0;i<4;i++){
		keyport &=~(0x80>>i);
		temp = keyport;
		temp &= 0x07;
		if(7-temp){
			if(!col1){
				key = k+0;
				while(!col1);
				return key;
			}
			if(!col2){
				key = k+1;
				while(!col2);
				return key;
			}
			if(!col3){
				key = k+2;
				while(!col3);
				return key;
			}
			j++;
		}
		k+=3;
		keyport |= 0x80>>i;
		delayms(10);
	}
	return FALSE;
}

unsigned char translate(unsigned char keyval){
	if(keyval<10)
		return keyval+'0';
	else if(keyval==10)
		return 'x';
	else if(keyval==11)
		return '0';
	else if(keyval==12)
		return 'e';
}