#include "serverWorker.h"

serverWorker::session::session(boost::asio::io_service &io_service) : socket_(io_service)
{
}

serverWorker::session::~session()
{
	BOOST_LOG_TRIVIAL(info) << "worker session end : " << session_id;
}

void serverWorker::session::start() {
	static tcp::no_delay option(true);
	socket_.set_option(option);

	auto endpoint = socket_.remote_endpoint();
	BOOST_LOG_TRIVIAL(info) << "worker session start,remote : " << endpoint.address() << " @ " << endpoint.port();
	session_id = endpoint.port();

	boost::asio::async_read_until(socket_,
		sbuf_,
		"\n",
		boost::bind(&session::handle_read,
			shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

boost::asio::ip::tcp::socket & serverWorker::session::socket() {
	return socket_;
}

void serverWorker::session::handle_write(const boost::system::error_code& error, size_t bytes_transferred) {
	boost::asio::async_read_until(socket_,
		sbuf_,
		"\n",
		boost::bind(&session::handle_read,
			shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void serverWorker::session::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {

	if ((boost::asio::error::eof == error) ||
		(boost::asio::error::connection_reset == error))
	{
		this->socket_.close();
		return;
	}

	try
	{
		// get string from buffer
		std::istream is(&sbuf_);
		
		std::string action;

		is >> action;

		boost::property_tree::ptree json;

		if (action == "check")
		{
			m_checker.check();
			auto res = m_checker.getResult();
			
			for (auto & i : res)
			{
				boost::property_tree::ptree node;

				node.put("c", i.car);
				node.put("r", i.reason);

				json.push_back(std::make_pair("", node));
			}
		}
		else if (action == "select")
		{
			std::string car;
			is >> car;

			auto res = m_memDB->select(car);

			for (auto & i : res)
			{
				boost::property_tree::ptree node;

				node.put("x", i.posX);
				node.put("y", i.posY);
				node.put("t", i.time);

				json.push_back(std::make_pair("", node));
			}
		}
		else
		{
			BOOST_LOG_TRIVIAL(error) << "unknow task";
			this->socket_.close();
		}

		std::ostringstream jsonStr;
		boost::property_tree::write_json(jsonStr, json, false);
		jsonStr << "\n";

		boost::asio::async_write(socket_,
			boost::asio::buffer(jsonStr.str().c_str(),jsonStr.str().length()),
			boost::bind(&session::handle_write,
				shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
	catch (...)
	{
		BOOST_LOG_TRIVIAL(error) << "unknow exception in session::handle_read";
		this->socket_.close();
	}

}

serverWorker::server::server(boost::asio::io_service &io_service, tcp::endpoint &endpoint)
	: io_service_(io_service), acceptor_(io_service, endpoint)
{
	session_ptr new_session(new session(io_service_));
	acceptor_.async_accept(new_session->socket(),
		boost::bind(&server::handle_accept,
			this,
			new_session,
			boost::asio::placeholders::error));
}

void serverWorker::server::handle_accept(session_ptr new_session, const boost::system::error_code& error) {
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

void serverWorker::server::run() {
	io_service_.run();
}