#pragma once
#include"ParkingFloor.h"
#include "Ticket.h"
#include"Vehicle.h"
#include "IDatabaseManager.h"
#include"IPaymentProcessor.h"
#include<map>
#include<string>
#include<vector>
#include<mutex>
#include<memory>
class ParkingLot {
	std::string name;
	std::vector<std::unique_ptr<ParkingFloor>> floors;
	std::map<std::string, Ticket> activeTickets;
	std::mutex mtx;
	IDatabaseManager& dbManager;
public:
	ParkingLot(const std::string& name, IDatabaseManager& dbManager);
	void AddFloor(int floorNumber);
	std::shared_ptr<Ticket> parkVehicle(std::shared_ptr<Vehicle> vehicle);
	double unparkVehicle(const std::string& licensePlate, IPaymentProcessor& paymentProcessor,
		const std::string& paymentDetails);
	void addSpotToFloor(int floorNumber, int spotId, const std::string& spotType);
	int getAvailableSpotsCount(const std::string& vehicleType) const;
	void displayStatus() const;
	void loadFromDatabase();
	void DebugPrintActiveTickets() const;

};
