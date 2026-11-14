#include "Truck.h"

Truck::Truck(int id, const std::string& licensePlate, const std::string& brand, const std::string& type)
    : Vehicle(id, licensePlate, brand, type) {
}

double Truck::getHourlyRate() const {
    return 1000.0;
};
