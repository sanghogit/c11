#include <iostream>
#include <string>
#include <sstream>
#include "person.h"

int main()
{
	string s( "(  \"sang ho\"  ,  20  )" );
	istringstream iss( s );

	Person me { "you won't see this", -1000 };
	iss >> me;
	cout << s << " ---> " << me << endl;
}
