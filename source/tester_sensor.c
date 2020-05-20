#include <16F877A.h>
#device ADC=8
#fuses XT,NOWDT,NOPROTECT,NOLVP,NODEBUG
#use delay(clock=6000000)

#include "flex_lcd.c"

#byte PORTA = 0x05
#byte PORTB = 0x06
#byte PORTC = 0x07
#byte PORTD = 0x08
#byte TRISA = 0x85
#byte TRISB = 0x86
#byte TRISC = 0x87
#byte TRISD = 0x88
#define on  output_high
#define off output_low

int lecturaV,lecturaI;
float voltajeV, voltajeI,Corriente;

void main()
{
   TRISA = 0xFF;
   TRISB = 0x00;
   TRISC = 0x00;
   TRISD = 0x00;
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_AN1_AN3);
   lcd_init();
   lcd_gotoxy(1,1);
   delay_ms(1000);
   printf(lcd_putc "   CONECTE ASI  ");
   lcd_gotoxy(1,2);
   printf(lcd_putc " Vdd VIn IIn Gnd");
   lcd_gotoxy(1,1);
   printf(lcd_putc "                ");
   lcd_gotoxy(1,2);
   printf(lcd_putc "                ");
   
   for(;;)
   {
      set_adc_channel(0);
      delay_ms(20);
      lecturaV = read_adc();            
      delay_ms(100);      
      set_adc_channel(1);
      delay_ms(20);
      lecturaI = read_adc();
            
      while(lecturaV != 0 & lecturaI != 0)
      {         
         set_adc_channel(0);
         delay_ms(20);
         lecturaV = read_adc();
         voltajeV = lecturaV*0.078125;      
         lcd_gotoxy(1,1);
         printf(lcd_putc "Voltaje:%f",voltajeV);
         delay_ms(100);
         set_adc_channel(1);
         delay_ms(20);
         lecturaI = read_adc();           
         voltajeI = lecturaI*0.01953125;
         corriente = voltajeI/220;
         corriente = corriente*1000;  
         lcd_gotoxy(1,2);
         printf(lcd_putc "Corriente:%f",corriente);
      }
      
      lcd_gotoxy(1,1);
      printf(lcd_putc "   CONECTE ASI  ");
      lcd_gotoxy(1,2);
      printf(lcd_putc " Vdd VIn IIn Gnd");
   }
}
