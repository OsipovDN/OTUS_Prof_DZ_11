#include "Storage.h"



namespace storage
{
	void Storage::create(std::string name)
	{
		std::string request = "CREATE TABLE IF NOT EXISTS " + name +
			"(id INTEGER PRIMARY KEY,"
			"name TEXT NOT NULL);";

		checkRes(sqlite3_exec(_db, request.c_str(), 0, nullptr, &_errMsg), _errMsg);
	}

	void Storage::insert(std::string table, int id, std::string name)
	{

		std::string request =
			"INSERT INTO " + table + " (id , name) VALUES ("
			+ std::to_string(id) + " , '" + name + "');";

		checkRes(sqlite3_exec(_db, request.c_str(), 0, nullptr, &_errMsg), _errMsg);
	}

	void Storage::insertData(std::string table, std::vector<TableLine>& data)
	{
		for (auto line : data)
			insert(table, line.id, line.name);
	}

	void Storage::truncate(std::string& table)
	{
		std::string request =
			"DELETE FROM " + table + ";";

		checkRes(sqlite3_exec(_db, request.c_str(), nullptr, nullptr, &_errMsg), _errMsg);
	}

	void Storage::intersection(std::string tableA, std::string tableB)
	{

		std::string request =
			//"SELECT id FROM " + tableA + " INTERSECT SELECT id FROM " + tableB + ";";

			"SELECT " +
			tableA + ".id, " +
			tableA + ".name, " +
			tableB + ".name FROM " +
			tableA + " INNER JOIN " +
			tableB + " ON " +
			tableA + ".id = " +
			tableB + ".id; ";

		checkRes(sqlite3_exec(_db, request.c_str(), nullptr, nullptr, &_errMsg), _errMsg);
		sqlite3_stmt* stmt;
		const char* stmt_tail;
		checkRes(
			sqlite3_prepare_v2(
				_db,
				request.data(),
				(int)(request.size()),
				&stmt,
				&stmt_tail));
		int res;
		do
		{
			res = sqlite3_step(stmt);
			if (res == SQLITE_ROW)
			{
				std::string str;
				for (int i = 0; i < 3; ++i)
				{
					auto text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
					str += text;
					if (i !=2)
						str += ",";
				}
				//Работаем со строкой
				std::cout << str << std::endl;
			}
		} while (res != SQLITE_DONE);

		sqlite3_finalize(stmt);

	}
	void Storage::symmetricDifference(std::string& tableA, std::string& tableB)
	{
		UNUSED(tableA);
		UNUSED(tableB);
	}

}
