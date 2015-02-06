
#ifndef PARSER_H_
#define PARSER_H_

#include <exception>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
#include <stdlib.h>
using namespace std;

class Parser {
public:
	void parseFile(string filename, char delimiter, vector<string>* row);
	void csv_read_row(istream &in, char delimiter, vector<string>* row);

};

#endif /* PARSER_H_ */
