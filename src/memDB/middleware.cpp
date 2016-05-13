#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include<time.h>
using namespace std;
#define MAX 200000

struct Index{ // 卡口每次的记录索引
    int time;
    int index;

public:
    Index(int time, int index){
        this -> time = time;
        this -> index = index;
    }
};

struct Record { // 卡口每次记录的数据类型
    string car;
    int posx;
    int posy;
    int time;
    void addrd(string car, int x, int y, int time){
        this -> car = car;
        this -> posx = x;
        this -> posy = y;
        this -> time = time;
    }
};

typedef struct {  // 记录5分钟内的所有记录
    Record rd[MAX * 10]; // record
}Record_Of_Five;

struct Global{

    int idx = 0; // 五分钟内的记录索引
    Record_Of_Five *rdf; // record_of_five
    Record_Of_Five *rdfbk; //另外备份的5分钟指针
    map<int, string> mapstr; // 将车牌号 映射为整形
    vector<Index> vec[MAX]; //根据车牌号索引卡口记录
    map<string, vector<Index> > mapvec; // 为每辆车创建一个vector，存放它经过卡口的记录的索引
    int term_five; // 记录是第几个五分钟
};


void init(Global &global){
    global.rdf = new Record_Of_Five();
    global.rdfbk = new Record_Of_Five();

    // 初始化 map<int ,string> 将 车牌号和 整型映射
    char buf[10];
    for(int i = 0; i < MAX; i++)
    {
        int j = 1000000 + i + 1;
        sprintf(buf, "%d", j);
        string str = "A";
        for(int ii = 1; ii < 7; ii++)
            str += buf[ii];
        global.mapstr[i] = str;
    }

    // 初始化 map<string, vector>
    for(int i = 0; i < MAX; i++){
        global.mapvec[(global.mapstr)[i]] = (global.vec)[i];
    }

}

bool insert(Global &global, string str, int x, int y, int time)
{
    int term_five_tmp = time / 300;
    if(term_five_tmp != global.term_five){ // 判断当前的5分钟是否满了
        global.term_five = term_five_tmp;
        Record_Of_Five *tmp = global.rdf;
        global.rdf = global.rdfbk;
        global.rdfbk = tmp;
        global.idx = 0;
    }

    global.rdf -> rd[(global.idx)++].addrd(str, x, y, time);
    Index index(time, global.idx - 1);
    global.mapvec[str].push_back(index);
    return true;
}
vector<Index> select(Global &global, string car)
{
    vector<Index> tmp = global.mapvec[car];
    int len = tmp.size();
    for(int i = 0; i < len; i++){
        cout << tmp[i].index;
    }
    return global.mapvec[car];
}
