#include "menu.h"

namespace gui {
	Menu::Menu(){
		barHeight = 30;
		barColor = glm::vec4(60.f, 68.f, 104.f, 255.f);
		titlesList = { "File", "Edit" };
		menuIsOpened = false;
	}

	void Menu::create() {
		topBar = gui::Rectangle();
		topBar.create("filled", 0, -barHeight, glb::getWindowSize().x, barHeight, "bottom-left", 0);

		titles["File"].title = "File";
		titles["File"].options = { "Save", "Exit" };

		titles["Edit"].title = "Edit";
		titles["Edit"].options = { "Edit1", "Edit2", "Edit3" };

		for (int i = 0; i < titles.size(); i++) {
			std::string s = titlesList[i];
			/* title */
			titles[s].pickingID = glb::getPickingId();
			titles[s].pickingColor = glm::vec4(glb::getPickingColorFromId(titles[s].pickingID), 255.f);
			pickingList[titles[s].title] = titles[s].pickingID;

			titles[s].color = barColor;
			titles[s].hoverColor = glm::vec4(40.f, 46.f, 70.f, 255.f);

			titles[s].titleWidth = 75;
			titles[s].titleHeight = barHeight;
			titles[s].titlePosition = glm::ivec2(titles[s].titleWidth * i, glb::getWindowSize().y - titles[s].titleHeight);
			titles[s].titleBack = gui::Rectangle();
		
			titles[s].titleBack = gui::Rectangle();
			titles[s].titleBack.create("filled", titles[s].titlePosition.x, titles[s].titlePosition.y, titles[s].titleWidth, titles[s].titleHeight, "bottom-left", titles[s].pickingID);
			titles[s].titleText = gui::SimpleText("static");
			titles[s].titleText.create_static(titles[s].title, "inconsolata_8", titles[s].titlePosition.x + 0.5f * titles[s].titleWidth, titles[s].titlePosition.y + 0.5f * titles[s].titleHeight, "center", "middle", glm::vec4(255.f));
		

			/* options */
			titles[s].optionsWidth = 100;
			titles[s].optionsHeight = barHeight;
			titles[s].optionsOffsetX = 20;
			for (int j = 0; j < titles[s].options.size(); j++) {
				titles[s].optionsPosition.push_back(glm::ivec2(titles[s].titleWidth * i, glb::getWindowSize().y - titles[s].optionsHeight * (j + 2)));

				gui::SimpleText tempText = gui::SimpleText("static");
				tempText.create_static(titles[s].options[j], "inconsolata_8", titles[s].optionsPosition[j].x + 0.5f * titles[s].optionsWidth - titles[s].optionsOffsetX, titles[s].optionsPosition[j].y + 0.5 * titles[s].optionsHeight, "left", "middle", glm::vec4(255.f));
				titles[s].optionsText.push_back(tempText);

				gui::Rectangle tempRect = gui::Rectangle();
				tempRect.create("filled", titles[s].optionsPosition[j].x, titles[s].optionsPosition[j].y, titles[s].optionsWidth, titles[s].optionsHeight, "bottom-left", titles[s].pickingID);
				titles[s].optionsBack.push_back(tempRect);
			}

			titles[s].isOpened = false;

			glb::increasePickingId();
		}
	}

	void Menu::render(bool pick) {
	
		/* picking rendering */
		if (pick){
			for (int i = 0; i < titles.size(); i++) {
				std::string s = titlesList[i];
				titles[s].titleBack.render(titles[s].pickingColor);
				if (titles[s].isOpened) {
					for (int j = 0; j < titles[s].options.size(); j++) {
						titles[s].optionsBack[j].render(titles[s].pickingColor);
					}
				}
			}

			picking();
		}

		/* normal rendering */
		else {
			topBar.render(barColor);
			for (int i = 0; i < titles.size(); i++) {
				std::string s = titlesList[i];
				if (isHover(titles[s].titlePosition, titles[s].titleWidth, titles[s].titleHeight)) {
					titles[s].titleBack.render(titles[s].hoverColor);
					if (menuIsOpened) {
						titles[s].isOpened = true;
						for (int j = 0; j < titles.size(); j++) {
							std::string s1 = titlesList[j];
							if (s1 != titles[s].title) {
								titles[s1].isOpened = false;
							}
						}
					}
				}
				else {
					titles[s].titleBack.render(titles[s].color);
				}
		
				titles[s].titleText.render_static();

				if (titles[s].isOpened) {
					for (int j = 0; j < titles[s].options.size(); j++) {
						if (isHover(titles[s].optionsPosition[j], titles[s].optionsWidth, titles[s].optionsHeight)) {
							titles[s].optionsBack[j].render(titles[s].hoverColor);
						}
						else {
							titles[s].optionsBack[j].render(titles[s].color);
						}
						titles[s].optionsText[j].render_static();
					}
				}
			}
		}
	}

	void Menu::picking() {

		if (glb::getMouseLeft()) {
			GLint mouseX = (GLint)glb::getMousePos().x;
			GLint mouseY = (GLint)glb::getMousePos().y;
			int clickId = glb::getId(mouseX, mouseY);
			int pos = ((mouseY - glb::getWindowSize().y)*(-1)) / titles["File"].titleHeight;

			//---------------------
			//   BACKGROUND
			//---------------------

			if (clickId == 0) {
				for (int i = 0; i < titles.size(); i++) {
					std::string s = titlesList[i];
					titles[s].isOpened = false;
					menuIsOpened = false;
				}
			}

			//---------------------
			//    FILE
			//---------------------

			if (pickingList["File"] == clickId) {
				if (pos == 0) {
					titles["File"].isOpened = true;
					menuIsOpened = true;
					for (int j = 0; j < titles.size(); j++) {
						std::string s = titlesList[j];
						if (s != "File") titles[s].isOpened = false;
					}
				}
				//---------------------
				//    SAVE

				if (pos == 1) { // save
					titles["File"].isOpened = false;
				}
				//---------------------
				//    EXIT

				if (pos == 2) { // exit
					titles["File"].isOpened = false;
					glb::setWindowClosingCondition(true);
				}	
			}

			//---------------------
			//    EDIT
			//---------------------

			if (pickingList["Edit"] == clickId) {
				titles["Edit"].isOpened = true;
				menuIsOpened = true;
				for (int j = 0; j < titles.size(); j++) {
					std::string s = titlesList[j];
					if (s != "Edit") titles[s].isOpened = false;
				}
			}

			//---------------------
			//---------------------
		}
	}

	bool Menu::isHover(glm::vec2 pos, int w, int h) {

		if ((glb::getMousePos().x > pos.x) && (glb::getMousePos().x < pos.x + w) && (glb::getMousePos().y > pos.y) && (glb::getMousePos().y < pos.y + h)) {
			return true;
		}
		else {
			return false;
		}
	}

	Menu::~Menu(){
	}
}
