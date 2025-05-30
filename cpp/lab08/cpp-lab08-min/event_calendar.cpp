#include <iostream>
#include <string>
#include <vector>

#include "custom_exceptions.h"

class Event {
   protected:
	std::string date_;
	std::string name_;
	std::string description_;

   public:
	Event() : date_(""), name_(""), description_("") {}

	Event(std::string date, std::string name, std::string description)
		: date_(date), name_(name), description_(description) {
		if (name.empty()) throw EmptyEventNameError();
		if (date.length() != 10)
			throw InvalidDateError();  // Примитивная проверка
	}

	virtual ~Event() {}

	virtual void print() const = 0;
};

class OneTimeEvent : public Event {
	std::string location_;

   public:
	OneTimeEvent(std::string date, std::string name, std::string description,
				 std::string location)
		: Event(date, name, description), location_(location) {}

	void print() const override {
		std::cout << "[One-Time] " << name_ << " on " << date_ << " at "
				  << location_ << "\n";
	}
};

class RecurringEvent : public Event {
	std::string recurrence_;

   public:
	RecurringEvent(std::string date, std::string name, std::string description,
				   std::string recurrence)
		: Event(date, name, description), recurrence_(recurrence) {}

	void print() const override {
		std::cout << "[Recurring] " << name_ << " every " << recurrence_
				  << ", starting " << date_ << "\n";
	}
};

class Calendar {
	std::vector<Event*> events_;

   public:
	~Calendar() {
		for (int i = 0; i < events_.size(); ++i) delete events_[i];
	}

	void addEvent(Event* e) { events_.push_back(e); }

	void print() const {
		for (int i = 0; i < events_.size(); ++i) {
			events_[i]->print();
		}
	}

	void generateStandardException() {
		throw std::length_error("Simulated length_error");
	}

	void generateCustomLogicError() { throw InvalidDateError(); }

	void generateLocalCatchDemo() {
		try {
			throw std::out_of_range("Demo out_of_range in local method");
		} catch (const std::out_of_range& e) {
			std::cout << "[Local catch] " << e.what() << "\n";
		}
	}
};
