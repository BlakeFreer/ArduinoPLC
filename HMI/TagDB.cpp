// Blake Freer
// Date Created: August 18, 2022
// Date Modified: August 18, 2022
// Description: A console based application for editing a tag database

#include<iostream>

class Tag {
    private:
        char name[32]; // -> for linking HMI elements to tags
        uint8_t type; // Combines IO type [bits 7-4] and datatype [bits 3-0] -> for determining size of memory allocation and if alarms are included
        uint8_t address; // memory location in PLC -> for allocating and accessing memory on PLC
        uint8_t physicalPin; // location on plc -> for compiling to configure PLC pins

        char description[128]; // -> for user to describe tag function
};
class AnalogTag : public Tag {
    // Add alarm values and units
    public:
        uint8_t units;
        int32_t LOLO;
        int32_t LO;
        int32_t HI;
        int32_t HIHI;
};

int main (void) {

    std::cout << "Hello World" << std::endl;

    return EXIT_SUCCESS;
}