#include "ParkingFloor.h"
ParkingFloor::ParkingFloor(int floorNumber) :floorNumber(floorNumber) {};
void ParkingFloor::AddSpot(std::unique_ptr<ParkingSpot> spot) {
	spots.push_back(move(spot));
}
ParkingSpot* ParkingFloor::findFreeSpot(const std::string& type) {
	for (auto& spot : spots) {
		if (spot->getSpotType() == type && spot->isFree()) {
			return spot.get();
		}
	}
	return nullptr;
}
int ParkingFloor::getFloorNumber() {
	return floorNumber;
}
ParkingSpot* ParkingFloor::getSpotById(int spotId) {
	for (auto& spot : spots) {
		if (spot->getSpotId() == spotId) {
			return spot.get();
		}
	}
	return nullptr;
}
int ParkingFloor::getAvailableCount(const std::string& VehicleType) const {
	int count = 0;
	for (auto& spot : spots) {
		if (spot->getSpotType() == VehicleType) {
			count++;
		}
	}
	return count;
}
