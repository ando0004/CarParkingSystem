#include<iostream>
#include "Vehicle.h"
#include<string>
using namespace std;
Vehicle::Vehicle(int id, const std::string& licensePlate, const std::string& brand, const std::string& type)
    : id(id), licensePlate(licensePlate), brand(brand), type(type) {
}

int Vehicle::getId() const {
    return id;
}

std::string Vehicle::getLicensePlate() const {
    return licensePlate;
}

std::string Vehicle::getBrand() const {
    return brand;
}

std::string Vehicle::getType() const {
    return type;
}
