#pragma once
#include <string>
class Vehicle {
protected:
    int id;
    std::string licensePlate;
    std::string brand;
    std::string type;

public:
    Vehicle(int id, const std::string& licensePlate, const std::string& brand, const std::string& type);
    virtual ~Vehicle() = default;
    int getId() const;
    std::string getLicensePlate() const;
    std::string getBrand() const;
    virtual std::string getType() const;
    virtual double getHourlyRate() const = 0;
    Vehicle(const Vehicle&) = delete;
    Vehicle& operator=(const Vehicle&) = delete;
    Vehicle(Vehicle&&) = default;
    Vehicle& operator=(Vehicle&&) = default;
};
