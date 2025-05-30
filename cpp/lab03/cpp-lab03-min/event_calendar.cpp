#include <iostream>
#include <string>
#include <vector>

class Event {
   protected:
	std::string date_;
	std::string name_;
	std::string description_;

   public:
	Event() : date_(""), name_(""), description_("") {
		std::cout << "Event default constructor called\n";
	}

	Event(std::string date, std::string name, std::string description)
		: date_(date), name_(name), description_(description) {
		std::cout << "Event parameterized constructor called: " << name_
				  << "\n";
	}

	Event(const Event& other)
		: date_(other.date_),
		  name_(other.name_),
		  description_(other.description_) {
		std::cout << "Event copy constructor called: " << name_ << "\n";
	}

	~Event() { std::cout << "Event destructor called: " << name_ << "\n"; }

	void input() {
		std::cout << "Enter name: ";
		std::getline(std::cin, name_);
		std::cout << "Enter date: ";
		std::getline(std::cin, date_);
		std::cout << "Enter description: ";
		std::getline(std::cin, description_);
	}

	void print() const {
		std::cout << "Name: " << name_ << "\n";
		std::cout << "Date: " << date_ << "\n";
		std::cout << "Description: " << description_ << "\n";
	}
};

class OneTimeEvent : public Event {
   private:
	std::string location_;

   public:
	OneTimeEvent() : Event(), location_("") {
		std::cout << "OneTimeEvent default constructor called\n";
	}

	OneTimeEvent(std::string date, std::string name, std::string description,
				 std::string location)
		: Event(date, name, description), location_(location) {
		std::cout << "OneTimeEvent parameterized constructor called: " << name_
				  << "\n";
	}

	OneTimeEvent(const OneTimeEvent& other)
		: Event(other), location_(other.location_) {
		std::cout << "OneTimeEvent copy constructor called: " << name_ << "\n";
	}

	~OneTimeEvent() {
		std::cout << "OneTimeEvent destructor called: " << name_ << "\n";
	}

	void input() {
		Event::input();
		std::cout << "Enter location: ";
		std::getline(std::cin, location_);
	}

	void print() const {
		Event::print();
		std::cout << "Location: " << location_ << "\n";
	}
};

class RecurringEvent : public Event {
   private:
	std::string recurrence_;

   public:
	RecurringEvent() : Event(), recurrence_("") {
		std::cout << "RecurringEvent default constructor called\n";
	}

	RecurringEvent(std::string date, std::string name, std::string description,
				   std::string recurrence)
		: Event(date, name, description), recurrence_(recurrence) {
		std::cout << "RecurringEvent parameterized constructor called: "
				  << name_ << "\n";
	}

	RecurringEvent(const RecurringEvent& other)
		: Event(other), recurrence_(other.recurrence_) {
		std::cout << "RecurringEvent copy constructor called: " << name_
				  << "\n";
	}

	~RecurringEvent() {
		std::cout << "RecurringEvent destructor called: " << name_ << "\n";
	}

	void input() {
		Event::input();
		std::cout << "Enter recurrence: ";
		std::getline(std::cin, recurrence_);
	}

	void print() const {
		Event::print();
		std::cout << "Recurrence: " << recurrence_ << "\n";
	}
};
