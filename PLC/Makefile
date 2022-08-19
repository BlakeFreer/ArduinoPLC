FILE = led

GCC_DEVICE = atmega328p # avr-gcc -mmcu
PROGRAMMER = arduino # avrdude -c default arduino
DUDE_DEVICE = m328p	# avrdude -p default ATMEGA328P, m328p

#atmega328p
# to find /dev/ttyACM*, type ls /dev/tty* and find item with ACM or USB

build:
	# From Arduino Forum answer
	@echo "\n********************************\nBuilding from $(FILE).c\n********************************\n"
	# avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(GCC_DEVICE) $(FILE).c -o $(FILE).bin
	avr-gcc -Os -mmcu=$(GCC_DEVICE) $(FILE).c -o $(FILE).bin
	avr-objcopy -O ihex -R .eeprom $(FILE).bin out.hex
	@echo "\n********************************\nFinished building from $(FILE).c\n********************************\n"
	@echo $(FILE).c > out.txt
	make clean

burn:
	@echo -n "\n********************************\nBurning from "
	@echo `cat out.txt`
	@echo "********************************\n"
	sudo avrdude -C /etc/avrdude.conf -F -V -c $(PROGRAMMER) -p $(DUDE_DEVICE) -P /dev/ttyACM0 -b115200 -D -Uflash:w:out.hex:i

build2:
	# From LowLevelLearning avr timer video
	avr-gcc -mmcu=atmega328p $(FILE).c -o $(FILE)
	avr-objcopy -O ihex -R .eeprom $(FILE) $(FILE).hex
	sudo avrdude -F -V -c arduino -p m328p -P /dev/ttyACM0 -b 115200 -U flash:w:$(FILE).hex

clean:
	rm -f *.bin *.o

buildburn:
	make build
	make burn