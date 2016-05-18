#pragma once

#include <vector>
#include <map>



namespace memDB {
	namespace ori {
		using namespace std;

		struct Record {
			int posx;
			int posy;
			int time;

			Record(int x, int y, int time) :posx(x), posy(y), time(time) {}
		};

		void init();
		bool insert(string str, int x, int y, int time);
		vector<Record> select(string str);
	}
}



