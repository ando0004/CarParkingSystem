#pragma once
#include "IDatabaseManager.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Truck.h"
#include <memory>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class DatabaseManager : public IDatabaseManager {
private:
    sql::mysql::MySQL_Driver* driver;
    std::unique_ptr<sql::Connection> connection;

public:
    DatabaseManager(const std::string& host, const std::string& user, const std::string& password, const std::string& database);
    ~DatabaseManager() override;

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    DatabaseManager(DatabaseManager&&) = default;
    DatabaseManager& operator=(DatabaseManager&&) = default;

    void createTables() override;
    void saveVehicle(const std::string& licensePlate, const std::string& brand, const std::string& type) override;
    int64_t saveTicket(const std::string& licensePlate, int spotId, long entryTime) override;
    void closeTicket(int ticketId, long exitTime, double fee) override;
    std::vector<Ticket> loadActiveTickets() override;
};
