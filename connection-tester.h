#ifndef CONNECTIONTESTER_H
#define CONNECTIONTESTER_H

#include "LabJackM.h"
#include <iostream>

//checks if PT value is within expected range
bool checkPT(double pressure) {
    if (pressure > 14 && pressure < 1500) {
        return true;
    }
    else {
        return false;
    }
}

//checks if LC value is within expected range
bool checkLC (double load) {
    if (load > -100 && load < 100) {
        return true;
    }
    else {
        return false;
    }
}

//checks if TC value is within expected range
bool checkTC (double temp) {
    if (temp > 20 && temp < 130) {
        return true;
    }
    else {
        return false;
    }
}

//checks if EMatch voltage is within expected range
//make sure DAC output for EMatch is outputting 1V to the EMatch
bool checkEMatch(double voltage) {
    if (voltage > 0.017 && voltage < 0.02) {
        return true;
    }
    else {
        return false;
    }
}

void writeEMatch(int handle) {
    int LJMErrorCode = 0;
    LJMErrorCode = LJM_eWriteName(handle, "DAC1", 1);
    if (LJMErrorCode != 0) {
        std::cout << "Error writing to DAC 1, error code: " << LJMErrorCode << std::endl;
    }
}

#endif // CONNECTIONTESTER_H
