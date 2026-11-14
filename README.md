# Automated Car Parking System (C++)

A high-performance, thread-safe, Object-Oriented Automated Car Parking System written in Modern C++ (C++17/C++20). The system models multi-level parking structures, manages dynamic spot allocation, processes payments via pluggable interfaces (SOLID principles), and maintains state persistence using MySQL.

---

## Key Features

- **Thread-Safe Architecture:** Utilizes `std::mutex` and `std::lock_guard` to safely handle concurrent vehicle entries, exits, and spot allocations in a multi-threaded environment.
- **SOLID Design Principles:**
  - **Open/Closed Principle (OCP):** Interface-driven payment architecture (`IPaymentProcessor`) allowing seamless addition of new payment channels (Credit Card, Cash, Apple/Google Pay) without modifying core business logic.
  - **Dependency Inversion Principle (DIP):** Decoupled `ParkingLot` core logic from direct database and payment system implementations via clean abstractions.
- **Database Persistence:** Integrated with MySQL (`mysqlcppconn`) to persist active tickets, spot allocations, timestamps, and payment histories.
- **Polymorphic Vehicle Hierarchy:** Extensible `Vehicle` base class supporting concrete types (`Car`, `Motorcycle`, `Truck`) with individual hourly rate calculation logic.
- **Dynamic Spot Allocation:** Real-time spot lookup, assignment, and release across multi-floor layouts.

---

## Tech Stack

| Category      | Details                                             |
|---------------|------------------------------------------------------|
| Language      | C++17 / C++20                                        |
| Build System  | CMake (v3.15+)                                       |
| Database      | MySQL Server 8.0+ / MySQL Connector/C++              |
| Concurrency   | C++ Standard Threading Library (`<mutex>`, `<thread>`) |
| Environment   | Linux (Ubuntu) / Dual-Boot Windows                   |

---

## System Architecture

```
                   +-------------------+
                   |    ParkingLot     |
                   +---------+---------+
                             |
    +------------------------+------------------------+
    |                        |                        |
+---v-----------+   +--------v--------+      +--------v--------+
| Floor / Spot  |   | IPaymentProcess |      | DatabaseManager |
|  Management   |   +--------+--------+      +-----------------+
+---------------+            |
                     +--------v--------+
                     | CreditCardPayment|
                     |    Processor     |
                     +-----------------+
```

---

## Prerequisites & Installation

### 1. Install Dependencies (Ubuntu / Debian)

```bash
sudo apt update
sudo apt install -y build-essential cmake libmysqlcppconn-dev
```

### 2. Set Up the Database

Ensure MySQL Server is running, then execute the following SQL script:

```sql
CREATE DATABASE IF NOT EXISTS parking_system;
USE parking_system;

CREATE TABLE IF NOT EXISTS tickets (
    ticket_id INT AUTO_INCREMENT PRIMARY KEY,
    license_plate VARCHAR(30) NOT NULL,
    spot_id INT NOT NULL,
    entry_time BIGINT NOT NULL,
    exit_time BIGINT DEFAULT NULL,
    fee DOUBLE DEFAULT 0.0,
    status VARCHAR(20) DEFAULT 'ACTIVE'
);
```

### 3. Build Using CMake

```bash
# Clone repository
git clone https://github.com/your-username/car-parking-system-cpp.git
cd car-parking-system-cpp

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run executable
./ParkingSystem
```

---

## Usage Example

```cpp
#include <iostream>
#include <memory>
#include "DatabaseManager.h"
#include "ParkingLot.h"
#include "Car.h"
#include "CreditCardPaymentProcessor.h"

int main() {
    DatabaseManager dbManager("127.0.0.1:3306", "root", "your_password", "parking_system");
    ParkingLot lot("City Center Parking", dbManager);

    lot.AddFloor(1);
    lot.addSpotToFloor(1, 101, "Car");

    auto car = std::make_shared<Car>(1, "77-XX-777", "Opel", "Car");
    lot.parkVehicle(car);

    CreditCardPaymentProcessor cardProcessor;
    double fee = lot.unparkVehicle("77-XX-777", cardProcessor, "Card-Token-1234");

    std::cout << "Vehicle unparked. Total fee: " << fee << " AMD\n";
    return 0;
}
```

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Contributing

Contributions are welcome. Please open an issue or submit a pull request with your proposed changes.