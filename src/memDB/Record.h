#pragma once

#include <string>
#include <chrono>

namespace memDB
{
	struct Record
	{
		using TimePoint = std::chrono::high_resolution_clock::time_point;
		int posX;
		int posY;
		TimePoint time;
		Record(int x, int y, TimePoint t)
			:posX(x), posY(y), time(t)
		{

		}
	};
}