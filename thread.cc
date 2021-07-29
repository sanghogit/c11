#include <iostream>
#include <thread>
#include <vector>
using namespace std;

using dvector = vector<double>;

void func( const dvector& v ) { cout << "func called\n"; };

struct fclass {
	dvector& v;

	fclass( dvector& _v ) 
		: v{_v} { }
	void operator()()  { cout << "operator()() called\n"; };
};

int main()
{
	dvector vec  { 1,2,3,4,5,6,7,8,9};
	dvector vec2 { 10, 11, 12, 13, 14 };

	thread t1 { func, cref(vec) };
	thread t2 { fclass ( vec2 ) };

	t1.join();
	t2.join();
}
