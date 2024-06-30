#include "Storage.h"



namespace storage
{
	void Storage::create(std::string name)
	{

		checkRes(sqlite3_open(name.c_str(), &_db), "Error open DB");

		std::string request = "CREATE TABLE IF NOT EXISTS " + name +
			"(id INTEGER PRIMARY KEY,"
			"name TEXT NOT NULL);";

		checkRes(sqlite3_exec(_db, request.c_str(), nullptr, nullptr, &_errMsg), _errMsg);
		checkRes(sqlite3_close(_db), "Error close DB");
	}

	void Storage::insert(std::string table, int id, std::string name)
	{
		checkRes(sqlite3_open(table.c_str(), &_db), "Error open DB");

		std::string request =
			"INSERT INTO " + table + " (id , name) VALUES ("
			+ std::to_string(id) + " , '" + name + "');";

		checkRes(sqlite3_exec(_db, request.c_str(), nullptr, nullptr, &_errMsg), _errMsg);
		checkRes(sqlite3_close(_db), "Error close DB");

	}
	void Storage::insertData(std::string table, std::vector<TableLine>& data)
	{
		for (auto line : data)
			insert(table, line.id, line.name);
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
