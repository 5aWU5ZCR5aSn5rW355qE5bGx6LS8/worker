// memDB.cpp : Defines the exported functions for the static library.
//

#include "memDB.h"

#include <iostream>

#define MAX 200000

using namespace memDB;

typedef struct {  // ��¼5�����ڵ����м�¼
	Record rd[MAX * 10]; // record
}Record_Of_Five;

int idx = 0; // ������ڵļ�¼����
Record_Of_Five *rdf; // record_of_five
Record_Of_Five *rdfbk; //���ⱸ�ݵ�5����ָ��
map<int, string> mapstr; // �����ƺ� ӳ��Ϊ����
vector<Index> vec[MAX]; //���ݳ��ƺ��������ڼ�¼
map<string, vector<Index> > mapvec;
int term_five; // ��¼�ǵڼ��������


void init() {
	rdf = new Record_Of_Five();
	rdfbk = new Record_Of_Five();

	// ��ʼ�� map<int ,string> �� ���ƺź� ����ӳ��
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

	// ��ʼ�� map<string, vector>
	for (int i = 0; i < MAX; i++) {
		mapvec[mapstr[i]] = vec[i];
	}

}

bool insert(string str, int x, int y, int time)
{
	int term_five_tmp = time / 300;
	if (term_five_tmp != term_five) { // �жϵ�ǰ��5�����Ƿ�����
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