#pragma once

// CANSTAT and CANCTRL are available at these addresses,
// plus any multiple of 16
// CAN status
#define CAN_CANSTAT 0x0E
// CAN control
#define CAN_CANCTRL 0x0F

// control & status for buffer-specific interrupt output pins
#define CAN_BFPCTRL 0x0C
// control & status for digital input and request-to-send pins
#define CAN_TXRTSCTRL 0x0D

// transmit error counter
#define CAN_TEC 0x1C
// receive error counter
#define CAN_REC 0x1D

// bit timing configuration
#define CAN_CNF3 0x28
#define CAN_CNF2 0x29
#define CAN_CNF1 0x2A
// interrupt enable register
#define CAN_CANINTE 0x2B
// interrupt flag register
#define CAN_CANINTF 0x2C
// error flag register
#define CAN_EFLG 0x2D

// receive filters (RXFn) and masks (RXMn)
#define CAN_RXF0 0x00
#define CAN_RXF1 0x04
#define CAN_RXF2 0x08
#define CAN_RXF3 0x10
#define CAN_RXF4 0x14
#define CAN_RXF5 0x18

#define CAN_RXM0 0x20
#define CAN_RXM1 0x24

// individual bytes in filters and masks
// message ID
#define CAN_RXF_ID_H 0
#define CAN_RXF_ID_L 1
// extended message ID
#define CAN_RXF_EID_H 2
#define CAN_RXF_EID_L 3

// transmit (TX) and receive (RX) buffers
#define CAN_TXB0 0x30
#define CAN_TXB1 0x40
#define CAN_TXB2 0x50

#define CAN_RXB0 0x60
#define CAN_RXB1 0x70
