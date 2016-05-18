#pragma once

#include <string>

namespace memDB
{
	struct RecordW
	{
		using TimePoint = int;
		int posX;
		int posY;
		TimePoint time;
		RecordW(int x, int y, TimePoint t)
			:posX(x), posY(y), time(t)
		{

		}
	};
}