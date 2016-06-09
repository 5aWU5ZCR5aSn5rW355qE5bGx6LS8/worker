#include "database.h"



mysql::RecordBufferItem::RecordBufferItem(const std::string & car, int x, int y, int t):r(Record(x, y, t)),car(car)
{
}

mysql::DataBase::DataBase(const std::string & addr, const  std::string & name, const std::string & pwd, int maxBufferSize)
	:addr(addr),name(name),pwd(pwd),maxBufferSize(maxBufferSize)
{
	driver = sql::mysql::get_driver_instance();
	con = driver->connect(addr, name, pwd);
}

void mysql::DataBase::insert(std::string car, int x, int y, int t)
{
	RecordBufferItem rec(car,x,y,t);

	this->recordBuffer.push_back(rec);
	
	if (this->recordBuffer.size() >= this->maxBufferSize)
	{
		commit();
	}
}

void mysql::DataBase::commit()
{
	try {
		con->setAutoCommit(false);
		auto prep_stmt = con->prepareStatement("INSERT INTO car (carid,x,y,t) VALUES ('?','?','?','?');");

		for (auto i : recordBuffer)
		{
			prep_stmt->setString(1, i.car);
			prep_stmt->setInt(2, i.r.posX);
			prep_stmt->setInt(3, i.r.posY);
			prep_stmt->setInt(4, i.r.time);

			prep_stmt->execute();
		}

		con->commit();

		delete prep_stmt;
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
}

std::vector<Record> mysql::DataBase::select(std::string str)
{
	std::vector<Record> result;

	try {
		auto prep_stmt = con->prepareStatement("SELECT * FROM car WHERE `carid` = '?' ORDER BY `carid` ASC");
		prep_stmt->setString(1, str);

		auto res = prep_stmt->executeQuery();
		while (res->next())
		{
			Record r(res->getInt(1), res->getInt(2), res->getInt(3));
			result.push_back(r);
		}

		delete prep_stmt;
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