#pragma once

#include <global.h>

#include "simple_text.h"
#include "image.h"

namespace gui {
	class Button
	{
	public:
		Button();
		void create(std::string imageName, std::string Text, int x, int y, int pickingID, glm::vec4 textColor);
		void render(bool picking);
		~Button();

	private:
		SimpleText buttonText;
		Image buttonImage;
	};
}

