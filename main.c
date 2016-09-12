#include "macros.h"
#include "disp_driver.h"

#include "cat.h"
void main()
{
	disp_init();
	disp_clear_text();
	disp_clear_graphics();
	
	disp_write_text(0, 0, STRING("Testing; 1 2 3..."));

	while(1){}
}
