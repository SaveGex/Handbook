#pragma once

#include <sqlite3.h>
#include <nlohmann/json.hpp>
#include <string>
#include "DataBase.cpp"

using namespace std;
using json = nlohmann::json;

class Handbook{
private:
	json json_data_of_class;
public:
	Handbook(string name_of_company, string CEO, string phone_number,string adress, string occupation) {
		json_data_of_class = {
			{"Company", name_of_company},
			{"CEO", CEO},
			{"Phone", phone_number},
			{"Adress", adress},
			{"Occupation", occupation}
		};
		
	}

	json SearchByName(string name_of_company) {

	}
	json SearchByCEO(string CEO) {

	}
	json SearchByPNumber(string phone_number) {

	}
	json SearchByOccupation(string occupation) {

	}
	void PrintAll() {

	}
	Handbook* operator+(Handbook some_post) {

		return this;
	}

};

