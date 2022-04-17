/*
 * line_follower.cpp
 *
 * Created: 2/6/2016
 *  Author: Simran Suresh
 */ 
 
#define F_CPU 100000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD = 0b00000000; //Setting Port D as input port
	DDRB = 0b11111111; //Setting Port B as output port
	PORTD = 0b11111111; //Pulling the values of all pins of port D 
	
	while(1)
    {
		int c = PIND; //Assigning the variable with the value of the read only register PIND
		
		if(c==0b11111100) //Both sensors on the white surface - both low
			PORTB = 0b00001010; //Both motors moving forward
		
		if(c==0b11111110) //Left sensor on black and right on white
			PORTB = 0b00000110; //Left motor in reverse and right in forward
			
		if(c==0b11111101) //Right sensor on black and left on white
			PORTB = 0b00001001; //Left motor in forward and right in reverse 
			 
    }
}
