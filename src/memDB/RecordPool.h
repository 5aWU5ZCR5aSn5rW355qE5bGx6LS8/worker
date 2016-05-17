#ifndef RECORDPOOL_H
#define RECORDPOOL_H

#include "Record.h"
#include <deque>
#include <memory>
#include <unordered_map>

namespace memDB
{
	namespace detail
	{
		class RecordPool
		{
			using BackStorage = std::unordered_multimap<std::string/*car name*/, Record>;
			using RecordIterator = typename BackStorage::iterator;
			using CacheTable = std::deque<RecordIterator>;

			static constexpr const size_t MIN_RECORDS = 2000000;
			static constexpr const auto TIME_INTERVAL = std::chrono::minutes(5);

			BackStorage mStorage;
			CacheTable mFrontCache;
			CacheTable mBackCache;
			std::chrono::high_resolution_clock::time_point mCheckPoint;
		public:
			RecordPool();

			~RecordPool() = default;

			bool insert(const std::string& str, int x, int y, const Record::TimePoint& time);
			std::vector<Record> selet(const std::string& str);

		private:
			void swapBuffer();
		};
	}
}

#endif