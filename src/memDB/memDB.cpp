// memDB.cpp : Defines the exported functions for the static library.
//

#include "memDB.h"

#include <iostream>

#define MAX 200000

using namespace memDB;

typedef struct {  // 记录5分钟内的所有记录
	Record rd[MAX * 10]; // record
}Record_Of_Five;

int idx = 0; // 五分钟内的记录索引
Record_Of_Five *rdf; // record_of_five
Record_Of_Five *rdfbk; //另外备份的5分钟指针
map<int, string> mapstr; // 将车牌号 映射为整形
vector<Index> vec[MAX]; //根据车牌号索引卡口记录
map<string, vector<Index> > mapvec;
int term_five; // 记录是第几个五分钟


void init() {
	rdf = new Record_Of_Five();
	rdfbk = new Record_Of_Five();

	// 初始化 map<int ,string> 将 车牌号和 整型映射
	char buf[10];
	for (int i = 0; i < MAX; i++)
	{
		int j = 1000000 + i + 1;
		sprintf(buf, "%d", j);
		string str = "A";
		for (int ii = 1; ii < 7; ii++)
			str += buf[ii];
		mapstr[i] = str;
	}

	// 初始化 map<string, vector>
	for (int i = 0; i < MAX; i++) {
		mapvec[mapstr[i]] = vec[i];
	}

}

bool insert(string str, int x, int y, int time)
{
	int term_five_tmp = time / 300;
	if (term_five_tmp != term_five) { // 判断当前的5分钟是否满了
		term_five = term_five_tmp;
		Record_Of_Five *tmp = rdf;
		rdf = rdfbk;
		rdfbk = tmp;
		idx = 0;
	}

	rdf->rd[idx++].addrd(str, x, y, time);
	Index index(time, idx - 1);
	mapvec[str].push_back(index);
	return true;
}


vector<Index> select(string car)
{
	vector<Index> tmp = mapvec[car];
	int len = tmp.size();
	for (int i = 0; i < len; i++) {
		cout << tmp[i].index;
	}
	return mapvec[car];
}