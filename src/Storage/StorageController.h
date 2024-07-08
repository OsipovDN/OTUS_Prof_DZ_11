#pragma once
#include <memory>

#include "Storage.h"
struct TableLine {};
std::vector <IStorage::TableLine> forTableA =
{
	{0,"lean"},
	{1,"sweater"},
	{2,"frank"},
	{3,"violation"},
	{4,"quality"},
	{5,"precision"}
};
std::vector <IStorage::TableLine> forTableB =
{
	{3,"proposal"},
	{4,"example"},
	{5,"lake"},
	{6,"flour"},
	{7,"wonder"},
	{8,"selection"}
};

class StorageController
{
private:
	std::unique_ptr<IStorage> _storage;
public:
	StorageController() :
		_storage(std::make_unique<storage::Storage>())
	{
		_storage->create("A");
		_storage->create("B");
		_storage->insertData("A", forTableA);
		_storage->insertData("B", forTableB);
	}

	void postRequest(std::string request)
	{
		_storage->intersection("A", "B");
		_storage->symmetricDifference("A", "B");

	}
	std::string getResponce()
	{

	}

};