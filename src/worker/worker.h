#pragma once

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include <boost/exception/all.hpp>

#include <thread>
#include <chrono>

#include "../common/global.h"
#include "../common/iniReader.h"

#include "../serverAddCar/server.h"
#include "../serverWorker/serverWorker.h"

#include "../checker/checker.h"

#include "signal.h"

checker::Checker m_checker;

int main(int argc,char *argv[]);
void init();
void threadServerCar();
void threadServerWorker();