#ifndef _PERSON_H_
#define _PERSON_H_

#include <iostream>
#include <string>
using namespace std;

class Person {
public:
	string name;
	int age;

	Person( string i, int a=0 ) 
			: age {a}
	{ 
		name.resize( 10000); // prevent short string optimization
		name = i; cout << "constructor "; showstr(); 
	}

	Person( const Person& other ) 
		: name( other.name ), age(other.age)
		{ cout << "copy_const. "; showstr(); }
	
	Person( Person&& other ) 
		: name(move(other.name)), age(other.age)
		{ cout << "move_const. "; showstr(); }

    // *** RULE1 *** declare move constrcutr, move operator in a class
	//               use move( .. ) if you want explicit move.

	Person& operator=( const Person& other )
	{
		name = other.name; 
		age=other.age;
		cout << "assign_operator."; showstr();
		return *this;
	}

	Person& operator=( Person&& other )
	{
		name = move( other.name ); 
		age=other.age; 
		cout << "move_operator. "; showstr();
		return *this;
	}

	void showstr()
	{
		cout << "this(" << this << "), name:" 
		     << name << "(" << (void*)(name.c_str()) << ")" << endl; 
	}

	// print { "sang ho", 20 }
	friend ostream& operator<<( ostream& os, const Person& per)
	{
		return os << "{\"" << per.name << "\", " << per.age << "}";
	}

	// read (   "sang ho",    20   )
	friend istream& operator>>( istream& is, Person& per )
	{
		char c, c2;
		if( is>>c && c=='(' && is>>c2 && c2=='"' ) {
			string name;
			while( is.get(c) && c!='"' ) 
					name += c;
			if( is>>c && c==',') {
				int age;
				if( is>>age>>c && c==')') {
					per = {name, age};
					return is;
				}
			}
		}
		is.setstate( ios_base::failbit);
		return is;
	}
};

#endif
