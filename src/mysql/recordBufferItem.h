#pragma once
#include <string>

namespace mysql
{
	class RecordBufferItem
	{
	public:
		std::string car;
		Record r;

		RecordBufferItem(const std::string & car, int x, int y, int t);
	};

}
