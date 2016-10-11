#include "disp_driver.h"

#include <stddef.h>
#include <stdint.h>

#include "disp_registers.h"
#include "disp_commands.h"
#include "disp_params.h"


void disp_send(uint8_t data)
{
    DISP_DATA = data;
    DISP_CTRL &= ~(DISP_WRITE);
    asm("nop");
    DISP_CTRL |= (DISP_WRITE);
}

void disp_send_wide(uint16_t data)
{
	disp_send((uint8_t)(0xFF & data));
	disp_send((uint8_t)(0xFF & (data >> 8)));
}


void disp_command(enum DISP_COMMAND command)
{
    DISP_CTRL |= DISP_CMD;

    disp_send((uint8_t)command);
    
    DISP_CTRL &= ~DISP_CMD;
}


void disp_init()
{
	// initialize ports
	
	DISP_DATA_DIR = 0xFF;
	DISP_CTRL |= DISP_CTRL_MASK;
	DISP_CTRL_DIR |= DISP_CTRL_MASK;
	DISP_CTRL &= ~DISP_CS;
	
	// initialize display controller
	
    disp_command(DC_SYSTEM_SET);
        disp_send     (DP_SYSTEM_SET_MYSTERY_BIT);
        disp_send     (DS_CHAR_WIDTH - 1);// | DP_USE_LONG_DRIVE_WAVEFORM);
        disp_send     (DS_CHAR_HEIGHT - 1);
        disp_send     (DS_BYTES_PER_CHAR * (DS_CHARS_PER_LINE - 1));
        disp_send     (DS_BYTES_PER_CHAR * (DS_CHARS_PER_LINE - 1) + DS_LINE_TIMING_CORRECTION);
        disp_send     (DS_SCREEN_HEIGHT - 1);
        disp_send_wide(DS_BYTES_PER_CHAR * DS_CHARS_PER_LINE);
    
    disp_command(DC_SCROLL);
        disp_send_wide(DS_TEXT_START_ADDRESS);
        disp_send     (DS_SCREEN_HEIGHT - 1);
        disp_send_wide(DS_GRAPHICS_START_ADDRESS);
        disp_send     (DS_SCREEN_HEIGHT - 1);
	disp_send_wide(0x0000);
	disp_send_wide(0x0000);
    
    disp_command(DC_CURSOR_FORM);
		disp_send(DS_CHAR_WIDTH - 1);
		disp_send(DS_CHAR_HEIGHT - 1);
	
	disp_command(DC_HORIZ_DOT_SCROLL);
		disp_send(0);
	
	disp_command(DC_OVERLAY);
		disp_send(DP_COMPOSITION_METHOD_OR | DP_DISPLAY_MODE_TEXT_AND_GRAPHICS);
	
	disp_command(DC_DISPLAY_ON);
		disp_send(DP_CURSOR_MODE(DP_MODE_FLASH_RATE_1)
		         |DP_BLOCK_1_MODE(DP_MODE_ON)
		         |DP_BLOCK_2_MODE(DP_MODE_ON));
}

void disp_clear_text()
{
    disp_command(DC_CURSOR_RIGHT);
	disp_command(DC_CURSOR_SET);
		disp_send_wide(DS_TEXT_START_ADDRESS);
	
	disp_command(DC_MEM_WRITE);
	for(int i = 0; i < DS_BYTES_PER_LINE * DS_CHAR_LINES; i++)
	{
		disp_send(' ');
	}
}

void disp_write_text(int line, int position, int length, const char* text)
{
    disp_command(DC_CURSOR_RIGHT);
	disp_command(DC_CURSOR_SET);
		disp_send_wide(DS_TEXT_START_ADDRESS + line * DS_BYTES_PER_LINE + position * DS_BYTES_PER_CHAR);
	
	disp_command(DC_MEM_WRITE);
	for(int i = 0; i < length; i++)
	{
		disp_send(text[i]);
	}
}

void disp_clear_graphics()
{
	disp_command(DC_CURSOR_RIGHT);
	disp_command(DC_CURSOR_SET);
		disp_send_wide(DS_GRAPHICS_START_ADDRESS);
	
	disp_command(DC_MEM_WRITE);
	for(int i = 0; i < DS_BYTES_PER_LINE * DS_SCREEN_HEIGHT; i++)
	{
		disp_send(0x00);
	}
}

void disp_write_graphics(int x, int y, int width, int height, const uint8_t* data)
{
	disp_command(DC_CURSOR_RIGHT);
	for(int i = 0; i < height; i++)
	{
		disp_command(DC_CURSOR_SET);
			disp_send_wide(DS_GRAPHICS_START_ADDRESS + DS_BYTES_PER_LINE * (i + y) + x);
			
		disp_command(DC_MEM_WRITE);
		for(int j = 0; j < width; j++)
		{
			disp_send(data[i*width + j]);
		}
	}
}
