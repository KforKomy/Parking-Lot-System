#include "Vehicle.h"
#include<iostream>
Vehicle::Vehicle(VehicleSize size, std::string plate) : size(size) , plate(plate) {}
std::string Vehicle::getPlate() const { return plate; }
VehicleSize Vehicle::getSize() const { return size; }
Vehicle::~Vehicle() {}