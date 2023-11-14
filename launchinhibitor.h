#ifndef LAUNCHINHIBITOR_H
#define LAUNCHINHIBITOR_H


class LaunchInhibitor
{
public:
    LaunchInhibitor();

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

    //bools
    bool nosTankGood;
    bool ethTankGood;
    bool injectorGood;
    bool chamberGood;

    //Functions
    bool checkAll();
    bool checkNOSTank();
    bool checkEthTank();
    bool checkInjector();
    bool checkChamber();

};

#endif // LAUNCHINHIBITOR_H
