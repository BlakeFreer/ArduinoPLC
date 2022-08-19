# ArduinoPLC Philosophy and Design Guide
Blake Freer, August 2022

## Purpose
I was first exposed to the world of PLCs during my 4-month co-op at Langtree Controls in the summer of 2022. Langtree provides engineering services to the various chemical refineries and manufacturing facilities in Sarnia, Ontario. During my time as a co-op student, I created a SCADA system using Wonderware, but felt that I didn't understand how the program interfaces with the PLCs and field devices.

This experience inspired me to try and develop my own complete, albeit small, process control system. This will involve creating my own field devices, writing my own HMI software, and creating the PLC to interface all of the components.

I am choosing to use an Arduino with an ATmega328P chip for the PLC due to its flexibility and extensive documentation. Most of the software will be written in C/C++, although I will experiment with other languages to create the HMI. Currently I want to try using OpenGL, .NET, and a browser based solution.

# PLC
## Hardware
The Arduino Uno supports 20 I/O points, which include
- 8 DI / DO pins
- 6 DI / DO / AO pins
- 6 DI / DO / AI pins

>> Part of the tag database compilation process includes arranging the tags to ensure each tag gets an appropriate pin. This will be done by placing the analog inputs and outputs on the respective pins, then placing the digital pins everywhere else.
>
> Changed my mind on this. The pin assignments should be done manually to ensure that the designer knows where each device is connected. The compiler will ensure that there is no overlap, but will not make any changes on its own.

## Software
The PLC loop has 3 main program steps. In order of execution:
1. Read inputs from field devices into memory addresses.
2. Execute the program.
4. Write outputs.

At any time during this cycle, the program can be interrupted by a message from the HMI. This is either to request a tag value or manually set an output tag value.

### Tags
Due to storage and memory constraints (32KB ROM and 2KB RAM), only a small amount of tag data will be stored on the PLC, and as much will be stored in ROM as possible. I want to use preprocessor directives, like ```#define```, as much as possible to reduce the code size and memory usage. The PLC will not store any tag data in RAM besides the tag value. The tag address, pin, and type will be hardcoded by the preprocessor. Therefore, the PLC will not know where any specific tag is, only how to collect or write the data.

I will use a 16 bit / 2 byte width for each tag value, regardless of whether the tag is a one bit boolean or 16 bit integer. This will provide more reliable structure to the memory, rather than needing to track variables of different sizes.

Every tag can exist in AUTO or MANUAL mode. AUTO is the default state, where inputs are read from field devices and outputs are calculated from these inputs. If a tag is switched to MANUAL mode by the operator, then inputs and outputs will be held at the most recent operator setting. The AUTO/MAN state will be stored in an individual bit on the PLC.

If the full range of an 8 bit address is used, then there are 256 tag addresses, each requiring 2 bytes and a single bit for the AUTO/MAN state. This totals 256 &times; 2 + 256 &times; (1&divide;8) = 544 bytes for the tag values. This leaves 1504 bytes for other program requirements.

# HMI
## Hardware
The HMI will run on a Windows laptop and interface with the PLC over USB using serial communication (exact method to be determined).

### Ideas for Serial Communication
HMI Sends a 2 byte message. First byte is an operation and the second byte is the address. If the operation indicates that a value will be written to memory, then 2 more bytes will follow with that value. Otherwise, the PLC will send its responce to the HMI.

#### Operations
With a 1 byte op-code, there are 256 available operations which should be more than enough.
- Read tag value
- Change AUTO/MAN state
- Write to a Manual tag (+2 bytes to send new value)
    - should this include changing the tag state to manual? or require the state to already be manual? Currently think that this operation should set the state to manual to ensure that the value gets changed with the state to avoid having an unset value.
    - Alterntively, when switched to manual mode, the tag would hold its current value until receiving a new value from the HMI. Then errors could be avoided by verifying that AUTO tags are not written to.
- Diagnostics
    - Test connection
    - Terminate connection
    - Order shutdown of PLC
    - Verify field devices are connected