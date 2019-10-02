#pragma once

#include <iostream>
#include <global.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Json {
public:

	json static string_to_document(std::string string) {

		json j = string.c_str();
		return j;
	}

	json static pathfile_to_document(std::string path) {
		return string_to_document(glb::readFile(path.c_str()).c_str());
	}
};


