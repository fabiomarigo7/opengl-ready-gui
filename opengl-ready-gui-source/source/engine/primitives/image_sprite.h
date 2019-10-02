#pragma once

#include <shader.h>

struct ImageData {
	glm::vec3 pickingColor;
	std::string imageName;
	float x, y, w, h;
	int origin;
	GLuint textureID;
};

class ImageSprite: public Shader
{
public:
	ImageSprite();
	void addPath(std::string imageName, std::string path) { imagesPathMap[imageName] = path; }
	void create();
	void getImageData(ImageData *d);
	void render(ImageData &imageData, bool picking = false);
	~ImageSprite();

private:
	std::map<std::string, std::string> imagesPathMap;
	std::map<GLuint, int[2]> imageSize;
	
	unsigned char *data;
	unsigned int indices[6] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	GLfloat vertices[20] = {
		// positions			// uv coords		
		0.f,	0.f,	0.f,	0.f, 1.f,	// in basso a sx
		1.f,	0.f,	0.f,	1.f, 1.f,	// in basso a dx
		1.f,	1.f,	0.f,	1.f, 0.f,	// in alto a dx
		0.f,	1.f,	0.f,	0.f, 0.f	// in alto a sx
	};

	void genBuffers();
};

