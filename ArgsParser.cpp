/* 
 * File:   ArgsParser.cpp
 * Author: williamhong
 */

#include "ArgsParser.h"

ArgsParser::ArgsParser() {
    
}

ArgsParser::~ArgsParser() {
    
}

bool ArgsParser::parse(int argc, char** argv) {
    
    int numArguments = argc;
    
    string argumentOne, _fileName;
    
    if (numArguments == 1) {
        cout << "too few arguments. Expecting ./main <fileName> or ./ main -f <fileName>.\n";
        return false;
    }
    
    argumentOne = argv[1];
    
    bool argIsFileFlag = (argumentOne == "-f" && argumentOne.length() == 2);
    
    if (argIsFileFlag) {
        
        if (numArguments != 3) { 
            cout << "three arguments expected: ./main -f <fileName>.\n";
            return false;
            
        } else _fileName = argv[2];
        
    } else {
        if (numArguments > 2) {
            cout << "too many arguments. Expecting ./main <fileName>.\n";
            return false;
        } 
        _fileName = argv[1];
    }
    
    ifstream shipmentStatsCSV(_fileName);
    bool fileAvailable = shipmentStatsCSV.is_open();
    
    if (!fileAvailable) {
        cout << "ERROR: trying to open shipment data file, but file not found, or incorrect name entered.\n";
        return false;
    } else {
        fileName = _fileName;
        return true;
    }
    
    return false;
       
}

string ArgsParser::getFileName() {
    return fileName;
}