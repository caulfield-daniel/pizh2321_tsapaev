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

	virtual ~Event() {
		std::cout << "Event destructor called: " << name_ << "\n";
	}

	virtual void print() const = 0;	 // Чисто виртуальная функция
};

// Разовое мероприятие
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

	~OneTimeEvent() override {
		std::cout << "OneTimeEvent destructor called: " << name_ << "\n";
	}

	void print() const override {
		std::cout << "[One-Time Event]\n";
		std::cout << "Name: " << name_ << "\n";
		std::cout << "Date: " << date_ << "\n";
		std::cout << "Description: " << description_ << "\n";
		std::cout << "Location: " << location_ << "\n";
	}
};

// Повторяющееся мероприятие
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

	~RecurringEvent() override {
		std::cout << "RecurringEvent destructor called: " << name_ << "\n";
	}

	void print() const override {
		std::cout << "[Recurring Event]\n";
		std::cout << "Name: " << name_ << "\n";
		std::cout << "Date: " << date_ << "\n";
		std::cout << "Description: " << description_ << "\n";
		std::cout << "Recurrence: " << recurrence_ << "\n";
	}
};

// Модифицированный класс Calendar
class Calendar {
   private:
	std::string room_;
	std::string address_;
	std::vector<Event*> events_;  // указатели на базовый класс

   public:
	Calendar() : room_(""), address_("") {
		std::cout << "Calendar default constructor called\n";
	}

	Calendar(std::string room, std::string address)
		: room_(room), address_(address) {
		std::cout << "Calendar parameterized constructor called: " << room_
				  << "\n";
	}

	~Calendar() {
		std::cout << "Calendar destructor called: " << room_ << "\n";
		for (int i = 0; i < events_.size(); ++i) {
			delete events_[i];
		}
	}

	void addEvent(Event* event) { events_.push_back(event); }

	void print() const {
		std::cout << "\n*** Calendar: " << room_ << ", " << address_
				  << " ***\n";
		for (int i = 0; i < events_.size(); ++i) {
			std::cout << "\nEvent " << i + 1 << ":\n";
			events_[i]->print();
		}
	}
};
