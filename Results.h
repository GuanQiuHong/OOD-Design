/* 
 * File:   Results.h
 * Author: williamhong
 */

#ifndef RESULTS_H
#define RESULTS_H

#include <utility>
#include <string>
#include "Time.h"

using namespace std;

struct Results {
    Time timeElapsedInTotal;
    Time timeInAsia;
    Time timeInUSA;
    Time timeInCanada;
    pair<string, string> maxIntervalStatusPair; 
};


#endif /* RESULTS_H */