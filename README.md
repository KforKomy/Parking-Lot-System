# High-Performance Object-Oriented Parking Management System

A production-grade, single-floor Parking Management System simulation built in modern C++. This project demonstrates  Object-Oriented Design (OOD), strict adherence to SOLID principles, memory safety through RAII, and a custom dual-index data architecture designed to drop common runtime bottlenecks from linear time $O(N)$ down to absolute constant time $O(1)$.

## 🛠️ Key Architectural & OOD Highlights

* **Polymorphic Hierarchy:** Utilizes runtime polymorphism for its `Vehicle` base layout, ensuring the system satisfies the **Open/Closed Principle (OCP)** when adding new vehicle classes (e.g., `Car`, `Motorcycle`).
* **Single Responsibility Principle (SRP):** Core components are strictly decoupled. System layout management (`ParkingSpot`), data ledger tracking (`Ticket`), and financial computations (`PriceCalculator`) remain completely isolated.
* **Dual-Index Data Optimization:** Rather than defaulting to plain sequential vectors, the `ParkingManager` maintains synchronized `std::unordered_map` and `std::unordered_set` structures. This optimizes both vehicle parking lookup queries and exit transactions into highly scalable **$O(1)$ constant-time operations**.

---

## 📦 Core C++ Standard Libraries Utilized

This project deliberately avoids raw pointers and old C-style patterns, relying entirely on modern standard library abstractions:

### 1. `<memory>` (Smart Pointers & RAII)
* **Usage:** Uses `std::unique_ptr` exclusively to handle vehicle ownership transfers (`std::move`). 
* **Benefit:** Guarantees strict Resource Acquisition Is Initialization (RAII). When a vehicle leaves a spot, memory cleanup is completely automated by the runtime environment with zero risks of memory leaks.

### 2. `<atomic>` (Lock-Free Thread Safety)
* **Usage:** Implements `std::atomic<int>` global sequential counters inside `ParkingSpot` and `Ticket`.
* **Benefit:** Ensures that if multiple terminal gates try to issue tickets or generate spot IDs concurrently across multiple processing threads, race conditions are mitigated without relying on heavy kernel mutex blocks.

### 3. `<chrono>` (High-Resolution Time Points)
* **Usage:** Tracks exact session parameters through `std::chrono::system_clock::now()`.
* **Benefit:** Enables accurate computation of parking durations down to precise millisecond intervals, feeding duration intervals safely into invoicing routines.

### 4. `<unordered_map>` & `<unordered_set>` (Hash-Table Indexes)
* **Usage:** Maps `TicketID` directly to `Ticket` references, and groups available `ParkingSpot` identifiers inside specialized `VehicleSize` categorical buckets.
* **Benefit:** Drives the optimized core lookup matrix, ensuring maximum search efficiency.

---

## 📐 Component Architecture Diagram

The system relies on strong **Composition** and **Association** relationships rather than bloated monolithic inheritance:
