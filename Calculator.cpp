/* 
 * File:   Calculator.cpp
 * Author: williamhong
 */

#include "Calculator.h"

Calculator::Calculator() {

}

Calculator::~Calculator() {
}

Time Calculator::timeElapsedInTotal(vector<ShipmentRow> shipmentTable) {
    int startIndex = shipmentTable.size()-1;
    int finalIndex = 0;
    string startTime = (shipmentTable[startIndex].getDate() + shipmentTable[startIndex].getTime());
    string endTime = (shipmentTable[finalIndex].getDate() + shipmentTable[finalIndex].getTime());
    Time totalHoursMinutes = timeDiffInHoursMinutes(startTime, endTime);
    return totalHoursMinutes;
}

Time Calculator::timeElapsedInCountry(vector<ShipmentRow> shipmentTable, string country) {
    for (int i = shipmentTable.size() - 1; i >= 0; i--) {
        
        bool shipmentNowInCountry = (shipmentTable[i].getCountry() == country);
        if (shipmentNowInCountry) {
            
            for (int j = i - 1; j >= 0; j--) {
                bool shipmentArrivedAtNextCountry = (shipmentTable[j].getCountry() != country && shipmentTable[j].getCountry() != "default");
                bool finalStop = (j == 0);
                if (shipmentArrivedAtNextCountry || finalStop) {
                    string timeBegin = (shipmentTable[i].getDate() + shipmentTable[i].getTime());
                    string timeEnd = (shipmentTable[j].getDate() + shipmentTable[j].getTime());
                    Time timeElapsedInThisCountry = timeDiffInHoursMinutes(timeBegin, timeEnd);
                    return timeElapsedInThisCountry;
                }
            }
        }
    }

    Time didNotFindCountry;
    didNotFindCountry.setHour(0);
    didNotFindCountry.setMinutes(0);
    return didNotFindCountry;
}

Time Calculator::timeElapsedInContinent(vector<ShipmentRow> shipmentTable, string continent) {
    for (int i = shipmentTable.size() - 1; i >= 0; i--) {
       
        bool shipmentNowInContinent = (shipmentTable[i].getContinent() == continent);
        if (shipmentNowInContinent) {
            for (int j = i - 1; j >= 0; j--) {
                bool shipmentArrivedAtNextContinent = (shipmentTable[j].getContinent() != continent && shipmentTable[j].getContinent() != "default");
                bool finalStop = (j == 0);
                if (shipmentArrivedAtNextContinent || finalStop) {
                    string timeBegin = (shipmentTable[i].getDate() + shipmentTable[i].getTime());
                    string timeEnd = (shipmentTable[j].getDate() + shipmentTable[j].getTime());
                    Time timeElapsedInThisContinent = timeDiffInHoursMinutes(timeBegin, timeEnd);
                    return timeElapsedInThisContinent;
                }
            }
        }
    }

    Time didNotFindContinent;
    didNotFindContinent.setHour(0);
    didNotFindContinent.setMinutes(0);
    return didNotFindContinent;
}


void Calculator::fillTimeIntervalsBetweenRows(vector<ShipmentRow>& shipmentTable) {
    for (int i = shipmentTable.size() - 1; i > 0; i--) {
        string timeBegin = (shipmentTable[i].getDate() + shipmentTable[i].getTime());
        string timeEnd = (shipmentTable[i-1].getDate() + shipmentTable[i-1].getTime());
        Time timeSinceLastStep = timeDiffInHoursMinutes(timeBegin, timeEnd);
        shipmentTable[i-1].setTimeSinceLastStep(timeSinceLastStep);
    }
}

pair<string, string> Calculator::findLongestInterval(vector<ShipmentRow>& shipmentTable) {
    string statusBegin, statusEnd;
    int localHours, maxHours;
    localHours = maxHours = 0;
    double localMinutes, maxMinutes;
    localMinutes = maxMinutes = 0;
    int maxIntervalIndex;
    pair<string, string> maxIntervalStatusPair;
    
    for (int i = shipmentTable.size() - 1; i >= 0; i--) {
        localHours = shipmentTable[i].getTimeSinceLastStep().getHour();
        localMinutes = shipmentTable[i].getTimeSinceLastStep().getMinutes();
        if(localHours > maxHours || ((localHours == maxHours) && (localMinutes > maxMinutes))) {
            maxHours = localHours;
            maxMinutes = localMinutes;
            maxIntervalIndex = i;
        }
    }
    
    statusBegin = shipmentTable[maxIntervalIndex+1].getStatus();
    statusEnd = shipmentTable[maxIntervalIndex].getStatus();
    
    maxIntervalStatusPair = make_pair(statusBegin, statusEnd);
    
    return maxIntervalStatusPair;
}


Time Calculator::timeDiffInHoursMinutes(string _timeBegin, string _timeEnd) {
    string timeBegin = _timeBegin;
    string timeEnd = _timeEnd;

    char* time1 = &timeBegin[0];
    char* time2 = &timeEnd[0];

    struct tm tm1, tm2; 
    time_t t1, t2;

    if (strptime(time1, "%Y-%m-%d %T", &tm1) == NULL)
        printf("\nstrptime failed-1\n");
    if (strptime(time2, "%Y-%m-%d %T", &tm2) == NULL)
        printf("\nstrptime failed-2\n");

    t1 = mktime(&tm1);
    t2 = mktime(&tm2);

    double time = difftime(t2, t1) / 60 / 60;
    int hours = (int) time;
    double minutes = round((time - hours) * 60);
    Time hourMinute;
    hourMinute.setHour(hours);
    hourMinute.setMinutes(minutes);
    return hourMinute;
}

void Calculator::processData(vector<ShipmentRow>& shipmentTable) {

    results.timeElapsedInTotal = timeElapsedInTotal(shipmentTable);
    results.timeInAsia = timeElapsedInContinent(shipmentTable, "Asia");
    results.timeInUSA = timeElapsedInCountry(shipmentTable, "usa");
    results.timeInCanada = timeElapsedInCountry(shipmentTable, "canada");
    fillTimeIntervalsBetweenRows(shipmentTable);
    results.maxIntervalStatusPair = findLongestInterval(shipmentTable);
    
}

void Calculator::printData(vector<ShipmentRow> shipmentTable) {
    for (int i = 0; i < shipmentTable.size(); i++) {
        shipmentTable[i].printDate();
        shipmentTable[i].printTime();
        shipmentTable[i].printStatus();
        shipmentTable[i].printCountry();
        shipmentTable[i].printContinent();
        shipmentTable[i].printTimeSinceLastStep();
    }
}

Results Calculator::getResults() {
    return results;
}