#pragma once
#include "ParkingSpot.h"
#include "Ticket.h"
#include "PriceCalculator.h"
#include <vector>
#include <memory>
#include<unordered_map>
#include<unordered_set>

class ParkingManager {
private:
    //SPOT ID to SPOT
    std::unordered_map<int, std::unique_ptr<ParkingSpot>> allSpots;

    //SIZE to SET OF FREE SPOTS OF THIS SIZE
    std::unordered_map<VehicleSize, std::unordered_set<int>> emptySpotIds;

    //TICKET ID  to TICKET
    std::unordered_map<int, std::unique_ptr<Ticket>> activeTickets;
    PriceCalculator calculator;


public:
    ParkingManager(int smallCount,int compactCount, int largeCount);

    
    int processEntry(std::unique_ptr<Vehicle> v);

    
    void processExit(int ticketId);


    Ticket* getActiveTicket(int ticketId);
  
};