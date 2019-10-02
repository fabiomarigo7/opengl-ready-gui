#include "bitmap_font.h"

#include <stb_image.h>  // manip. texture

BitmapFont::BitmapFont() {
	vPath = "assets/engine/shaders/font/vertex.glsl";
	fPath = "assets/engine/shaders/font/fragment.glsl";
	h_align = "left";
	v_align = "normal";
	hAlignMap["left"] = 0;
	hAlignMap["center"] = 1;
	vAlignMap["normal"] = 0;
	vAlignMap["middle"] = 1;
}

void BitmapFont::set_align(std::string hAlign, std::string vAlign) {
	h_align = hAlign;
	v_align = vAlign;
}

/* Dynamic text */

void BitmapFont::create() {

	glUseProgram(shaderId);

	unsigned int indices[] = {
		 0, 1, 3,   // first triangle
		 1, 2, 3    // second triangle
	};

	float vertices[] = {
		// positions	// uv coords		
		0.f,	0.f,	0.0f, 1.0,   // in basso a sx
		32.f,	0.f,	1.0, 1.0,    // in basso a dx
		32.f,	32.f,	1.0, 0.0f,   // in alto a dx
		0.f,	32.f,	0.0f, 0.0f   // in alto a sx
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* Texture */

	std::ifstream path_fonts("assets/engine/fonts.json");
	json d = json::parse(path_fonts);

	std::map<std::string, json> jsonData;
	std::string fontName;

	for (int i = 0; i < d["fonts"].size(); i++){
		fontName = d["fonts"][i].get<std::string>();
		path = "assets/engine/fonts/" + fontName + ".png";
		
		// load image
		textureIdList.push_back(0);
		textureInfoList.push_back(glm::ivec3(0, 0, 0));
		unsigned char *data = stbi_load(path.c_str(), &textureInfoList[i].x, &textureInfoList[i].y, &textureInfoList[i].z, 0);
		if (!data) { std::cout << "Failed to load texture" << std::endl; }

		path = "assets/engine/fonts/" + fontName + ".json";

		std::ifstream json_path(path);
		jsonData[fontName] = json::parse(json_path);

		glUniform1f(glGetUniformLocation(shaderId, "max_x"), 16.f);
		glUniform1f(glGetUniformLocation(shaderId, "max_y"), 16.f);

		glUniform1i(glGetUniformLocation(shaderId, "tex"), 0); // texture
		glGenTextures(1, &textureIdList[i]);
		glBindTexture(GL_TEXTURE_2D, textureIdList[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// create texture and generate mipmaps
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureInfoList[i].x, textureInfoList[i].y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
		textureIdMap[fontName] = textureIdList[i];

		/* save json data in struct */

		for (int i = 0; i < 256; ++i) {
			fontData[fontName].charWidth[i] = jsonData[fontName]["Char " + std::to_string(i) + " Base Width"].get<int>();
		}
		fontData[fontName].startChar = jsonData[fontName]["Start Char"].get<int>();
		fontData[fontName].fontHeight = (GLint)jsonData[fontName]["Font Height"].get<int>();
		fontData[fontName].fontWidth = (float)jsonData[fontName]["Font Width"].get<int>();
	}
}

void BitmapFont::render_dynamic(std::string &font, float xPos, float yPos, std::string &text, glm::vec4 &color, bool shadow) {
	
	glUseProgram(shaderId);
	glUniform1i(glGetUniformLocation(shaderId, "startChar"), fontData[font].startChar);
	glUniform4f(glGetUniformLocation(shaderId, "color"), color.x / 255.f, color.y / 255.f, color.z / 255.f, color.w / 255.f);
	glUniform1f(glGetUniformLocation(shaderId, "y"), yPos);
	glUniform1i(glGetUniformLocation(shaderId, "hAlign"), hAlignMap[h_align]);
	glUniform1i(glGetUniformLocation(shaderId, "vAlign"), vAlignMap[v_align]);
	glUniform1i(glGetUniformLocation(shaderId, "fontHeight"), fontData[font].fontHeight);
	glUniform1i(glGetUniformLocation(shaderId, "shadow"), 0);

	if (h_align != "left"){
		total_width = 0;
		for (int i = 0; i < text.size(); i++) {
			total_width += fontData[font].charWidth[text.c_str()[i]];
		}
		glUniform1i(glGetUniformLocation(shaderId, "totalWidth"), total_width);
	}

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIdMap[font]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	offset_x = 0;
	for (int i = 0; i < text.size(); i++) {
		glUniform1f(glGetUniformLocation(shaderId, "x"), xPos + offset_x);
		glUniform1i(glGetUniformLocation(shaderId, "currentChar"), text.c_str()[i]);
		if (shadow) {
			glUniform1i(glGetUniformLocation(shaderId, "shadow"), 1);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glUniform1i(glGetUniformLocation(shaderId, "shadow"), 0);
		}
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		offset_x += fontData[font].charWidth[text.c_str()[i]];
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/* Static text */

txt::StaticData BitmapFont::create_static(std::string &font, std::string &text, float x) {
	txt::StaticData static_data = txt::StaticData();

	// x positions, chars and total width
	int totw = 0;
	for (int i = 0; i < text.size(); i++) {
		static_data.X.push_back(x + totw);
		static_data.charList.push_back((GLint)text.c_str()[i]);
		totw += fontData[font].charWidth[text.c_str()[i]];
	}	
	static_data.totalWidth = totw;

	// other information
	static_data.textureID = textureIdMap[font];
	static_data.startChar = fontData[font].startChar;
	static_data.textSize = (int)text.size();
	static_data.fontHeight = fontData[font].fontHeight;

	return static_data;
}

void BitmapFont::render_static(txt::StaticData &data) {

	glUseProgram(shaderId);
	glUniform4f(glGetUniformLocation(shaderId, "color"), data.color.x / 255.f, data.color.y / 255.f, data.color.z / 255.f, data.color.w / 255.f);
	glUniform1i(glGetUniformLocation(shaderId, "startChar"), data.startChar);
	glUniform1f(glGetUniformLocation(shaderId, "y"), data.y);
	glUniform1i(glGetUniformLocation(shaderId, "hAlign"), hAlignMap[h_align]);
	glUniform1i(glGetUniformLocation(shaderId, "vAlign"), vAlignMap[v_align]);
	glUniform1i(glGetUniformLocation(shaderId, "fontHeight"), data.fontHeight);
	glUniform1i(glGetUniformLocation(shaderId, "totalWidth"), data.totalWidth);
	glUniform1i(glGetUniformLocation(shaderId, "shadow"), 0);

	/* Draw */
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data.textureID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	for (int i = 0; i < data.textSize; i++) {
		glUniform1f(glGetUniformLocation(shaderId, "x"), data.X[i]);
		glUniform1i(glGetUniformLocation(shaderId, "currentChar"), data.charList[i]);
		if (data.shadow) {
			glUniform1i(glGetUniformLocation(shaderId, "shadow"), 1);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glUniform1i(glGetUniformLocation(shaderId, "shadow"), 0);
		}
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

BitmapFont::~BitmapFont() {}