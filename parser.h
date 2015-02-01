
#ifndef PARSER_H_
#define PARSER_H_

#include <exception>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
using namespace std;

class Parser {
public:
	vector<string> parseFile(string filename, char delimiter);
	vector<string> csv_read_row(istream &in, char delimiter);

};

#endif /* PARSER_H_ */
