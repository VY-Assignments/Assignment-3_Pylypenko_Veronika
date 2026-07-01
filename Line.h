#pragma once
#include<string>
#include<memory>

class Line {
public:
	virtual void print() const = 0;
	virtual std::string serialize() const = 0;
	virtual ~Line() = default;
};
class TextLine : public Line {
	std::string text_;
public: explicit TextLine(const std::string& text);
	  void print() const override;
	  std::string serialize() const override;
	  const std::string& getText() const;
	  void setText(const std::string& text);
	  void append(const std::string& fragment);
	  void insertAt(size_t pos, const std::string& fragment);
	  void deleteAt(size_t pos, size_t count);

};
class CheckListLine :public Line {
public:
	virtual void print() const = 0;
	std::string item_;
	bool checked_;
public: CheckListLine(const std::string& item, bool checked);
	  void print() const override;
	  std::string serialize() const override;
	  void toggle();
	  bool isChecked() const;
	  const std::string& getItem() const;
	  void setItem(const std::string& item);
};
class ContactLine :public Line {
public:
	std::string name_;
	std::string surname_;
	std::string email_;
public: ContactLine(const std::string& name, const std::string& surname, const std::string& email);
	  void print() const override;
	  const std::string& getName() const;
	  const std::string& getSurname() const;
	  const std::string& getEmail() const;
};
std::unique_ptr<Line> deserializeLine(const  std::string& raw);
