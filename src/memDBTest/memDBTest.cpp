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

<<<<<<< HEAD
//Global global;

int main()
{

    	Global *global = new Global();
	init(global);
=======
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


// åŽŸå§‹ç‰ˆæœ¬çš„memDBçš„æµ‹è¯•
void testOri()
{
	cout << "*********************" << endl;
	cout << "test for ori arg" << endl<< endl << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;

	start = std::chrono::system_clock::now();
	init();
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "init elapsed:" << elapsed_seconds.count() << "s " << endl;

	{
		start = std::chrono::system_clock::now();
		insert("A000001", 1, 1, 1);
		insert("A000002", 1, 1, 1);
		insert("A000001", 1, 1, 1);
		insert("A000001", 1, 1, 1);
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		cout << "insert small data elapsed:" << elapsed_seconds.count() << "s " << endl;
	}

	{
		start = std::chrono::system_clock::now();
		auto tmp = select("A000001");
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
			insert(r.car, r.x, r.y, r.t);
		}
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		cout << "big insert elapsed:" << elapsed_seconds.count() << "s " << endl;
	}


	{
		start = std::chrono::system_clock::now();
		auto tmp = select("A000099");
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

// æµ‹è¯•è–‡å„¿å†™çš„cppè§„èŒƒæ ‡å‡†çš„å†…å­˜æ•°æ®åº“
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
>>>>>>> origin/master

	{
		start = std::chrono::system_clock::now();
		auto tmp = db.selet("A000001");
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		cout << "query elapsed:" << elapsed_seconds.count() << "s " << endl;

<<<<<<< HEAD
	for (int i = 0; i < 200000; i++) {
		string car = global -> mapstr[i];
		//        cout << car << endl;
		for (int j = 0; j < 5; j++) { // ¹²²âÊÔ i.max * j.max ´ÎÊý¾Ý
			insert(global, car, j, 1, 1);
		}
	}
	cout << "the number of total insert£º " << global -> idx << endl;
=======
		cout << endl << "query result:" << endl;
		for (auto & car : tmp)
		{
			cout << "A000001" << " , " << car.posX << " , " << car.posY << " , " << car.time << endl;
		}
	}
>>>>>>> origin/master

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
		auto tmp = db.selet("A000099");
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


<<<<<<< HEAD
	vector<Index> tmp = select(global, "A000002");
=======
int main()
{
	loadTestData();
	testOri();
	testWeier();

>>>>>>> origin/master
	return 0;
}
