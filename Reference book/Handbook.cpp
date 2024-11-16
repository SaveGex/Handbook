#include "Handbook.h"

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
            );
        }
    }
	cout << "\033[033mDatabase End\033[0m";
	sqlite3_finalize(stmt);
}
