#include "main.h"

int main(int argc, char* argv[]) {

	Parser* parser = new Parser();

	try {
		parser->parseFile("fixed.csv", ';');
	} catch(exception& e) {
		cout << e.what();
	}

	return 0;
}

