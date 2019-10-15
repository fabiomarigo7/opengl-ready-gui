#include "button.h"

namespace gui {
	Button::Button(){
	}

	void Button::create(std::string imageName, std::string Text, int x, int y, int pickingID, glm::vec4 textColor) {

		buttonImage = Image(imageName);
		buttonImage.create("center", (float)x, (float)y, (float)0, (float)0, pickingID);

		buttonText = gui::SimpleText("static");
		buttonText.create_static(Text, "tahomabold_13px", (float)x, (float)y, "center", "middle", textColor);
	}

	void Button::render(bool picking) {
		buttonImage.render(picking);

		if (!picking) buttonText.render_static();
	}

	Button::~Button()
	{
	}

}
