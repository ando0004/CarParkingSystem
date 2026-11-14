#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "Ticket.h"

class IDatabaseManager {
public:
    virtual ~IDatabaseManager() = default;

    virtual void createTables() = 0;
    virtual void saveVehicle(const std::string& licensePlate, const std::string& brand, const std::string& type) = 0;
    virtual int64_t saveTicket(const std::string& licensePlate, int spotId, long entryTime) = 0;
    virtual void closeTicket(int ticketId, long exitTime, double fee) = 0;
    virtual std::vector<Ticket> loadActiveTickets() = 0;
};
