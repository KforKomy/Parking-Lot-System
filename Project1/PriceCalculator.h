#pragma once
#include"Vehicle.h"
class PriceCalculator
{
private:
	double baseRatePerMinute;

public:
	PriceCalculator();
	double calculateFare(long  long minutes ,VehicleSize size ) const ;
};

