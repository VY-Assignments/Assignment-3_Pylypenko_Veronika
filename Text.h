#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Line.h"
class Text {
	std::vector<std::unique_ptr<Line>> lines_;
public: Text() = default; 
	  void addLine(std::unique_ptr<Line> line);
	  void insertLine(size_t index, std::unique_ptr<Line> line);
	  void removeLine(size_t index);
	  size_t size() const; 
	  bool empty() const;
	  Line* getLine(size_t index) const;
	  void printAll() const;
	  std::string serializeAll() const;
	  void loadFromSerialized(const std::string& data);
	  void clear();
	  std::vector<size_t> find(const std::string& target) const;
};