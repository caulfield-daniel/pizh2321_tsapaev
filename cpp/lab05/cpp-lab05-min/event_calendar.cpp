#include <iostream>
#include <string>
#include <vector>

class Event {
   protected:
	std::string date_;
	std::string name_;
	std::string description_;

   private:
	static int objectCount;	 // счётчик всех объектов

   public:
	Event() : date_(""), name_(""), description_("") {
		objectCount++;
		std::cout << "Event default constructor called\n";
	}

	Event(std::string date, std::string name, std::string description)
		: date_(date), name_(name), description_(description) {
		objectCount++;
		std::cout << "Event parameterized constructor called: " << name_
				  << "\n";
	}

	Event(const Event& other)
		: date_(other.date_),
		  name_(other.name_),
		  description_(other.description_) {
		objectCount++;
		std::cout << "Event copy constructor called: " << name_ << "\n";
	}

	virtual ~Event() {
		objectCount--;
		std::cout << "Event destructor called: " << name_ << "\n";
	}

	static int getObjectCount() { return objectCount; }

	virtual void print() const = 0;
};

int Event::objectCount = 0;

class OneTimeEvent : public Event {
   private:
	std::string location_;

   public:
	OneTimeEvent(std::string date, std::string name, std::string description,
				 std::string location)
		: Event(date, name, description), location_(location) {}

	void print() const override {
		std::cout << "[One-Time Event] " << name_ << " on " << date_ << " at "
				  << location_ << "\n";
	}
};

class RecurringEvent : public Event {
   private:
	std::string recurrence_;

   public:
	RecurringEvent(std::string date, std::string name, std::string description,
				   std::string recurrence)
		: Event(date, name, description), recurrence_(recurrence) {}

	void print() const override {
		std::cout << "[Recurring Event] " << name_ << " every " << recurrence_
				  << ", starting " << date_ << "\n";
	}
};

class Calendar {
   private:
	std::string room_;
	std::string address_;
	std::vector<Event*> events_;
	static int calendarEventCount;

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
		for (int i = 0; i < events_.size(); ++i) {
			delete events_[i];
		}
		std::cout << "Calendar destructor called\n";
	}

	void addEvent(Event* e) {
		events_.push_back(e);
		calendarEventCount++;
	}

	static int getCalendarEventCount() { return calendarEventCount; }

	void print() const {
		std::cout << "*** Calendar: " << room_ << ", " << address_ << " ***\n";
		for (int i = 0; i < events_.size(); ++i) {
			events_[i]->print();
		}
	}
};

int Calendar::calendarEventCount = 0;
