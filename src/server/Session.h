#pragma once
#include "StorageController.h"

#define UNUSED(x) (void)(x)

namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;


class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket, std::shared_ptr<StorageController> controller)
		: _socket(std::move(socket)),
		_controller(controller)
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

	void handle_read_header(const boost::system::error_code& err, std::size_t bytes_transferred)
	{
		UNUSED(bytes_transferred);
		if (!err)
		{
			auto msg = std::istream(&_streambuf).rdbuf();
			std::string str(std::istreambuf_iterator<char>(msg), {});
			std::cout << "message: " << str;
			do_read();
		}
	}
	void do_read()
	{
		asio::async_read_until(_socket,
			_streambuf,
			'\n',
			std::bind(&Session::handle_read_header, this,
				std::placeholders::_1,
				std::placeholders::_2));
	}

	tcp::socket _socket;
	boost::asio::streambuf _streambuf;
	std::shared_ptr<StorageController> _controller;
};