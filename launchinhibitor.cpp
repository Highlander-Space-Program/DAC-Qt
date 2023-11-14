#include "launchinhibitor.h"

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

void LaunchInhibitor::updateLCValues() {
    thrustLoad = -1;
    ethTankLoad = -1;
    nosTankLoad = -1;
}

void LaunchInhibitor::updateTCValues() {
    chamberTemp1 = -1;
    chamberTemp2 = -1;
    ethTankLoad = -1;
    nosTankTemp = -1;
}

bool LaunchInhibitor::checkAll(){
    if (checkNOSTank() && checkEthTank() && checkInjector() && checkChamber()) {
        return true;
    }
    else {
        return false;
    }
}

bool LaunchInhibitor::checkNOSTank(){
    if (nosTankLoad && (nosTankPres > 750 && nosTankPres < 850) && nosTankTemp) {
        return true;
    }
    else {
        return false;
    }
}

bool LaunchInhibitor::checkEthTank(){
    if (ethTankLoad && (nosTankPres > 750 && nosTankPres < 850) && ethTankTemp) {
        return true;
    }
    else {
        return false;
    }
}

bool LaunchInhibitor::checkInjector(){
    if (ethInjectorPres && nosInjectorPres) {
        return true;
    }
    else {
        return false;
    }
}

bool LaunchInhibitor::checkChamber(){
    if (chamberPres && chamberTemp1 && chamberTemp2) {
        return true;
    }
    else {
        return false;
    }
}

void LaunchInhibitor::inhibitLaunch() {

}

void LaunchInhibitor::allowLaunch() {

}
