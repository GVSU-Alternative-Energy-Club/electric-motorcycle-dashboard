#include

CANGetRecieveRegistors();
CANUnpackIdentifier();


//data types
struct CANmessage{uint8_t standardIDH; uint8_t standardIDL; uint8_t extendedIDH; uint8_t extendedIDL; uint_8 DataLength; 
                  uint8_t Data[8]};

//CAN recieve function
void CANGetRecieveRegistors(struct CANmessage* RecieveBuffer);
{
  spi_selecet_device (PORTB, 1<<2)//Tell transmitter we are recieving data from it
  spi_exchange (0x90); //Send over SPI to the microcontrol to send buffer.
  RecieveBuffer -> standardIDH = spi_exchange(0); //Send over SPI to the microcontrol to send buffer.
    spi_exchange (0x90); //Send over SPI to the microcontrol to send buffer.
  
