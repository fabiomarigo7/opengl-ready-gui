#pragma once

#include <global.h>
#include <objects.h>

namespace gui {
	class Image
	{
	public:
		Image();
		Image(std::string ImageName);
		void create(std::string Origin, float x, float y, float w, float h, int pickingID);
		void render(bool picking, float x = 0.f, float y = 0.f);
		~Image();
	private:
		ImageData imgData;
		std::string imageName;
		std::map<std::string, int> originMap;
	};
}


