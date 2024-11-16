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

	int OpenDB();
public:
	Handbook(string name_of_company, string CEO, string phone_number, string address, string occupation);
	Handbook();
	~Handbook();

	void Save();

	friend void PrintAll(Handbook& some_variable);

	json SearchByName(string name_of_company);
	json SearchByCEO(string CEO);
	json SearchByPNumber(string phone_number);
	json SearchByOccupation(string occupation);
	//Handbook* operator+(Handbook some_post) { makes just some post in DB by help operator of cros
	//	return this;
	//}

};

