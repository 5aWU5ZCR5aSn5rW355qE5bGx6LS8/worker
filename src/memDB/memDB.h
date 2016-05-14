#pragma once

#include <vector>
#include <map>
#define MAX 200000


namespace memDB {
	using namespace std;

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

	struct Record_Of_Five{  // 记录5分钟内的所有记录
		Record rd[MAX * 10]; // record
	};

	struct Index {
		int time;
		int index;

	public:
		Index(int time, int index) {
			this->time = time;
			this->index = index;
		}
	};


	struct Global{

    		int idx = 0; // 五分钟内的记录索引
    		Record_Of_Five *rdf; // record_of_five
    		Record_Of_Five *rdfbk; //另外备份的5分钟指针
    		map<int, string> mapstr; // 将车牌号 映射为整形
    		vector<Index> vec[MAX]; //根据车牌号索引卡口记录
    		map<string, vector<Index> > mapvec; // 为每辆车创建一个vector，存放它经过卡口的记录的索引
    		int term_five; // 记录是第几个五分钟
	};

	


	void init(Global &global);
	bool insert(Global &global, string str, int x, int y, int time);
	vector<Index> select(Global &global, string car);

}



