/*
 * obstacle_avoidance.cpp
 *
 * Created: 3/6/2016
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
		c = PIND;
		
		if(c==0b11111111) //No obstacle 
		{
			PORTB = 0b00001010; //Move forward 
				_delay_ms(5);
			
			PORTB = 0b00000000; //Stop for 5 ms
				_delay_ms(5);
		}
			
		if(c==0b11111110) //Obstacle on the right
			PORTB = 0b00000110; //Left turn
			
		if(c==0b11111101) //Obstacle at the center
		{
			PORTB = 0b00000101; //Go back 
			_delay_ms(300);
			
			PORTB = 0b00001001; //Take right
			_delay_ms(300);
		}
		
		if(c==0b11111100) //Obstacle to the center and right
		{
			PORTB = 0b00000101; //Move backward
			_delay_ms(300);
			
			PORTB = 0b00000110; //Move Left
			_delay_ms(300);
		}
		
		if(c==0b11111011) //Obstacle to the left
		PORTB = 0b00001001; //Move Right 
		
		if(c==0b11111010) //Obstacle on both sides of the robot
		{
			PORTB = 0b00000101; //Move backwards
			_delay_ms(300);
			
			PORTB = 0b00001001; //Move right
			_delay_ms(300);
		}
		
		if(c==0b11111001) //Obstacle on the center and left
		{
			PORTB = 0b00000101; //Move backwards
			_delay_ms(300);
			
			PORTB = 0b00001001; //Move Right
			_delay_ms(300);
		}
		
		if(c==0b11111000) //Obstacle on all the sides
		{
			PORTB = 0b00000101; //Move backwards
			_delay_ms(300);
			
			PORTB = 0b00001001; //Move right
			_delay_ms(1200);
		}
		
    }
}
