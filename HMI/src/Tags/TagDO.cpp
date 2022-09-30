#include <string>
#include <sstream>

#include "TagDO.hpp"

TagDO::TagDO(std::string _name, std::string _description, uint8_t _physicalPin, uint8_t _memoryAddress, bool _stateInitial)
    : Tag("DO", _name, _description, _physicalPin, _memoryAddress), stateInitial(_stateInitial) {}


std::string TagDO::PrintToCSV() {
    std::stringstream ss;
    ss << Tag::PrintToCSV() << "," << stateInitial;
    return ss.str();
}