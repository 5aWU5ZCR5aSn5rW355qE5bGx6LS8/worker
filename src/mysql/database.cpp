#include "database.h"



mysql::RecordBufferItem::RecordBufferItem(const std::string & car, int x, int y, int t):r(Record(x, y, t)),car(car)
{
}

mysql::DataBase::DataBase(const std::string & addr, const  std::string & name, const std::string & pwd, int maxBufferSize)
	:addr(addr),name(name),pwd(pwd),maxBufferSize(maxBufferSize)
{
	driver = sql::mysql::get_driver_instance();
	connect();
}

void mysql::DataBase::insert(std::string car, int x, int y, int t)
{
	lock.lock();

	RecordBufferItem rec(car,x,y,t);

	this->recordBuffer.push_back(rec);
	
	if (this->recordBuffer.size() >= this->maxBufferSize)
	{
		//std::thread t(&DataBase::commit,this);
		//t.detach();
		commit();
	}

	lock.unlock();
}

void mysql::DataBase::commit()
{
	//lock.lock();

	try {
		auto len = recordBuffer.size();
		for (int j = 0; j < len; j++)
		{
			auto i = *(recordBuffer.end()-1);

			prep_stmt_insert->setString(4 * j + 1, i.car);
			prep_stmt_insert->setInt(4 * j + 2, i.r.posX);
			prep_stmt_insert->setInt(4 * j + 3, i.r.posY);
			prep_stmt_insert->setInt(4 * j + 4, i.r.time);

			recordBuffer.pop_back();
		}

		prep_stmt_insert->execute();

		con->commit();
	}
	catch (sql::SQLException e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}

	//lock.unlock();
}

std::vector<Record> mysql::DataBase::select(std::string str)
{
	std::vector<Record> result;

	try {
		auto res = prep_stmt_check->executeQuery();
		delete res;
	}
	catch (sql::SQLException& e) {
		connect();
	}

	try {
		
		prep_stmt_select->setString(1, str);

		auto res = prep_stmt_select->executeQuery();
		while (res->next())
		{
			Record r(res->getInt(1), res->getInt(2), res->getInt(3));
			result.push_back(r);
		}
		delete res;
	}
	catch (sql::SQLException e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}

	return result;
}

void mysql::DataBase::connect()
{
	if (prep_stmt_insert != nullptr)
		delete prep_stmt_insert;

	if (prep_stmt_select != nullptr)
		delete prep_stmt_select;

	if (prep_stmt_check != nullptr)
		delete prep_stmt_check;

	if (con != nullptr) {
		delete con;
	}

	con = driver->connect(addr, name, pwd);
	con->setSchema("car");
	con->setAutoCommit(false);

	if (maxBufferSize <= 1)
	{
		throw "max buffer size max lager than 1";
	}


	for (int i = 1; i < maxBufferSize; i++)
	{
		insert_sql += ",(?,?,?,?)";
	}

	this->prep_stmt_insert = con->prepareStatement(insert_sql);
	this->prep_stmt_select = con->prepareStatement("SELECT x,y,t FROM car WHERE carid = ? ORDER BY t ASC");
	this->prep_stmt_check = con->prepareStatement("SELECT 1");
}