# ArduinoPLC Design Guide
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

The pin assignments will be done manually to ensure that the designer knows where each device is connected. The compiler will ensure that there is no overlap, but will not make any changes on its own.

## Software

### Tags
Due to storage and memory constraints (32KB ROM and 2KB RAM), only a small amount of tag data will be stored on the PLC, and as much will be stored in ROM as possible. I want to use preprocessor directives, like ```#define```, as much as possible to reduce the code size and memory usage. The PLC will not store any tag data in RAM besides the tag value. The tag address, pin, and type will be hardcoded by the preprocessor. Therefore, the PLC will not know where any specific tag is, only how to collect or write the data.

I will use a 16 bit / 2 byte width for each tag value, regardless of whether the tag is a one bit boolean or 16 bit integer. This will provide more reliable structure to the memory, rather than needing to track variables of different sizes.

Every tag can exist in AUTO or MANUAL mode. AUTO is the default state, where inputs are read from field devices and outputs are calculated from these inputs. If a tag is switched to MANUAL mode by the operator, then inputs and outputs will be held at the most recent operator setting. The AUTO/MAN state will be stored in an individual bit on the PLC.

If the full range of an 8 bit address is used, then there are 256 tag addresses, each requiring 2 bytes and a single bit for the AUTO/MAN state. This totals 256 &times; 2 + 256 &times; (1&divide;8) = 544 bytes for the tag values. This leaves 1504 bytes for other program requirements.

**Note:** Memory address ```0x00``` is reserved and should not be used.

### Memory Management
Fixed memory addressing is not available on Arduino (as far as I know). To emulate fixed addressing, the PLC will allocate a large block (512 bytes) for the 256 two-byte tag values. Then memory address 0 will be the start of this block, memory address 1 will be two bytes later, and so on.

There will also be a smaller (32 byte) block of memory allocated to hold the AUTO/MAN states for each tag as individual bits. The state corresponding to memory address 0 will be the final (LSB) of this 32 byte block, while the state for memory address 255 will be the first (MSB) bit.
> I may choose to reverse this, so that the AUTO state of memory address 0 is the first bit of the block. This decision will depend on which direction makes it easiest to access the bits.  

### Program Loop
The PLC loop has 3 main program steps. In order of execution:
1. Read inputs from field devices into memory addresses.
2. Execute the program.
3. Write outputs.
4. Respond to HMI commands

At any time during this cycle, the program can be interrupted by a command from the HMI. The imcoming command bytes will be pushed into a circular command buffer. The commands  in the buffer will be executed during step 4 of the PLC program cycle.

Step 1, 2, and 3 will only affect tags in the AUTO state. If a tag is set to manual, then any input or output to that tag value will be ignored, and only direct manipulation from the HMI will change the value. When the HMI is writing to a tag, the PLC will ensure that the tag is in MANUAL mode or else it will return an error/rejected status to the HMI.

# HMI to PLC Interface
The HMI will run on a Windows laptop and interface with the PLC over USB using serial communication.

The HMI will send short commands to the PLC, then the PLC will respond. A command has two or three components
- 1 byte Opcode
- 1 byte Address
- 2 byte Value (Optional)

The optional value should only be provided when a "Write" opcode is specified, and this value will indicate how the PLC should modify a memory value.

The PLC will always respond with a two byte message. This format will change depending on the original HMI command. If reading a value from an address, then the response is that value. If performing an operation (such as writing to an address), then the repsonse will be a success / failure code.

## Operations
A 1 byte opcode provides up to 256 operations that the HMI can instruct the PLC to perform, which will be far more than required for this project.
Bit 7 (MSB) of the opcode will be used to indicate whether the opcode is a write operation (Bit 7 = 1) or not (Bit 7 = 0).

### List of Opcodes
| Opcode | Operation (Read) || Opcode | Operation (Write)|
|:---|:---|-|:---|:---|
|```0x00```|Reserved (Do not use)||```0x80```|Reserved (Do not use)|
|```0x01```|Return value||```0x81```|Write value|
|```0x02```|Return AUTO bit||```0x82```|Write AUTO bit|
|          |               ||```0x83```|Toggle Value|
|          |               ||```0x84```|Increment Value|
|          |               ||```0x85```|Multiply Value|
|          |               ||```0x86```|Divide Value|

### Examples:
HMI Command: ```0x01 0x15```\
PLC Action: Responds with value stored at memory address ```0x15```

HMI Sends: ```0x82 0x42 0x00 0x01```\
PLC Action: Set memory address ```0x42``` mode to 1=AUTO, respond with ```0x00 0x01``` if success and ```0x00 0x00``` if fail.

HMI Command: ```0x02 0x07 0xA3 0X12```\
PLC Action: Responds with AUTO but state for memory address ```0x07```, followed by **Undesired behaviour**. Opcode ```0x02``` is a "Read" code and does not expect a 3rd or 4th byte. The ```0xA3 0x12``` bytes would be interpreted as there own command, rather than as 16 bit literal value intended for the previous command.

