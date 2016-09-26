# electric-motorcycle-dashboard

This is the code for the electronic dashboard for an electric motorcycle.

## Hardware used

* MCU: ATMega328P (Arduino is used for prototyping)
* Display: Newhaven Display NHD-320240WG-BoTFH-VZ# (320 x 240 transflective LCD display with backlight)
* CAN controller: Microchip MCP2515 (on Arduino CAN shield for prototyping)
* CAN transciever: Microchip MCP2551 (on Arduino CAN shield for prototyping)

The CAN controller and transciever are used to communicate with the Sevcon Gen4 motor controller, which
controls most of the functionality of the motorcycle.

## Software requirements

### Communication over CAN

The motor controller regularly sends data on motor performance, battery charge, and various sensors over the CAN bus using
a version of the CANOpen protocol. The display software should receive all this information and display what is relevant
to the operator.

The display software should never interfere with the operation of the motor controller. The easiest way to avoid this
is to avoid sending messages over the CAN bus.

Sending and receiving messages is done by the CAN controller, which is controlled over SPI and which has a number of
interrupt outputs to get the attention of the MCU. The CAN controller can hold a maximum of 2 received messages at a time,
so an interrupt service routine must be used to deal with received messages.

### Displayed information

Displayed information must include:

* speed of the vehicle
* motor RPM
* energy in battery
* distance traveled
* indicators for turn signals & high-beam headlights
* indicators for warnings or errors from the motor controller

Speed and RPM in particular can change very quickly, and must be updated accordingly.

Sending information to the display takes a significant amount of time on the MCU. It should only be
done for parts of the display which need to be updated.

Memory on the MCU and space on the display itself are limited. Only information which is relevant to the
safe and legal operation of the vehicle should be displayed.

## Software design

The software has 3 major components: An interrupt service routine (ISR) which processes CAN messages,
a main loop which updates the display from the contents of the CAN messages, and a collection
of software libraries which are initialized, then used to communicate with the display and CAN
controller. Information is sent from the ISR to the display update loop using state variables
for each indicator on the display.

### initialization

Initialization routines for the software libraries are called when the system is powered on.

### state variables

The current state of each indicator or quantity displayed is stored in memory on the MCU.
Each of these variables also has a separate flag indicating whether it has changed and
should be updated on the display.

### interrupt service routine (ISR) for CAN messages

Each CAN message received is processed by an ISR which determines the contents and type of the
message and whether it is relevant to the display. The contents of the message are converted to
a convenient type and unit for display and written to the appropriate state variables.

### display update loop

Images are copied from the MCU memory to the display based on the state variables for each
indicator or quantity.

### software libraries for display, SPI, CAN, and CANOpen

A few simple libraries handle the register manipulations and commands needed to communicate with the display
and the CAN controller.

* The display uses an 8-bit parallel interface for data, with separate read, write, and command/data select lines
controlled by the MCU.
* The CAN controller uses an SPI interface.
