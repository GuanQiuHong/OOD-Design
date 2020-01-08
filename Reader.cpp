/* 
 * File:   Reader.cpp
 * Author: williamhong
 */

#include "Reader.h"

Reader::Reader() {
}

Reader::~Reader() {
}

void Reader::read(string fileName) {
    
    geoHashTable geoHashMap;
    geoHashMap.importCountryContinentMap();

    ifstream shipmentStatsCSV(fileName);

    string date;
    string time;
    string status;
    string country;
    string continent;

    while (shipmentStatsCSV.good()) {

        ShipmentRow rowInShipment;

        getline(shipmentStatsCSV, date, ',');
        getline(shipmentStatsCSV, time, ',');
        getline(shipmentStatsCSV, status, '\n');

        rowInShipment = constructShipmentRow(date, time, status, geoHashMap);

        shipmentTable.push_back(rowInShipment);
    }

    shipmentStatsCSV.close();

    return;
}

ShipmentRow Reader::constructShipmentRow(string _date, string _time, string _status, geoHashTable geoHashMap) {

    ShipmentRow row;
    row.setDate(_date);
    row.setTime(_time);
    row.setStatus(_status);

    pair<string, string> countryContinent = parseCountryFromStatus(_status, geoHashMap);
    row.setCountry(countryContinent.first);
    row.setContinent(countryContinent.second);

    return row;
}

pair<string, string> Reader::parseCountryFromStatus(string _status, geoHashTable geoHashMap) {
    
    transform(_status.begin(), _status.end(), _status.begin(), ::tolower);

    char cstr[_status.size() + 1];
    strcpy(cstr, _status.c_str());

    char * wordsInStatus;
    wordsInStatus = strtok(cstr, " ,.-");

    while (wordsInStatus != NULL) {

        auto countryWord = geoHashMap.getTable().find(wordsInStatus);
        if (countryWord != geoHashMap.getTable().end()) {
            string country = geoHashMap.getTable().find(wordsInStatus)->first;
            string continent = geoHashMap.getTable().find(wordsInStatus)->second;
            pair<string, string> countryContinent = make_pair(country, continent);
            return countryContinent;

        }
        wordsInStatus = strtok(NULL, " ,.-");
    }
    pair<string, string> noCountryInStatus = make_pair("default", "default");
    return noCountryInStatus;
}

void Reader::printData() {
    for (int i = 0; i < shipmentTable.size(); i++) {
        shipmentTable[i].printDate();
        shipmentTable[i].printTime();
        shipmentTable[i].printStatus();
        shipmentTable[i].printCountry();
        shipmentTable[i].printContinent();
    }
}

vector<ShipmentRow> Reader::getAdaptedData() {
    return shipmentTable;
}

string Reader::getDate(int index) {
    return shipmentTable[index].getDate();
}

string Reader::getTime(int index) {
    return shipmentTable[index].getTime();
}

string Reader::getStatus(int index) {
    return shipmentTable[index].getStatus();
}

string Reader::getCountry(int index) {
    return shipmentTable[index].getCountry();
}