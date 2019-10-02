#pragma once

#include <headers.h>
#include <global.h>

class myWindow
{
public:
	myWindow();
	
	void init();
	void swap_buffers() { glfwSwapBuffers(mainWindow); }
	void clear_buffers();
	GLFWwindow *get_GLFW_window() { return mainWindow; }
	void create_callbacks();
	int get_mouse_x() { return (int)lastX; };
	int get_mouse_y() { return (int)lastY; };
	bool* getKeys() { return keys; }
	~myWindow();

private:
	GLFWwindow *mainWindow;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	static void handle_mouse(GLFWwindow* window, double xPos, double yPos);
	static void handle_keys(GLFWwindow* window, int key, int code, int action, int mode);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	// input mouse
	GLfloat lastX;
	GLfloat lastY;
};

