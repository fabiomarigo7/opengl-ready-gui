#pragma once

#include <shader.h>
#include <json.hpp>

namespace txt {
	struct CharData {
		int charWidth[256];
		GLint fontHeight;
		float fontWidth;
		int startChar;
	};

	struct StaticData {
		std::vector<float> X;
		std::vector<GLint> charList;
		glm::vec4 color;	
		float y;		
		int textSize;
		int totalWidth;
		int startChar;
		GLint fontHeight;
		GLuint textureID;
		bool shadow;
	};
}

class BitmapFont : public Shader 
{
public:
	BitmapFont();
	void set_align(std::string hAlign = "left", std::string vAlign = "normal");
	void create();
	void render_dynamic(std::string &font, float xPos, float yPos, std::string &text, glm::vec4 &color, bool shadow);
	txt::StaticData create_static(std::string &font, std::string &text, float x);
	void render_static(txt::StaticData &data);
	int getShaderId() { return shaderId; }
	~BitmapFont();

 private:
	 std::map<std::string, txt::CharData> fontData;
	 std::string h_align, v_align, path;
	 int total_width;
	 int offset_x;
	 std::map<std::string, int> hAlignMap;
	 std::map<std::string, int> vAlignMap;
};