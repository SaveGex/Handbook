#include "Handbook.h"


int Handbook::OpenDB() {
	// open DB and create table if not exists
	int errors = sqlite3_open(pathDB.c_str(), &DB);
	if (errors != SQLITE_OK) {
		throw ("Error call during open DB \nERROR: ");
	}

	std::string sql = "CREATE TABLE IF NOT EXISTS HANDBOOK("
		"`ID` INTEGER PRIMARY KEY AUTOINCREMENT,"
		"`NAME_OF_COMPANY` TEXT NOT NULL,"
		"`CEO` VARCHAR(200) NOT NULL,"
		"`ADDRESS` TEXT NOT NULL,"
		"`PHONE` TEXT DEFAULT 1,"
		"`OCCUPATION` VARCHAR(500) NOT NULL);";

	errors = sqlite3_exec(DB, sql.c_str(), NULL, 0, nullptr);

	if (errors != SQLITE_OK) {
		cerr << "Error during fulfill a request: " << sqlite3_errmsg(DB) << endl;
		sqlite3_close(DB);
		return -1;
	}
	return 0;
}

Handbook::Handbook(string name_of_company, string CEO, string phone_number, string address, string occupation) :
	company_name{ name_of_company }, CEO{ CEO }, phone_number{ phone_number }, address{ address }, occupation{ occupation } {

	int errors = OpenDB();
	if (errors != 0) {
		cerr << "DB wasn't openning \nERROR:" << sqlite3_errmsg(DB) << endl;
		return;
	}
}

Handbook::Handbook() {
	OpenDB();
}

Handbook::~Handbook() {
	sqlite3_close(DB);
}

void Handbook::Save() {
	sqlite3_stmt* stmt;
	string sql = "INSERT INTO HANDBOOK (NAME_OF_COMPANY, CEO, ADDRESS, PHONE, OCCUPATION) VALUES(?, ?, ?, ?, ?)";

	int errors = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0);
	if (errors != SQLITE_OK) {
		cerr << "Call error during to prepare request \n ERROR: " << sqlite3_errmsg(DB);
		return;
	}
	sqlite3_bind_text(stmt, 1, company_name.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, CEO.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, address.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, phone_number.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, occupation.c_str(), -1, SQLITE_STATIC);

	errors = sqlite3_step(stmt);
	if (errors != SQLITE_DONE) {
		cerr << "Error during fulfill the request of save\n ERROR: " << sqlite3_errmsg(DB);
		return;
	}
	sqlite3_finalize(stmt);
}

json Handbook::SearchByName(string name_of_company){
	sqlite3_stmt* stmt;
	json json_data;
	string sql = "SELECT * FROM HANDBOOK WHERE NAME_OF_COMPANY = ?";  

	int errors = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0);

	if (errors != SQLITE_OK) {
		cerr << "error during preparing statement" << sqlite3_errmsg(DB) << endl;
		sqlite3_close(DB);
		return json();
	}

	sqlite3_bind_text(stmt, 1, name_of_company.c_str(), -1, SQLITE_STATIC);

	int index{ 0 };
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		json_data["company_data"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
		json_data["company_data"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		json_data["company_data"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
		json_data["company_data"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
		json_data["company_data"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
		json_data["company_data"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));


		index++;
	}
	sqlite3_finalize(stmt);

	return json_data;
}

json Handbook::SearchByCEO(string CEO){
	sqlite3_stmt* stmt;
	json json_data;
	string sql = "SELECT * FROM HANDBOOK WHERE CEO = ?";

	int errors = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0);

	if (errors != SQLITE_OK) {
		cerr << "error during preparing statement" << sqlite3_errmsg(DB) << endl;
		sqlite3_close(DB);
		return json();
	}

	sqlite3_bind_text(stmt, 1, CEO.c_str(), -1, SQLITE_STATIC);

	int index{ 0 };
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		json_data["CEO"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
		json_data["CEO"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		json_data["CEO"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
		json_data["CEO"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
		json_data["CEO"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
		json_data["CEO"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));


		index++;
	}
	sqlite3_finalize(stmt);

	return json_data;
}

json Handbook::SearchByPNumber(string phone_number){
	sqlite3_stmt* stmt;
	json json_data;
	string sql = "SELECT * FROM HANDBOOK WHERE PHONE = ?";

	int errors = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0);

	if (errors != SQLITE_OK) {
		cerr << "error during preparing statement" << sqlite3_errmsg(DB) << endl;
		sqlite3_close(DB);
		return json();
	}

	sqlite3_bind_text(stmt, 1, phone_number.c_str(), -1, SQLITE_STATIC);

	int index{ 0 };
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		json_data["PHONE"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
		json_data["PHONE"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		json_data["PHONE"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
		json_data["PHONE"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
		json_data["PHONE"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
		json_data["PHONE"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));


		index++;
	}
	sqlite3_finalize(stmt);

	return json_data;
}

json Handbook::SearchByOccupation(string occupation){
	sqlite3_stmt* stmt;
	json json_data;
	string sql = "SELECT * FROM HANDBOOK WHERE PHONE = ?";

	int errors = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0);

	if (errors != SQLITE_OK) {
		cerr << "error during preparing statement" << sqlite3_errmsg(DB) << endl;
		sqlite3_close(DB);
		return json();
	}

	sqlite3_bind_text(stmt, 1, occupation.c_str(), -1, SQLITE_STATIC);

	int index{ 0 };
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		json_data["OCCUPATION"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
		json_data["OCCUPATION"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		json_data["OCCUPATION"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
		json_data["OCCUPATION"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
		json_data["OCCUPATION"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
		json_data["OCCUPATION"][index].push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));


		index++;
	}
	sqlite3_finalize(stmt);

	return json_data;
}

void PrintAll(Handbook& some_variable){
	sqlite3_stmt* stmt;

	string sql = "SELECT * FROM HANDBOOK";

	int errors = sqlite3_prepare_v2(some_variable.DB, sql.c_str(), -1, &stmt, 0);

	if (errors != SQLITE_OK) {
		cerr << "error during prepearing statement" << endl;
		sqlite3_close(some_variable.DB);
		return;
	}
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Extract the length of each column to avoid null terminators and invalid characters
        const char* name_of_company = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* ceo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        const char* phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        const char* occupation = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        // Check if the data is not null and print only valid data
        if (name_of_company && ceo && address && phone && occupation) {
			cout << format(
				"Name company: {} \nCEO: {} \nAddress' company: {} \nPhone's company: {} \nOccupation's company: {}\n",
				name_of_company, ceo, address, phone, occupation
			) << endl;
        }
    }
	cout << "\033[033mDatabase End\033[0m";
	sqlite3_finalize(stmt);
}