#pragma once
#include<string>
enum class VehicleSize {
	small,
	Compact,
	Large
};
class Vehicle
{
protected:
	VehicleSize size;
	std::string plate;

public:
	Vehicle(VehicleSize size , std::string plate);
	std::string getPlate() const;
	VehicleSize getSize() const;
	virtual ~Vehicle()=0;


};

