#ifndef CONNECTIONTESTER_H
#define CONNECTIONTESTER_H

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
#endif // CONNECTIONTESTER_H
