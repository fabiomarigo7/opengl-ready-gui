
#include "bitmap_font.h"
#include <global.h>
#include <stb_image.h>
#include <codecvt>
#include <locale>

using namespace glb;

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

void BitmapFont::set_align(string hAlign, string vAlign) {
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
		0.f,	-1.f,	0.0f, 1.0,   // in basso a sx
		1.f,	-1.f,	1.0, 1.0,    // in basso a dx
		1.f,	0.f,	1.0, 0.0f,   // in alto a dx
		0.f,	0.f,	0.0f, 0.0f   // in alto a sx
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
	//Close the game if it wasn't able to find or process fonts.json file
	ifstream path_fonts("assets/engine/fonts.json");
	json d = json::parse(path_fonts);

	map<string, json> jsonData;
	string fontName;

	

	for (int i = 0; i < d["fonts"].size(); i++){
		fontName = d["fonts"][i].get<string>();
		path = "assets/engine/fonts/" + fontName + ".png";

		// load image
		textureIdList.push_back(0);
		textureInfoList.push_back(ivec3(0, 0, 0));
		unsigned char *data = stbi_load(path.c_str(), &textureInfoList[i].x, &textureInfoList[i].y, &textureInfoList[i].z, 0);
		if (!data) { cout << "Failed to load texture" << endl; }

		path = "assets/engine/fonts/" + fontName + ".json";

		ifstream json_path(path);
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
		fontIdMap[fontName] = i;

		int ncharacters = (int)jsonData[fontName]["characters"].size();
		for (int _char = 0; _char < ncharacters; _char++){
			txt::Character CharData = txt::Character();
			int charID = jsonData[fontName]["characters"][_char]["id"].get<int>();
			CharData.base_width = jsonData[fontName]["common"]["base-width"].get<int>();
			CharData.line_height = jsonData[fontName]["common"]["line-height"].get<int>();
			CharData.x = jsonData[fontName]["characters"][_char]["x"].get<int>();
			CharData.y = jsonData[fontName]["characters"][_char]["y"].get<int>();
			CharData.width = jsonData[fontName]["characters"][_char]["width"].get<int>();
			CharData.height = jsonData[fontName]["characters"][_char]["height"].get<int>();
			CharData.xoffset = jsonData[fontName]["characters"][_char]["xoffset"].get<int>();
			CharData.yoffset = jsonData[fontName]["characters"][_char]["yoffset"].get<int>();
			CharData.xadvance = jsonData[fontName]["characters"][_char]["xadvance"].get<int>();
			fontData[i][charID] = CharData;
		}

		

	}
}

void BitmapFont::render_dynamic(string &font, float xPos, float yPos, string &text, vec4 &color, bool shadow) {
	
	int fontID = fontIdMap[font];

	glUseProgram(shaderId);
	glUniform4f(glGetUniformLocation(shaderId, "color"), color.x / 255.f, color.y / 255.f, color.z / 255.f, color.w / 255.f);
	glUniform1f(glGetUniformLocation(shaderId, "y"), yPos);
	glUniform1i(glGetUniformLocation(shaderId, "hAlign"), hAlignMap[h_align]);
	glUniform1i(glGetUniformLocation(shaderId, "vAlign"), vAlignMap[v_align]);
	glUniform1i(glGetUniformLocation(shaderId, "fontHeight"), (GLint)fontData[fontID][32].line_height);
	glUniform1i(glGetUniformLocation(shaderId, "shadow"), 0);
	wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
	wstring wtext = converter.from_bytes(text);

	if (h_align != "left"){
		total_width = 0;
		for (int i = 0; i < wtext.size(); i++) {
			GLint codepoint = GLint(wtext[i]);
			if (codepoint > 0){
				total_width += fontData[fontID][codepoint].width;
			}
		}
		glUniform1i(glGetUniformLocation(shaderId, "totalWidth"), total_width);
	}

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIdMap[font]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	offset_x = 0;
	for (int i = 0; i < wtext.size(); i++) {
		GLint codepoint = GLint(wtext[i]);
		glUniform1f(glGetUniformLocation(shaderId, "x"), xPos + offset_x);
		glUniform1i(glGetUniformLocation(shaderId, "char_xpos"), fontData[fontID][codepoint].x);
		glUniform1i(glGetUniformLocation(shaderId, "char_ypos"), fontData[fontID][codepoint].y);
		glUniform1i(glGetUniformLocation(shaderId, "char_width"), fontData[fontID][codepoint].width);
		glUniform1i(glGetUniformLocation(shaderId, "char_xadvance"), fontData[fontID][codepoint].xadvance);
		glUniform1i(glGetUniformLocation(shaderId, "char_height"), fontData[fontID][codepoint].height);
		glUniform1i(glGetUniformLocation(shaderId, "char_xoffset"), fontData[fontID][codepoint].xoffset);
		glUniform1i(glGetUniformLocation(shaderId, "char_yoffset"), fontData[fontID][codepoint].yoffset);
		if (shadow) {
			glUniform1i(glGetUniformLocation(shaderId, "shadow"), 1);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glUniform1i(glGetUniformLocation(shaderId, "shadow"), 0);
		}
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		offset_x += (fontData[fontID][codepoint].width + 1);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/* Static text */

txt::StaticData BitmapFont::create_static(string &font, string &text, float x) {
	txt::StaticData static_data = txt::StaticData();
	wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
	wstring wtext = converter.from_bytes(text);

	// x positions, chars and total width
	int totw = 0;
	int fontID = fontIdMap[font];
	for (int i = 0; i < wtext.size(); i++) {
		static_data.X.push_back(x + totw);
		GLint codepoint = GLint(wtext[i]);
		if (codepoint > 0){
			static_data.charList.push_back(fontData[fontID][codepoint]);
			totw += (fontData[fontID][codepoint].width);
		}
	}	
	static_data.totalWidth = totw;

	// other information
	static_data.textureID = textureIdMap[font];
	static_data.textSize = (int)wtext.size();
	static_data.fontHeight = (int)fontData[fontID][32].line_height;
	return static_data;
}

void BitmapFont::render_static(txt::StaticData &data) {

	glUseProgram(shaderId);
	glUniform4f(glGetUniformLocation(shaderId, "color"), data.color.x / 255.f, data.color.y / 255.f, data.color.z / 255.f, data.color.w / 255.f);
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
		glUniform1i(glGetUniformLocation(shaderId, "char_xpos"), data.charList[i].x);
		glUniform1i(glGetUniformLocation(shaderId, "char_ypos"), data.charList[i].y);
		glUniform1i(glGetUniformLocation(shaderId, "char_width"), data.charList[i].width);
		glUniform1i(glGetUniformLocation(shaderId, "char_xadvance"), data.charList[i].xadvance);
		glUniform1i(glGetUniformLocation(shaderId, "char_height"), data.charList[i].height);
		glUniform1i(glGetUniformLocation(shaderId, "char_xoffset"), data.charList[i].xoffset);
		glUniform1i(glGetUniformLocation(shaderId, "char_yoffset"), data.charList[i].yoffset);
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