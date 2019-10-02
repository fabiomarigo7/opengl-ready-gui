#include <headers.h>
#include <global.h>
#include <json.hpp>

#include "source/engine/engine.h"

using namespace glb;

int main() {

	/* read engine settings */

	std::ifstream settings_path("config");
	json settings = json::parse(settings_path);

	setWindowSize(settings["window-width"], settings["window-height"]);

	Engine e = Engine();
	return e.launch();
}