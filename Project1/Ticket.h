#pragma once
#include"Vehicle.h"
#include<chrono>
#include<atomic>
class Ticket
{
private:
	static std::atomic<int> ticketcounter;
	int ticketid;
	int spotid;
	std::string plate;
	VehicleSize vehiclesize;
	std::chrono::time_point<std::chrono::system_clock> entryTime;
	std::chrono::time_point<std::chrono::system_clock> exitTime;
	bool issettled;

public:
	Ticket(int spotid , const std::string & plate , VehicleSize size);
	void markExit();
	long long getDurationMinutes() const;
	int getTicketId() const;
	int getSpotId() const;
	VehicleSize getVehicleSize() const;
	std::string getLicensePlate() const;
	bool getIsSettled() const;
	void forceFakeEntryTime(int minutesInPast);



};

