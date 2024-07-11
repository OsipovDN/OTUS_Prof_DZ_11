#pragma once
#include <memory>
#include <optional>
//Boost
#include <boost/asio.hpp>

#include "Session.h"
#include "StorageController.h"

namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

class Server
{
public:
	Server(asio::io_context& cont, short port, std::shared_ptr<StorageController> controller)
		:_context(cont),
		_acceptor(cont, tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), port)),
		_controller(controller)
	{
		
		std::cout << __FUNCTION__ << std::endl;
		do_accept();
	}
	~Server() {
		std::cout << __FUNCTION__ << std::endl;
	}

private:
	void do_accept()
	{
		_socket=std::make_shared<tcp::socket>(_context);
		_acceptor.async_accept(*_socket,
			[this](boost::system::error_code ec)
			{
				if (!ec)
				{

					_session = std::make_shared<Session>(std::move(*_socket), _controller);

					_session->start();
				}
				else
				{
					std::cout << __FUNCTION__ << std::endl;
				}
				do_accept();
			});
	}

	asio::io_context& _context;
	tcp::acceptor _acceptor;
	std::shared_ptr<tcp::socket> _socket;
	std::shared_ptr <Session> _session;
	std::shared_ptr<StorageController> _controller;
};