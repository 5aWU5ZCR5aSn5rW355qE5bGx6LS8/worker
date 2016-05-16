#include "DataBase.h"
#include <algorithm>

memDB::DataBase::DataBase(const Record::TimePoint& initTime)
	:mSwapChain(mStorage), mCheckPoint(initTime)
{
}

bool memDB::DataBase::insert(std::string str, int x, int y, memDB::Record::TimePoint time)
{
	if (time - mCheckPoint > 3*TIME_INTERVAL) {
		return false;
	}

	auto pos = mStorage.emplace(
		std::piecewise_construct,
		std::forward_as_tuple(str),
		std::forward_as_tuple(x, y, time));

	if (time - mCheckPoint > 2*TIME_INTERVAL){
		mCheckPoint = time;
		mSwapChain.swap();
	}

	if (time  - mCheckPoint > TIME_INTERVAL){
		mSwapChain.front().add(pos);
	}
	else {
		mSwapChain.back().add(pos);
	}
	return true;
}

std::vector<memDB::Record> memDB::DataBase::selet(std::string str)
{
	std::vector<Record> result;
	std::vector<Record*> temp;
	Storage::iterator begin, end;
	std::tie(begin, end) = mStorage.equal_range(str);
	std::for_each(begin, end, [&](Storage::value_type& pair)
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
