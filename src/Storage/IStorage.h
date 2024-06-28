#pragma once

class IStorage
{
	virtual bool create(const char& name) = 0;
	virtual void insert(const char& table, int id, std::string& name) = 0;
	virtual void truncate(const char& table) = 0;
	virtual void intersection(const char& tableA, const char& tableB) = 0;
	virtual void symmetricDifference(const char& tableA, const char& tableB) = 0;
};
