#include "DataBase.h"
#include <algorithm>

memDB::DataBase::DataBase()
	:mSwapChain(mStorage), mMaxTime(0)
{

}

bool memDB::DataBase::insert(std::string str, int x, int y, int time)
{
	if (time / TIME_INTERVAL - mMaxTime < -1) {
		return false;
	}

	auto pos = mStorage.emplace(
		std::piecewise_construct,
		std::forward_as_tuple(str),
		std::forward_as_tuple(x, y, time));

	if (time / TIME_INTERVAL - mMaxTime > 0){
		mMaxTime = time / TIME_INTERVAL;
		mSwapChain.swap();
	}

	if (time / TIME_INTERVAL - mMaxTime == 0){
		mSwapChain.front().add(pos);
	}
	else {
		mSwapChain.back().add(pos);
	}
	return true;
}

std::vector<Record> memDB::DataBase::select(std::string str)
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


std::set<std::string> memDB::DataBase::list()
{
	std::set<std::string> result;

	for (auto it = mStorage.begin(); it != mStorage.end(); it++)
	{
		result.insert(it->first);
	}

	return result;
}