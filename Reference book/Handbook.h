#pragma once

#include <sqlite3.h>
#include <nlohmann/json.hpp>
#include <string>
#include <format>
#include <iostream>

using namespace std;
using json = nlohmann::json;

const std::string pathDB = "Reference book";


class Handbook {
private:
	string company_name;
	string CEO;
	string phone_number;
	string address; 
	string occupation;
	sqlite3* DB;

	int OpenDB() {
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
public:
	Handbook(string name_of_company, string CEO, string phone_number, string address, string occupation) :
		company_name{ name_of_company }, CEO{ CEO }, phone_number{ phone_number }, address{ address }, occupation{ occupation } {

		int errors = OpenDB();
		if (errors != 0) {
			cerr << "DB wasn't openning \nERROR:" << sqlite3_errmsg(DB) << endl;
			return;
		}
	}
	Handbook() {
		OpenDB();
	}
	~Handbook() {
		sqlite3_close(DB);
	}
	void Save() {
		sqlite3_stmt* stmt;
		string sql = "INSERT INTO HANDBOOK (NAME_OF_COMPANY, CEO, ADDRESS, PHONE, OCCUPATION) VALUES(?, ?, ?, ?, ?)";

		int errors = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0);
		if (errors != SQLITE_OK) {
			cerr << "Call error during to prepare request \n ERROR: " << sqlite3_errmsg(DB);
			return;
		}
		sqlite3_bind_text(stmt, 1, company_name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, CEO.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, phone_number.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 4, address.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 5, occupation.c_str(), -1, SQLITE_STATIC);

		errors = sqlite3_step(stmt);
		if (errors != SQLITE_DONE) {
			cerr << "Error during fulfill the request of save\n ERROR: " << sqlite3_errmsg(DB);
			return;
		}
		sqlite3_finalize(stmt);
	}

	friend void PrintAll(Handbook& some_variable);

	json SearchByName(string name_of_company) {

	}
	json SearchByCEO(string CEO) {

	}
	json SearchByPNumber(string phone_number) {

	}
	json SearchByOccupation(string occupation) {

	}
	Handbook* operator+(Handbook some_post) {

		return this;
	}

};

