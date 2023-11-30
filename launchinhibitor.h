#ifndef LAUNCHINHIBITOR_H
#define LAUNCHINHIBITOR_H


class LaunchInhibitor
{
public:
    LaunchInhibitor();

    bool manualOveride = false;
    //PTs
    double chamberPres;
    double ethInjectorPres;
    double nosInjectorPres;
    double ethTankPres;
    double nosTankPres;

    //LCs
    double thrustLoad;
    double ethTankLoad;
    double nosTankLoad;

    //TCs
    double chamberTemp1;
    double chamberTemp2;
    double ethTankTemp;
    double nosTankTemp;

    //maxVals
    const int maxEthTankPres = 1000;
    const int maxNosTankPres = 1000;
    const double maxEthTankLoad = 4.166;
    const double maxNosTankLoad = 13.325;
    const int maxEthTankTemp = 96;
    const int maxNosTankTemp = 96;

    //minVals
    const int minEthTankPres = 750;
    const int minNosTankPres = 750;
    const double minEthTankLoad = 3.666;
    const double minNosTankLoad = 12.825;
    const int minEthTankTemp = 56;
    const int minNosTankTemp = 56;

    //Functions
    void updateInhibit(const int handle);
    void toggleManualOveride();
    void updatePTValues();
    void updateLCValues();
    void updateTCValues();
    bool checkAll();
    bool checkNOSTank();
    bool checkEthTank();
    bool checkInjector();
    bool checkChamber();
    void inhibitLaunch(const int handle);
    void allowLaunch(const int handle);
};

#endif // LAUNCHINHIBITOR_H
