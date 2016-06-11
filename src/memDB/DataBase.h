#pragma once
#include "memDB.h"
#include "../common/Record.h"
#include "RecordPool.h"
#include "SwapChain.h"
#include <unordered_map>
#include <string>
#include <deque>
#include <set>

namespace memDB
{
	class DataBase
	{
		static constexpr const size_t MAX_RECORDS = 2000000;
		static constexpr const int TIME_INTERVAL = 300;
		static constexpr const size_t BUFFER_COUNT = 2;
		using Dictionary = std::unordered_multimap<std::string/*Car ID*/, Record>;
		using Storage = std::deque<Dictionary>;
		Record::TimePoint mMaxTime;
		Storage mStorage;

	private:
		void pushNewBuffer(size_t count);
		void popTopBuffer(size_t count);

	public:
		DataBase();
		~DataBase() = default;
		bool insert(const std::string& str, int x, int y, int time);
		std::vector<Record> select(const std::string& str);
		std::set<std::string> list();
	};

}