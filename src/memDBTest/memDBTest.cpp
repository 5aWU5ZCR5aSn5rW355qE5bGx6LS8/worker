#include "memDBTest.h"

using namespace memDB;
using namespace std;

int main();


int main()
{
	
	init();

	clock_t start_time = clock();

	//for (int i = 0; i < 200000; i++) {
	//	string car = global.mapstr[i];
	//	//        cout << car << endl;
	//	for (int j = 0; j < 5; j++) { // ������ i.max * j.max ������
	//		insert(global, car, j, 1, 1);
	//	}
	//}
	//cout << "��ǰ�Ѿ�insert��Ŀ�� " << global.idx << endl;

	insert("A000001", 1, 1, 1);
	insert("A000002", 1, 1, 1);
	insert("A000001", 1, 1, 1);
	insert("A000001", 1, 1, 1);


	clock_t end_time = clock();
	cout << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;//�������ʱ��


	auto tmp = select("A000001");
	return 0;
}
