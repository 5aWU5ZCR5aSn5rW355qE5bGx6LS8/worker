#include "worker.h"

using namespace std;

Ini ini("../conf/conf.ini");

int main(int argc,char *argv[])
{
	try
	{
		try
		{
			init();

			thread threadCar(threadServerCar);
			thread threadWorker(threadServerWorker);

			threadCar.detach();
			threadWorker.detach();

			try
			{
				SignalHandler signalHandler;

				// Register signal handler to handle kill signal
				signalHandler.setupSignalHandlers();

				// Infinite loop until signal ctrl-c (KILL) received
				while (!signalHandler.gotExitSignal())
				{
					std::this_thread::sleep_for(1s);
				}
			}
			catch (SignalException& e)
			{
				std::cerr << "SignalException: " << e.what() << std::endl;
			}
		}
		catch(boost::exception_ptr & e)
		{
			BOOST_LOG_TRIVIAL(fatal) << "boost fatal" <<  boost::diagnostic_information(e);
			exit(-1);
		}
	}
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "unknown fatal in main thread";
		exit(-1);
	}

	return 0;
	
}

void init()
{
	boost::log::core::get()->add_global_attribute("TimeStamp", boost::log::attributes::utc_clock());

	if (ini.getInt("log.file") != -1)
	{
		boost::log::add_file_log(
			boost::log::keywords::file_name = ini.get("log.path"),
			boost::log::keywords::format = "[%TimeStamp%]: %Message%"
		);
	}

	if (ini.getInt("log.display") != -1)
	{
		boost::log::add_console_log(
			std::cout,
			boost::log::keywords::format = "[%TimeStamp%]: %Message%"
		);
	}

	if (ini.get("log.level") != "")
	{
		if (ini.get("log.level") == "info")
		{
			boost::log::core::get()->set_filter
			(
				boost::log::trivial::severity >= boost::log::trivial::info
			);
		}
		else if (ini.get("log.level") == "warning")
		{
			boost::log::core::get()->set_filter
			(
				boost::log::trivial::severity >= boost::log::trivial::warning
			);
		}
		else if (ini.get("log.level") == "error")
		{
			boost::log::core::get()->set_filter
			(
				boost::log::trivial::severity >= boost::log::trivial::error
			);
		}
		else if (ini.get("log.level") == "fatal")
		{
			boost::log::core::get()->set_filter
			(
				boost::log::trivial::severity >= boost::log::trivial::fatal
			);
		}
	}

	auto mysql_addr = ini.get("mysql.addr");
	auto mysql_name = ini.get("mysql.name");
	auto mysql_pass = ini.get("mysql.pwd");
	auto mysql_buffer = ini.getInt("mysql.buffer");

	if (mysql_addr == "" || mysql_name == "" || mysql_pass == "")
	{
		BOOST_LOG_TRIVIAL(fatal) << "no mysql info";
		exit(-1);
	}

	if (mysql_buffer == -1)
	{
		mysql_buffer = 64;
	}

	m_memDB = new DataBase();

	try
	{
		m_mysqlDB = new mysql::DataBase(mysql_addr, mysql_name, mysql_pass, mysql_buffer);
	}
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "cannot connect to mysql";
		exit(-1);
	}
	
	
}


void threadServerCar()
{
	try
	{
		try
		{
			auto portCar = ini.getInt("car.port");
			if (portCar == -1)
				portCar = 8889;

			boost::asio::io_service m_io_service;
			boost::asio::ip::tcp::endpoint m_endpoint(boost::asio::ip::tcp::v4(), portCar);

			auto m_serverCar = serverAddCar::server(m_io_service, m_endpoint);

			m_serverCar.run();
		}
		catch (boost::exception_ptr & e)
		{
			BOOST_LOG_TRIVIAL(fatal) << "boost fatal" << boost::diagnostic_information(e);
			exit(-1);
		}
	}
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "unknown fatal in car thread";
		exit(-1);
	}
}

void threadServerWorker()
{
	try
	{
		try
		{
			auto portWorker = ini.getInt("worker.port");

			if (portWorker == -1)
				portWorker = 8900;

			boost::asio::io_service m_io_service;
			boost::asio::ip::tcp::endpoint m_endpoint(boost::asio::ip::tcp::v4(), portWorker);

			auto m_serverWorker = serverWorker::server(m_io_service, m_endpoint);

			m_serverWorker.run();
		}
		catch (boost::exception_ptr & e)
		{
			BOOST_LOG_TRIVIAL(fatal) << "boost fatal" << boost::diagnostic_information(e);
			exit(-1);
		}
	}
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "unknown fatal in worker thread";
		exit(-1);
	}
}