#include "Car.h"

Car::Car(int id, const std::string& licensePlate, const std::string& brand, const std::string& type)
    : Vehicle(id, licensePlate, brand, type) {
}

double Car::getHourlyRate() const {
    return 500.0;
}
