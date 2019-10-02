#pragma once

#include <headers.h>
#include "../primitives/primitives.h"

namespace obj {

	static BitmapFont txt;
	BitmapFont *Text();

	static EmptyRectangle eRect;
	EmptyRectangle *ERectangle();

	static FilledRectangle fRect;
	FilledRectangle *FRectangle();

	static ImageSprite img;
	ImageSprite *Img();

	void applyMenuMatrices(glm::mat4 proj);
	void init();
	void compile();
	void create();
}
