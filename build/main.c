/*
Description: Code loop to display Speedm Odometer, Battery percentage, Motor RPM, Turn Signals, High-beam, Warnernings for microcontrollers.
                This loop will constantly update specific areas of the LCD depending on the data being received
*/

#define F_CPU 16000000L
#include <util/delay.h>

#include "macros.h"
#include "disp_driver.h"

#include "image_positions.h"
#include "digit_images.h"

void display_number(int number, int n_digits);

void main()
{
	disp_init();
	disp_clear_text();
	disp_clear_graphics();

	disp_write_text(0, 0, STRING("Testing; 1 2 3..."));
	
	while(1)
	{
		for(int i = 0; i < 1000; i++)
		{
			display_number(i, 3);
			_delay_ms(1000);
		}
	}
}

void display_number(int number, int n_digits)
{
    int digits[6];

    for (int i=0; i<n_digits; i++) //Assign digits of speed into hundreds, tens, ones.
    {
        digits[n_digits - 1 - i] = number%10;
        number/=10;
    }

    for(int i=0; i<n_digits; i++)    //Display digits separately depending on x/y coordinates
    {
        disp_write_graphics(
                            SPEED_DISPLAY_DIGIT_X + SPEED_DISPLAY_DIGIT_SPACING * i,
                            SPEED_DISPLAY_DIGIT_Y,
                            DIGIT_DISPLAY_IMG_WIDTH,
                            DIGIT_DISPLAY_IMG_HEIGHT,
                            digit_image(digits[i])
                            );
    }
}
