/* 
 * File:   Time.cpp
 * Author: williamhong
 */

#include "Time.h"

using namespace std;

Time::Time() {
}

void Time::setHour(int _hour) {
    hour = _hour;
}

void Time::setMinutes(double _minutes) {
    minutes = _minutes;
}

int Time::getHour() {
    return hour;
}

double Time::getMinutes() {
    return minutes;
}