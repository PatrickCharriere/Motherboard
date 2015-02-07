#include "main.h"



int main(int argc, char* argv[]) {

	Parser* parser = new Parser();
	vector<string> fixedItems;
	static int nbRowsFixedItems = 13;

	try {
		parser->parseFile("fixed.csv", ';', &fixedItems);
	} catch(exception& e) {
		cout << e.what();
	}

	//fixedItems format: 0 ID, 1 type, 2 franchissable?, 3 R, 4 V, 5 B, 6 centreX, 7 centreY, 8 rectangle?, 9 width, 10 height, 11 angle, 12 radius
	for(int l=0; l<fixedItems.size()/nbRowsFixedItems; l++) {
		point_t centre;
		centre.x = stoi(fixedItems[6]);
		centre.y = stoi(fixedItems[7]);
		object_t type = map;//fixedItems[1];
		//Shape shape;

		if(stoi(fixedItems[8])) {		//fixedItems[8] <=> rectangle ?
			Rectangle shape = new Rectangle(centre,type,fixedItems[9],fixedItems[10],fixedItems[11]);
		} else {
			Circle shape = new Circle(centre,type,fixedItems[12]);
		}
		//Mesh mesh = new Mesh(shape, fixedItems[2]);
	}
	return 0;
}

