/*
 * speed_control.cpp (with delay)
 *
 * Created: 5/6/2016 
 *  Author: Simran Suresh
 */ 


#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void init_adc() //ADC Initializing function
{
	ADCSRA = ADCSRA | (0b00000001 << ADEN);//ADCSRA = 10000000 ENABLES the ADC
	ADCSRA = ADCSRA | (0b00000001 << ADPS2); //ADCSRA = 10000011 SETS the SAMPLING RATE
	ADMUX = ADMUX | (0b00000001 << REFS0); //ADMUX = 01000000 will SET the REFERENCE VOLTAGE
}

unsigned int read_adc()
{
	
	int p = 0b00000010;
	ADMUX = ADMUX | p; //Select the input pin
	ADCSRA = ADCSRA | (0b00000001 << ADSC); //ADCSRA = 10000011 will START the CONVERSION
	while((ADCSRA & (0b00000001 << ADIF)) == 0); //Check for ENDING the CONVERSION
	
	ADCSRA = ADCSRA | (0b00000001 << ADIF); //CLEARING ADIF
	ADMUX = ADMUX | (0b00000001 << ADLAR); //ADMUX = 01100010 OUTPUT is LEFT aligned
	
	return(ADCH);
}

void delay(int n)
{
	for(int i=0; i<n; i++)
	{
		_delay_ms(1);
	}
	
}

int main(void)
{
	DDRB = 0b11111111; //PART B is OUTPUT
	init_adc(); //CALL the adc_init function
	
	_delay_ms(500);
	unsigned int a;
	unsigned int q;
	
	unsigned int T;
	unsigned int TON;
	unsigned int TOFF;
	
	while(1)
	{
		q = read_adc(); //Read the ADC input from the ADC
		a = (q/10); //SCALING the total TIME PERIOD
		T = 25.5; //TOTAL TIME PERIOD
		TON = a; //ON TIME based on the analog input
		TOFF = T-TON; //OFF TIME = Total time - TON
		
		if(a>=0 && a<=6.3)
		{
			PORTB = 0b00001010; //Move Forward
			delay(TON);
			PORTB = 0b00000000;
			delay(TOFF);
		}
		
		if(a>=6.4 && a<=12.5)
		{
			PORTB = 0b00001001; //Turn Right
			delay(TON);
			PORTB = 0b00000000;
			delay(TOFF);
		}
		
		if(a>=12.6 && a<=18.9)
		{
			PORTB = 0b00000110; //Turn Left
			delay(TON);
			PORTB = 0b00000000;
			delay(TOFF);
		}
		
		if(a>=19 && a<=25.5)
		{
			PORTB = 0b00000101; //Move back
			delay(TON);
			PORTB = 0b00000000;
			delay(TOFF);
		}
	}
}
