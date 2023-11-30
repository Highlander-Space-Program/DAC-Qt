#include "launchinhibitor.h"
#include "LabJackM.h"
#include <iostream>

LaunchInhibitor::LaunchInhibitor()
{
    //Broadcaster<sensorType>->getInstance().subscribe(updateValues);
}

//generates callback to get updated values
void LaunchInhibitor::updatePTValues() {
    chamberPres = -1;
    ethInjectorPres = -1;
    nosInjectorPres = -1;
    ethTankPres = -1;
    nosTankPres = -1;
}

//updates LC Values
void LaunchInhibitor::updateLCValues() {
    thrustLoad = -1;
    ethTankLoad = -1;
    nosTankLoad = -1;
}


//updates TC Values
void LaunchInhibitor::updateTCValues() {
    chamberTemp1 = -1;
    chamberTemp2 = -1;
    ethTankLoad = -1;
    nosTankTemp = -1;
}

//calls all check functions to check each component, returns true if all are true
bool LaunchInhibitor::checkAll(){
    if (checkNOSTank() && checkEthTank() && checkInjector() && checkChamber()) {
        return true;
    }
    else {
        return false;
    }
}

//checks NOS tank sensors
bool LaunchInhibitor::checkNOSTank(){
    if (nosTankLoad && (nosTankPres > 750 && nosTankPres < 850) && nosTankTemp) {
        return true;
    }
    else {
        return false;
    }
}

//checks Eth tank sensors
bool LaunchInhibitor::checkEthTank(){
    if (ethTankLoad && (nosTankPres > 750 && nosTankPres < 850) && ethTankTemp) {
        return true;
    }
    else {
        return false;
    }
}

//checks Injector Sensors
bool LaunchInhibitor::checkInjector(){
    if (ethInjectorPres && nosInjectorPres) {
        return true;
    }
    else {
        return false;
    }
}

//checks Chamber sensors
bool LaunchInhibitor::checkChamber(){
    if (chamberPres && chamberTemp1 && chamberTemp2) {
        return true;
    }
    else {
        return false;
    }
}

//Writes 0.1 Volts to DAC0
void LaunchInhibitor::inhibitLaunch(const int handle) {
    int LJMError;
    LJMError = LJM_eWriteAddress(handle, 1000, 3, 0.1);
    if (LJMError) {
        std::cout << "Error Writing to DAC Output on inhibit, Error code: " << LJMError << std::endl;
    }
}

//writes 5 Volts to DAC0
void LaunchInhibitor::allowLaunch(const int handle) {
    int LJMError;
    LJMError = LJM_eWriteAddress(handle, 1000, 3, 5);
    if (LJMError) {
        std::cout << "Error Writing to DAC Output on allow, Error code: " << LJMError << std::endl;
    }
}

//toggles Manual Overide
void LaunchInhibitor::toggleManualOveride() {
    manualOveride = !manualOveride;
}

//if all sensors are in range or manualOveride is true, calls allowLaunch, else calls inhibitLaunch
void LaunchInhibitor::updateInhibit(const int handle) {
    if (checkAll()) {
        allowLaunch(handle);
    }
    else if (!checkAll() && manualOveride) {
        allowLaunch(handle);
    }
    else {
        inhibitLaunch(handle);
    }
}
//what are you doin all the way down here huh?
