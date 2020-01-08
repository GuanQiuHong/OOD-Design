/* 
 * File:   Time.h
 * Author: williamhong
 */

#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time {
private:
    int hour;
    double minutes;

public:
    Time();
    void setHour(int hour);
    void setMinutes(double minutes);
    int getHour();
    double getMinutes();
};

#endif /* TIME_H */