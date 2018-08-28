#pragma once

#include <string>
#include <algorithm>
#include <vector>

namespace engine {

	class String : public std::string {

	public:
		String();
		String(std::string string);

		String toLowerCase();
		String toUpperCase();

		String removeConsecChar(char c);

		std::vector<std::string> split(char c);
		std::vector<std::string> split(std::string regex);

		static String toLowerCase(std::string string);
		static String toUpperCase(std::string string);

		static String removeConsecChar(std::string string, char c);

		static std::vector<std::string> split(std::string str, char c);
		static std::vector<std::string> split(std::string str, std::string regex);

	};
}
