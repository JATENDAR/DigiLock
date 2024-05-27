#include "keypad.h"
#include "lcd.h"
#include "delay.h"
#include "lock.h"

unsigned char code masterlock[10]="1234567890", defaultulock[5]="54321";
unsigned char userlock[5], input[10];
extern bit newlock;

bit check(unsigned char *first, unsigned char *second, unsigned char len){
	unsigned char i=0;
	for(i=0;i<len;i++){
		if(first[i]!=second[i])
			return FALSE;
	}
	return TRUE;
}

void setulock(){
	char status;
retry:
	lcd_cmd(LCD_CLS);
	lcd_cmd(LCD_SETDDADDR);
	lcd_str("Enter Mastercode");
	lcd_cmd(0xC0);
	lcd_data(LOCK);
	lcd_data(':');
	status = getinput(10);
	if(status == TRUE){
		if(check(input,masterlock,10)){
		retry1:
			lcd_cmd(LCD_CLS);
			lcd_str("Enter new code");
			lcd_cmd(0xC0);
			lcd_data(LOCK);
			lcd_data(':');
			status = getinput(5);
			if(status == TRUE){
				lcd_cmd(LCD_CLS);
				lcd_data(OK);
				lcd_str("lock code saved!");
				newlock = TRUE;
				store_code();
				delayms(250);
				delayms(250);
				delayms(250);
				delayms(250);
				goto exit;
			}
			else if(status == RETRY)
				goto retry1;
			else if(status == EXIT)
				goto exit;
		}
		else{
			lcd_cmd(LCD_CLS);
			lcd_str("WRONG CODE!");
			delayms(250);
			delayms(250);
			delayms(250);
			delayms(250);
			goto exit;
		}
	}
	else if(status == RETRY)
		goto retry;
	else if(status == EXIT)
		goto exit;
exit:;	
}

char getinput(unsigned char max){
	unsigned char i,key;
	i=0;
	while(1){
		while(!(key=getkey()));
		key = translate(key);
		input[i]=key;
		if(key=='x'){
			if(i==0)
				return EXIT;
			i--;
			lcd_cmd(0xC2+i);
			lcd_data(' ');
			lcd_cmd(0xC2+i);
		}
		else if(key=='e'){
			return TRUE;
		}
		else{
			i++;
			if(i>max){
				lcd_cmd(LCD_CLS);
				lcd_data(EX);
				lcd_str(" Code too Long...");
				delayms(250);
				delayms(250);
				delayms(250);
				delayms(250);
				return RETRY;
			}
			lcd_data(key);
		}
	}
}


void store_code(){
	unsigned char i;
	for(i=0;i<5;i++)
		userlock[i]=input[i];
}