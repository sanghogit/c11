#include <iostream>
#include <functional>
using namespace std;

void PrintNumber(int i) { cout << i << endl; } 

void bind_ref()
{
	int n = 0; 
	function<void()> print1 = bind(&PrintNumber, n); 
	function<void()> print2 = bind(&PrintNumber, ref(n)); 
	n = 100; 

	print1();
	print2();
}

int main()
{
	bind_ref();
}

