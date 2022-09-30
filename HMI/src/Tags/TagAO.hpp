#pragma once
#ifndef TAGAO_H
#define TAGAO_H

#include "Tag.hpp"

class TagAO : public Tag {
    private:
        // Tag parameters
        int16_t valMin;
        int16_t valMax;
        int16_t valInitial;
        // Runtime value
        int16_t val;
    public:
        // Constructor
        TagAO(std::string _name, std::string _description, uint8_t _physicalPin, uint8_t _memoryAddress, uint16_t _valInitial, uint16_t _valMin, uint16_t _valMax); 
        
        // Interfaces
        std::string PrintToCSV();
};

#endif