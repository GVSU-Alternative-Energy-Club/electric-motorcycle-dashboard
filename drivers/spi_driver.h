#pragma once

#include <stdint.h>

void spi_select_device(uint8_t *port, uint8_t pin);

uint8_t spi_exchange(uint8_t data);

void spi_init();
