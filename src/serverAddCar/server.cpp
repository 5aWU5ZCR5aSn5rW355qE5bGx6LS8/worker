#include "server.h"

serverAddCar::session::session(boost::asio::io_service &io_service) : socket_(io_service)
{
}

void serverAddCar::session::start() {
	static tcp::no_delay option(true);
	socket_.set_option(option);

	boost::asio::async_read_until(socket_,
		sbuf_,
		"\n",
		boost::bind(&session::handle_read,
			shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

boost::asio::ip::tcp::socket & serverAddCar::session::socket() {
	return socket_;
}

void serverAddCar::session::handle_write(const boost::system::error_code& error, size_t bytes_transferred) {
	boost::asio::async_read_until(socket_,
		sbuf_,
		"\n",
		boost::bind(&session::handle_read,
			shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void serverAddCar::session::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
	boost::asio::async_write(socket_,
		sbuf_,
		boost::bind(&session::handle_write,
			shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

serverAddCar::server::server(boost::asio::io_service &io_service, tcp::endpoint &endpoint)
	: io_service_(io_service), acceptor_(io_service, endpoint)
{
	session_ptr new_session(new session(io_service_));
	acceptor_.async_accept(new_session->socket(),
		boost::bind(&server::handle_accept,
			this,
			new_session,
			boost::asio::placeholders::error));
}

void serverAddCar::server::handle_accept(session_ptr new_session, const boost::system::error_code& error) {
	if (error) {
		return;
	}

	new_session->start();
	new_session.reset(new session(io_service_));
	acceptor_.async_accept(new_session->socket(),
		boost::bind(&server::handle_accept,
			this,
			new_session,
			boost::asio::placeholders::error));
}

void serverAddCar::server::run() {
	io_service_.run();
}