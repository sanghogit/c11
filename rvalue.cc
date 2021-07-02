#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <typeinfo>
#include <array>
#include <memory>	// unique_ptr
#include "person.h"

using namespace std;

/*
RULES
*** RULE1 *** declare move constrcutr, move operator in a class
               use move( .. ) if you want explicit move.
*** RULE2 *** 'move' does nothging but casting. 
*** RULE3 *** you should treat rvalue reference the same 99% of the time. 
              (never return a && or & to a local variable)
*/

// _rvalue_move_constructor -------------------------------
/*
void showstr(const string& s) {
	cout << "str:"  << s << ", addr:" << (void*)(s.c_str()) << endl; 
}
*/

Person returnMan( string n )
{
	Person man(n);
	return man;
}

// _rvalue_call_simple ------------------------------------
void _rvalue_call_simple()
{
	Person aaa( "aaa" );	 // constructor
	Person bbb( aaa ); 		 // copy
	Person ccc( move(aaa) ); // move (RECOMMANDED)
}

// _rvalue_call -------------------------------------------
void _rvalue_call()
{
	// COPY: old way, passed via const reference, expensive copy 
	vector<Person> Family; 
	Person me( "sangho" );
	Family.push_back( me );

	vector<Person> Company;
	// AUTO MOVE: automatically uses rvalue reference constructor if available 
	// because myclass is an unamed temp variable 
	Company.push_back( returnMan("babo") ); 

	// Explicit MOVE: passed via rvalue reference, cheap move
	// don't use aboy again
	vector<Person> School;
	Person aboy( "michael" );
	School.push_back(move(aboy)); // (RECOMMANDED)
    // *** RULE1 *** declare move constrcutr, move operator in a class
	//               use move( .. ) if you want explicit move.
}

// _rvalue_return -----------------------------------------
Person&& returnMan_rref( string n )	// ERROR!!!! returning destructed man
{
	Person man(n);
	return move(man);
/*
*** RULE2 *** 'move' does nothging but casting. 
    There is no temporary created on the return line.  move doesn't create a temporary. 'move' just casts an lvalue to an xvalue, making no copies, creating nothing, destroying nothing. 
*** RULE3 *** you should treat rvalue reference the same 99% of the time. 
              (never return a && or & to a local variable)
    This example is the exact same situation as if you returned by lvalue-reference and removed the move from the return line: Either way you've got a dangling reference to a local variable inside the function and which has been destructed
*/
}

Person returnMan_moved( string n )
{
	Person man(n);
	return move(man);      // UNNECESSARY move_constr call, ret is just Person
}

//*** RULE3 *** you should treat rvalue reference the same 99% of the time. 
void _rvalue_return()
{
	Person aaa = returnMan( "aaa" );			
		// Person( string i ) called. (nature of C++)
	Person &&rref1 = returnMan( "bbb" ); 		
		// no move called. rref1 is just a reference to a class (just like a pointer)
	//Person &&rref2 = returnMan_rref( "ccc" );	
		// run-time error!!
	Person &&rref3 = returnMan_moved( "ddd" );	
		// unnecessary move called before return People

	aaa.showstr();
	rref1.showstr();
	//rref2.showstr();
	rref3.showstr();
}

// _perfect forwarding -------------------------------------
void bar( int& i )  { cout << "bar: " << i << endl; }
void foo( int&& i ) { bar(i); }

void _perfect_forwarding()
{
	foo( 1 );

	int a = 1;
	foo( move(a) );
}

// -------------------------- MAIN -------------------------
int main()
{
	_rvalue_call_simple();
	//_rvalue_call();
	//_rvalue_return();
	//_perfect_forwarding();
}
