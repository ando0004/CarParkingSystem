#include"Ticket.h"

Ticket::Ticket(int ticketId, std::shared_ptr<Vehicle> vehicle, int spotId,long entrTime) :
	ticketId(ticketId), vehicle(vehicle), spotId(spotId), entryTime(entrTime),exitTime(0) {
};
Ticket::Ticket() :ticketId(0), licensePlate(""), spotId(0), entryTime(0), exitTime(0) {};
Ticket::Ticket(std::shared_ptr<Vehicle> vehicle, int spotId) :vehicle(vehicle) , spotId(spotId) , entryTime(std::time(nullptr)), exitTime(0),ticketId(0) {}
void Ticket::closeTicket() {
	exitTime = std::time(nullptr);
}
double Ticket::GetDurationHours() const {
	if ((exitTime - entryTime) >= 3600) {
		return (exitTime - entryTime) / 3600.0;
	}
	return 1;
}
int Ticket::getTicketId() const {
	return ticketId;
}
std::string Ticket::getLicensePlate() const {
	return licensePlate;
}
int Ticket::getSpotId() const {
	return spotId;
}
time_t Ticket::getEntryTime() const {
	return entryTime;
}
time_t Ticket::getExitTime() const {
	return exitTime;
}
std::shared_ptr<Vehicle> Ticket::getVehicle() const {
	return vehicle;
}
void Ticket::setEntryTime(long long time) {
	entryTime = time;
}
