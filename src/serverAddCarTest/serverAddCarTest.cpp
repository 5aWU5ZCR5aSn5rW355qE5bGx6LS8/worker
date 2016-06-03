#include "serverAddCarTest.h"


memDB::DataBase * m_memDB;

int main()
{
	m_memDB = new memDB::DataBase();

	boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::endpoint m_endpoint(boost::asio::ip::address::from_string("0.0.0.0"),8888);

	serverAddCar::server m_serverAddCar(m_io_service,m_endpoint);
	m_serverAddCar.run();
	return 0;
}