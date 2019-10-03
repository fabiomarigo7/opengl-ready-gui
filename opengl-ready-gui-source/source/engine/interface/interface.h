#pragma once

#include <headers.h>
#include <global.h>
#include <objects.h>
#include "../gui/gui.h"

class Interface
{
public:
	Interface();
	void create();
	void render();
	~Interface();
private:
	gui::Menu menu;
	gui::Image img1;
	gui::Image img2;
	gui::SimpleText text1;
	gui::SimpleText text2;
	gui::SimpleText text3;
	gui::Rectangle rect1;
	gui::Rectangle rect2;
	gui::Rectangle rect3;
};