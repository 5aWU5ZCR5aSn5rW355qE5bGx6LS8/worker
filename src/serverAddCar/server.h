#pragma once

#include <iostream>
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <boost\smart_ptr.hpp>


namespace serverAddCar {
	
	using boost::asio::ip::tcp;
	using boost::asio::ip::address;

	class session : public boost::enable_shared_from_this<session> {
	public:
		session(boost::asio::io_service &io_service);
		void start();
		tcp::socket &socket();
	private:
		tcp::socket socket_;
		boost::asio::streambuf sbuf_;
		void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
		void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
	};

	typedef boost::shared_ptr<session> session_ptr;

	class server {
	public:
		server(boost::asio::io_service &io_service, tcp::endpoint &endpoint);
		void handle_accept(session_ptr new_session, const boost::system::error_code& error);
		void run();

	private:
		boost::asio::io_service &io_service_;
		tcp::acceptor acceptor_;
	};
	
}