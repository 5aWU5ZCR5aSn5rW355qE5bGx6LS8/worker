// memDB.cpp : Defines the exported functions for the static library.
//

#include "memDB.h"

#include <iostream>

#define MAX_RECORDS 2000000 /*区间内最大的记录条数*/
#define TIME_INTERVAL 300  /*时间判断区间*/



namespace memDB {

	class RecordPool {  // 记录5分钟内的所有记录
	public:
		vector<Record> records;
		
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

	bool inited = false;

	int maxTime = 0;

	map<string, vector<Index>> * carMapPtr = nullptr;
	map<string, vector<Index>> * carMapBkPtr = nullptr;

	RecordPool * recordPoolPtr = nullptr;
	RecordPool * recordPoolBkPtr = nullptr;


	void init() {
		if (inited)
		{
			cout << "memDB inited twice!" << endl;
			return;
		}
		else
		{
			inited = true;
		}

		// These codes are not safe
		carMapPtr = new map<string, vector<Index>>;
		carMapBkPtr = new map<string, vector<Index>>;

		recordPoolPtr = new RecordPool;
		recordPoolBkPtr = new RecordPool;
	}

	bool insert(string str, int x, int y, int time)
	{
		auto & carMap = *carMapPtr;
		auto & carMapBk = *carMapBkPtr;
		auto & recordPool = *recordPoolPtr;
		auto & recordPoolBk = *recordPoolBkPtr;

		if (time/TIME_INTERVAL - maxTime > 0) //本条记录时间更靠前
		{
			maxTime = time / TIME_INTERVAL;

			//These codes are not safe
			delete carMapBkPtr;
			delete recordPoolBkPtr;
			carMapBkPtr = carMapPtr;
			recordPoolBkPtr = recordPoolPtr;
			carMapPtr = new map<string, vector<Index>>;
			recordPoolPtr = new RecordPool;

			insert(str, x, y, time);
		}
		else if(time/TIME_INTERVAL - maxTime == 0) // 在当前池
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
	vector<Record> select(string str)
	{
		auto & carMap = *carMapPtr;
		auto & carMapBk = *carMapBkPtr;
		auto & recordPool = *recordPoolPtr;
		auto & recordPoolBk = *recordPoolBkPtr;

		auto car = carMap[str];
		auto carBk = carMapBk[str];

		auto res = vector<Record>();

		for (auto & rec : carBk)
		{
			res.push_back(Record(recordPoolBk.records[rec.index]));
		}

		for (auto & rec : car)
		{
			res.push_back(Record(recordPool.records[rec.index]));
		}

		return res;
	}
}

