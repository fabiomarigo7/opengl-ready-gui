#pragma once

#include <global.h>
#include <objects.h>

#include "simple_text.h"
#include "rectangle.h"

namespace gui {
	class FormInput
	{
	public:
		FormInput(bool options = true);
		void create(float x, float y, float w, float h, std::vector<std::string> options, int pickingID);
		void render(bool picking, glm::vec4 color);
		void open_close();
		void close();
		void select_option(int i);
		std::string selectedText;
		~FormInput();

	private:
		gui::Rectangle back;
		gui::Rectangle back_options;
		std::vector<gui::Rectangle> back_options_picking;

		gui::SimpleText text;
		std::vector<gui::SimpleText> optionsText;

		float width, height, x, y;
		std::vector<std::string> form_options;

		glm::vec2 mainTextPos;

		bool boolOptions;
		bool isOpened;
		bool hasText;
		int nOptions;
	};
}


