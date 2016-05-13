.PHONY: build
build: unitTest.o memDB.o
	g++ --std=c++11 -O2 -o UnitTest/unitTest build/unitTest.o
	@./UnitTest/unitTest

unitTest.o:
	g++ --std=c++11 -O2 -c -o build/unitTest.o unitTest.cpp
memDB.o:
	g++ --std=c++11 -O2 -c -o build/memDB.o memDB.cpp
