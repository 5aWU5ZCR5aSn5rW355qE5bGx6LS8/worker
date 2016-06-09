#pragma once

#include <string>
#include <vector>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <cppconn/prepared_statement.h>

#include "../common/Record.h"
#include "recordBufferItem.h"
#include <mutex>
#include <thread>


namespace mysql
{

	class DataBase
	{
		std::string addr;
		std::string name;
		std::string pwd;

		std::mutex lock;

		sql::Driver *driver;
		sql::Connection *con;

		sql::PreparedStatement * prep_stmt_insert;
		sql::PreparedStatement * prep_stmt_select;

		int maxBufferSize;

		std::vector<RecordBufferItem> recordBuffer;

		void commit();
	public:
		DataBase(const std::string & addr, const  std::string & name, const std::string & pwd, int maxBufferSize = 10);
		void insert(std::string car, int x, int y, int t);
		std::vector<Record> select(std::string str);
	};

	
}