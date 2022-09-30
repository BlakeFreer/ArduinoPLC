#pragma once
#ifndef TAGDI_H
#define TAGDI_H

#include "Tag.hpp"

class TagDI : public Tag {
    private:
        // Tag properties
        bool stateInitial;
        // Runtime value
        bool state;
    public:
        // Constructor
        TagDI(std::string _name, std::string _description, uint8_t _physicalPin, uint8_t _memoryAddress, bool _stateInitial); 
        // Interfaces
        std::string PrintToCSV();
};

#endif