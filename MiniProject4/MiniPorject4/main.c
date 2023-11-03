/*
 * main.c
 *
 *  Created on: Oct 11, 2023
 *      Author: stw00
 */
#include"lcd.h"
#include "ultrasonic.h"
#include "avr/io.h"
#include "common_macros.h"

void main()
{
	SET_BIT(SREG,7);
	 LCD_init();
	 Ultrasonic_init();
	 LCD_displayStringRowColumn(0,0,"distance=    cm");
	while(1)
	{
		LCD_moveCursor(0,10);
		uint16 distance= Ultrasonic_readDistance();
		 LCD_moveCursor(0,10);
		 if(distance>=100)
		 {
		LCD_intgerToString(distance);
		 }
		 else
		 {
			 LCD_intgerToString(distance);
			 LCD_displayString(" ");
		 }
	}
}
