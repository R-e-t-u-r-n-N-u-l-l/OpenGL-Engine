#include "string.h"

using namespace engine;

String::String() {}
String::String(std::string string) : std::string(string) {}

String String::toLowerCase() {
	this->assign(toLowerCase(*this));
	return *this;
}

String String::toUpperCase() {
	this->assign(toUpperCase(*this));
	return *this;
}

String String::removeConsecChar(char c) {
	this->assign(removeConsecChar(c));
	return *this;
}

std::vector<std::string> String::split(char c) {
	return split(*this, c);
}

std::vector<std::string> String::split(std::string regex) {
	return split(*this, regex);
}

String String::toLowerCase(std::string string) {
	for (int i = 0; i < string.length(); i++)
		string[i] = tolower(string[i]);
	return string;
}

String String::toUpperCase(std::string string) {
	for (int i = 0; i < string.length(); i++)
		string[i] = tolower(string[i]);
	return string;
}

String String::removeConsecChar(std::string string, char c) {
	std::string::iterator new_end = std::unique(string.begin(), string.end(), [c] (char left, char right) { return (left == right) && (left == c); });
	string.erase(new_end, string.end());
	return string;
}

std::vector<std::string> String::split(std::string str, char c) {
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

std::vector<std::string> String::split(std::string str, std::string regex) {
	std::vector<std::string> array;

	while (str.find(regex)) {
		array.push_back(str.substr(0, str.find(regex)));
		str = str.substr(str.find(regex), str.size());
	}

	if (str != "")
		array.push_back(str);

	return array;
}
