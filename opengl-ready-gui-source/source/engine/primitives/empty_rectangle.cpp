#include "empty_rectangle.h"

EmptyRectangle::EmptyRectangle() {
	vPath = "assets/engine/shaders/empty_rectangle/vertex.glsl";
	fPath = "assets/engine/shaders/empty_rectangle/fragment.glsl";
}

void EmptyRectangle::create() {

	/*
	x0,y0------x3,y3
	|          |
	|          |
	|          |
	x1,y1------x2,y2
	*/

	/*
	positions
	x0,		y0,		0.0f,
	x1,		y1,		0.0f,
	//------------------
	x1,		y1,		0.0f,
	x2,		y2,		0.0f,
	//------------------
	x2,		y2,		0.0f,
	x3,		y3,		0.0f,
	//------------------
	x3,		y3,		0.0f,
	x0,		y0,		0.0f,
	*/

	// bottom-left alignment

	vertices[0] = (0.f); vertices[1] = (1.f); vertices[2] = (0.f);
	vertices[3] = (0.f); vertices[4] = (0.f); vertices[5] = (0.f);

	vertices[6] = (0.f); vertices[7] = (0.f); vertices[8] = (0.f);
	vertices[9] = (1.f); vertices[10] = (0.f); vertices[11] = (0.f);

	vertices[12] = (1.f); vertices[13] = (0.f); vertices[14] = (0.f);
	vertices[15] = (1.f); vertices[16] = (1.f); vertices[17] = (0.f);

	vertices[18] = (1.f); vertices[19] = (1.f); vertices[20] = (0.f);
	vertices[21] = (0.f); vertices[22] = (1.f); vertices[23] = (0.f);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void EmptyRectangle::render(RectangleData &data) {
	
	glUseProgram(shaderId);

	glUniform1f(glGetUniformLocation(shaderId, "x"), data.x);
	glUniform1f(glGetUniformLocation(shaderId, "y"), data.y);
	glUniform1f(glGetUniformLocation(shaderId, "w"), data.w);
	glUniform1f(glGetUniformLocation(shaderId, "h"), data.h);
	glUniform1i(glGetUniformLocation(shaderId, "origin"), data.origin);

	glUniform4f(glGetUniformLocation(shaderId, "BorderColor"), data.borderColor.x / 255.0f, data.borderColor.y / 255.0f, data.borderColor.z / 255.0f, data.borderColor.w);

	/* Draw */

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, IBO);
	glDrawArrays(GL_LINES, 0, 8);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

//int EmptyRectangle::areaSize(std::array<float, 8> coords) {
//	int base = (int)coords[6] - (int)coords[0];
//	int height = (int)coords[3] - (int)coords[1];
//	return base*height;
//}

EmptyRectangle::~EmptyRectangle()
{
}