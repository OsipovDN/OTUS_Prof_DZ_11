#pragma once

#include "IStorage.h"

namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;


class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket, std::shared_ptr<IStorage> db)
		: _socket(std::move(socket)),
		_db(db)
	{
		
		std::cout << __FUNCTION__ << std::endl;
	}

	void start()
	{
		do_read();
	}

	~Session()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

private:
	void do_read()
	{

		_socket.async_read_some(boost::asio::buffer(_data, 1024),
			[self = shared_from_this()](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				auto msg = std::string{ self->_data, length };
				msg += "EOF\n";
				std::cout << "message: " << msg;
				self->do_read();

			}
		});
	}

	tcp::socket _socket;
	char _data[1024];
	std::shared_ptr<IStorage> _db;
};