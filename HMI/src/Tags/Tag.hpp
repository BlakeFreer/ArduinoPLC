#pragma once
#ifndef TAG_H
#define TAG_H

#include<string>

class Tag {
    private:
        std::string type;
        std::string name;
        uint8_t physicalPin;
        uint8_t memoryAddress;
    public:
        std::string getType();
        std::string getName();
        uint8_t getPin();
        uint8_t getMemoryAddress();
};

#endif