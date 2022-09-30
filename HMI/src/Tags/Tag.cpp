// Author: Blake Freer
// Date Created: September 29, 2022
// Description: Implements some functionality for the abtract Tag class

#include "Tag.hpp"
#include "DEFINES.hpp"

#include <cctype>
#include <string>
#include <sstream>

// Constructor
Tag::Tag(std::string _type, std::string _name, std::string _description, uint8_t _physicalPin, uint8_t _memoryAddress) {
    type = _type;
    name = _name;
    description = _description;
    physicalPin = _physicalPin;
    memoryAddress = _memoryAddress;
}

// Verification methods
bool Tag::VerifyName(Tag* tag){
    // Check if name is too long
    if(tag->name.length() > TAG_NAME_LENGTH) {
        return false;
    }

    // Check that all characters are legal (alphanumeric or underscore)
    for(const char &c: tag->name){
        if(!isalnum(c) && c != '_'){
            // std::cout << "Tag name may only contain alphanumeric characters and underscores _" << std::endl;
            return false;
        }
    }
    
    // If no prevous statements returned false, then the name is valid
    return true;
}

// Interfaces
std::string Tag::PrintToCSV() {
    // Concatenate parameters to csv form
    // Enclose description in quotation marks to avoid csv delimiter issues without restricting the description text
    std::stringstream ss;
    ss << type << "," << name << "," << "\"" << description << "\"" << "," << physicalPin << "," <<  memoryAddress;
    return ss.str();
}

// Accessor methods
std::string Tag::GetName() {
    return name;
}
std::string Tag::GetType(){
    return type;
}
uint8_t Tag::GetPin(){
    return physicalPin;
}
uint8_t Tag::GetMemoryAddress(){
    return memoryAddress;
}

