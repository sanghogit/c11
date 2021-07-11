#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

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

// _iterator ------------
template<typename C>
void _iterator_template( C& container )
{
	for( auto i: container ) 
		cout << i;
	cout << endl;

	typename C::iterator it;
	for( it = container.begin(); it != container.end(); it++ ) 
			cout << *it;
	cout << endl;

	for_each( container.begin(), container.end(), 
					[](auto val) {cout << val; } );
	cout << endl;
}

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

int main()
{
	array<int,10> ary {0,1,2,3,4,5,6,7,8,9};
	_iterator_template( ary );

//	_sort();
//	_find_if();
//	_iterator();
}
