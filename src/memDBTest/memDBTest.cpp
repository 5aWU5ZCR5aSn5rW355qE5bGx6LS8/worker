#include "memDBTest.h"

using namespace memDB;

int main();


int  main() 
{
	init();

	clock_t start_time = clock();

	for (int i = 0; i < 200000; i++) {
		string car = mapstr[i];
		//        cout << car << endl;
		for (int j = 0; j < 5; j++) { // ������ i.max * j.max ������
			insert(car, j, 1, 1);
		}
	}
	cout << "��ǰ�Ѿ�insert��Ŀ�� " << idx << endl;

	//    insert("A000001", 1, 1, 1);
	//    insert("A000002", 1, 1, 1);
	//    insert("A000001", 1, 1, 1);
	//    insert("A000001", 1, 1, 1);
	//    cout << mapvec["A000001"].at(1).index << endl;
	//    cout << rdf -> rd[199998].time << endl;


	clock_t end_time = clock();
	cout << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;//�������ʱ��


	vector<Index> tmp = select("A000002");

	return 0;
}