/*
clang++ boost.cc -I ~/boost/include -L ~/boost/lib
*/
#include <boost/type_index.hpp> 
#include <iostream> 
#include <string> 

using std::cout;
using std::endl;
using boost::typeindex::type_id_with_cvr;

template <typename T>
void show_type( const T& param )
{
	cout << "typeid\n";
	cout << typeid(T).name() << endl;		// int*
	cout << typeid(param).name() << endl;	// int* (wrong!)

	cout << "boost\n";
	cout << type_id_with_cvr<T>().pretty_name() << endl;	// int*
	cout << type_id_with_cvr<decltype(param)>().pretty_name() << endl; // int* const& (right!)
}

int main()
{
	std::vector<int> vec =  {100, 200};
	show_type( &vec[0] );

	/* 
	exercises:
		int* p  			pointer 		to int
		const int* p		pointer 		to (const int)
		const int* const p	(const pointer) to (const int)
		int* const p		(const pointer) to int
		int* const& r		(const reference) to (int pointer)
	*/
}
