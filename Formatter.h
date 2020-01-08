/* 
 * File:   Formatter.h
 * Author: williamhong
 */

#ifndef FORMATTER_H
#define FORMATTER_H

#include "ShipmentRow.h"
#include <string>
#include "Results.h"
#include <iostream>

using namespace std;

class Formatter {
private:
    string resultString;
    pair<int, int> getHoursMinutes(Time time);
    
public:
    Formatter();
    void format(Results results);
    virtual ~Formatter();
    string getResultString();
};

#endif /* FORMATTER_H */

