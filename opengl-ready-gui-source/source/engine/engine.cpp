#include "engine.h"

using namespace glb;

Engine::Engine(){
	window = myWindow();
}

//----------------------------------------------------------------------------------

int Engine::launch() {

	window.init();	
	obj::init();
	
	read_data();

	obj::compile();
	obj::create();

	glm::mat4 projection = glm::ortho(0.0f, (float)getWindowSize().x, 0.0f, (float)getWindowSize().y, -100.0f, 100.0f);
	obj::applyMenuMatrices(projection);

	iface.create();

	while (!getWindowShouldClose()) {

		glfwPollEvents();
		window.clear_buffers();
		setMousePos((int)window.get_mouse_x(), (int)window.get_mouse_y());

		iface.render();

		glfwSwapBuffers(window.get_GLFW_window());
	}

	glfwTerminate();
	return 0;
}

//----------------------------------------------------------------------------------

void Engine::read_data() {
	/* images */

	std::ifstream path2("assets/engine/images_data.json");
	json dataClass = json::parse(path2);

	for (int i = 0; i < dataClass["image_names"].size(); i++) {
		std::string imageName = dataClass["image_names"][i].get<std::string>();
		std::string root = dataClass["roots"][imageName];

		obj::Img()->addPath(imageName, root);
	}
}

Engine::~Engine(){}
