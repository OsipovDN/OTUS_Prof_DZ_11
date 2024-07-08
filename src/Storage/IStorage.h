#pragma once
#include <string>

class IStorage
{
public:
	struct TableLine
	{
		int id;
		std::string name;
		TableLine() = default;
	};

	virtual void create(std::string name) = 0;
	virtual void insert(std::string table, int id, std::string name) = 0;
	virtual void truncate(std::string& table) = 0;
	virtual void intersection(std::string tableA, std::string tableB) = 0;
	virtual void insertData(std::string table, std::vector<TableLine>& data) = 0;
	virtual void symmetricDifference(std::string tableA, std::string tableB) = 0;
	virtual ~IStorage() noexcept = default;
};
