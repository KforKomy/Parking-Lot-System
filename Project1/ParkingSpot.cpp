#include "ParkingSpot.h"
#include<iostream>
std::atomic<int> ParkingSpot::idcounter{1};
std::atomic<int> ParkingSpot::currentcars{ 0 };
ParkingSpot::ParkingSpot( VehicleSize spottype) : id(ParkingSpot::idcounter ++) , spotType(spottype) {};
void ParkingSpot::Occupy( std::unique_ptr<Vehicle> v) {
	if (v->getSize() != spotType) {
		std::cout << "VEHICLE SIZE DOESNT MATCH THE SPOT SIZE\n";
		return;
	}
	currentvehicle = std::move(v);
	currentcars++;
	
	

}
void ParkingSpot::Freespot() {
	currentvehicle.reset();
	currentcars--;
}
bool ParkingSpot::isOccupied() const{
	return !(currentvehicle == nullptr);
}
int ParkingSpot::getId() const { return id; }
