#include "DataBase.h"
#include <algorithm>
#include <numeric>
#include <iostream>

void memDB::DataBase::pushNewBuffer(size_t count)
{
	for (size_t k = 0; k < count; ++k) {
		mStorage.emplace_front();
		mStorage.front().reserve(MAX_RECORDS);
	}
}

void memDB::DataBase::popTopBuffer(size_t count)
{
	for (size_t k = 0; k < count; ++k) {
		mStorage.pop_back();
	}
}
memDB::DataBase::DataBase()
	:mMaxTime(0)
{
	pushNewBuffer(BUFFER_COUNT);
}

bool memDB::DataBase::insert(const std::string& str, int x, int y, int time)
{
	if (time / TIME_INTERVAL - mMaxTime > 0) {
		mMaxTime = time / TIME_INTERVAL;
		pushNewBuffer(1);
		popTopBuffer(1);
	}

	auto insertTo = [&](Dictionary& map)
	{
		map.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(str),
			std::forward_as_tuple(x, y, time));
	};

	if (time / TIME_INTERVAL - mMaxTime == 0) {
		insertTo(mStorage[0]);
	}
	else if (time / TIME_INTERVAL - mMaxTime == -1) {
		insertTo(mStorage[1]);
	}
	else {
		return false;
	}
	return true;
}

std::vector<Record> memDB::DataBase::select(const std::string& str)
{
	//scan for entries
	std::vector<Record*> temp;
	{
		Dictionary::iterator begin, end;
		for (auto& dic : mStorage) {
			std::tie(begin, end) = dic.equal_range(str);
			std::for_each(begin, end, [&](Dictionary::value_type& pair)
			{
				temp.emplace_back(std::addressof(pair.second));
			});
		}
	}

	//Copy result
	std::vector<Record> result;
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

	for (auto& dic : mStorage) {
		for (auto i = dic.begin(); i != dic.end(); i++)
		{
			result.insert(i->first);
		}
	}

	return result;
}