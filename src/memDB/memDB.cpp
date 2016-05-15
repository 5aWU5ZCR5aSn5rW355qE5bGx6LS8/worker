// memDB.cpp : Defines the exported functions for the static library.
//

#include "memDB.h"

#include <iostream>



using namespace memDB;

void memDB::init(Global *global) {
	global -> rdf = new Record_Of_Five();
	global -> rdfbk = new Record_Of_Five();

	// 初始化 map<int ,string> 将 车牌号和 整型映射
	char buf[10];
	for (int i = 0; i < MAX; i++)
	{
		int j = 1000000 + i + 1;
		sprintf(buf, "%d", j);
		string str = "A";
		for (int ii = 1; ii < 7; ii++)
			str += buf[ii];
		global -> mapstr[i] = str;
	}

	// 初始化 map<string, vector>
	for (int i = 0; i < MAX; i++) {
		global -> mapvec[(global -> mapstr)[i]] = (global -> vec)[i];
	}

}

bool memDB::insert(Global *global, string str, int x, int y, int time)
{
	int term_five_tmp = time / 300;
	if (term_five_tmp != global -> term_five) { // 判断当前的5分钟是否满了
		global -> term_five = term_five_tmp;
		Record_Of_Five *tmp = global -> rdf;
		global -> rdf = global -> rdfbk;
		global -> rdfbk = tmp;
		global -> idx = 0;
	}

	global -> rdf->rd[(global -> idx)++].addrd(str, x, y, time);
	Index index(time, global -> idx - 1);
	global -> mapvec[str].push_back(index);
	return true;
}
vector<Index> memDB::select(Global *global, string car)
{
	vector<Index> tmp = global -> mapvec[car];
	int len = tmp.size();
	for (int i = 0; i < len; i++) {
		cout << tmp[i].index;
	}
	return global -> mapvec[car];
}
