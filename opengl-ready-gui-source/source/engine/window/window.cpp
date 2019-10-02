#include "window.h"

myWindow::myWindow(){}

void myWindow::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	mainWindow = glfwCreateWindow(glb::getWindowSize().x, glb::getWindowSize().y, "Ready GUI", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(mainWindow);

	create_callbacks(); // handle key + mouse input

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Define the viewport dimensions
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this); // this function is for taking inputs

	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);	// hide the mouse cursor in the window
	glb::setWindowClosingCondition(false);
}

void myWindow::clear_buffers() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (glfwWindowShouldClose(mainWindow)) {
		glb::setWindowClosingCondition(true);
	}
}

void myWindow::create_callbacks() { // important for taking the keyboard / mouse input 
	glfwSetKeyCallback(mainWindow, handle_keys);
	glfwSetCursorPosCallback(mainWindow, handle_mouse);
	glfwSetMouseButtonCallback(mainWindow, mouse_button_callback);
	glfwSetScrollCallback(mainWindow, scroll_callback);
}

void myWindow::handle_keys(GLFWwindow* window, int key, int code, int action, int mode) 
{
	myWindow* theWindow = static_cast<myWindow*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE) {
		if (action == GLFW_PRESS) {
			glb::setWindowClosingCondition(true);
		}
	}
}

void myWindow::handle_mouse(GLFWwindow* window, double xPos, double yPos)
{
	myWindow* theWindow = static_cast<myWindow*>(glfwGetWindowUserPointer(window));
	theWindow->lastX = (GLfloat)xPos;
	double y = fabs(yPos - glb::getWindowSize().y);
	theWindow->lastY = (GLfloat)y;
}

void myWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	myWindow* theWindow = static_cast<myWindow*>(glfwGetWindowUserPointer(window));

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			glb::setMouseLeft(true);
		}
		else if (action == GLFW_RELEASE) {
			glb::setMouseLeft(false);
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			glb::setMouseRight(true);
		}
		else if (action == GLFW_RELEASE) {
			glb::setMouseRight(false);
		}
	}
}

void myWindow::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){}

myWindow::~myWindow(){}
