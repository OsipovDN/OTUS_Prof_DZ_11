//STL
#include <iostream>

//Boost
#include <boost/asio.hpp>

#include "Server.h"
#include "StorageController.h"

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
			auto controller = std::make_shared<StorageController>();

			Server server(context, port, controller);
			context.run();
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Exception: " << ex.what() << std::endl;
	}

	return 0;
}

