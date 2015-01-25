#include "main.h"

int main(int argc, char* argv[]) {
	point_t centre;
	centre.x = 5;
	centre.y = 5;

	object_t robot = robot_main;
	object_t yellowStand = item_stand_yellow;

	Rectangle* mainRobotShape = new Rectangle(centre, robot, 10, 10, 0);
	Circle* yellowStand1 = new Circle(centre, yellowStand, 5);

	Mesh* rectangleMesh = new Mesh(mainRobotShape);
	Mesh* circleMesh = new Mesh(yellowStand1);

	//circleMesh->TerminalPrintMesh();

	for(int i=0; i<=360; i+=1) {
		mainRobotShape->SetAngle(i);
		rectangleMesh->GenerateFromShape(mainRobotShape);
		rectangleMesh->TerminalPrintMesh();
		usleep(10000);
		system("clear");
	}
	return 0;
}
