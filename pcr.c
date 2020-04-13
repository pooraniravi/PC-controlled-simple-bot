#include<avr/io.h>
#include<util/delay.h>
#include<string.h>
#define F_CPU 1000000UL
#define BAUDRATE 4800
#define myubrr ((F_CPU/(BAUDRATE*16UL))-1)
#define lcd_data PORTC
#define lcd_ctrl PORTB
#define rs PB0
#define rw PB1
#define en PB2
void init()                      
{
UBRRH=(myubrr>>8);
UBRRL=myubrr;
UCSRB|=(1<<RXEN)|(1<<TXEN);
UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}
unsigned char recei()
{
while((UCSRA&(1<<RXC))==0)
{
}
return(UDR);
}
void init_lcd()
{
lcd_cmd(0x38); // initialization of 16X2 LCD in 8bit mode
_delay_ms(1);
 
lcd_cmd(0x01); // clear LCD
_delay_ms(1);
 
lcd_cmd(0x0E); // cursor ON
_delay_ms(1);
 
lcd_cmd(0x80); // ---8 go to first line and --0 is for 0th position
_delay_ms(1);
}
void lcd_cmd(unsigned char inst)
{
lcd_data=inst;
lcd_ctrl =(0<<rs)|(0<<rw)|(1<<en);
_delay_ms(1);
lcd_ctrl =(0<<rs)|(0<<rw)|(0<<en);
_delay_ms(50);
}
void lcd_write(unsigned char info)
{
lcd_data=info;
lcd_ctrl=(1<<rs)|(0<<rw)|(1<<en);
_delay_ms(1);
lcd_ctrl=(1<<rs)|(0<<rw)|(0<<en);
_delay_ms(50);
return;
}
void main()
{
char v[10];
DDRB=0b11111111;

init();
_delay_ms(50);
while(1)
{
v=recei();
if(v=='w')
PORTB=0b00001010;
else if(v=='s')
PORTB=0b00000101;
else if(v=='a')
PORTB=0b00000110;
else if(v=='d')
PORTB=0b00001001;
else
PORTB=0b00000000;
}
}