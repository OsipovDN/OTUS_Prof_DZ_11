#pragma once
#include "IStorage.h"


namespace storage
{
	class Storage : public IStorage
	{
	private:
	public:

		virtual bool create(const char& name) {};
		void insert(const char& table, int id, std::string& name) override {};
		void truncate(const char& table) override {};
		void intersection(const char& tableA, const char& tableB) override {};
		void symmetricDifference(const char& tableA, const char& tableB)override {};

	};
}