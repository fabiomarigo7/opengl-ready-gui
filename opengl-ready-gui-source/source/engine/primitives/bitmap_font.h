#pragma once

#include <shader.h>
#include <json.hpp>

using namespace std;
using namespace glm;

namespace txt {
	struct CharData {
		int charWidth[256];
		float fontHeight;
		float fontWidth;
		int startChar;
	};

	struct Character {
		int x, y, width, height, xoffset, yoffset, xadvance, line_height, base_width;
	};

	struct StaticData {
		vector<float> X;
		vector<Character> charList;
		vec4 color;
		float y;
		int textSize;
		int totalWidth;
		int startChar;
		int fontHeight;
		GLuint textureID;
		bool shadow;
	};
};


class BitmapFont : public Shader
{
public:
	BitmapFont();
	void set_align(string hAlign = "left", string vAlign = "normal");
	void create();
	void render_dynamic(string &font, float xPos, float yPos, string &text, vec4 &color, bool shadow);
	txt::StaticData create_static(string &font, string &text, float x);
	void render_static(txt::StaticData &data);
	int getShaderId() { return shaderId; }
	~BitmapFont();

private:
	map<int, txt::Character> fontData[10];
	map<string, int> fontIdMap;
	string h_align, v_align, path;
	int total_width;
	int offset_x;
	map<string, int> hAlignMap;
	map<string, int> vAlignMap;
};