#pragma once
#include "../common/Record.h"
#include "RecordPool.h"
#include "SwapChain.h"
#include <unordered_map>
#include <string>
#include <set>

namespace memDB
{
	class DataBase
	{
		static constexpr const size_t MAX_RECORDS = 2000000;
		static constexpr const int TIME_INTERVAL = 300;
		using Storage = std::unordered_multimap<std::string/*car name*/, Record>;
		Storage mStorage;
		SwapChain<RecordPool<Storage, MAX_RECORDS>> mSwapChain;
		Record::TimePoint mMaxTime;
	public:
		DataBase();
		~DataBase() = default;
		bool insert(std::string str, int x, int y, int time);
		std::vector<Record> select(std::string str);
		std::set<std::string> list();
	};

}