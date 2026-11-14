#pragma once
#include"Vehicle.h"
#include<memory>
class ParkingSpot {
	int SpotId;
	std::string spotType;
	bool isOccupied;
	std::shared_ptr<Vehicle> ParkedVehicle;
public:
	ParkingSpot(int SpotId, const std::string& spotType);
	bool isFree() const;
	bool assignVehicle(std::shared_ptr<Vehicle> vehicle);
	std::shared_ptr<Vehicle> releaseVehicle();
	int getSpotId() const;
	std::string getSpotType() const;
};
