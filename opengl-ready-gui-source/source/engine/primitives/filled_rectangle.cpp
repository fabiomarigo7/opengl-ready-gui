#include "filled_rectangle.h"
#include "empty_rectangle.h"

FilledRectangle::FilledRectangle(){
	vPath = "assets/engine/shaders/filled_rectangle/vertex.glsl";
	fPath = "assets/engine/shaders/filled_rectangle/fragment.glsl";
}

void FilledRectangle::create() {

	float size = 1.f;

	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	
	float vertices[] = {
		// positions				
			0.f,	0.f,	0.0f,  // bottom-left
			size,	0.f,	0.0f,  // bottom-right
			size,	size,	0.0f,  // top-right
			0.f,	size,	0.0f,  // top-left
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void FilledRectangle::render(RectangleData &data, bool picking) {

	glUseProgram(shaderId);

	glUniform1f(glGetUniformLocation(shaderId, "x"), data.x);
	glUniform1f(glGetUniformLocation(shaderId, "y"), data.y);
	glUniform1f(glGetUniformLocation(shaderId, "w"), data.w);
	glUniform1f(glGetUniformLocation(shaderId, "h"), data.h);
	glUniform1i(glGetUniformLocation(shaderId, "origin"), data.origin);

	if (picking) {
		glUniform4f(glGetUniformLocation(shaderId, "color"), data.pickingColor.x / 255.0f, data.pickingColor.y / 255.0f, data.pickingColor.z / 255.0f, data.pickingColor.w);
	}
	else {
		glUniform4f(glGetUniformLocation(shaderId, "color"), data.backColor.x / 255.0f, data.backColor.y / 255.0f, data.backColor.z / 255.0f, data.backColor.w);
	}
	

	/* Draw */
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
}

FilledRectangle::~FilledRectangle()
{
}
