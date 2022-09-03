// Blake Freer
// Date Created: August 18, 2022
// Date Modified: September 2, 2022
// Description: A console based application for editing a tag database

#define DBPATH "tags.tdb"

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

enum IO_TYPES{reserved=0x00, DI=0x01, DO=0x02, AI=0x03, AO=0x04, SOFTD=0x05, SOFTA=0x06};

class Tag {
    public:
        Tag(uint8_t *);
    private:
        uint8_t address; // memory location in PLC -> for allocating and accessing memory on PLC
        uint8_t type;
        uint8_t physicalPin; // location on plc -> for compiling to configure PLC pins
        char name[32]; // -> for linking HMI elements to tags
};

Tag::Tag (uint8_t * dbLine) {
    // Copy over all values
    uint8_t pos = 0;
    address = dbLine[pos++];
    type = dbLine[pos++];
    physicalPin = dbLine[pos++];
    while(pos < 35) {
        name[pos-3] = dbLine[pos];
    }
}

int main (void) {

    cout << "Tag Database Editor" << endl;
    cout << "Using tag database file \"" << DBPATH << "\"" << endl;
    
    vector<Tag> tags;

    // Read DB into array of tags
    string line;
    ifstream file (DBPATH, ios::binary);
    if(file.is_open()){
        while(getline(file,line)){
            Tag * newTag (line);
            newTag+= 32
            tags.push_back(new Tag(line));
        }
        file.close();
    } else {
        cout << "Unable to open \"" << DBPATH << "\"\n";
    }


    return EXIT_SUCCESS;
}