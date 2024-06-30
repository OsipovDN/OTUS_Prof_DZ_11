#include "Storage.h"

#define UNUSED(x) (void)(x)

namespace storage
{
	bool Storage::create(std::string name)
	{
		std::string request= "CREATE TABLE "+name+
			"(id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"name TEXT NOT NULL);";

		int exit = 0;
		exit = sqlite3_open(name.c_str(), &_db);
		char* messaggeError;
		exit = sqlite3_exec(_db, request.c_str(), NULL, 0, &messaggeError);

		if (exit != SQLITE_OK) {
			std::cerr << "Error Create Table" << std::endl;
			sqlite3_free(messaggeError);
			return 1;
		}
		else
		{
			std::cout << "Table "<< name << "created Successfully" << std::endl;
			sqlite3_close(_db);
			return 0;
		}

	}
	void Storage::insert(std::string& table, int id, std::string& name)
	{
		UNUSED(table);
		UNUSED(id);
		UNUSED(name);
	}
	void Storage::truncate(std::string& table)
	{
		UNUSED(table);
	}
	void Storage::intersection(std::string& tableA, std::string& tableB)
	{
		UNUSED(tableA);
		UNUSED(tableB);
	}
	void Storage::symmetricDifference(std::string& tableA, std::string& tableB)
	{
		UNUSED(tableA);
		UNUSED(tableB);
	}
	Storage::~Storage()
	{

	}
}
