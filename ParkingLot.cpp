#include"ParkingLot.h"
#include<iostream>
ParkingLot::ParkingLot(const std::string& name, IDatabaseManager& dbManager) :name(name),dbManager(dbManager) {};
void ParkingLot::AddFloor(int floorNumber) {
	floors.push_back(std::make_unique<ParkingFloor>(floorNumber));
}
void ParkingLot::loadFromDatabase() {
	std::vector<Ticket>  loadedTickets = dbManager.loadActiveTickets();
	for (const auto& ticket : loadedTickets) {
		ParkingSpot* spot = nullptr;
		for (auto& floor : floors) {
			spot = floor->getSpotById(ticket.getSpotId());
			if (spot != nullptr) break;
		}
		if (spot != nullptr) {
			spot->assignVehicle(ticket.getVehicle());
		}
		activeTickets[ticket.getVehicle()->getLicensePlate()] = ticket;
	}
}
std::shared_ptr<Ticket> ParkingLot::parkVehicle(std::shared_ptr<Vehicle> vehicle) {
	std::lock_guard<std::mutex> lock(mtx);
	auto existing = activeTickets.find(vehicle->getLicensePlate());
	if (existing != activeTickets.end()) {
		std::cerr << "Vehicle already has an active ticket: " << vehicle->getLicensePlate() << std::endl;
		return nullptr;
	}
	for (auto& floor : floors) {
		ParkingSpot* spot = floor->findFreeSpot(vehicle->getType());
		if (spot != nullptr) {
			spot->assignVehicle(vehicle);

			long entryTime = static_cast<long>(std::time(nullptr));
			int64_t generatedTicketId = 0;
			try {
				dbManager.saveVehicle(vehicle->getLicensePlate(), vehicle->getBrand(), vehicle->getType());
				generatedTicketId = dbManager.saveTicket(vehicle->getLicensePlate(), spot->getSpotId(), entryTime);
			}
			catch (const std::exception& e) {
				std::cerr << "[DB Error in parkVehicle]: " << e.what() << "\n";
			}
			auto ticketPtr = std::make_shared<Ticket>(generatedTicketId, vehicle, spot->getSpotId(), entryTime);
			activeTickets[vehicle->getLicensePlate()] = *ticketPtr;
			return ticketPtr;
		}
	}
	return nullptr;
}
double ParkingLot::unparkVehicle(const std::string& licensePlate,
	IPaymentProcessor& paymentProcessor,
	const std::string& paymentDetails)
{
	std::lock_guard<std::mutex> lock(mtx);

	auto it = activeTickets.find(licensePlate);
	if (it == activeTickets.end()) {
		std::cerr << "[Warning]: Vehicle with plate " << licensePlate << " not found!\n";
		return -1.0;
	}

	Ticket& ticket = it->second;

	auto vehicle = ticket.getVehicle();
	if (!vehicle) {
		std::cerr << "[Error]: Null vehicle pointer for ticket ID: " << ticket.getTicketId() << "\n";
		activeTickets.erase(it);
		return -1.0;
	}

	ticket.closeTicket();
	double fee = ticket.GetDurationHours() * vehicle->getHourlyRate();

	bool paymentSuccess = paymentProcessor.processPayment(fee, paymentDetails);
	if (!paymentSuccess) {
		std::cerr << "[Payment Error]: Transaction failed for vehicle " << licensePlate << ".\n";
		return -1.0;
	}

	int spotId = ticket.getSpotId();
	bool spotFound = false;

	for (auto& floor : floors) {
		ParkingSpot* spot = floor->getSpotById(spotId);
		if (spot != nullptr) {
			spot->releaseVehicle();
			spotFound = true;
			break;
		}
	}

	if (!spotFound) {
		std::cerr << "[Warning]: Spot ID " << spotId << " not found on any floor.\n";
	}

	long exitTime = static_cast<long>(ticket.getExitTime());
	try {
		dbManager.closeTicket(ticket.getTicketId(), exitTime, fee);
	}
	catch (const std::exception& e) {
		std::cerr << "[DB Error in unparkVehicle]: " << e.what() << "\n";
	}

	activeTickets.erase(it);
	return fee;
}
int ParkingLot::getAvailableSpotsCount(const std::string& vehicleType) const {
	int count = 0;
	for (auto& floor : floors) {
		count += floor->getAvailableCount(vehicleType);
	}
	return count;
}
void ParkingLot::displayStatus() const {
	std::cout << "Parking Lot:" << name <<"\n";
	for (auto& floor : floors) {
		std::cout << "Floor" << floor->getFloorNumber() << "\n";
	}
}
void ParkingLot::addSpotToFloor(int floorNumber, int spotId, const std::string& spotType) {
	for (auto& floor : floors) {
		if (floor->getFloorNumber() == floorNumber) {
			floor->AddSpot(std::make_unique<ParkingSpot>(spotId, spotType));
		}
	}
}
void ParkingLot::DebugPrintActiveTickets() const {
	std::cout << "=== Active Tickets (" << activeTickets.size() << ")===\n";
	for (const auto& pair : activeTickets) {
	std::cout << "KEY: [" << pair.first << "] TicketID:" << pair.second.getTicketId() << "\n";
	}
}
