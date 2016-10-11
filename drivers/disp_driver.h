#pragma once

#include <stdint.h>

void disp_init();

void disp_clear_text();

void disp_write_text(int line, int position, int length, const char* text);

void disp_clear_graphics();

void disp_write_graphics(int x, int y, int width, int height, const uint8_t* data);
