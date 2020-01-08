/* 
 * File:   Reader.h
 * Author: williamhong
 */

#ifndef READER_H
#define READER_H

#include "ShipmentRow.h"
#include "geoHashTable.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>


class Reader {
    
private:
    vector<ShipmentRow> shipmentTable;
    ShipmentRow constructShipmentRow(string date, string time, string status, geoHashTable geoHashMap);
    pair<string, string> parseCountryFromStatus(string status, geoHashTable geoHashMap); //should be private
    string getDate(int index);
    string getTime(int index);
    string getStatus(int index);
    string getCountry(int index);
    
public:
    Reader();
    virtual ~Reader();
    void read(string fileName); 
    vector<ShipmentRow> getAdaptedData(); 
    void printData();
    
};

#endif /* READER_H */

