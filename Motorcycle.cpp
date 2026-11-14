#include "Motorcycle.h"

Motorcycle::Motorcycle(int id, const std::string& licensePlate, const std::string& brand, const std::string& type)
    : Vehicle(id, licensePlate, brand, type) {
}

double Motorcycle::getHourlyRate() const {
    return 300.0;
}
