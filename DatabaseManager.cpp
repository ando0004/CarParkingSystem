#include"DatabaseManager.h"

DatabaseManager::DatabaseManager(const std::string& host, const std::string& user, const std::string& password, const std::string& database) {
	driver = sql::mysql::get_mysql_driver_instance();
	sql::Connection* rawConnection = driver->connect(host, user, password);
	connection = std::unique_ptr<sql::Connection>(rawConnection);
	connection->setSchema(database);
}
DatabaseManager::~DatabaseManager() {};
void DatabaseManager::createTables() {
	sql::Statement* stmt = connection->createStatement();
	stmt->execute(
		"CREATE TABLE IF NOT EXISTS vehicles("
		"license_plate VARCHAR(20) PRIMARY KEY,"
		"brand VARCHAR(50),"
		"type VARCHAR(20)"
		")"
	);

	stmt->execute(
		"CREATE TABLE IF NOT EXISTS tickets("
		"ticket_id INT AUTO_INCREMENT PRIMARY KEY,"
		"license_plate VARCHAR(20),"
		"spot_id INT,"
		"entry_time BIGINT,"
		"exit_time BIGINT,"
		"fee DOUBLE "
		"FOREIGN KEY (license_plate) REFERENCES vehicles(license_plate) ON DELETE CASCADE"
		")"
	);
	delete stmt;
}
std::vector<Ticket> DatabaseManager::loadActiveTickets() {
	std::vector<Ticket> activeTickets;
	try {
		std::unique_ptr<sql::Statement> stmt(connection->createStatement());
		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(
			"SELECT t.ticket_id, t.license_plate, v.type, t.spot_id, t.entry_time, v.brand "
			"FROM tickets t "
			"JOIN vehicles v ON t.license_plate = v.license_plate "
			"WHERE t.exit_time IS NULL OR t.exit_time = 0"
		));
		while (res->next()) {
			int ticketId = res->getInt("ticket_id");
			std::string plate = res->getString("license_plate");
			std::string brand = res->getString("brand");
			std::string type = res->getString("type");
			int spotId = res->getInt("spot_id");
			int64_t entryTime = res->getInt64("entry_time");
			std::shared_ptr<Vehicle> vehicle = nullptr;
			if (type == "Truck") {
				vehicle = std::make_shared<Truck>(ticketId,plate,brand,type);
			}
			else if (type == "Motorcycle") {
				vehicle = std::make_shared<Motorcycle>(ticketId, plate, brand, type);
			}
			else {
				vehicle = std::make_shared<Car>(ticketId, plate, brand, type);
			}
			Ticket ticket(ticketId, vehicle, spotId,entryTime);
			activeTickets.push_back(ticket);
		}
	}
	catch(const sql::SQLException& e){
		std::cerr << "[DB Error - loadActiveTickets]: " << e.what() << "\n";
	}
	return activeTickets;
}
void DatabaseManager:: saveVehicle(const std::string& licensePlate, const std::string& brand, const std::string& type) {
	sql::PreparedStatement* pstmt = connection->prepareStatement("INSERT IGNORE INTO vehicles VALUES (?,?,?)");
	pstmt->setString(1, licensePlate);
	pstmt->setString(2, brand);
	pstmt->setString(3, type);
	pstmt->executeUpdate();
	delete pstmt;

}
int64_t DatabaseManager::saveTicket(const std::string& licensePlate, int spotId, long entryTime) {
	if (!connection || connection->isClosed()) {
		return 0;
	}

	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(
			connection->prepareStatement("INSERT INTO tickets (license_plate, spot_id, entry_time) VALUES (?, ?, ?)")
		);

		pstmt->setString(1, licensePlate);
		pstmt->setInt(2, spotId);
		pstmt->setInt64(3, static_cast<int64_t>(entryTime));

		pstmt->executeUpdate();

		std::unique_ptr<sql::Statement> stmt(connection->createStatement());
		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT LAST_INSERT_ID() AS id"));

		int64_t newTicketId = 0;
		if (res->next()) {
			newTicketId = res->getInt64("id");
		}

		return newTicketId;

	}
	catch (const sql::SQLException& e) {
		std::cerr << "[DB Error]: " << e.what() << "\n";
		return 0;
	}
}
void DatabaseManager::closeTicket(int ticketId, long exitTime, double fee){
	sql::PreparedStatement* pstmt = connection->prepareStatement("UPDATE  tickets SET exit_time = ?, fee = ? WHERE ticket_id = ?");
	pstmt->setInt64(1, exitTime);
	pstmt->setDouble(2,fee);
	pstmt->setInt(3, ticketId);
	pstmt->executeUpdate();
	delete pstmt;
}
