#pragma once

#include <headers.h>
#include <objects.h>
#include <global.h>

#include "gui.h"

namespace gui {
	struct menuData {
		std::string title;
		gui::Rectangle titleBack;
		gui::SimpleText titleText;
		glm::ivec2 titlePosition;
		int titleWidth, titleHeight;
		std::vector<std::string> options;
		std::vector<gui::Rectangle> optionsBack;
		std::vector<gui::SimpleText> optionsText;
		std::vector<glm::ivec2> optionsPosition;
		int optionsWidth, optionsHeight;
		int optionsOffsetX;
		glm::vec4 color;
		glm::vec4 hoverColor;
		glm::vec4 pickingColor;
		int pickingID;
		bool isOpened;
	};

	class Menu
	{
	public:
		Menu();
		void create();
		void render(bool pick);
		~Menu();
	private:
		gui::Rectangle topBar;
		glm::vec4 barColor;
		std::map<std::string, menuData> titles;
		std::array<std::string, 2> titlesList;
		std::map<std::string, int>pickingList;

		int barHeight;
		bool isHover(glm::vec2 pos, int w, int h);
		void picking();
		bool menuIsOpened;

	};
}

