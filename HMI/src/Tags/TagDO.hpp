#pragma once
#ifndef TAGDO_H
#define TAGDO_H

#include "Tag.hpp"

class TagDO : public Tag {
    private:
        // Tag Properties
        bool stateInitial;
        // Runtime value
        bool state;
    public:
        // Constructor
        TagDO(std::string _name, std::string _description, uint8_t _physicalPin, uint8_t _memoryAddress, bool _stateInitial); 

        // Interfaces
        std::string PrintToCSV();
};

#endif