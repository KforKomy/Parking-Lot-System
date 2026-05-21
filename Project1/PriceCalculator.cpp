#include "PriceCalculator.h"
PriceCalculator::PriceCalculator() : baseRatePerMinute(0.5) {};
double PriceCalculator::calculateFare(long  long minutes, VehicleSize size) const {
	double multiplier = 1.0;
	switch (size) {
	case VehicleSize::small: multiplier = 0.5;
		break;
	case VehicleSize::Compact: multiplier = 1.0;
		break;
	case VehicleSize::Large: multiplier = 2.0;
		break;
	}
	return minutes * baseRatePerMinute * multiplier;
}
