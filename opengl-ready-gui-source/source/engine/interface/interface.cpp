#include "interface.h"

Interface::Interface() {}

void Interface::create() {
	ifstream json_path("assets/engine/interface/texts.json");
	json texts = json::parse(json_path);
	glb::resetPickingId();
	glb::increasePickingId();
	img1 = gui::Image("smile");
	img1.create("center", 100, 200, 100, 100, 0);
	img2 = gui::Image("smile");
	img2.create("center", 650, 300, 200, 200, 0);
	text1 = gui::SimpleText("static");
	text1.create_static(texts["text-1"], "tahomabold_15px", 50, 50, "left", "normal", glm::vec4(255.f));
	text2 = gui::SimpleText("static");
	text2.create_static(texts["text-2"], "tahoma_15px", 200, 300, "left", "normal", glm::vec4(255.f, 0.f, 0.f, 255.f));
	text3 = gui::SimpleText("static");
	text3.create_static(texts["text-3"], "couriernew_15px", 50, 500, "left", "normal", glm::vec4(0.f, 255.f, 0.f, 255.f));
	rect1 = gui::Rectangle();
	rect1.create("border", 600, 500, 50, 50, "center", 0);
	rect2 = gui::Rectangle();
	rect2.create("filled", 500, 100, 300, 80, "center", 0);
	rect3 = gui::Rectangle();
	rect3.create("border-filled", 300, 500, 40, 40, "center", 0);
	menu = gui::Menu();
	menu.create();
}

void Interface::render() {
	/* picking */
	menu.render(true);

	/* normal rendering */
	img1.render(false);
	img2.render(false);
	text1.render_static();
	text2.render_static();
	text3.render_static();
	rect1.render(glm::vec4(255.f, 255.f, 0.f, 255.f));
	rect2.render(glm::vec4(255.f, 0.f, 0.f, 255.f));
	rect3.render(glm::vec4(255.f, 0.f, 255.f, 255.f));
	menu.render(false);
}

Interface::~Interface() {}