#pragma once


#include "../common/global.h"


namespace checker
{
	constexpr float MAX_SPEED = 60/3.6;
	constexpr float MIN_SPEED = 20/3.6;

	constexpr int REASON_SPEED_LARGE = 1;
	constexpr int REASON_SPEED_SMALL = 2;
	constexpr int REASON_DUP = 4;

	class Result
	{
	public:
		std::string car;
		int reason;

		Result(std::string car, int reason) :car(car), reason(reason) {};
	};

	class Checker
	{
	public:
		void check();
		std::vector<Result> getResult();
	private:
		std::vector<Result> result;
		inline float distant(int x1, int x2, int y1, int y2);
	};



}