//STL
#include <iostream>

//Boost
#include <boost/asio.hpp>

#include "Server.h"
#include "Storage.h"

namespace asio = boost::asio;


int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cout << "input port number" << std::endl;
			return -1;
		}
		else
		{	
			short port = (unsigned short)strtoul(argv[1], NULL, 0);
			asio::io_context context;
			auto db = std::make_shared<storage::Storage>();
			db->create("A");
			db->create("B");

			std::vector <storage::TableLine> forTableA = {
				{0,"lean"},
				{1,"sweater"},
				{2,"frank"},
				{3,"violation"},
				{4,"quality"},
				{5,"precision"}
			};
			std::vector <storage::TableLine> forTableB = {
				{3,"proposal"},
				{4,"example"},
				{5,"lake"},
				{6,"flour"},
				{7,"wonder"},
				{8,"selection"}
			};
			db->insertData("A", forTableA);
			db->insertData("B", forTableB);

			db->intersection("A", "B");

			Server server(context, port, db);
			context.run();
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Exception: " << ex.what() << std::endl;
	}

	return 0;
}

