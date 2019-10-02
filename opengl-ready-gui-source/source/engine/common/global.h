#pragma once

#include <headers.h>

namespace glb {
	static int windowWidth;
	static int windowHeight;
	static bool windowShouldClose;
	void setWindowSize(int width, int height);
	void setWindowClosingCondition(bool b);
	bool getWindowShouldClose();
	glm::ivec2 getWindowSize();
	
	static int mouseX;
	static int mouseY;
	void setMousePos(int x, int y);
	glm::ivec2 getMousePos();

	static bool mouseLeft;
	static bool mouseRight;
	void setMouseLeft(bool b);
	void setMouseRight(bool b);
	bool getMouseLeft();
	bool getMouseRight();


	std::string readFile(const char* fileLocation);
	int getId(GLint x, GLint y);
	glm::vec3 getPickingColorFromId(int id);
};

