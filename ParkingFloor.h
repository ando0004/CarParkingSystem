#pragma once
#include"ParkingSpot.h"
#include<vector>
#include<memory>
class ParkingFloor {
	int floorNumber;
	std::vector < std::unique_ptr<ParkingSpot>> spots;
public:
	ParkingFloor(int floorNumber);
	void AddSpot(std::unique_ptr<ParkingSpot> spot);
	ParkingSpot* findFreeSpot(const std::string& type);
	int getFloorNumber();
	ParkingSpot* getSpotById(int spotId);
	int getAvailableCount(const std::string& VehicleType) const;
};
