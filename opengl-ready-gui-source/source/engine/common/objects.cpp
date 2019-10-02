#include "objects.h"

BitmapFont *obj::Text(){
	return &obj::txt; 
}

EmptyRectangle *obj::ERectangle() {
	return &obj::eRect;
}

FilledRectangle *obj::FRectangle() {
	return &obj::fRect;
}

ImageSprite *obj::Img() {
	return &obj::img;
}

void obj::init() {
	*obj::Text() = BitmapFont();
	*obj::ERectangle() = EmptyRectangle();
	*obj::FRectangle() = FilledRectangle();
	*obj::Img() = ImageSprite();
}

void obj::compile() {
	obj::Text()->compile();
	obj::ERectangle()->compile();
	obj::FRectangle()->compile();
	obj::Img()->compile();
}

void obj::create() {
	obj::Text()->create();
	obj::ERectangle()->create();
	obj::FRectangle()->create();
	obj::Img()->create();
}

void obj::applyMenuMatrices(glm::mat4 proj) {
	obj::Text()->apply_projection_matrix(proj);
	obj::Img()->apply_projection_matrix(proj);
	obj::ERectangle()->apply_projection_matrix(proj);
	obj::FRectangle()->apply_projection_matrix(proj);
}