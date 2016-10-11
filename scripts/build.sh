rm -r ./build/*
cp -t ./build/ *.{c,h} **/*.{c,h} **/**/*.{c,h}
cd ./build/
avr-gcc -mmcu=atmega328p -O0 *.c -o main.elf
avr-objcopy -O ihex main.elf main.hex
avrdude -v -p atmega328p -c arduino -P /dev/ttyACM0 -D -U flash:w:main.hex:i
