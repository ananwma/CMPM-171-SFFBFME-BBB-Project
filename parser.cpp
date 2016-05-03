#include "stdafx.h"
#include "parser.h"
#include <fstream>

using namespace std;

parser::parser()
{
}

void parser::parse(string filename) {
	ifstream file;
	string line;
	char c;
	file.open(filename, ios::in);
	while (file.get(c)) {
		if (c == '<') {
		}
	}


	file.close();
}

parser::~parser()
{
}
