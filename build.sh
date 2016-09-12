rm *.{o,out,elf,hex}
avr-gcc -mmcu=atmega328p -O0 *.c -o main.elf
avr-objcopy -O ihex main.elf main.hex
avrdude -v -p atmega328p -c arduino -P /dev/ttyACM0 -D -U flash:w:main.hex:i
