/* 
 * File:   geoHashTable.cpp
 * Author: williamhong
 */

#include "geoHashTable.h"

geoHashTable::geoHashTable() {
}

void geoHashTable::importCountryContinentMap() {
    
    ifstream countryContinentCSV("countries.csv");

    if (!countryContinentCSV.is_open()) std::cout << "ERROR: File not found, or of incorrect type" << '\n';

    string continent;
    string country;

    while (countryContinentCSV.good()) {

        getline(countryContinentCSV, continent, ',');
        getline(countryContinentCSV, country, '\n');
        pair<string, string> countryContinent = make_pair(country, continent);
        hashMap.insert (countryContinent);
    }

    countryContinentCSV.close();
}

unordered_map<string, string> geoHashTable::getTable() {
    return hashMap;
}