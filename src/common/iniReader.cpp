#include "iniReader.h"
#include <io.h>

Ini::Ini(std::string ini_file) {
	if (access(ini_file.c_str(), 0) == 0) {
		this->err_code = 0;
		boost::property_tree::ini_parser::read_ini(ini_file, this->m_pt);
	}
	else {
		this->err_code = 1;
	}
}

short Ini::errCode() {
	return this->err_code;
}

std::string Ini::get(std::string path) {
	if (this->err_code == 0) {
		try 
		{
			return this->m_pt.get<std::string>(path);
		}
		catch (...)
		{
			return "";
		}
	}
	else {
		return "";
	}
}

int Ini::getInt(std::string path) {
	if (this->err_code == 0) {
		try 
		{
			return this->m_pt.get<int>(path);
		}
		catch (...)
		{
			return -1;
		}
	}
	else {
		return -1;
	}
}