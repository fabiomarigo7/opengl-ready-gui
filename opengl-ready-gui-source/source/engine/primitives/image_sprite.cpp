#define STB_IMAGE_IMPLEMENTATION  
#include <stb_image.h>  // manip. texture

#include "image_sprite.h"

ImageSprite::ImageSprite(){
	vPath = "assets/engine/shaders/image/vertex.glsl";
	fPath = "assets/engine/shaders/image/fragment.glsl";
	imagesPathMap = std::map<std::string, std::string>();
}

void ImageSprite::create() {

	glUseProgram(shaderId);

	genBuffers();

	int k = 0;
	int w, h, nrChannels;
	GLuint texID;
	
	for (std::map<std::string, std::string>::iterator i = imagesPathMap.begin(); i != imagesPathMap.end(); i++) {

		w = 0; h = 0; nrChannels = 0; texID = 0;

		std::string imageName = i->first;
		std::string imagePath = i->second;

		// load image
		data = stbi_load(imagePath.c_str(), &w, &h, &nrChannels, 0);
		if (!data) { std::cout << "Failed to load texture" << std::endl; }

		// TEXTURE
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// create texture and generate mipmaps
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);

		/* store information */
		
		textureIdMap[imageName] = texID;
		imageSize[texID][0] = w;
		imageSize[texID][1] = h;

		k++;
	}
}

void ImageSprite::getImageData(ImageData *d) {
	(*d).textureID = textureIdMap[d->imageName];
	(*d).w = (float)imageSize[textureIdMap[d->imageName]][0];
	(*d).h = (float)imageSize[textureIdMap[d->imageName]][1];
}

void ImageSprite::render(ImageData &imageData, bool picking) {

	glUseProgram(shaderId);

	/* Uniform Variables */
	glUniform1f(glGetUniformLocation(shaderId, "x"), imageData.x);
	glUniform1f(glGetUniformLocation(shaderId, "y"), imageData.y);
	glUniform1f(glGetUniformLocation(shaderId, "w"), imageData.w);
	glUniform1f(glGetUniformLocation(shaderId, "h"), imageData.h);
	glUniform1i(glGetUniformLocation(shaderId, "origin"), imageData.origin);
	glUniform1i(glGetUniformLocation(shaderId, "picking"), int(picking));  // enable/disable picking
	glUniform1i(glGetUniformLocation(shaderId, "texture1"), 0); // texture

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, imageData.textureID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	
	if (picking) {
		glUniform4f(glGetUniformLocation(shaderId, "picking_color"), imageData.pickingColor.r/255.f, imageData.pickingColor.y/255.f, imageData.pickingColor.b/255.f, 1.0f);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	
	/* Draw */
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ImageSprite::genBuffers() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ImageSprite::~ImageSprite()
{
}
