#pragma once

#include <headers.h>
#include <global.h>
#include <objects.h>
#include <json.hpp>

#include "window/window.h"
#include "interface/interface.h"

class Engine
{
public:
	Engine();
	int launch();
	~Engine();
private:
	myWindow window;
	Interface iface;
	void read_data();
};

