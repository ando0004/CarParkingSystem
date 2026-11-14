#pragma once
#include "Vehicle.h"
#include<memory>
class Car : public Vehicle {
public:
    Car(int id, const std::string& licensePlate, const std::string& brand, const std::string& type = "Car");
    ~Car() override = default;
    double getHourlyRate() const override;
    Car(const Car&) = delete;
    Car& operator=(const Car&) = delete;
    Car(Car&&) = default;
    Car& operator=(Car&&) = default;
};
