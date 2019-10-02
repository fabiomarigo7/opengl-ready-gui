#pragma once

#include <headers.h>
#include <global.h>


class Shader
{
public:
	Shader();
	void compile();
	void apply_projection_matrix(glm::mat4 mat = glm::mat4(1.0f));
	void apply_view_matrix(glm::mat4 mat = glm::mat4(1.0f));
	void apply_model_matrix(glm::mat4 mat = glm::mat4(1.0f));
	~Shader();

protected:
	const char* vPath;
	const char* fPath;
	int shaderId;
	GLuint VAO, VBO, IBO;
	std::vector<GLuint> textureIdList;
	std::map<std::string, GLuint> textureIdMap;
	std::vector<glm::ivec3> textureInfoList; // width, height, nrChannels

private:
	int success;
	char infoLog[512];
	int vertexShader, fragmentShader;
	const GLchar* vShaderCode;
	const GLchar* fShaderCode;
};
