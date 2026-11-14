#pragma once
#include "Vehicle.h"
#include<memory>
class Truck : public Vehicle {
public:
	Truck(int id, const std::string& licensePlate, const std::string& brand, const std::string& type = "Truck");
	~Truck() override = default;
	double getHourlyRate() const override;
	Truck(const Truck&) = delete;
	Truck& operator=(const Truck&) = delete;
	Truck(Truck&&) = default;
	Truck& operator=(Truck&&) = default;
};
