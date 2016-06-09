#include "serverAddCarTest.h"

memDB::DataBase * m_memDB;

using namespace std;

class row {
public:
	int x, y, t;
	string car;
	row(int x, int y, int t, string car) :x(x), y(y), t(t), car(car) {};
};

vector<row> raw;
vector<row> sorted;


void server()
{
	m_memDB = new memDB::DataBase();

	boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::endpoint m_endpoint(boost::asio::ip::tcp::v4(), 8889);

	try {
		serverAddCar::server m_serverAddCar(m_io_service, m_endpoint);
		cout << "server running" << endl;
		m_serverAddCar.run();
		cout << "server stop" << endl;
	}
	catch (boost::exception & e)
	{
		std::cerr << "OMG!" << boost::diagnostic_information(e);
		exit(-1);
	}
}


void client()
{
	std::this_thread::sleep_for(2s);
	cout << "test start !" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;

	//testEntire();
	// toooooo slooooow

	//start = std::chrono::system_clock::now();
	//testOne();
	//end = std::chrono::system_clock::now();
	//elapsed_seconds = end - start;
	//cout << "testOne elapsed:" << elapsed_seconds.count() << "s " << endl;


	start = std::chrono::system_clock::now();
	testGroup(9);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "testGroup 9 elapsed:" << elapsed_seconds.count() << "s " << endl;


	{
		start = std::chrono::system_clock::now();
		auto tmp = m_memDB->select("A000099");
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		cout << "query elapsed:" << elapsed_seconds.count() << "s " << endl;

		cout << endl << "query result:" << endl;
		for (auto & car : tmp)
		{
			cout << "A000099" << " , " << car.posX << " , " << car.posY << " , " << car.time << endl;
		}
	}


	start = std::chrono::system_clock::now();
	testGroup(11);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "testGroup 11 elapsed:" << elapsed_seconds.count() << "s " << endl;


	start = std::chrono::system_clock::now();
	testGroup(13);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "testGroup 13 elapsed:" << elapsed_seconds.count() << "s " << endl;


	start = std::chrono::system_clock::now();
	testGroup(17);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "testGroup 17 elapsed:" << elapsed_seconds.count() << "s " << endl;

	start = std::chrono::system_clock::now();
	testGroup(19);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "testGroup 19 elapsed:" << elapsed_seconds.count() << "s " << endl;


	start = std::chrono::system_clock::now();
	testGroup(21);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "testGroup 21 elapsed:" << elapsed_seconds.count() << "s " << endl;


	start = std::chrono::system_clock::now();
	testGroup(23);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "testGroup 23 elapsed:" << elapsed_seconds.count() << "s " << endl;

	start = std::chrono::system_clock::now();
	testGroup(25);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "testGroup 25 elapsed:" << elapsed_seconds.count() << "s " << endl;


	start = std::chrono::system_clock::now();
	testGroup(27);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "testGroup 27 elapsed:" << elapsed_seconds.count() << "s " << endl;


	start = std::chrono::system_clock::now();
	testGroup(297);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	cout << "testGroup 29 elapsed:" << elapsed_seconds.count() << "s " << endl;
}

// 所有的数据都放到一个巨大的json，因为太耗时，爆炸（
void testEntire()
{
	boost::asio::io_service ios;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8889);
	boost::asio::ip::tcp::socket socket(ios);
	socket.connect(endpoint);

	boost::property_tree::ptree json;
	for (auto i : raw)
	{
		boost::property_tree::ptree node;
		node.put("c", i.car);
		node.put("x", i.x);
		node.put("y", i.y);
		node.put("t", i.t);

		json.push_back(std::make_pair("", node));
	}
	std::ostringstream jsonStr;
	boost::property_tree::write_json(jsonStr, json, false);

	base64::base64 b;
	auto base64Str = b.base64_encode((const unsigned char *)jsonStr.str().c_str(), jsonStr.str().length());
	base64Str += "\n";
	socket.write_some(boost::asio::buffer(base64Str.c_str(), base64Str.size()));

	socket.close();
}

//一次只测试一个数据
void testOne()
{
	boost::asio::io_service ios;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8889);
	boost::asio::ip::tcp::socket socket(ios);
	socket.connect(endpoint);
	
	for (auto i : raw)
	{
		boost::property_tree::ptree json;

		boost::property_tree::ptree node;
		node.put("c", i.car);
		node.put("x", i.x);
		node.put("y", i.y);
		node.put("t", i.t);

		json.push_back(std::make_pair("", node));

		std::ostringstream jsonStr;
		boost::property_tree::write_json(jsonStr, json, false);

		base64::base64 b;
		auto base64Str = b.base64_encode((const unsigned char *)jsonStr.str().c_str(), jsonStr.str().length());
		base64Str += "\n";
		socket.write_some(boost::asio::buffer(base64Str.c_str(), base64Str.size()));

	}
	socket.close();
}

void testGroup(int groupSize)
{
	boost::asio::io_service ios;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8889);
	boost::asio::ip::tcp::socket socket(ios);
	socket.connect(endpoint);

	boost::property_tree::ptree json;

	int j = 0;
	for (auto i : raw)
	{
		j++;

		boost::property_tree::ptree node;
		node.put("c", i.car);
		node.put("x", i.x);
		node.put("y", i.y);
		node.put("t", i.t);

		json.push_back(std::make_pair("", node));

		if (j > groupSize)
		{
			j = 0;
			std::ostringstream jsonStr;
			boost::property_tree::write_json(jsonStr, json, false);

			base64::base64 b;
			auto base64Str = b.base64_encode((const unsigned char *)jsonStr.str().c_str(), jsonStr.str().length());
			base64Str += "\n";
			socket.write_some(boost::asio::buffer(base64Str.c_str(), base64Str.size()));
			
			json.clear();
		}
	}
	socket.close();
}



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
	loadTestData();
	cout << "test data load finish!" << endl;

	std::thread t1(server);
	client();
	t1.detach();

	cout << "test done" << endl;

	return 0;
}