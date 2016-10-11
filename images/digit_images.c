#include "digit_images.h"

#include <stddef.h>

const char* digit_image(int n)
{
	switch(n)
	{
		case 0:
			return DISP_IMG_DIGIT_0_DATA;
		case 1:
			return DISP_IMG_DIGIT_1_DATA;
		case 2:
			return DISP_IMG_DIGIT_2_DATA;
		case 3:
			return DISP_IMG_DIGIT_3_DATA;
		case 4:
			return DISP_IMG_DIGIT_4_DATA;
		case 5:
			return DISP_IMG_DIGIT_5_DATA;
		case 6:
			return DISP_IMG_DIGIT_6_DATA;
		case 7:
			return DISP_IMG_DIGIT_7_DATA;
		case 8:
			return DISP_IMG_DIGIT_8_DATA;
		case 9:
			return DISP_IMG_DIGIT_9_DATA;
	}
};
