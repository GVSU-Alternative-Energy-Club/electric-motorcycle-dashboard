#pragma once

// This file defines the registers used to control the LCD.
// These correspond to section 5-1-1 (MCU interface) in the
// datasheet for the RA8835 controller.

#include <avr/io.h>

#define DISP_CMD    (1 << 0) // A0 in datasheet, set to 0 for command, 1 for data
#define DISP_WRITE  (1 << 1) // WR in datasheet, used to write commands/data
#define DISP_READ   (1 << 2) // RD in datasheet, read data
#define DISP_CS     (1 << 3) // CS in datasheet, usually set to 0
#define DISP_RESET  (1 << 4) // RES in datasheet, hardware reset

#define DISP_CTRL_MASK (DISP_CMD    \
                      | DISP_WRITE  \
                      | DISP_READ   \
                      | DISP_CS     \
                      | DISP_RESET)

#define DISP_CTRL PORTC
#define DISP_CTRL_DIR DDRC

#define DISP_DATA PORTD
#define DISP_DATA_DIR DDRD
