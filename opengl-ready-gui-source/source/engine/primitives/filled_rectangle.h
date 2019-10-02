#pragma once

#include <shader.h>

struct RectangleData;

class FilledRectangle : public Shader
{
public:
	FilledRectangle();
	void create();
	void render(RectangleData &data, bool picking);
	~FilledRectangle();
};

