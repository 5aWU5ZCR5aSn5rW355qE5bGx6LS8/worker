#include "mysqlTest.h"

using namespace std;

string addr,name,pwd;

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

int main()
{
	addr = "tcp://127.0.0.1:3306";
	cout << "name:" << endl;
	cin >> name ;
	cout << "password:" << endl;
	cin >> pwd;

	cout << "start loading test data" << endl;
	loadTestData();
	cout << "test data loaded" << endl;

	mysql::DataBase db(addr, name, pwd,40);
	cout << "mysql connected" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;

	start = std::chrono::system_clock::now();
	for (auto & i : raw)
	{
		db.insert(i.car, i.x, i.y, i.t);
	}
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "insert data elapsed:" << elapsed_seconds.count() << "s " << endl;

	start = std::chrono::system_clock::now();
	auto res = db.select("A000099");
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "query elapsed:" << elapsed_seconds.count() << "s " << endl;

	cout << endl << "query result:" << endl;
	for (auto & car : res)
	{
		cout << "A000099" << " , " << car.posX << " , " << car.posY << " , " << car.time << endl;
	}

	return 0;
}