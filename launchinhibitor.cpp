#include "launchinhibitor.h"

LaunchInhibitor::LaunchInhibitor()
{

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
