#include "Storage.h"

namespace storage
{
	int Storage::checkRes(int code, char* msg)
	{
		UNUSED(msg);
		if (code != SQLITE_OK) {
			sqlite3_close(_db);
			throw std::runtime_error(_errMsg);
		}
		return code;
	}


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
			"SELECT " +
			tableA + ".id, " +
			tableA + ".name, " +
			tableB + ".name FROM " +
			tableA + " INNER JOIN " +
			tableB + " ON " +
			tableA + ".id = " +
			tableB + ".id;";

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
		std::vector<Str> table;
		do
		{
			res = sqlite3_step(stmt);
			if (res == SQLITE_ROW)
			{
				Str str =
					std::make_tuple(
						sqlite3_column_int(stmt, 0),
						std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))),
						std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)))
					);
				table.push_back(str);
			}
		} while (res != SQLITE_DONE);
		_collections.push_back(table);
		printTable(0);
		sqlite3_finalize(stmt);
	}
	void Storage::symmetricDifference(std::string tableA, std::string tableB)
	{
		std::string request =
			"SELECT " +
			tableA + ".id, " +
			tableA + ".name, " +
			tableB + ".name FROM " +
			tableA + " LEFT JOIN " +
			tableB + " ON " +
			tableA + ".id = " +
			tableB + ".id WHERE " +
			tableB + ".name IS NULL UNION SELECT " +
			tableB + ".id, " +
			tableA + ".name, " +
			tableB + ".name FROM " +
			tableB + " LEFT JOIN " +
			tableA + " ON " +
			tableB + ".id = " +
			tableA + ".id WHERE " +
			tableA + ".id IS NULL AND " +
			tableA + ".name IS NULL;";

		sqlite3_stmt* stmt;
		sqlite3_prepare_v2(_db, request.c_str(), -1, &stmt, nullptr);
		std::vector<Str> table;
		std::string aName, bName;
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id = sqlite3_column_int(stmt, 0);
			if (sqlite3_column_text(stmt, 1) != NULL)
			{
				aName = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
			}
			else
			{
				aName = {};
			}

			if (sqlite3_column_text(stmt, 2) != NULL)
			{
				bName = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
			}
			else
			{
				bName = {};
			}

			table.emplace_back(std::make_tuple( id,aName,bName));
		}

		sqlite3_finalize(stmt);

		_collections.push_back(table);
		printTable(1);

	}

	void Storage::printTable(int num)
	{

		for (auto str : _collections[num])
		{
			std::cout << std::get<0>(str) << " , " << std::get<1>(str) << " , " << std::get<2>(str) << std::endl;
		}
		std::cout << std::endl;
	}


}
