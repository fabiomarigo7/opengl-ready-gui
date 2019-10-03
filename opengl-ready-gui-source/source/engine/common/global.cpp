#include "global.h"

namespace glb {
	void setWindowSize(int width, int height) {
		windowWidth = width;
		windowHeight = height;
	}

	glm::ivec2 getWindowSize() {
		return glm::vec2(windowWidth, windowHeight);
	}

	void setWindowClosingCondition(bool b) {
		windowShouldClose = b;
	}

	bool getWindowShouldClose() {
		return windowShouldClose;
	}

	void setMousePos(int x, int y) {
		mouseX = x;
		mouseY = y;
	}

	void setMouseLeft(bool b) {
		mouseLeft = b;
	}

	void setMouseRight(bool b) {
		mouseRight = b;
	}
 
	bool getMouseLeft() {
		return mouseLeft;
	}
	bool getMouseRight() {
		return mouseRight;
	}

	glm::ivec2 getMousePos() {
		return glm::ivec2(mouseX, mouseY);
	}

	int getPickingId() {
		return pickingId;
	}

	void increasePickingId() {
		pickingId++;
	}

	void resetPickingId() {
		pickingId = 0;
	}

	int getId(GLint x, GLint y) {
		unsigned char data[4];
		glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data);
		int pickedID =
			data[0] +
			data[1] * 256 +
			data[2] * 256 * 256;
		return pickedID;
	}

	glm::vec3 getPickingColorFromId(int id) {
		int r = (id & 0x000000FF) >> 0;
		int g = (id & 0x0000FF00) >> 8;
		int b = (id & 0x00FF0000) >> 16;
		return glm::vec3(r, g, b);
	}

	std::string readFile(const char* fileLocation) {
		std::string content;
		std::ifstream fileStream(fileLocation, std::ios::in);
		if (!fileStream.is_open()) {
			printf("Failed to read %s! File doesn't exist.", fileLocation);
			return "";
		}
		std::string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			content.append(line + "\n");
		}
		fileStream.close();
		return content;
	}
}