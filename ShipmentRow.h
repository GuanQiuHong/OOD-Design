/* 
 * File:   ShipmentRow.h
 * Author: williamhong
 */

#ifndef SHIPMENTROW_H
#define SHIPMENTROW_H

#include <string>
#include "Time.h"


using namespace std;

class ShipmentRow {
private:
    string date;
    string time;
    string status;
    string country;
    string continent;
    Time timeSinceLastStep;
    
public:
   
    ShipmentRow();
    string getDate();
    string getTime();
    string getStatus();
    string getCountry();
    string getContinent();
    Time getTimeSinceLastStep();
    void setDate(string date);
    void setTime(string time);
    void setStatus(string status);
    void setCountry(string country);
    void setContinent(string continent);
    void setTimeSinceLastStep(Time _time);
    void printDate();
    void printTime();
    void printStatus();
    void printCountry();
    void printContinent();
    void printTimeSinceLastStep();
    
};

#endif /* SHIPMENTROW_H */

