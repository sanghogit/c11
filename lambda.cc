#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;

// functor ------------
template <typename T>
class Greater_Than {
	T val;
public:
	Greater_Than() {}
	Greater_Than( const T& v) : val(v) {}
	bool operator()( const T& v ) const
		{ return v > val; }
	bool operator()( const T& a, const T& b ) const
		{ return a > b; }
};

void _functor()
{
	Greater_Than<int> greater_than {33};
	cout << "88 > 33 : " << greater_than(88) << endl;
}


// _lambda ------------
void _lambda()
{
	vector<int> v {3,7,5,6,1,2,9,0,8,4};
	
	auto showvec = [](vector<int>& x) {
		for( int i: x ) cout << i;
		cout<< endl;
	};

	auto showvec2 = [&] {
		for( int i: v ) cout << i;
		cout<< endl;
	};

	showvec( v );
	sort( v.begin(), v.end(), less<int>());  // std::less
	showvec2();

	sort( v.begin(), v.end(), Greater_Than<int>());
	showvec2();
}


// ---------- MAIN ------------
int main()
{
	_functor();
	_lambda();
}
