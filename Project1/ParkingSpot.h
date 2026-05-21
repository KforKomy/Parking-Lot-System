#pragma once
#include"Vehicle.h"
#include<memory>
#include<atomic>
class ParkingSpot
{
private:
	static std::atomic<int> idcounter;
	static std::atomic<int> currentcars;
	std::unique_ptr<Vehicle> currentvehicle;
	int id;
	VehicleSize spotType;

public:
	ParkingSpot(VehicleSize spottype );
	void Occupy( std::unique_ptr<Vehicle> v);
	void Freespot();
	bool isOccupied() const;
	int getId() const;
		

	

};

