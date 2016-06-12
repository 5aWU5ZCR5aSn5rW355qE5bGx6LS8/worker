#pragma once

#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/ini_parser.hpp>  
#include <string>

class Ini {
public:
	Ini(std::string ini_file);
	std::string get(std::string path);
	int getInt(std::string path);
	short int errCode();
private:
	short int err_code;
	boost::property_tree::ptree m_pt;
};