#include "simple_text.h"

namespace gui {

	using namespace glb;

	SimpleText::SimpleText(std::string Type, bool Shadow) {
		type = Type;
		hAlign = "left";
		vAlign = "normal";
		shadow = Shadow;
	}

	void SimpleText::create_static(std::string text, std::string font, float x, float y, std::string halign, std::string valign, glm::vec4 color) {
		if (type == "dynamic") {
			std::cout << "Dynamic text created with static option\n";
		}
		if (x < 0) x += getWindowSize().x;
		if (y < 0) y += getWindowSize().y;

		hAlign = halign;
		vAlign = valign;
		data = obj::Text()->create_static(font, text, x);
		data.y = y;
		data.color = color;
		data.shadow = shadow;
	}

	void SimpleText::render_static() {
		if (type == "dynamic") {
			std::cout << "Dynamic text rendered with static option\n";
		}	
		obj::Text()->set_align(hAlign, vAlign);		
		obj::Text()->render_static(data);
	}

	void SimpleText::render_dynamic(std::string text, std::string Font, float x, float y, glm::vec4 color, std::string halign, std::string valign) {
		if (type == "static") {
			std::cout << "Static text rendered with dynamic option\n";
		}
		obj::Text()->set_align(halign, valign);
		obj::Text()->render_dynamic(Font, x, y, text, color, shadow);
	}

	SimpleText::~SimpleText()
	{
	}
}


