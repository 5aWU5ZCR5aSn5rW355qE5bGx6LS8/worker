#pragma once

//#define BOOST_LOG_DYN_LINK 1

#include "../common/csvReader.h"
#include "../common/global.h"
#include "../serverAddCar/server.h"

#include <thread>
#include <chrono>
#include <iostream>

int main();
void server();
void client();