#include <REG2051.H>
#define lcd_port          P3

//LCD Registers addresses
#define LCD_EN		0x80
#define LCD_RS		0x20
                     
//LCD Commands        
#define LCD_CLS			   0x01
#define LCD_HOME		   0x02
#define LCD_SETMODE		   0x04
#define LCD_SETVISIBLE	   0x08
#define LCD_SHIFT		   0x10
#define LCD_SETFUNCTION	   0x28
#define LCD_SETCGADDR	   0x40
#define LCD_SETDDADDR	   0x80

#define FALSE 0
#define TRUE  1                                                       
                                                                                            
                                                                                               
/******************************
***** FUNCTION PROTOTYPES *****                                                             
******************************/                                                             
void lcd_init();
void lcd_reset();
void lcd_cmd (char);
void lcd_data(unsigned char);
void lcd_str (unsigned char*);
