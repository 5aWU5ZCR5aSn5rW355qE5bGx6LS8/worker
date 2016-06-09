#include "database.h"

#include <mysql_connection.h>

mysql::DataBase::DataBase(const std::string & addr, const  std::string & name, const std::string & pwd, int maxBufferSize = 10)
{
	this->addr = addr;
	this->name = name;
	this->pwd = pwd;
	this->maxBufferSize = maxBufferSize;
}

void mysql::DataBase::insert(std::string car, int x, int y, int t)
{

}

std::vector<Record> mysql::DataBase::select(std::string str)
{
	std::vector<Record> result;

	return result;
}