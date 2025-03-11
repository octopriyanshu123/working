#include <thread>
#include <iostream>

using namespace std;

class Request
{
public:
	Request(int id) : mId(id) { }

	void process(int val)
	{
		cout << "Processing request " << mId <<" value "<<val<< endl;
	}

private:
	int mId;
};

int main()
{
	Request req(100);
	thread t{ &Request::process, &req , 43 };

	t.join();

	return 0;
}