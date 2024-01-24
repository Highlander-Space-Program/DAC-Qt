#include "launchinhibitor.h"
#include "LabJackM.h"
#include "broadcast/Broadcaster.h"
#include "PressureData.h"
#include "MassData.h"
#include "TemperatureData.h"
#include <iostream>

LaunchInhibitor::LaunchInhibitor()
{
    pressureBroadcaster = Broadcaster<PressureData>::getInstance();
    temperatureBroadcaster = Broadcaster<TemperatureData>::getInstance();
    massBroadcaster = Broadcaster<MassData>::getInstance();
}

//generates callback to get updated values
void LaunchInhibitor::updatePTValues(std::shared_ptr<Broadcaster<PressureData>> &pressureBroadcaster) {
    pressureBroadcaster->subscribe([this](const PressureData *data) {
        if (data->label == "PT-05") {
            chamberPres = data->pressure;
        }
        if (data->label == "PT-04") {
            nosTankPres = data->pressure;
        }
        if (data->label == "PT-03") {
            nosFillPres = data->pressure;
        }
        if (data->label == "PT-02") {
            ethTankPres = data->pressure;
        }
        if (data->label == "PT-01") {
            n2LinePres = data->pressure;
        }
    });
}

//updates LC Values
void LaunchInhibitor::updateLCValues(std::shared_ptr<Broadcaster<MassData>> &massBroadcaster) {
    massBroadcaster->subscribe([this](const MassData *data) {
        if (data->label == "LC-01") {
            thrustLoad = data->mass;
        }
        if (data->label == "LC-02") {
            ethTankLoad = data->mass;
        }
        if (data->label == "LC-03") {
            nosTankLoad = data->mass;
        }
    });
}


//updates TC Values
void LaunchInhibitor::updateTCValues(std::shared_ptr<Broadcaster<TemperatureData>> &temperatureBroadcaster) {
    temperatureBroadcaster->subscribe([this](const TemperatureData *data){
        if (data->label == "TC-01") {
            chamberTemp1 = data->temperature;
        }
        if (data->label == "TC-02") {
            chamberTemp2 = data->temperature;
        }
        if (data->label == "TC-03") {
            ethTankTemp = data->temperature;
        }
        if (data->label == "TC-04") {
            nosTankTemp = data->temperature;
        }
    });
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
    if ((nosTankLoad > minNosTankLoad && nosTankLoad < maxNosTankLoad)
        && (nosTankPres > minNosTankPres && nosTankPres < maxNosTankPres)
        && (nosTankTemp > minNosTankTemp && nosTankTemp < maxNosTankTemp)) {
        return true;
    }
    else {
        return false;
    }
}

//checks Eth tank sensors
bool LaunchInhibitor::checkEthTank(){
    if ((ethTankLoad > minEthTankLoad && ethTankLoad < maxEthTankLoad)
        && (ethTankPres > minEthTankPres && nosTankPres < maxEthTankPres)
        && (ethTankTemp > minEthTankTemp && ethTankTemp < maxEthTankTemp)) {
        return true;
    }
    else {
        return false;
    }
}

//checks Injector Sensors, always returns true since no chamber sensors are inhibitors at the moment
bool LaunchInhibitor::checkInjector(){
    return true;
}

//checks Chamber sensors, always returns true since no chamber sensors are inhibitors at the moment
bool LaunchInhibitor::checkChamber(){
    return true;
}

//Writes 0.1 Volts to DAC0
void LaunchInhibitor::inhibitLaunch(const int handle) {
    int LJMError = 0;
    LJMError = LJM_eWriteName(handle, "DAC0", 0.5);
    if (LJMError) {
        std::cout << "Error Writing to DAC Output on inhibit, Error code: " << LJMError << std::endl;
    }
}

//writes 5 Volts to DAC0
void LaunchInhibitor::allowLaunch(const int handle) {
    int LJMError = 0;
    LJMError = LJM_eWriteName(handle, "DAC1", 5);
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
    updateLCValues(massBroadcaster);
    updateTCValues(temperatureBroadcaster);
    updatePTValues(pressureBroadcaster);

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
