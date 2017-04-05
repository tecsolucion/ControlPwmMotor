#include <18F4550.h>
#device ADC = 10
#fuses NOMCLR INTRC_IO
#use delay(clock = 8000000)


//LCD module connections
#define LCD_RS_PIN PIN_D0
#define LCD_RW_PIN PIN_D1
#define LCD_ENABLE_PIN PIN_D2
#define LCD_DATA4 PIN_D3
#define LCD_DATA5 PIN_D4
#define LCD_DATA6 PIN_D5
#define LCD_DATA7 PIN_D6

#include "lcd.c"                // libreria para el control de LCD

void main(){


FLOAT pwmanalogica;
INT16 pwmdigital; //Variables para  lectura de ADC y señal de Control a modulo CCP

lcd_init();                   // Turn LCD ON, along with other initialization commands
   
 lcd_gotoxy(1,1); 
 lcd_putc("PWM:");

   //  periodo reloj = 1/f  ;  periodo de ciclo maquina = 4/f  ; preescaler 2,4, 8, 16   4/f / prescaler;
   
   //  F_pwm  =  F_osc / [4 x PRE x (PR2+1)]

setup_timer_2(t2_div_by_4,249,1); // Configuracion   de Timer 2 para establecer frec. PWM a   F_pwm =   8M/4*4*(255) = 1960. 8=2khz  T=1/2kHz =0.5ms
setup_ccp1(ccp_pwm); //Configurar modulo CCP1 en modo PWM


output_c(0);                           // PORTC initial state
  set_tris_c(0);                         // Configure PORTC pins as outputs
  output_d(0);                           // PORTD initial state
  set_tris_d(0);                         // Configure PORTD pins as outputs
  setup_adc(ADC_CLOCK_DIV_8);            // Set ADC conversion time to 8Tosc
  setup_adc_ports(AN0);                  // Configure AN0 as analog input


  
while(true){


set_adc_channel(0); //Seleccionar Canal 0 
delay_ms(1);

pwmdigital=read_adc(); //Leer ADC 
delay_ms(1);



pwmanalogica=pwmdigital*(100.0/255.0);  


lcd_gotoxy(5,1);              // point LCD cursor to col5 row1
   
     
printf(lcd_putc,"%2.1f",pwmanalogica);


set_pwm1_duty(pwmanalogica); //
}
} 
