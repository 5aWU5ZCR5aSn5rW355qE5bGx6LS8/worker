#include "RecordPool.h"
#include <algorithm>

memDB::detail::RecordPool::RecordPool()
	:mStorage(MIN_RECORDS), mCheckPoint(std::chrono::high_resolution_clock::now())
{
}

bool memDB::detail::RecordPool::insert(const std::string& str, int x, int y, const Record::TimePoint& time)
{
	if (time - mCheckPoint > 3 * TIME_INTERVAL) {
		return false;
	}

	auto pos = mStorage.emplace(
		std::piecewise_construct,
		std::forward_as_tuple(str),
		std::forward_as_tuple(x, y, time));

	if (time - mCheckPoint > 2 * TIME_INTERVAL) {
		swapBuffer();
		mCheckPoint = time;
	}

	if (time - mCheckPoint > TIME_INTERVAL) {
		mFrontCache.emplace_back(pos);
	}
	else {
		mBackCache.emplace_back(pos);
	}
	return true;
}

std::vector<memDB::detail::Record> memDB::detail::RecordPool::selet(const std::string& str)
{
	std::vector<Record> result;
	std::vector<Record*> temp;
	BackStorage::iterator begin, end;
	std::tie(begin, end) = mStorage.equal_range(str);
	std::for_each(begin, end, [&](BackStorage::value_type& pair)
	{
		temp.emplace_back(std::addressof(pair.second));
	});
	result.reserve(temp.size());
	for (auto pRecord : temp)
	{
		result.emplace_back(*pRecord);
	}
	return result;
}

void memDB::detail::RecordPool::swapBuffer()
{
	mBackCache.swap(mFrontCache);
	mBackCache.clear();
}
