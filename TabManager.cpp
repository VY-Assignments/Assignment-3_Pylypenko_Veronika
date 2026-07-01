#include "TabManager.h"
#include <iostream>
TabManager::TabManager() {
tabs_.push_back(std::make_unique<Text>());
names_.push_back("Tab 1"); 
activeIndex_ = 0; 
}
Text& TabManager::active() {
	return *tabs_[activeIndex_];

}
size_t TabManager::activeIndex() const {
	return activeIndex_; 
}
size_t TabManager::tabCount() const {
	return tabs_.size();
}
void TabManager::newTab(const std::string& name) {
	tabs_.push_back(std::make_unique<Text>());
	std::string  finalName = name.empty() ? ("Tab " + std::to_string(tabs_.size())) : name;
	names_.push_back(finalName);
	activeIndex_ = tabs_.size() - 1;
	std::cout << "Created and switched to \"" << finalName << "\"\n";
}
void TabManager::closeTab(size_t index) {
if (index >= tabs_.size()) {
	std::cout << "Tab index is out of range.\n";
	return;
}
if (tabs_.size() == 1) {
	std::cout << "Cannot close the last remaining tab.\n"; return;
}
std::cout << "Tab closed. Active tab is now \"" << names_[activeIndex_] << "\"\n";}

void TabManager::switchTab(size_t index) {
	if (index >= tabs_.size()) {
		std::cout << "Tab index is out of range.\n";
		return;
	}
	activeIndex_ = index;
	std::cout << "Switched to \"" << names_[activeIndex_] << "\"\n";
}

void TabManager::renameActiveTab(const std::string& name) {
	if (!name.empty()) {
		names_[activeIndex_] = name;
	}
}

void TabManager::listTabs() const {
	for (size_t i = 0; i < tabs_.size(); ++i) {
		std::cout << (i == activeIndex_ ? "* " : "  ")
			<< "[" << i << "] " << names_[i]
			<< " (" << tabs_[i]->size() << " lines)\n";
	}
}
