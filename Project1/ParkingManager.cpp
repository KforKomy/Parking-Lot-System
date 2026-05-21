#include"ParkingManager.h"
#include<memory>
#include<iostream>

ParkingManager::ParkingManager(int smallCount, int compactCount, int largeCount)
{
	for (int i = 0; i < smallCount; i++) {
		auto spot = std::make_unique<ParkingSpot>(VehicleSize::small);
		int spotid = spot->getId();
		allSpots[spotid] = std::move(spot);
		emptySpotIds[VehicleSize::small].insert(spotid);
	}
	for (int i = 0; i < compactCount; i++) {
		auto spot = std::make_unique<ParkingSpot>(VehicleSize::Compact);
		int spotid = spot->getId();
		allSpots[spotid] = std::move(spot);
		emptySpotIds[VehicleSize::Compact].insert(spotid);
	}
	for (int i = 0; i < largeCount; i++) {
		auto spot = std::make_unique<ParkingSpot>(VehicleSize::Large);
		int spotid = spot->getId();
		allSpots[spotid] = std::move(spot);
		emptySpotIds[VehicleSize::Large].insert(spotid);
	}
}
int ParkingManager::processEntry(std::unique_ptr<Vehicle> v) {
	if (!v) return -1;
	VehicleSize requiredSize = v->getSize();
	std::string vehicleplate = v->getPlate();
	auto &availableSet = emptySpotIds[requiredSize];
	if (availableSet.empty()) {
		std::cout << "NO FREE SPACES COME ANOTHER TIME\n";
		return -1;
	}
	int targetspotid = *availableSet.begin();
	auto& targetspot = allSpots[targetspotid];
	auto ticket = std::make_unique<Ticket>(targetspotid, vehicleplate, requiredSize);
	int ticketId = ticket->getTicketId();
	targetspot->Occupy(std::move(v));
	availableSet.erase(targetspotid);
	activeTickets[ticketId] = std::move(ticket);
	std::cout << "Vehicle parked succefully at spot id: " << targetspotid << " Ticket issued id is " << ticketId<<std::endl;

	return ticketId;
}
void ParkingManager::processExit(int tid) {
	auto ticketit = activeTickets.find(tid);
	if (ticketit == activeTickets.end()) {
		std::cout << "Error ticket id #" << tid << " Not found\n";
		return;
	}
	Ticket* ticket = ticketit->second.get();
	int spotid = ticket->getSpotId();
	VehicleSize vehiclesize = ticket->getVehicleSize();
	ticket->markExit();
	long long duration = ticket->getDurationMinutes();
	double finalfee = calculator.calculateFare(duration, vehiclesize);
	allSpots[spotid]->Freespot();
	emptySpotIds[vehiclesize].insert(spotid);
	// Print Receipt Statement
	std::cout << "\n======= PARKING RECEIPT =======" << "\n"
		<< "Ticket ID:    #" << ticket->getTicketId() << "\n"
		<< "Plate Number: " << ticket->getLicensePlate() << "\n"
		<< "Time Parked:  " << duration << " minutes\n"
		<< "Total Fee:    $" << finalfee << "\n"
		<< "===============================\n\n";
	activeTickets.erase(ticketit);
}
Ticket* ParkingManager::getActiveTicket(int ticketId) {
	auto it = activeTickets.find(ticketId);
	if (it != activeTickets.end()) {
		return it->second.get();
	}
	return nullptr;
}