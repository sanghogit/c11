#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <typeinfo>
#include <array>
#include <memory>	// unique_ptr

using namespace std;

class animal { };

class human : animal {
private:
	int _age;
	string _name;
public:
	human( const int a, const string& n)
		: _age(a), _name(n) { }
	string name() { return _name; }
	int age() { return _age; }
};

// auto --------------
void _auto()
{
	vector<int> v;
	v.push_back( 1 );
	v.push_back( 2 );
	v.push_back( 3 );

	vector<int>::const_iterator it;

	for( it = v.begin(); it != v.end(); ++it) cout << *it << ' ';
	cout << endl;

	for( auto it: v) cout << it << ' ';
	cout << endl;

	for( auto& it: v) {
		it *= 10;
		cout << it << ' ';
	}
	cout << endl;

	for_each( v.begin(), v.end(), [](int i) { cout << i << ' '; });
	cout << endl;
}

// uniform_init --------------
void uniform_init()
{
	human p1( 40, "dad" );
	human p2( 38, "mon" );
	vector<human> vec { {10, "A"}, {20, "B"}, {30, "C"} };

	for_each( vec.begin(), vec.end(),
		[](human p) { cout <<p.name() << p.age() << endl; });
}

// decltype --------------
string num2str( const int i ) {  return "one"; }
int str2num( const string& s ) {  return 2; }

template<typename T, typename F>
auto execute(const T& value, F func) -> decltype(func(value)) {
	return func( value );
}

void _decltype()
{
	auto a = execute( 3, num2str );
	cout << a << endl;
	cout << typeid( a ).name() << endl; 
	auto b = execute( "two", str2num );
	cout << b << endl;
	cout << typeid( b ).name() << endl;
}

// std::array ------------
void _array()
{
	array<human, 3> a { human(10, "AA"), human(20, "BB"),  human(40, "CC")  };

	for( auto it: a )
		cout << it.name() << endl;
		
	for( auto& it: a)
		cout << it.name() << endl;

	for( auto it = a.begin(); it != a.end(); ++it) 
		cout << it->name() << endl;				// pointer !
}

// std::unique_ptr ------------
void _unique_ptr()
{
	unique_ptr<int> p1 (new int(100));
	cout << p1.get() << endl;

	unique_ptr<int> p2 = move(p1);
	cout << p1.get() << endl;
	cout << p2.get() << endl;
	p2.reset();
}

// _sort ------------
void _sort()
{
	array<int, 5> ary {7,3,5,1,9};
	sort( ary.begin(), ary.end(), less<int>() );
	
	for( int v: ary )
		cout << v << endl;

	for_each( ary.begin(), ary.end(), 
		[](int val) { cout << val << endl; } );
}

// _find_if ------------
void _find_if()
{
	struct isodd {
		bool operator()( int i ) { 
			return( (i%2) == 1 );
		}
	};

	array<int, 10> ary {0,1,2,3,4,5,6,7,8,9};
	//for_each( ary.begin(), ary.end(), [](int val) {cout << val << endl; } );
	
	array<int,10>::iterator it = ary.begin();
	while( (it = find_if( it, ary.end(), isodd())) != ary.end() ) {
		cout << *it << endl;
		it++;
	}
}

// _iterator ------------
void _iterator()
{
	array<int,10> ary {0,1,2,3,4,5,6,7,8,9};

	for( int i: ary ) cout << i;
	cout << endl;

	array<int,10>::iterator it;
	for( it = ary.begin(); it != ary.end(); it++ ) cout << *it;
	cout << endl;

	for_each( ary.begin(), ary.end(), [](int val) {cout << val; } );
	cout << endl;
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
	sort( v.begin(), v.end(), less<int>());
	showvec2();
}

// _static_assert ------------
template<typename T>
class A {
	static_assert( sizeof(T) == 4, "sizeof(T) should be 4" );
public:
	A( T n ) {  }
};

void _static_assert()
{
	A<int> a(10);
}


// ---------- MAIN ------------
int main()
{
	//_auto();
	//uniform_init();
	//_decltype();
	//_array();
	//_unique_ptr();
	//_sort();
	//_find_if();
	//_iterator();
	//_lambda();
	//_static_assert();
}
