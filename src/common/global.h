#pragma once

#include "../memDB/DataBase.h"
#include "../mysql/database.h"
#include "../checker/checker.h"

using namespace memDB;

extern DataBase * m_memDB;
extern mysql::DataBase * m_mysqlDB;
extern checker::Checker m_checker;