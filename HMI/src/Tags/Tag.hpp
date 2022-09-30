// Author: Blake Freer
// Date Created: September 29, 2022
// Purpose: Defines the abstract Tag class

#pragma once
#ifndef TAG_H
#define TAG_H

#include<string>

class Tag {
    protected:
        std::string type;
        std::string name;
        std::string description;
        uint8_t physicalPin;
        uint8_t memoryAddress;

        // Constructor / Destructor
        Tag(std::string, std::string, std::string, uint8_t, uint8_t);
        virtual ~Tag();

        // Interfaces
        virtual std::string PrintToCSV();
        virtual Tag* CreateTag();
    public:
        // Accessor methods
        std::string GetType();
        std::string GetName();
        uint8_t GetPin();
        uint8_t GetMemoryAddress();
        
        // Verification methods
        static bool VerifyName(Tag*);
};

#endif