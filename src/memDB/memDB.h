#pragma once

#include <vector>
#include <map>



namespace memDB {
	using namespace std;

	struct Index {
		int time;
		int index;

	public:
		Index(int time, int index) {
			this->time = time;
			this->index = index;
		}
	};


	struct Record {
		string car;
		int posx;
		int posy;
		int time;
		void addrd(string car, int x, int y, int time) {
			this->car = car;
			this->posx = x;
			this->posy = y;
			this->time = time;
		}
	};


	void init();
	bool insert(string str, int x, int y, int time);
	vector<Index> select(string car);

}



