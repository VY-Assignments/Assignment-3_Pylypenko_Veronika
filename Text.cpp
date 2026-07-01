#include "Text.h"
#include <iostream>
#include <sstream>

void Text::addLine(std::unique_ptr<Line> line) {
	lines_.push_back(std::move(line));
}
void Text::insertLine(size_t index, std::unique_ptr<Line> line) {
	if (index >= lines_.size()) {
		lines_.push_back(std::move(line));
		return;
	}
	lines_.insert(lines_.begin() + index, std::move(line));
}
void Text::removeLine(size_t index) {
	if (index >= lines_.size()) {
		std::cout << "Line index is out of range.\n";
		return;
	}
	lines_.erase(lines_.begin() + index);
}
size_t Text::size() const {
	return lines_.size();
}
bool Text::empty() const {
	return lines_.empty();
}
Line* Text::getLine(size_t index) const {
	if (index >= lines_.size()) { return nullptr; }
	return lines_[index].get();
}
void Text::printAll() const {
	if (lines_.empty()) {
		std::cout << "Your text is empty.\n";
		return;
	}
	for (size_t i = 0; i < lines_.size();i++) {
		std::cout << "[" << i << "]";
		lines_[i]->print();
	}
}
std::string Text::serializeAll() const {
	std::ostringstream oss;
	for (size_t i = 0; i < lines_.size();i++) {
		oss << lines_[i]->serialize();
		if (i + 1 < lines_.size()) {
			oss << "\n";
		}
	
	}
	return oss.str();
}

void Text::loadFromSerialized(const std::string& data) {
	lines_.clear();
	std::istringstream iss(data);
	std::string row;
	while (std::getline(iss, row))
	{
		if (row.empty()) { continue; }

		try {
			lines_.push_back(deserializeLine(row));
		}
		catch (const std::exception& e) {
			std::cout << "Failure! Skipping corrupted line (" << e.what() << ")\n";

		}
	}
}

void Text::clear() {
	lines_.clear();
}
std::vector<size_t> Text::find(const std::string& target) const {
	std::vector<size_t> result;
	if (target.empty()) { return result; }
	for (size_t i = 0; i < lines_.size(); ++i) {
		if (lines_[i]->serialize().find(target) != std::string::npos) {
			result.push_back(i);
		}
	}
	return result;
}