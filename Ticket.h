#pragma once
#include<ctime>
#include<string>
#include<memory>
#include"Vehicle.h"
class Ticket {
	int ticketId;
	std::string licensePlate;
	int spotId;
	time_t entryTime;
	time_t exitTime;
	std::shared_ptr<Vehicle> vehicle;
public:
	Ticket(int ticketId, std::shared_ptr<Vehicle> vehicle, int spotId, long entrTime);
	Ticket();
	Ticket(std::shared_ptr<Vehicle> vehicle, int spotId);
	void closeTicket();
	double GetDurationHours() const;
	int getTicketId() const;
	std::string getLicensePlate() const;
	int getSpotId() const;
	time_t getEntryTime() const;
	time_t getExitTime() const;
	std::shared_ptr<Vehicle> getVehicle() const;
	void setEntryTime(long long time);
};
