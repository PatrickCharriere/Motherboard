#include "main.h"



int main(int argc, char* argv[]) {

	Parser* parser = new Parser();
	vector<string> fixedItems;
	vector<string> mobileItems;
	static int nbRowsItems = 13;

	try {
		parser->parseFile("fixed.csv", ';', &fixedItems);
		parser->parseFile("mobile.csv", ';', &mobileItems);
	} catch(exception& e) {
		cout << e.what();
	}

	//fixedItems format: 0 ID, 1 type, 2 franchissable?, 3 R, 4 V, 5 B, 6 centreX, 7 centreY, 8 rectangle?, 9 width, 10 height, 11 angle, 12 radius
	//WARN: Line 0 of csv = title line so first line is l = 1 !
	//WARN: line 1 of csv fixed = map !!

	//Traitement à part de la map
	point_t center;
	center.x = stoi(fixedItems[nbRowsItems*1+6]);
	center.y = stoi(fixedItems[nbRowsItems*1+7]);
	object_t object_type = object(fixedItems[nbRowsItems*1+1]);

	Rectangle* mapShape = new Rectangle(center,object_type,stoi(fixedItems[nbRowsItems*1+9]),stoi(fixedItems[nbRowsItems*1+10]),stoi(fixedItems[nbRowsItems*1+11]));
	Mesh* mapMesh = new Mesh(mapShape, stoi(fixedItems[nbRowsItems*1+2]));

	for(int l=2; l<(fixedItems.size()+1)/nbRowsItems; l++) {

		center.x = stoi(fixedItems[nbRowsItems*l+6]);
		center.y = stoi(fixedItems[nbRowsItems*l+7]);
		object_t object_type = object(fixedItems[nbRowsItems*l+1]);
		//Shape* shape = new Shape(center, object_type);
		Mesh* mesh;

		if(stoi(fixedItems[nbRowsItems*l+8])) {		//fixedItems[8] <=> rectangle ?
			Rectangle* shape = new Rectangle(center,object_type,stoi(fixedItems[nbRowsItems*l+9]),stoi(fixedItems[nbRowsItems*l+10]),stoi(fixedItems[nbRowsItems*l+11]));
			mesh = new Mesh(shape, stoi(fixedItems[nbRowsItems*l+2]));
		} else {
			Circle* shape = new Circle(center,object_type,stoi(fixedItems[nbRowsItems*l+12]));
			mesh = new Mesh(shape, stoi(fixedItems[nbRowsItems*l+2]));
		}

		mapMesh->Merge(mesh);
		cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;

	}
	return 0;
}


object_t object(string str) {

	if(str.compare("map")) {
		return map;
	} else if(str.compare("item_carpet")) {
		return item_carpet;
	} else if(str.compare("item_spot")) {
		return item_spot;
	} else if(str.compare("item_popcorn")) {
		return item_popcorn;
	} else if(str.compare("item_cup")) {
		return item_cup;
	} else if(str.compare("item_stand_yellow")) {
		return item_stand_yellow;
	} else if(str.compare("item_stand_green")) {
		return item_stand_green;
	} else if(str.compare("item_clap_yellow")) {
		return item_clap_yellow;
	} else if(str.compare("item_clap_green")) {
		return item_clap_green;
	} else if(str.compare("item_popcorn_machine")) {
		return item_popcorn_machine;
	} else if(str.compare("area_building")) {
		return area_building;
	} else if(str.compare("area_platform")) {
		return area_platform;
	} else if(str.compare("area_step_yellow")) {
		return area_step_yellow;
	} else if(str.compare("area_step_green")) {
		return area_step_green;
	} else if(str.compare("area_starting_yellow")) {
		return area_starting_yellow;
	} else if(str.compare("area_starting_green")) {
		return area_starting_green;
	} else if(str.compare("area_cinema_yellow")) {
		return area_cinema_yellow;
	} else if(str.compare("area_cinema_green")) {
		return area_cinema_green;
	} else if(str.compare("wall")) {
		return wall;
	} else if(str.compare("robot_main")) {
		return robot_main;
	} else if(str.compare("robot_secondary")) {
		return robot_secondary;
	}

	return map;
}





