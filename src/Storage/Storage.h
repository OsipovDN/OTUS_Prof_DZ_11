#pragma once
#include <iostream>

#include "IStorage.h"
#include "sqlite3.h"
namespace storage
{
struct Table
{
	int id;
	std::string name;
	Table() = default;
};

	class Storage final: public IStorage
	{
	private:
		sqlite3* _db;
	public:
		Storage() : _db(nullptr) {};
		bool create(std::string name) override;
		void insert(std::string& table, int id, std::string& name) override;
		void truncate(std::string& table) override;
		void intersection(std::string& tableA, std::string& tableB) override;
		void symmetricDifference(std::string& tableA, std::string& tableB)override;
		~Storage()noexcept override;
	};
}