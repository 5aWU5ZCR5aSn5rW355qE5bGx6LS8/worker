#include "database.h"



mysql::RecordBufferItem::RecordBufferItem(const std::string & car, int x, int y, int t):r(Record(x, y, t)),car(car)
{
}

mysql::DataBase::DataBase(const std::string & addr, const  std::string & name, const std::string & pwd, int maxBufferSize)
	:addr(addr),name(name),pwd(pwd),maxBufferSize(maxBufferSize)
{
	driver = sql::mysql::get_driver_instance();
	con = driver->connect(addr, name, pwd);
	con->setSchema("car");
	con->setAutoCommit(false);

	if (maxBufferSize < 20)
	{
		throw "max buffer size max lager than 20";
	}

	this->prep_stmt_insert = con->prepareStatement("INSERT INTO car (`carid`,`x`,`y`,`t`) VALUES (?,?,?,?) , (?,?,?,?) , (?,?,?,?), (?,?,?,?), (?,?,?,?), (?,?,?,?), (?,?,?,?), (?,?,?,?), (?,?,?,?), (?,?,?,?),(?,?,?,?) , (?,?,?,?) , (?,?,?,?), (?,?,?,?), (?,?,?,?), (?,?,?,?), (?,?,?,?), (?,?,?,?), (?,?,?,?), (?,?,?,?)");
	this->prep_stmt_select = con->prepareStatement("SELECT x,y,t FROM car WHERE carid = ? ORDER BY t ASC");
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
		while (this->recordBuffer.size()>=20)
		{
			for (int j = 0; j < 20; j++)
			{
				auto i = *(recordBuffer.end()-1);

				prep_stmt_insert->setString(4 * j + 1, i.car);
				prep_stmt_insert->setInt(4 * j + 2, i.r.posX);
				prep_stmt_insert->setInt(4 * j + 3, i.r.posY);
				prep_stmt_insert->setInt(4 * j + 4, i.r.time);

				recordBuffer.pop_back();
			}

			prep_stmt_insert->execute();

		}
		/*for (auto i : recordBuffer)
		{
			prep_stmt_insert->setString(1, i.car);
			prep_stmt_insert->setInt(2, i.r.posX);
			prep_stmt_insert->setInt(3, i.r.posY);
			prep_stmt_insert->setInt(4, i.r.time);

			prep_stmt_insert->execute();
		}*/

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
	recordBuffer.clear();

	//lock.unlock();
}

std::vector<Record> mysql::DataBase::select(std::string str)
{
	std::vector<Record> result;

	try {
		
		prep_stmt_select->setString(1, str);

		auto res = prep_stmt_select->executeQuery();
		while (res->next())
		{
			Record r(res->getInt(1), res->getInt(2), res->getInt(3));
			result.push_back(r);
		}
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