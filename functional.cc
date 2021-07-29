#include <iostream>
#include <functional>

void PrintNum(int& i) 
{ 
	std::cout << i << std::endl;
	i = 50;
}

void bind_ref()
{
	int n = 0;
	std::function<void()> print1 = std::bind(&PrintNum, n);
													// n is copied
	n = 100;
	std::function<void()> print2 = std::bind(&PrintNum, std::ref(n));
	n = 200;

	print1(); // print 0
	print2(); // print 200
}

void _mem_fn()
{
	struct Foo {
		void greeting() { std::cout << "greeting() called\n"; }
		void number(int i) { std::cout << "number() called\n"; }
		int data = 7;
	};

	Foo foo;

	auto greeting = std::mem_fn( &Foo::greeting );
	greeting( foo );

	auto number = std::mem_fn( &Foo::number );
	number( foo, 42 );

	auto access_data = std::mem_fn( &Foo::data );
	std::cout << "data: " << access_data( foo ) << '\n';
}

int main()
{
	bind_ref();
	_mem_fn();
}

