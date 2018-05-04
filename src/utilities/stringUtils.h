#pragma once

#include <vector>
#include <sstream>
#include <string>

namespace engine {
	namespace String {

		static std::vector<std::string> split(std::string str, char c) {
			std::vector<std::string> array;
			std::string element = "";

			for (unsigned i = 0; i < str.length(); i++) {
				if (str[i] != c)
					element += str[i];
				else if (str[i] == c && element != "") {
					array.push_back(element);
					element = "";
				}
			} if (element != "")
				array.push_back(element);

			return array;
		}

		static bool startsWith(std::string line, std::string start) {
			return line.substr(0, start.size()) == start;
		}

		static std::vector<std::string> split(std::string str, std::string regex) {
			std::vector<std::string> array;

			while (str.find(regex) != std::string::npos) {
				array.push_back(str.substr(0, str.find(regex)));
				str = str.substr(str.find(regex) + regex.length(), str.size());
			}

			if (str != "")
				array.push_back(str);

			return array;
		}
	}
}