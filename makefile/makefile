.PHONY: build
build: ../test/memDBTest.o ../build/memDB.o ../build/DataBase.o
	g++ --std=c++11 -O2 -o ../test/memDBTest  ../test/memDBTest.o ../build/memDB.o # 单元测试的结果
	@../test/memDBTest

../test/memDBTest.o:
	g++ --std=c++11 -O2 -c -o ../test/memDBTest.o ../src/memDBTest/memDBTest.cpp
../build/memDB.o:
	g++ --std=c++11 -O2 -c -o ../build/memDB.o ../src/memDB/memDB.cpp
../build/DataBase.o:
	g++ --std=c++11 -O2 -c -o ../build/DataBase.o ../src/memDB/DataBase.cpp

clean:
	rm ../test/memDBTest.o ../test/memDBTest ../build/memDB.o
