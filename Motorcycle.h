#pragma once
#include "Vehicle.h"
#include<memory>
class Motorcycle : public Vehicle {
public:
	Motorcycle(int id, const std::string& licensePlate, const std::string& brand, const std::string& type = "Motorcycle");
	~Motorcycle() override = default;
	double getHourlyRate() const override;
	Motorcycle(const Motorcycle&) = delete;
	Motorcycle& operator=(const Motorcycle&) = delete;
	Motorcycle(Motorcycle&&) = default;
	Motorcycle& operator=(Motorcycle&&) = default;
};
