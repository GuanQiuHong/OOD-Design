/*
 * File:   Formatter.cpp
 * Author: williamhong
 */

#include "Formatter.h"

Formatter::Formatter() {
}

Formatter::~Formatter() {
}

pair<int, int> Formatter::getHoursMinutes(Time time) {
    
    pair<int, int> hoursMinutes;
    
    hoursMinutes.first = time.getHour();
    hoursMinutes.second = (int) time.getMinutes();
    
    return hoursMinutes;
}

void Formatter::format(Results results) {
    string totalTime, timeInAsia, timeInUSA, 
            timeInCanada, maxIntervalStatusPair;

    pair<int, int> hoursMinutes;
    
    Time _totalTime = results.timeElapsedInTotal;
    hoursMinutes = getHoursMinutes(_totalTime);
    totalTime = "Total shipment time: " + to_string(hoursMinutes.first) +
            ":" + to_string(hoursMinutes.second) + "\n";
    
    Time _timeInAsia = results.timeInAsia;
    hoursMinutes = getHoursMinutes(_timeInAsia);
    timeInAsia = "Total time in Asia: " + to_string(hoursMinutes.first) +
            ":" + to_string(hoursMinutes.second) + "\n";
    
    Time _timeInUSA = results.timeInUSA;
    hoursMinutes = getHoursMinutes(_timeInUSA);
    timeInUSA = "Total time in USA: " + to_string(hoursMinutes.first) + 
            ":" + to_string(hoursMinutes.second) + "\n";
    
    Time _timeInCanada = results.timeInCanada;
    hoursMinutes = getHoursMinutes(_timeInCanada);
    timeInCanada = "Total time in Canada: " + to_string(hoursMinutes.first) + 
            ":" + to_string(hoursMinutes.second) + "\n";
    
    pair<string, string> _maxIntervalStatusPair = results.maxIntervalStatusPair;
    maxIntervalStatusPair = "Longest shipment step: from" + _maxIntervalStatusPair.first +
            " to" + _maxIntervalStatusPair.second + "\n";
    
    resultString = totalTime + timeInAsia + timeInUSA + timeInCanada + maxIntervalStatusPair;
    
}

string Formatter::getResultString() {
    return resultString;
}