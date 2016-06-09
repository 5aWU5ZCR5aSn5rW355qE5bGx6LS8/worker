#pragma once

#include <string>
#include <vector>

#include "../common/Record.h"

namespace mysql
{
	class DataBase
	{
		std::string addr;
		std::string name;
		std::string pwd;

		int maxBufferSize;

		std::vector<Record> recordBuffer;
	public:
		DataBase(const std::string & addr, const  std::string & name, const std::string & pwd, int maxBufferSize = 10);
		void insert(std::string car, int x, int y, int t);
		std::vector<Record> select(std::string str);
	};
}