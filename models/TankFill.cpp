#include "TankFill.h"

TankFill::TankFill(double tankVolume, double vaporDensity, double liquidDensity)
    : Vtank_(tankVolume), DVapor_(vaporDensity), DLiquid_(liquidDensity),
    mass_(0), percentLiquid_(0), volumeLiquid_(0) {}

void TankFill::updateMass(double mass) {
    mass_ = mass;
    calculate();
}
//Thanks Javen
void TankFill::calculate() {
    if (mass_ <= Vtank_ * DVapor_) {
        percentLiquid_ = 0;
    } else if (mass_ >= Vtank_ * DLiquid_) {
        percentLiquid_ = 100;
    } else {
        percentLiquid_ = ((mass_ - Vtank_ * DVapor_) / (Vtank_ * (DLiquid_ - DVapor_))) * 100;
    }
    volumeLiquid_ = percentLiquid_ / 100.0 * Vtank_;
}

double TankFill::getPercentLiquid() const {
    return percentLiquid_;
}

double TankFill::getVolumeLiquid() const {
    return volumeLiquid_;
}
