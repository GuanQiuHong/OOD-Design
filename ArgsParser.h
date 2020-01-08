/* 
 * File:   ArgsParser.h
 * Author: williamhong
 */

#ifndef ARGSPARSER_H
#define ARGSPARSER_H

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class ArgsParser {

private:
    string fileName;
    
public:
    ArgsParser();
    virtual ~ArgsParser();
    
    bool parse(int argc, char** argv);
    string getFileName();
    
};

#endif /* ARGSPARSER_H */

