/* 
 * File:   Calculator.h
 * Author: williamhong
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "Time.h"
#include "ShipmentRow.h"
#include <time.h>
#include <math.h>
#include <string>
#include <vector>
#include "Results.h"

using namespace std;

class Calculator {
    
private:

    struct Results results;
    
    Time timeDiffInHoursMinutes(string _timeBegin, string _timeEnd);
    Time timeElapsedInTotal(vector<ShipmentRow> shipmentTable);
    Time timeElapsedInCountry(vector<ShipmentRow> shipmentTable, string country);
    Time timeElapsedInContinent(vector<ShipmentRow> shipmentTable, string continent);
    void fillTimeIntervalsBetweenRows(vector<ShipmentRow>& shipmentTable);
    pair<string, string> findLongestInterval(vector<ShipmentRow>& shipmentTable);
    
    
public:
    Calculator();
    virtual ~Calculator();
    void processData(vector<ShipmentRow>& shipmentTable);
    Results getResults();
    void printData(vector<ShipmentRow> shipmentTable); //for my own testing purposes
};

#endif /* CALCULATOR_H */

