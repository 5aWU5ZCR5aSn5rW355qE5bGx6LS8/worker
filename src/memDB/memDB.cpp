// memDB.cpp : Defines the exported functions for the static library.
//

#include "memDB.h"

#include <iostream>
#include <algorithm>




namespace memDB {
	namespace ori {


		DataBase::DataBase()
		{
			carMapPtr = new std::map<std::string, std::vector<Index>>;
			carMapBkPtr = new std::map<std::string, std::vector<Index>>;

			recordPoolPtr = new RecordPool;
			recordPoolBkPtr = new RecordPool;
		}

		bool DataBase::insert(std::string str, int x, int y, int time)
		{
			auto & carMap = *carMapPtr;
			auto & carMapBk = *carMapBkPtr;
			auto & recordPool = *recordPoolPtr;
			auto & recordPoolBk = *recordPoolBkPtr;

			if (time / TIME_INTERVAL - maxTime > 0) //本条记录时间更靠前
			{
				maxTime = time / TIME_INTERVAL;

				//These codes are not safe
				delete carMapBkPtr;
				delete recordPoolBkPtr;
				carMapBkPtr = carMapPtr;
				recordPoolBkPtr = recordPoolPtr;
				carMapPtr = new std::map<std::string, std::vector<Index>>;
				recordPoolPtr = new RecordPool;

				insert(str, x, y, time);
			}
			else if (time / TIME_INTERVAL - maxTime == 0) // 在当前池
			{
				auto & car = carMap[str];

				recordPool.records.push_back(Record(x, y, time));
				car.push_back(Index(time, recordPool.records.size() - 1));
			}
			else if (time / TIME_INTERVAL - maxTime == -1) // 在备份池
			{
				auto & car = carMapBk[str];

				recordPoolBk.records.push_back(Record(x, y, time));
				car.push_back(Index(time, recordPoolBk.records.size() - 1));
			}
			else //记录过早，丢弃
			{
				return false;
			}
			return true;
		}
		std::vector<Record> DataBase::select(std::string str)
		{
			auto & carMap = *carMapPtr;
			auto & carMapBk = *carMapBkPtr;
			auto & recordPool = *recordPoolPtr;
			auto & recordPoolBk = *recordPoolBkPtr;

			auto car = carMap[str];
			auto carBk = carMapBk[str];

			auto res = std::vector<Record>();

			for (auto & rec : carBk)
			{
				res.push_back(Record(recordPoolBk.records[rec.index]));
			}

			for (auto & rec : car)
			{
				res.push_back(Record(recordPool.records[rec.index]));
			}

			std::sort(res.begin(), res.end(), [](auto i, auto j) {return i.time < j.time; });

			return res;
		}

		std::set<std::string> DataBase::list()
		{
			std::set<std::string> result;

			for (auto i : *carMapPtr)
			{
				result.insert(i.first);
			}

			for (auto i : *carMapBkPtr)
			{
				result.insert(i.first);
			}

			return result;
		}
	}

}

