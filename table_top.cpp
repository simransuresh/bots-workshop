/*
 * table_top.cpp
 *
 * Created: 4/6/2016
 *  Author: Simran Suresh
 */ 
 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0b00000000; //Assigning Port D as input port
	DDRB = 0b11111111; //Assigning Port B as output port
	PORTD = 0b11111111; //Pulling up the values of all the pins of port D
	int c;
	
	while(1)
	{
		c = PIND; //Read only register PIND
		
		if(c==0b11110000) //All sensors are on the table
		{
			PORTB = 0b00001010; //Move forward
			_delay_ms(50);
			
			PORTB = 0b00000000; //Stop for 5 ms
			_delay_ms(50);
		}
		
		if(c==0b11111000) //Sensor 1 is OUT OF THE TABLE
		{
			
			PORTB=0b00011001; //Turn Right
			_delay_ms(200);
		}
		
		if(c==0b11110100) //Sensor 2 is OUT OF THE TABLE
		{
			PORTB=0b00010110; //Turn left
			_delay_ms(200);
		}
		
		if(c==0b11110010) //Sensor 3 is OUT OF THE TABLE
		{	
			PORTB=0b00010110; //Turn left
			_delay_ms(200);
		}
		
		if(c==0b11110001) //Sensor 4 is out of the table
		{	
			PORTB=0b00011001; //Turn right
			_delay_ms(200);
		}
		
		if(c==0b11111100) //Sensors 1 & 2 are OUT OF THE TABLE
		{
			PORTB=0b00010101; //Move back
			_delay_ms(200);
			PORTB=0b00011001; //Turn right
			_delay_ms(200);
		}
		
		if(c==0b11111001) //Sensors 1 & 4 are OUT OF THE TABLE
		{
			PORTB=0b00011001; //Turn right
			_delay_ms(250);
		}
		
		if(c==0b11110011) //Sensors 3 & 4 are OUT OF THE TABLE
		{
		    PORTB=0b00011010; //Move forward
			_delay_ms(200);
			PORTB=0b00011001; //Turn right
		}
		
		if(c==0b11110110) //Sensors 2 & 3 are OUT OF THE TABLE
		{
			PORTB=0b00010110; //Move left
			_delay_ms(200);
		}
		
		if(c==0b11111110) //Sensors 1,2 & 3 are OUT OF THE TABLE
		{
			PORTB=0b00010110; //Long Left Turn
			_delay_ms(700);
		}
		
		if(c==0b11111101) //Sensors 1,2 & 4 are OUT OF THE TABLE
		{
			PORTB=0b00010110; //Long Right Turn
			_delay_ms(700);
		}
		
		if(c==0b11111011) //Sensors 1,3 & 4 are OUT OF THE TABLE
		{
			PORTB=0b00011001; //Long Right Turn
			_delay_ms(700);
		}
		
		if(c==0b11110111) //Sensors 2,3 & 4 are OUT OF THE TABLE
		{
			PORTB=0b00010110; //Long LEFT U Turn
			_delay_ms(700);
		}
			
    }
}
