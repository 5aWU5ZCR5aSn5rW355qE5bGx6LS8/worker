#include "checkerTest.h"

DataBase * m_memDB;

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

int main()
{
	m_memDB = new DataBase();

	loadTestData();
	
	for (auto & data : sorted)
	{
		m_memDB->insert(data.car, data.x, data.y, data.t);
	}

	cout << "data load finish" << endl;

	checker::Checker c;
	c.check();

	auto res = c.getResult();
	for (auto & i : res)
	{
		cout << i.car << "\t";
		if (i.reason&checker::REASON_DUP)
		{
			cout << "DUP ";
		}

		if (i.reason&checker::REASON_SPEED_LARGE)
		{
			cout << "FAST ";
		}

		if (i.reason&checker::REASON_SPEED_SMALL)
		{
			cout << "SLOW ";
		}

		cout << endl;
	}


	return 0;
}