#pragma once

#include <global.h>
#include <objects.h>

namespace gui {
	class Rectangle
	{
	public:
		Rectangle();
		void create(std::string type, float x, float y, float w, float h, std::string origin, int pickingID);
		void render(glm::vec4 Color, bool picking = false, float x = 0.f, float y = 0.f, float w = 0.f, float h = 0.f, int origin = -1);
		~Rectangle();
	private:
		RectangleData data;
		std::map<std::string, int> originMap;
		
	};
}
