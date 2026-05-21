#include "Ticket.h"
std::atomic<int> Ticket::ticketcounter{ 1 };
Ticket::Ticket(int spotid, const std::string& plate, VehicleSize size) :
	spotid(spotid), plate(plate), vehiclesize(size) , ticketid(Ticket::ticketcounter++) , entryTime (std::chrono::system_clock::now()) , issettled(false) {};
void Ticket::markExit() {
	exitTime = std::chrono::system_clock::now();
	issettled = true;
	}
long long Ticket::getDurationMinutes() const {
	auto endtime = issettled ? exitTime : std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::minutes>(endtime - entryTime);
	return duration.count();
}

void Ticket::forceFakeEntryTime(int minutesInPast) {
	entryTime = std::chrono::system_clock::now() - std::chrono::minutes(minutesInPast);
}
int Ticket::getTicketId() const { return ticketid; }
int Ticket::getSpotId() const { return spotid; }
VehicleSize Ticket::getVehicleSize() const { return vehiclesize; }
std::string Ticket::getLicensePlate() const { return plate; }
bool Ticket::getIsSettled() const { return issettled; }