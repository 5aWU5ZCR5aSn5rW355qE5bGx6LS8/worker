#include "server.h"

serverAddCar::session::session(boost::asio::io_service &io_service) : socket_(io_service)
{
}

serverAddCar::session::~session()
{
	BOOST_LOG_TRIVIAL(info) << "session end : " << session_id;
}

void serverAddCar::session::start() {
	static tcp::no_delay option(true);
	socket_.set_option(option);

	auto endpoint = socket_.remote_endpoint();
	BOOST_LOG_TRIVIAL(info) << "session start,remote : " << endpoint.address() << " @ " << endpoint.port();
	session_id = endpoint.port();

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

	if ((boost::asio::error::eof == error) ||
		(boost::asio::error::connection_reset == error))
	{
		this->socket_.close();
		return;
	}

	try 
	{
		/*boost::asio::async_write(socket_,
		sbuf_,
		boost::bind(&session::handle_write,
		shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));*/

		// get string from buffer
		std::istream is(&sbuf_);
		std::string line;
		std::getline(is, line);

		std::string jsonStr;

		// decode base64
		try
		{
			base64::base64 b;
			jsonStr = b.base64_decode(line);
		}
		catch (boost::exception & e)
		{
			BOOST_LOG_TRIVIAL(error) << "unable to decode base64 : " << line;
			this->socket_.close();
			return;
		}


		// decode json
		try
		{

			boost::property_tree::ptree json;
			boost::property_tree::read_json(std::istringstream(jsonStr), json);
			for (auto it : json)
			{
				auto time = it.second.get<int>("t");
				auto car = it.second.get<std::string>("c");
				auto x = it.second.get<int>("x");
				auto y = it.second.get<int>("y");

				// TODO:  add data to mysql
				m_memDB->insert(car, x, y, time);
			}
		}
		catch (boost::exception & e)
		{
			BOOST_LOG_TRIVIAL(error) << "unable to decode json : " << jsonStr;
			BOOST_LOG_TRIVIAL(error) << boost::diagnostic_information(e);
			this->socket_.close();
			return;
		}

		// continue listening
		boost::asio::async_read_until(socket_,
			sbuf_,
			"\n",
			boost::bind(&session::handle_read,
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