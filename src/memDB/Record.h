#pragma once

#include <string>

namespace memDB
{
	struct Record
	{
		using TimePoint = int;
		int posX;
		int posY;
		TimePoint time;
		Record(int x, int y, TimePoint t)
			:posX(x), posY(y), time(t)
		{

		}
	};
}