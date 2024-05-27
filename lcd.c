#include "lcd.h"
#include "delay.h"
#include <REG2051.H>

unsigned char code lockicon[]={0xe, 0xa, 0x1f, 0x1f, 0x1b, 0x1b, 0xe, 0x0};
unsigned char code unlockicon[]={0xe, 0x2, 0x1f, 0x1f, 0x1b, 0x1b, 0xe, 0x0};
unsigned char code ex[]={0x1f, 0x1b, 0x1b, 0x1b, 0x1b, 0x1f, 0x1b, 0x1f};
unsigned char code ok[]={0x0, 0x1, 0x3, 0x16, 0x1c, 0x8, 0x0, 0x0};

void lcd_reset()
{
	lcd_port = 0xFF;
	delayms(20);
	lcd_port = 0x03+LCD_EN;
	lcd_port = 0x03;
	delayms(10);
	lcd_port = 0x03+LCD_EN;
	lcd_port = 0x03;
	delayms(1);
	lcd_port = 0x03+LCD_EN;
	lcd_port = 0x03;
	delayms(1);
	lcd_port = 0x02+LCD_EN;
	lcd_port = 0x02;
	delayms(1);
}
void lcd_init ()
{
	unsigned char i;
	lcd_reset();
	lcd_cmd(LCD_SETFUNCTION);                    // 4-bit mode - 1 line - 5x7 font. 
	lcd_cmd(LCD_SETVISIBLE+0x04);                // Display no cursor - no blink.
	lcd_cmd(LCD_SETMODE+0x02);                   // Automatic Increment - No Display shift.
	lcd_cmd(LCD_SETCGADDR);
	for(i=0;i<8;i++)
		lcd_data(lockicon[i]);
	for(i=0;i<8;i++)
		lcd_data(unlockicon[i]);
	for(i=0;i<8;i++)
		lcd_data(ex[i]);
	for(i=0;i<8;i++)
		lcd_data(ok[i]);
	lcd_cmd(LCD_SETDDADDR);                      // Address DDRAM with 0 offset 80h.
 }
 
void lcd_cmd (char cmd)
{ 
	lcd_port = ((cmd >> 4) & 0x0F)|LCD_EN;
	lcd_port = ((cmd >> 4) & 0x0F);

	lcd_port = (cmd & 0x0F)|LCD_EN;
	lcd_port = (cmd & 0x0F);

	delayus(200);
	delayus(200);
}

void lcd_data (unsigned char dat)
{ 
	lcd_port = (((dat >> 4) & 0x0F)|LCD_EN|LCD_RS);
	lcd_port = (((dat >> 4) & 0x0F)|LCD_RS);
	
	lcd_port = ((dat & 0x0F)|LCD_EN|LCD_RS);
	lcd_port = ((dat & 0x0F)|LCD_RS);

	delayus(200);
	delayus(200);
}

void lcd_str (unsigned char *str)
{
	while(*str){
		lcd_data(*str++);
	}
}