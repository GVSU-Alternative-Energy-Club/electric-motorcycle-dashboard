/*
Description: Code loop to display Speedm Odometer, Battery percentage, Motor RPM, Turn Signals, High-beam, Warnernings for microcontrollers.
                This loop will constantly update specific areas of the LCD depending on the data being received
*/

#include "macros.h"
#include "disp_driver.h"

#include "cat.h"

int speed;
int rpm;
int distance;

void main()
{
	disp_init();
	disp_clear_text();
	disp_clear_graphics();

	disp_write_text(0, 0, STRING("Testing; 1 2 3..."));

	while(1){}
}

void display_speed()
{
    int digits[i];

    for (int i=0; i<3; i++) //Assign digits of speed into hundreds, tens, ones.
    {
        digits[i] = speed%10;
        speed/=10;
    }

    for(int i; i<3; i++)    //Display digits separatly depending on x/y coordinates
    {
        disp_write_graphics(
                            SPEED_DISPLAY_DIGIT_X,
                            SPEED_DISPLAY_DIGIT_Y,
                            NUMBER_DISPLAY_IMG_WIDTH,
                            NUMBER_DISPLAY_HEIGHT,
                            SPEED_DISPLAY_DIGIT_SPACING,
                            SPEED_DISPLAY_DIGIT_Y_1
                            )
    }
}
