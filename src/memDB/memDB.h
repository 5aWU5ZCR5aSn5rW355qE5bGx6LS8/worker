#pragma once

#include <vector>
#include <map>
#include <set>
#include "../common/Record.h"




namespace memDB {
	namespace ori {

		constexpr int MAX_RECORDS = 2000000; /*区间内最大的记录条数*/
		constexpr int TIME_INTERVAL = 300;  /*时间判断区间*/

		class RecordPool {  // 记录5分钟内的所有记录
		public:
			std::vector<Record> records;

			RecordPool() {
				records.reserve(MAX_RECORDS);
			}
		};

		class Index {
		public:
			int time;
			int index;

			Index(int time, int index) :time(time), index(index) {}
		};


		class DataBase
		{
			bool inited = false;
			int maxTime = 0;

			std::map<std::string, std::vector<Index>> * carMapPtr = nullptr;
			std::map<std::string, std::vector<Index>> * carMapBkPtr = nullptr;

			RecordPool * recordPoolPtr = nullptr;
			RecordPool * recordPoolBkPtr = nullptr;

		public:
			DataBase();
			bool insert(std::string str, int x, int y, int time);
			std::vector<Record> select(std::string str);
			std::set<std::string> list();
		};
	}
}



