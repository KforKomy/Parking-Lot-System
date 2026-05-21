#include "ParkingManager.h"
#include "Car.h"
#include"Motorcycle.h"
#include"Bus.h"
#include <memory>
#include <iostream>

int main() {
    std::cout << "==================================================\n";
    std::cout << "INITIALIZING PARKING SYSTEM WITH MULTI-INDEX MAPS\n";
    std::cout << "==================================================\n";

    // Create a lot with 1 Small spot, 1 Compact spot, and 0 Large spots
    ParkingManager manager(1, 1, 0);

    std::cout << "\n--- Scenario 1: Parking a valid vehicle ---\n";
    // Create a compact car wrapped in a unique pointer
    auto Firstcar = std::make_unique<Car>("123-ABC");

    int carTicketId = manager.processEntry(std::move(Firstcar));


    std::cout << "\n--- Scenario 2: Simulating 45 minutes of time passing ---\n";
    // Fetch the ticket from the manager's active record using our helper method
    Ticket* activeTicket = manager.getActiveTicket(carTicketId);
    if (activeTicket != nullptr) {
        // Artificially push the entry time 45 minutes into the past
        activeTicket->forceFakeEntryTime(45);
        std::cout << "Clock modified. Ticket #" << carTicketId << " is now 45 minutes old.\n";
    }


    std::cout << "\n--- Scenario 3: Attempting to park in a completely full category ---\n";

    auto secondCar = std::make_unique<Car>("671-xyz");
    std::cout << "Attempting to park a second compact car...\n";
    int failedTicketId = manager.processEntry(std::move(secondCar));
    // This should print your "NO FREE SPACES" warning message and return -1


    std::cout << "\n--- Scenario 4: Processing checkout and invoicing ---\n";
    // Process the checkout for our first car. This will calculate the fee and free the spot.
    if (carTicketId != -1) {
        manager.processExit(carTicketId);
    }


    std::cout << "\n--- Scenario 5: Re-testing the previously full spot ---\n";
    // Since the first car left, that compact spot should now be instantly available again.
    auto thirdCar = std::make_unique<Car>("329-Amr");
    std::cout << "Attempting to park a new car in the newly vacated spot...\n";
    int newTicketId = manager.processEntry(std::move(thirdCar));


    std::cout << "\n==================================================\n";
    std::cout << "TEST RUN COMPLETION SUCCESSFUL\n";
    std::cout << "==================================================\n";

    return 0;
}