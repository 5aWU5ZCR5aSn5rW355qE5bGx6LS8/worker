#include "memDBTest.h"
#include "../common/csvReader.h"

using namespace memDB;
using namespace std;

class row {
public:
	int x, y, t;
	string car;
	row(int x, int y, int t, string car) :x(x), y(y), t(t), car(car) {};
};

vector<row> raw;
vector<row> sorted;




void loadTestData()
{
	ifstream fileRaw("testRaw.csv");
	ifstream fileSort("testSorted.csv");

	if (!fileRaw.is_open() || !fileSort.is_open()) 
	{
		cout << "error to load test data";
		exit(-1);
	}

	CSVIterator loopRaw(fileRaw);
	for (++loopRaw; loopRaw != CSVIterator(); ++loopRaw)
	{
		raw.push_back(row(stoi((*loopRaw)[2]), stoi((*loopRaw)[3]), stoi((*loopRaw)[1]), (*loopRaw)[0]));
	}

	CSVIterator loopSort(fileSort);
	for (++loopSort; loopSort != CSVIterator(); ++loopSort)
	{
		sorted.push_back(row(stoi((*loopSort)[2]), stoi((*loopSort)[3]), stoi((*loopSort)[1]), (*loopSort)[0]));
	}

	fileRaw.close();
	fileSort.close();
}


// 原始版本的memDB的测试
void testOri()
{
	cout << "*********************" << endl;
	cout << "test for ori arg" << endl<< endl << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;

	start = std::chrono::system_clock::now();
	ori::init();
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "init elapsed:" << elapsed_seconds.count() << "s " << endl;

	{
		start = std::chrono::system_clock::now();
		ori::insert("A000001", 1, 1, 1);
		ori::insert("A000002", 1, 1, 1);
		ori::insert("A000001", 1, 1, 1);
		ori::insert("A000001", 1, 1, 1);
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		cout << "insert small data elapsed:" << elapsed_seconds.count() << "s " << endl;
	}

	{
		start = std::chrono::system_clock::now();
		auto tmp = ori::select("A000001");
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		cout << "query elapsed:" << elapsed_seconds.count() << "s " << endl;

		cout << endl << "query result:" << endl;
		for (auto & car : tmp)
		{
			cout << "A000001" << " , " << car.posx << " , " << car.posy << " , " << car.time << endl;
		}
	}

	{
		start = std::chrono::system_clock::now();
		for (auto & r : raw)
		{
			ori::insert(r.car, r.x, r.y, r.t);
		}
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		cout << "big insert elapsed:" << elapsed_seconds.count() << "s " << endl;
	}


	{
		start = std::chrono::system_clock::now();
		auto tmp = ori::select("A000099");
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		cout << "query elapsed:" << elapsed_seconds.count() << "s " << endl;

		cout << endl << "query result:" << endl;
		for (auto & car : tmp)
		{
			cout << "A000099" << " , " << car.posx << " , " << car.posy << " , " << car.time << endl;
		}
	}
	
}

// 测试薇儿写的cpp规范标准的内存数据库
void testWeier()
{
	cout << "*********************" << endl;
	cout << "test for weier's arg" << endl << endl << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;

	start = std::chrono::system_clock::now();
	DataBase db;
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "init elapsed:" << elapsed_seconds.count() << "s " << endl;

	{
		start = std::chrono::system_clock::now();
		db.insert("A000001", 1, 1, 1);
		db.insert("A000002", 1, 1, 1);
		db.insert("A000001", 1, 1, 1);
		db.insert("A000001", 1, 1, 1);
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		cout << "insert small data elapsed:" << elapsed_seconds.count() << "s " << endl;
	}

	{
		start = std::chrono::system_clock::now();
		auto tmp = db.select("A000001");
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		cout << "query elapsed:" << elapsed_seconds.count() << "s " << endl;


		cout << endl << "query result:" << endl;
		for (auto & car : tmp)
		{
			cout << "A000001" << " , " << car.posX << " , " << car.posY << " , " << car.time << endl;
		}
	}


	{
		start = std::chrono::system_clock::now();
		for (auto & r : raw)
		{
			db.insert(r.car, r.x, r.y, r.t);
		}
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		cout << "big insert elapsed:" << elapsed_seconds.count() << "s " << endl;
	}

	{
		start = std::chrono::system_clock::now();
		auto tmp = db.select("A000099");
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		cout << "query elapsed:" << elapsed_seconds.count() << "s " << endl;

		cout << endl << "query result:" << endl;
		for (auto & car : tmp)
		{
			cout << "A000099" << " , " << car.posX << " , " << car.posY << " , " << car.time << endl;
		}
	}
}



int main()
{
	loadTestData();
	testOri();
	testWeier();

	return 0;
}
