#include "lcd.h"
#include "keypad.h"
#include "lock.h"
#include "delay.h"

extern unsigned char input[10], userlock[5];
extern unsigned char code defaultulock[5],masterlock[10];
bit newlock=FALSE;
unsigned char retrycount=3;

void main(){
	unsigned char status,i=0;
	bit lockstatus;
	lcd_init();
	keypad_init();
	while(1){
		lcd_cmd(LCD_CLS);
		lcd_str("Enter lock code");
		lcd_cmd(0xC0);
		lcd_data(LOCK);
		lcd_data(':');
		status = getinput(5);
		if(check(input,"12345",5)){
			setulock();
			goto done;
		}
		if(status == TRUE){
			if(newlock)
				lockstatus = check(input,userlock,5);
			else
				lockstatus = check(input,defaultulock,5);
			if(lockstatus){
				retrycount = 3;
				lockpin = 0;
				lcd_cmd(LCD_CLS);
				lcd_data(OK);
				lcd_str(" Lock is");
				lcd_cmd(0xC0);
				lcd_str("deactivated!");
				delayms(250);
				delayms(250);
				delayms(250);
				delayms(250);
				lcd_cmd(LCD_CLS);
				lcd_str("Press '#' key to");
				lcd_cmd(0xC0);
				lcd_str("lock again!");
				while(getkey()!=12);
				lockpin = 1;
				lcd_cmd(LCD_CLS);
				lcd_data(OK);
				lcd_str("Lock is active!");
			}
			else{
				retrycount--;
				lcd_cmd(LCD_CLS);
				lcd_data(EX);
				lcd_str(" Wrong Code!");
				lcd_cmd(0xC0);
				lcd_str("Tries left = ");
				lcd_data('0'+retrycount); 
				delayms(250);
				delayms(250);
				delayms(250);
				delayms(250);
				if(retrycount==0){
				blocked:
					lcd_cmd(LCD_CLS);
					lcd_data(EX);
					lcd_str("BLOCKED");
					lcd_data(EX);
					lcd_cmd(0xC0);
					lcd_data(LOCK);
					lcd_data(':');
					status = getinput(10);
					if(check(input,masterlock,10)){
						retrycount=3;
						lcd_cmd(LCD_CLS);
						lcd_data(EX);
						lcd_str("UNBLOCKED");
						lcd_data(EX);
						delayms(250);
						delayms(250);
						delayms(250);
						delayms(250);
					}
					else{
						lcd_cmd(LCD_CLS);
						lcd_data(EX);
						lcd_str("WRONG CODE");
						lcd_data(EX);
						delayms(250);
						delayms(250);
						delayms(250);
						delayms(250);
						goto blocked;
					}
				}
			}
		}
	done:;
	}		
}