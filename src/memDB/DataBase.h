#pragma once
#include "Record.h"
#include "RecordPool.h"
#include "SwapChain.h"
#include <unordered_map>
#include <string>
#include <chrono>

namespace memDB
{
	class DataBase
	{
		using namespace std::chrono::literals;
		static constexpr const size_t MAX_RECORDS = 2000000;
		static constexpr const auto TIME_INTERVAL = 5min;
		using Storage = std::unordered_multimap<std::string/*car name*/, Record>;
		Storage mStorage;
		SwapChain<RecordPool<Storage, MAX_RECORDS>> mSwapChain;
		Record::TimePoint mCheckPoint;
	public:
		DataBase();
		~DataBase() = default;
		bool insert(std::string str, int x, int y, Record::TimePoint time);
		std::vector<Record> selet(std::string str);
	};

}