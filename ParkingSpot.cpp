#include"ParkingSpot.h"
ParkingSpot::ParkingSpot(int SpotId, const std::string& spotType) :SpotId(SpotId), spotType(spotType), isOccupied(false) {};
bool ParkingSpot::isFree() const {
	return !isOccupied;
}
bool ParkingSpot::assignVehicle(std::shared_ptr<Vehicle> vehicle) {
	if (isOccupied) return false;
	if (vehicle->getType() != spotType) return false;
	ParkedVehicle = vehicle;
	isOccupied = true;
	return true;
}
std::shared_ptr<Vehicle> ParkingSpot::releaseVehicle() {
	if (!isOccupied) return nullptr;
	std::shared_ptr<Vehicle> temp = ParkedVehicle;
	ParkedVehicle = nullptr;
	isOccupied = false;
	return temp;
}
int ParkingSpot::getSpotId() const {
	return SpotId;
}
std::string ParkingSpot::getSpotType() const {
	return spotType;
}
