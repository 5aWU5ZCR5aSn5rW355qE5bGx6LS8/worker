#include "serverAddCarTest.h"

memDB::DataBase * m_memDB;

using namespace std;

void server()
{
	m_memDB = new memDB::DataBase();

	boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::endpoint m_endpoint(boost::asio::ip::tcp::v4(), 8889);

	try {
		serverAddCar::server m_serverAddCar(m_io_service, m_endpoint);
		cout << "server running" << endl;
		m_serverAddCar.run();
		cout << "server stop" << endl;
	}
	catch (boost::exception & e)
	{
		std::cerr << "OMG!" << boost::diagnostic_information(e);
		exit(-1);
	}
}


void client()
{
	std::this_thread::sleep_for(10min);
}

int main()
{
	std::thread t1(server);
	client();
	t1.detach();
	return 0;
}