#include "shader.h"

Shader::Shader() {
	VAO = 0; VBO = 0; IBO = 0;
	shaderId = 0;
};

void Shader::compile() {
	// Compile and setup the shader
	std::string vertexString = glb::readFile(vPath);
	std::string fragmentString = glb::readFile(fPath);
	vShaderCode = vertexString.c_str();
	fShaderCode = fragmentString.c_str();

	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	shaderId = glCreateProgram();
	glAttachShader(shaderId, vertexShader);
	glAttachShader(shaderId, fragmentShader);
	glLinkProgram(shaderId);
	// check for linking errors
	glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::apply_projection_matrix(glm::mat4 mat) {
	glUseProgram(shaderId);
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "projection"), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::apply_view_matrix(glm::mat4 mat) {
	glUseProgram(shaderId);
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "view"), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::apply_model_matrix(glm::mat4 mat) {
	glUseProgram(shaderId);
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "model"), 1, GL_FALSE, glm::value_ptr(mat));
}

Shader::~Shader() {

}