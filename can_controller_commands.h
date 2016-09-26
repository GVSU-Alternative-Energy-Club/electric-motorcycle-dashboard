#pragma once

#define RESET 0xC0

// read from an arbitrary memory location
#define READ 0x03

// read from RX buffer number n, possibly skipping message ID
#define READ_RX_BUFFER(n, skip_id) (0x90 | ((n & 0x01) << 2) | (skip_id << 1))

// write to an arbitrary memory location
#define WRITE 0x02

// write from TX buffer number n, possibly skipping message ID
#define WRITE_TX_BUFFER(n, skip_id) (0x40 | ((n & 0x03) << 1) | skip_id)

// request to send data in TX buffer n, may be combined with another REQUEST_TO_SEND
#define REQUEST_TO_SEND(n) (0x80 | (1 << (n % 3)))

#define READ_STATUS 0xA0

#define READ_RX_STATUS 0xB0

#define BIT_MODIFY 0x05
