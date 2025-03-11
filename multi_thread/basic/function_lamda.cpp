#include <thread>
#include <iostream>

using namespace std;

int main()
{
	int id = 1;
	int numIterations = 5;

	thread t1([id, numIterations] {
		for (int i = 0; i < numIterations; ++i) {
			cout << "Counter " << id << " has value " << i << endl;
		}
	});

    id  = 2;
    numIterations = 13;
    thread t2([id, numIterations] {
		for (int i = 0; i < numIterations; ++i) {
			cout << "Counter " << id << " has value " << i << endl;
		}
	});


	t1.join();
    t2.join();

	return 0;
}