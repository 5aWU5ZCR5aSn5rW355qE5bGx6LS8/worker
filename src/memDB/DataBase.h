#pragma once
#include "Record.h"
#include "RecordPool.h"
#include "SwapChain.h"
#include <unordered_map>
#include <string>

namespace memDB
{
	class DataBase
	{
		static constexpr const size_t MAX_RECORDS = 2000000;
		static constexpr const int TIME_INTERVAL = 300;
		using Storage = std::unordered_multimap<std::string/*car name*/, RecordW>;
		Storage mStorage;
		SwapChain<RecordPool<Storage, MAX_RECORDS>> mSwapChain;
		RecordW::TimePoint mMaxTime;
	public:
		DataBase();
		~DataBase() = default;
		bool insert(std::string str, int x, int y, int time);
		std::vector<RecordW> selet(std::string str);
	};

}