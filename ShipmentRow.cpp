/* 
 * File:   ShipmentRow.cpp
 * Author: williamhong
 */

#include <iostream>
#include "ShipmentRow.h"

ShipmentRow::ShipmentRow() {
    timeSinceLastStep.setHour(0);
    timeSinceLastStep.setMinutes(0);
    country = "default";
    continent = "default";
}

string ShipmentRow::getDate() {
    return date;
}

string ShipmentRow::getTime() {
    return time;
}

string ShipmentRow::getStatus() {
    return status;
}

string ShipmentRow::getCountry() {
    return country;
}

string ShipmentRow::getContinent() {
    return continent;
}

Time ShipmentRow::getTimeSinceLastStep() {
    return timeSinceLastStep;
}

void ShipmentRow::setDate(string _date) {
    date = _date;
}

void ShipmentRow::setTime(string _time) {
    time = _time;
}

void ShipmentRow::setStatus(string _status) {
    status = _status;
}

void ShipmentRow::setCountry(string _country) {
    country = _country;
}

void ShipmentRow::setContinent(string _continent) {
    continent = _continent;
}

void ShipmentRow::setTimeSinceLastStep(Time _time) {
    timeSinceLastStep = _time;
}

void ShipmentRow::printDate() {
    cout << "date: " << date << endl;
}

void ShipmentRow::printTime() {
    cout << "time: " << time << endl;
}

void ShipmentRow::printStatus() {
    cout << "status: " << status << endl;
}

void ShipmentRow::printCountry() {
    cout << "country: " << country << endl;
}

void ShipmentRow::printContinent() {
    cout << "continent: " << continent << endl;
}

void ShipmentRow::printTimeSinceLastStep() {
    int hour = timeSinceLastStep.getHour();
    double minutes = timeSinceLastStep.getMinutes();
    cout << "time since last step: " << hour << " hours " << minutes << " minutes." << endl << "-------------------------------" << endl << endl;
}