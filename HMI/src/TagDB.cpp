// Blake Freer
// Date Created: August 18, 2022
// Date Modified: September 25, 2022
// Description: A console based application for editing a tag database

#define DBPATH "tags.tdb"

#include<iostream>
#include<fstream>
#include<cstring>
#include<cctype>
#include<string>
#include<vector>

using namespace std;

enum IO_TYPES{reserved=0x00, DI=0x01, DO=0x02, AI=0x03, AO=0x04, SOFTD=0x05, SOFTA=0x06};

class Tag {
    public:
        Tag(char* data);
        Tag(string name, uint8_t type, uint8_t pin, uint8_t address);
        friend ostream& operator<<(ostream& out, Tag& tag);
    private:
        uint8_t type;
        uint8_t physicalPin; // location on plc -> for compiling to configure PLC pins
        uint8_t address; // memory location in PLC -> for allocating and accessing memory on PLC
        char name[32]; // -> for linking HMI elements to tags
};

Tag::Tag (char* data) {
    // Create a tag from a 35 byte binary package
    uint8_t pos = 0;
    memcpy(&this->name, data, 32*sizeof(char));
    this->type = data[32];
    this->physicalPin = data[33];
    this->address = data[34];
}
Tag::Tag(string name, uint8_t type, uint8_t pin, uint8_t address){
    // Create a tag from the individual parameters
    name.copy(this->name, 32);
    this->type = type;
    this->physicalPin = pin;
    this->address = address;
}


ostream& operator<<(ostream& out, Tag& tag){
    out << string(tag.name) << " | Type: " << tag.type << " | Pin: " << tag.physicalPin << " | Address: " << tag.address;
    return out; 
}
template <class T>
void UserPrompt(string prompt, T& output){
    cout << prompt;
    cin >> output;
}

void User_CreateTag(vector<Tag>* tags){
    string name;
    uint8_t type;
    uint8_t pin;
    uint8_t address;
    cout << "Enter tag name.\nMust only use alphanumeric characters or underscores. Maximum length is 32 characters.\n";
    getline(cin, name);
    UserPrompt<uint8_t>("Enter the data type: ", type);
    UserPrompt<uint8_t>("Enter the physical pin: ", pin);
    UserPrompt<uint8_t>("Enter the memory address (1-256): ", address);
    Tag t(name, type, pin, address);
    tags->push_back(t);
    cout << "Created new tag:" << endl << t << endl;
}

int main (void) {

    cout << "Tag Database Editor" << endl;
    cout << "Using tag database file \"" << DBPATH << "\"" << endl;
    
    vector<Tag> tags;

    // Read DB into vector of tags
    char* buffer = new char [35];
    ifstream file (DBPATH, ifstream::binary);
    if(!file.is_open()){
        cout << "Unable to open \"" << DBPATH << "\"\n";
    }
    // Read contents of the tags into a vector
    while(!file.eof()){
        file.read(buffer, 35*sizeof(char));
        Tag t(buffer);
        tags.push_back(t);
        cout << t << endl;
    }
    char userNav;
    while(true){
        User_CreateTag(&tags);
    }

    return EXIT_SUCCESS;
}