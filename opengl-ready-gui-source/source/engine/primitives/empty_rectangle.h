#pragma once

#include <shader.h>

struct RectangleData {
	glm::vec4 borderColor, backColor, pickingColor;
	std::string type;
	float x, y, w, h;
	int origin;
};

class EmptyRectangle : public Shader
{
public:
	EmptyRectangle();
	void create();
	void render(RectangleData &data);
	~EmptyRectangle();
private:
	float vertices[24];
};