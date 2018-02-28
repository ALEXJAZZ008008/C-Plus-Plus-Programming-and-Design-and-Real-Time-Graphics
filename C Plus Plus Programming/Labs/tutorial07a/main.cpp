#include <crtdbg.h>
#include <iostream>
using namespace std;

#include "Ball.h"
#include "Cube.h"

#ifdef _DEBUG
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

int main(int, char**)
{
	Ball *ball = new Ball(Vector3d(20, 34, 25), 20);
	ball->SetColour(Colour(255, 0, 0));

	Cube *cube = new Cube(Vector3d(40, -56, -6), 10);
	cube->SetColour(Colour(0, 255, 0));

	NewtonianObject *newtonianObject[2] = { ball, cube };

	for (int i = 0; i < 2; i++)
	{
		newtonianObject[i]->ApplyPhysics(0.1); // update object's position after 0.1s 
	}

	for (int i = 0; i < 2; i++)
	{
		delete newtonianObject[i];
	}

	return CloseProgram();
} 