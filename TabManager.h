#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Text.h"
class TabManager {
	std::vector<std::unique_ptr<Text>> tabs_;
	std::vector<std::string> names_;
	size_t activeIndex_ = 0;
public: TabManager();
	  Text& active();
	  const std::string& activeName() const; 
	  size_t activeIndex() const;
	  size_t tabCount() const;
	  void newTab(const std::string& nme = " ");
	  void closeTab(size_t index);
	  void switchTab(size_t index);
	  void renameActiveTab(const std::string& name);
	  void listTabs() const; 
};
