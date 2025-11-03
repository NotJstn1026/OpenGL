#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Viewport.h"

int main(int a_argsC, char** a_argsV) {

	Viewport* viewport = new Viewport(800, 800, "OpenGL");

	if (viewport == nullptr) return -1;

	viewport->Initialize();

	viewport->Update();

	viewport->Finalize();

	delete(viewport);
	viewport = nullptr;

	return 0;
}