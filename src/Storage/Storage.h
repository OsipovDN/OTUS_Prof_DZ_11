#pragma once
#include <iostream>
#include <vector>
#include <tuple>

#include "IStorage.h"
#include "sqlite3.h"

#define UNUSED(x) (void)(x)
namespace storage
{
	class Storage final : public IStorage
	{
		using Str = std::tuple<int, std::string, std::string >;

	private:
		sqlite3* _db = nullptr;
		std::vector<std::vector<Str>> _collections;
		char* _errMsg{};

	private:
		int checkRes(int code, char* msg = nullptr);

	public:
		Storage() : _db(nullptr)
		{
			checkRes(sqlite3_open("DB", &_db), "Error open DB");
		};
		void create(std::string name) override;
		void insert(std::string table, int id, std::string name) override;
		void insertData(std::string table, std::vector<TableLine>& data) override;
		void truncate(std::string& table) override;
		void intersection(std::string tableA, std::string tableB) override;
		void symmetricDifference(std::string tableA, std::string tableB) override;
		~Storage()noexcept override { checkRes(sqlite3_close(_db), "Error close DB"); };

		void printTable(int num);
	};
}