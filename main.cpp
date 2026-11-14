#include <iostream>
#include <memory>

#include "DatabaseManager.h"
#include "ParkingLot.h"
#include "Car.h"
#include "CreditCardPaymentProcessor.h"
using namespace std;
int main() {
    try {
        DatabaseManager dbManager("127.0.0.1:3306", "root", "93456791andA#", "parking_system");

        ParkingLot lot("City Center Parking", dbManager);

        lot.AddFloor(1);
        lot.addSpotToFloor(1, 101, "Car");
        lot.addSpotToFloor(1, 102, "Car");
        lot.addSpotToFloor(1, 103, "Car");

        CreditCardPaymentProcessor cardProcessor;

        std::cout << "=== Parking is ready ===\n";
        lot.displayStatus();

        auto car1 = std::make_shared<Car>(1, "77-XX-777", "Opel", "Car");
        auto car2 = std::make_shared<Car>(2, "35-ST-500", "Suzuki", "Car");
        auto car3 = std::make_shared<Car>(3, "10-UU-010", "BMW", "Car");

        std::cout << "[PARK 1] Parking " << car1->getLicensePlate() << " (" << car1->getBrand() << ")...\n";
        auto ticket1 = lot.parkVehicle(car1);
        if (ticket1) std::cout << "   -> Successfully parked! Ticket ID: " << ticket1->getTicketId() << "\n\n";

        std::cout << "[PARK 2] Parking " << car2->getLicensePlate() << " (" << car2->getBrand() << ")...\n";
        auto ticket2 = lot.parkVehicle(car2);
        if (ticket2) std::cout << "   -> Successfully parked! Ticket ID: " << ticket2->getTicketId() << "\n\n";

        std::cout << "[PARK 3] Parking " << car3->getLicensePlate() << " (" << car3->getBrand() << ")...\n";
        auto ticket3 = lot.parkVehicle(car3);
        if (ticket3) std::cout << "   -> Successfully parked! Ticket ID: " << ticket3->getTicketId() << "\n\n";

        std::cout << "=== ALL 3 VEHICLES PARKED IN DATABASE ===\n\n";

        double fee = lot.unparkVehicle("77-XX-777", cardProcessor, "Card-4111-XXXX-1111");
        double fee1 = lot.unparkVehicle("35-ST-500", cardProcessor, "Card-4111-XXXX-2222");
        double fee2 = lot.unparkVehicle("10-UU-010", cardProcessor, "Card-4111-XXXX-3333");

        cout << "\nFee for 77-XX-777: " << fee << " AMD\n";
        cout << "Fee for 35-ST-500: " << fee1 << " AMD\n";
        cout << "Fee for 10-UU-010: " << fee2 << " AMD\n";

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "\n[CRITICAL ERROR]: " << e.what() << "\n";
        return 1;
    }
}
