#include "Line.h"
#include <iostream>
#include <stdexcept>
#include <vector>


static std::vector<std::string> splitLimited(const std::string& raw, char delim, size_t maxParts) {
	std::vector<std::string> parts;
	size_t start = 0;
	while (parts.size() + 1 < maxParts) {
		size_t pos = raw.find(delim, start);
		if (pos == std::string::npos) { break; }
		parts.push_back(raw.substr(start, pos - start));
		start = pos + 1;

	}
	parts.push_back(raw.substr(start));
	return parts;
}
TextLine::TextLine(const std::string& text):text_(text){}
void TextLine::print() const {
	std::cout << "Text: " << text_ << std::endl;
}
std::string TextLine::serialize() const {
	return "TEXT|" + text_;
}
const std::string& TextLine::getText() const {
	return text_;
}
void TextLine::setText(const std::string& text) {
	text_ = text;
}
void TextLine::append(const std::string& fragment) {
	text_ += fragment; 
}
void TextLine::insertAt(size_t pos, const std::string& fragment) {
	if (pos > text_.size()) {
		pos = text_.size();
	}
	text_.insert(pos, fragment);
}
void TextLine::deleteAt(size_t pos, size_t count) {
	if (pos >= text_.size()) {
		return;
	}
	text_.erase(pos, count);
}

CheckListLine::CheckListLine(const std::string& item, bool checked) :
	item_(item), checked_(checked) {}
void CheckListLine::print() const {
	std::cout << "[ " << (checked_ ? "x" : " ")<< " ] "<<item_ << std::endl;
}
std::string CheckListLine::serialize() const {
	return  std::string("CHECK|") + (checked_ ? "1" : "0") + "|" + item_;
}

void CheckListLine::toggle() {
	checked_ = !checked_;
}
bool CheckListLine::isChecked() const {
	return checked_;
}
const std::string& CheckListLine:: getItem() const{
	return item_;
}
void CheckListLine::setItem(const std::string& item) {
	item_ = item;
}


ContactLine::ContactLine(const std::string& name, const std::string& surname, const std::string& email) :
	name_(name), surname_(surname), email_(email) {
}
void ContactLine::print() const {
	std::cout << "Contact -  " << name_ << " "<<surname_<< ", E-mail: "<<email_ << std::endl;
}
std::string ContactLine::serialize() const {
	return  "CONTACT|" + name_+ "|" + surname_+"|"+email_;
}

const std::string& ContactLine::getName() const {
	return name_;
}
const std::string& ContactLine::getSurname() const {
	return surname_;
}
const std::string& ContactLine::getEmail() const {
	return email_;
}
std::unique_ptr<Line> deserializeLine(const  std::string& raw) {
	size_t firstDelim = raw.find('|');
	std::string type = (firstDelim == std::string::npos) ? raw : raw.substr(0, firstDelim);
	if (type == "TEXT") {
		std::string text = (firstDelim == std::string::npos) ? "" : raw.substr(firstDelim + 1);
		return std::make_unique<TextLine>(text);
	}
	if (type == "CHECK")
	{
		std::vector<std::string> parts = splitLimited(raw, '|', 3);
		if (parts.size() < 3) {
			throw std::invalid_argument("Corrupted CHECK line: " + raw);
		}
		bool checked = (parts[1] == "1");
		return std::make_unique<CheckListLine>(parts[2], checked);
	}
	if (type == "CONTACT")
	{
		std::vector<std::string> parts = splitLimited(raw, '|', 4);
		if (parts.size() < 4) {
			throw std::invalid_argument("Corrupted CONTACT line: " + raw);
		}

		return std::make_unique<ContactLine>(parts[1], parts[2],parts[3]);
	}
	throw std::invalid_argument("Unknown line type in: " + raw);
}

