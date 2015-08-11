#include<iostream>
#include<string>
#include<cstring>
#include "PathString.h"

using namespace std;

std::vector<std::string> PathString::getTokens() const
{
	char *cstr = new char [base_path.length()+1];
	const char *delim = delimiter.c_str();
	char *tok;
	std::vector<string> tokens;
	strcpy(cstr,base_path.c_str());
	tok = strtok(cstr, delim);
	while (tok != nullptr){
		string token(tok);
		tokens.push_back(token);
		tok = strtok(nullptr, delim);
	}
	delete [] cstr;
	return tokens;
}

void PathString::printTokens() const
{
	std::vector<string> tokens = getTokens();

	for(string tok : tokens)
		cout << tok << endl;
}

/************** Demo program on how to use PathString ********************/

/*
main()
{
	string p1("/usr/local/bin");
	PathString path1(p1,"/");

	cout << "path1: " << path1.getPath() << endl;

	cout << "path1 tokens" << endl;
	path1.printTokens();

	cout << "path1.getLast() - " << path1.getLast() << endl;
	cout << "path1.excludeLast() - " << path1.excludeLast() << endl;

	string p2("/usr/");
	PathString path2(p2,"/");
	cout << "path2: " << path2.getPath() << endl;
	cout << "path2.getLast() - " << path2.getLast() << endl;
	cout << "path2.excludeLast() - " << path2.excludeLast() << endl;

	string p3("/");
	PathString path3(p3,"/");
	cout << "path3: " << path3.getPath() << endl;
	cout << "path3.getLast() - " << path3.getLast() << endl;
	cout << "path3.excludeLast() - " << path3.excludeLast() << endl;

	string p4("#usr#vfs#demo#folder");
	PathString path4(p4,"#");
	cout << "path4: " << path4.getPath() << endl;
	cout << "path4.getLast() - " << path4.getLast() << endl;
	cout << "path4.excludeLast() - " << path4.excludeLast() << endl;
}
*/
