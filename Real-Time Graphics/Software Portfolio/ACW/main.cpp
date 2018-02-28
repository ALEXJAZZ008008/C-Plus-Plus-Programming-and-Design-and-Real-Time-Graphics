#include "scene.h"

int WINAPI main(const HINSTANCE hInstance, const HINSTANCE hPreviousInstance, const PSTR pCommandLine, const int iCommandShow)
{
	const char * const graphicsFilename = "../ACW/models/graphics.txt";
	
	// Create the scene object.
	Scene *const scene = new Scene(graphicsFilename);

	// Run the scene object.
	scene->Run();

	// Release the scene object.
	delete scene;

	return 0;
}