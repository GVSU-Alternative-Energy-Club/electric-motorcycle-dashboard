#pragma once

// Commands and their parameters are taken from the datasheet for
// the RA8835 LCD controller, section 6. Parameters are given
// descriptive names where possible.

enum DISP_COMMAND
{
	// "system control"
    DC_SYSTEM_SET = 0x40,
    DC_SLEEP_IN   = 0x53,

	// "display control"
    DC_DISPLAY_ON        = 0x59,
    DC_DISPLAY_OFF       = 0x58,
    DC_SCROLL            = 0x44,
    DC_CURSOR_FORM       = 0x5D, // CSRFORM in datasheet
    DC_CHAR_GEN_RAM_ADDR = 0x5C, // CGRAM ADR in datasheet
    DC_CURSOR_RIGHT      = 0x4C, // CSRDIR, along with the other cursor directions
    DC_CURSOR_LEFT       = 0x4D, // ...
    DC_CURSOR_UP         = 0x4E, // ...
    DC_CURSOR_DOWN       = 0x4F, // ...
    DC_HORIZ_DOT_SCROLL  = 0x5A, // HDOT SCR in datasheet, can't really blame them for abbreviating here
    DC_OVERLAY           = 0x5B, // OVLAY in datasheet

	// "drawing control"
    DC_CURSOR_SET  = 0x46, // CSRW in datasheet
    DC_CURSOR_READ = 0x47, // CSRR in datasheet

	// "memory control"
    DC_MEM_WRITE = 0x42, // MWRITE in datasheet
    DC_MEM_READ  = 0x43  // MREAD in datasheet
};


// DC_SYSTEM_SET parameters //
// 1st byte
#define DP_USE_EXTERNAL_CG_ROM     (1 << 0) // M0 in datasheet
#define DP_D6_CORRECTION           (1 << 1) // M1 in datasheet, some arcane character generator memory layout stuff
#define DP_USE_TALL_CHARS          (1 << 2) // M2 in datasheet, use 16 pixel tall characters
#define DP_USE_DUAL_PANEL_DRIVE    (1 << 3) // W/S in datasheet
#define DP_SYSTEM_SET_MYSTERY_BIT  (1 << 4) // Required. No reason given in datasheet.
#define DP_SHIFT_TEXT_DOWN_1_PIXEL (1 << 5) // IV in datasheet, used to avoid mangling first line of text when inverted
// 2nd byte
	// FX in datasheet. Datasheet says this is 3 bit parameter, but states behavior with 4 bits
#define DP_USE_LONG_DRIVE_WAVEFORM (1 << 7) // WF in datasheet, reduces flickering at the expense of display contrast
// 3rd byte
	// FY in datasheet
// 4th byte
	// C/R in datasheet, width of screen in bytes
// 5th byte
	// TC/R in datasheet, used to minimize jitter
// 6th byte
	// L/F in datasheet, height of frame displayed on screen
// 7th byte & 8th byte are 16-bit address range, AP in datasheet


// DC_SLEEP_IN parameters //
// (no parameters)


// DC_DISPLAY_[ON,OFF] parameters //
#define DP_MODE_OFF          0x00 // one of 4 modes for FC and FP parameters
#define DP_MODE_ON           0x01 // ...
#define DP_MODE_FLASH_RATE_1 0x02 // ...
#define DP_MODE_FLASH_RATE_2 0x03 // ...
// 1st byte
#define DP_CURSOR_MODE(x)  ((0x03 & x) << 0) // FC in datasheet
#define DP_BLOCK_1_MODE(x) ((0x03 & x) << 2) // FP[1,0] in datasheet
#define DP_BLOCK_2_MODE(x) ((0x03 & x) << 4) // FP[3,2] in datasheet
#define DP_BLOCK_3_MODE(x) ((0x03 & x) << 6) // FP[5,4] in datasheet


// DC_SCROLL parameters //
// This command has 4 block start address (SAD in datasheet) parameters and
// 2 block height (SL in datasheet) parameters, in the format
// [SAD 1L, SAD 1H, SL1, SAD 2L, SAD 2H, SL 2, SAD 3L, SAD 3H, SAD 4L, SAD 4H].
//
// If not using a partitioned screen, dual-drive screen, or other weird layout,
// SAD 1 and 2, SL 1 and 2, and (for 3 layers) SAD 3[L,H] are the only
// parameters that need to be set.
// SL 1 and SL 2 should both be set to DP_FRAME_HEIGHT in this case.


// DC_CURSOR_FORM parameters //
// 1st byte
	// CRX in datasheet
// 2nd byte
	// CRY in datasheet
#define DP_USE_BLOCK_CURSOR (1 << 7) // CM in datasheet, set to 1 in graphics mode


// DC_HORIZ_DOT_SCROLL parameters //
// 1st byte
	// D[2-0] in datasheet


// DC_OVERLAY parameters //
// 1st byte
#define DP_COMPOSITION_METHOD_OR       0x00 // one of 4 modes for MX parameter
#define DP_COMPOSITION_METHOD_XOR      0x01 // ...
#define DP_COMPOSITION_METHOD_AND      0x02 // ...
#define DP_COMPOSITION_METHOD_PRIORITY 0x03 // ...
#define DP_DISPLAY_MODE_TEXT_AND_GRAPHICS 0x00 // one of 3 modes for DM and OV parameters
#define DP_DISPLAY_MODE_2_LAYER_GRAPHICS  0x0C // ...
#define DP_DISPLAY_MODE_3_LAYER_GRAPHICS  0x1C // ...


// No parameters for:
// DC_SLEEP_IN,
// DC_CURSOR_[LEFT, RIGHT, UP, DOWN]
//
// DC_CURSOR_READ and DC_MEM_READ write back to the data register instead
//
// DC_MEM_WRITE takes the raw byte data to be written
//
// DC_CHAR_GEN_RAM_ADDR and DC_CURSOR_SET take 16-bit address parameters
