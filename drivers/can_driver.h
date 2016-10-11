#pragma once

#include <stddef.h>
#include <stdint.h>

void can_reset();

void can_send(int priority, size_t message_size, uint8_t* message);
