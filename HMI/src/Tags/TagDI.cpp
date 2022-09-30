#include "TagDI.hpp"

#include <string>
#include <sstream>

TagDI::TagDI(std::string _name, std::string _description, uint8_t _physicalPin, uint8_t _memoryAddress, bool _stateInitial)
    : Tag("DI", _name, _description, _physicalPin, _memoryAddress), stateInitial(_stateInitial) {}

std::string TagDI::PrintToCSV() {
    std::stringstream ss;
    ss << Tag::PrintToCSV() << "," << stateInitial;
    return ss.str();
}