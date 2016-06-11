#include "checker.h"

void checker::Checker::check()
{
	this->result.clear();

	auto list = m_memDB->list();
	for (auto & c : list)
	{
		auto route = m_memDB->select(c);
		
		auto i = route.begin();
		auto j = route.begin();
		j++;
		auto end = route.end();

		for (; j != end; i++, j++)
		{
			auto t = j->time - i->time;
			auto dis = distant(j->posX, i->posX, j->posY, i->posY);

			if (t == 0)
			{
				result.push_back(Result(c, REASON_DUP));
				break;
			}

			auto speed = dis / t;

			if (speed > MAX_SPEED)
			{
				result.push_back(Result(c, REASON_SPEED_LARGE));
				break;
			}

			if (speed < MIN_SPEED)
			{
				result.push_back(Result(c, REASON_SPEED_SMALL));
				break;
			}
		}
	}
}

std::vector<checker::Result> checker::Checker::getResult()
{
	return this->result;
}


inline float checker::Checker::distant(int x1, int x2, int y1, int y2)
{
	auto deltaX = x1 - x2;
	deltaX = deltaX >= 0 ? deltaX : -deltaX;

	auto deltaY = y1 - y2;
	deltaY = deltaY >= 0 ? deltaY : -deltaY;

	return deltaX + deltaY;
}