#ifndef TANKFILL_H
#define TANKFILL_H

class TankFill {
public:
    TankFill(double tankVolume, double vaporDensity, double liquidDensity);

    void updateMass(double mass);
    double getPercentLiquid() const;
    double getVolumeLiquid() const;

private:
    double Vtank_;  // Tank volume in cubic meters
    double DVapor_; // Density of vapor at given conditions
    double DLiquid_; // Density of liquid at given conditions

    double mass_; // Current mass of tank contents
    double percentLiquid_; // Calculated percent liquid
    double volumeLiquid_; // Calculated volume of liquid

    void calculate();
};

#endif // TANKFILL_H
