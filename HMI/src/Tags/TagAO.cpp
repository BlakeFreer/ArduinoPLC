#include "TagAO.hpp"

#include <string>
#include <sstream>

TagAO::TagAO(std::string _name, std::string _description, uint8_t _physicalPin, uint8_t _memoryAddress, uint16_t _valInitial, uint16_t _valMin, uint16_t _valMax)
    : Tag("AO", _name, _description, _physicalPin, _memoryAddress), valInitial(_valInitial), valMin(_valMin), valMax(_valMax){}

std::string TagAO::PrintToCSV() {
    std::stringstream ss;
    ss << Tag::PrintToCSV() << "," << valInitial <<  "," << valMin << "," << valMax;
    return ss.str();
}
