#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Event {
   protected:
	std::string date_;
	std::string name_;
	std::string description_;

   public:
	Event() : date_(""), name_(""), description_("") {}
	Event(std::string date, std::string name, std::string description)
		: date_(date), name_(name), description_(description) {}

	virtual ~Event() {}

	virtual void print() const {
		std::cout << "Name: " << name_ << "\nDate: " << date_
				  << "\nDescription: " << description_ << "\n";
	}

	virtual void saveToFile(std::ofstream& out) const {
		out << "Event\n"
			<< date_ << "\n"
			<< name_ << "\n"
			<< description_ << "\n";
	}

	virtual void loadFromFile(std::ifstream& in) {
		std::getline(in, date_);
		std::getline(in, name_);
		std::getline(in, description_);
	}

	friend std::ostream& operator<<(std::ostream& os, const Event& e) {
		os << e.name_ << " (" << e.date_ << "): " << e.description_;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Event& e) {
		std::cout << "Enter name: ";
		std::getline(is, e.name_);
		std::cout << "Enter date: ";
		std::getline(is, e.date_);
		std::cout << "Enter description: ";
		std::getline(is, e.description_);
		return is;
	}
};

class OneTimeEvent : public Event {
   private:
	std::string location_;

   public:
	OneTimeEvent() : location_("") {}
	OneTimeEvent(std::string d, std::string n, std::string desc,
				 std::string loc)
		: Event(d, n, desc), location_(loc) {}

	void print() const override {
		std::cout << "[One-Time] " << name_ << " on " << date_ << " at "
				  << location_ << "\n";
	}

	void saveToFile(std::ofstream& out) const override {
		out << "OneTime\n"
			<< date_ << "\n"
			<< name_ << "\n"
			<< description_ << "\n"
			<< location_ << "\n";
	}

	void loadFromFile(std::ifstream& in) override {
		std::getline(in, date_);
		std::getline(in, name_);
		std::getline(in, description_);
		std::getline(in, location_);
	}
};

class RecurringEvent : public Event {
   private:
	std::string recurrence_;

   public:
	RecurringEvent() : recurrence_("") {}
	RecurringEvent(std::string d, std::string n, std::string desc,
				   std::string rec)
		: Event(d, n, desc), recurrence_(rec) {}

	void print() const override {
		std::cout << "[Recurring] " << name_ << " every " << recurrence_
				  << " starting from " << date_ << "\n";
	}

	void saveToFile(std::ofstream& out) const override {
		out << "Recurring\n"
			<< date_ << "\n"
			<< name_ << "\n"
			<< description_ << "\n"
			<< recurrence_ << "\n";
	}

	void loadFromFile(std::ifstream& in) override {
		std::getline(in, date_);
		std::getline(in, name_);
		std::getline(in, description_);
		std::getline(in, recurrence_);
	}
};

class Calendar {
   private:
	std::vector<Event*> events_;
	std::string name_;

   public:
	Calendar(std::string n = "Default Calendar") : name_(n) {}

	~Calendar() {
		for (int i = 0; i < events_.size(); ++i) delete events_[i];
	}

	void addEvent(Event* e) { events_.push_back(e); }

	void print() const {
		std::cout << "\n=== " << name_ << " ===\n";
		for (int i = 0; i < events_.size(); ++i) {
			events_[i]->print();
		}
	}

	void saveToFile(const std::string& filename) const {
		std::ofstream out(filename);
		out << name_ << "\n";
		out << events_.size() << "\n";
		for (int i = 0; i < events_.size(); ++i) {
			events_[i]->saveToFile(out);
		}
	}

	void loadFromFile(const std::string& filename) {
		std::ifstream in(filename);
		if (!in) {
			std::cout << "Error opening file.\n";
			return;
		}

		std::getline(in, name_);
		int count;
		in >> count;
		in.ignore();  // skip newline

		for (int i = 0; i < count; ++i) {
			std::string type;
			std::getline(in, type);
			Event* e = nullptr;
			if (type == "OneTime")
				e = new OneTimeEvent();
			else if (type == "Recurring")
				e = new RecurringEvent();
			else
				e = new Event();  // fallback (base)

			e->loadFromFile(in);
			events_.push_back(e);
		}
	}
};
