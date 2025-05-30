#include <iostream>
#include <string>
#include <vector>

class Event {
   private:
	std::string date_;
	std::string name_;
	std::string description_;

   public:
	Event() : date_(""), name_(""), description_("") {
		std::cout << "Event default constructor called" << std::endl;
	}

	Event(std::string date, std::string name, std::string description)
		: date_(date), name_(name), description_(description) {
		std::cout << "Event parameterized constructor called: " << name
				  << std::endl;
	}

	Event(const Event& other)
		: date_(other.date_),
		  name_(other.name_),
		  description_(other.description_) {
		std::cout << "Event copy constructor called: " << name_ << std::endl;
	}

	~Event() { std::cout << "Event destructor called: " << name_ << std::endl; }

	std::string getDate() const { return date_; }
	std::string getName() const { return name_; }
	std::string getDescription() const { return description_; }
};

class Calendar {
   private:
	std::string room_;
	std::string address_;
	std::vector<Event> events_;

   public:
	Calendar() : room_(""), address_("") {
		std::cout << "Calendar default constructor called" << std::endl;
	}

	Calendar(std::string room, std::string address)
		: room_(room), address_(address) {
		std::cout << "Calendar parameterized constructor called: " << room
				  << std::endl;
	}

	Calendar(const Calendar& other)
		: room_(other.room_), address_(other.address_), events_(other.events_) {
		std::cout << "Calendar copy constructor called: " << room_ << std::endl;
	}

	~Calendar() {
		std::cout << "Calendar destructor called: " << room_ << std::endl;
	}

	void addEvent(const Event& event) { events_.push_back(event); }

	void removeEvent(const std::string& eventName) {
		auto it = events_.begin();
		while (it != events_.end()) {
			if (it->getName() == eventName) {
				it = events_.erase(it);
			} else {
				++it;
			}
		}
	}

	void addEventWithParams(const std::string& date, const std::string& name,
							const std::string& description) {
		events_.emplace_back(date, name, description);
	}

	void addCopiesOfEvent(const Event& event, int count) {
		for (int i = 0; i < count; ++i) {
			events_.push_back(Event(event));
		}
	}

	void print() const {
		int i = 1;
		std::cout << "*** " << room_ << ", " << address_ << " ***" << std::endl;
		for (const Event& event : events_) {
			std::cout << "\n                           EVENT " << i
					  << std::endl;
			std::cout
				<< "-----------------------------------------------------------"
				<< std::endl;
			std::cout << "Name:\t\t" << event.getName() << std::endl;
			std::cout << "Date:\t\t" << event.getDate() << std::endl;
			std::cout << "Description:\t" << event.getDescription()
					  << std::endl;
			std::cout
				<< "-----------------------------------------------------------"
				<< std::endl;
			std::cout << std::endl;
			i++;
		}
	}
};
