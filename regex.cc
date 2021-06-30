#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
	string input = "12345   90  1357\nxy  cde";

	istringstream iss( input );
	string line;
	regex pat { "\\w{2}\\s+" };
	int lineno = 0;
	while( getline( iss, line ) ) {
		lineno++;
		for( sregex_iterator it(line.begin(), line.end(), pat); it!=sregex_iterator(); ++it )
			cout << lineno << ":" << (*it).str() << '\n';
	}
/*
	input = "ab c dddd +ee ff;gg hh";
	regex pat2 {R"(\s+(\w+))"};
	for( sregex_iterator it(input.begin(), input.end(), pat2);
					it!=sregex_iterator{}; ++it )
			cout << (*it)[1] << '\n';
*/
}
