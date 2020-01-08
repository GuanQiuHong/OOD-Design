/* 
 * File:   geoHashTable.h
 * Author: williamhong
 */

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;

#ifndef GEOHASHTABLE_H
#define GEOHASHTABLE_H

class geoHashTable {
private:
    unordered_map<string, string> hashMap;
        
public:
    geoHashTable();
    void importCountryContinentMap();
    unordered_map<string, string> getTable();


};

#endif /* GEOHASHTABLE_H */

