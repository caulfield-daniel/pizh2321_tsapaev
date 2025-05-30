#include "event_calendar.cpp"

int main() {
	Calendar calendar("My Events");

	calendar.addEvent(
		new OneTimeEvent("2025-06-01", "Exam", "Final exam", "Hall A"));
	calendar.addEvent(
		new RecurringEvent("2025-06-15", "Yoga", "Weekly yoga", "Weekly"));

	std::cout << "--- Original Calendar ---\n";
	calendar.print();

	std::string filename = "calendar_data.txt";
	calendar.saveToFile(filename);
	std::cout << "\nCalendar saved to file.\n";

	Calendar loadedCalendar;
	loadedCalendar.loadFromFile(filename);
	std::cout << "\n--- Loaded Calendar ---\n";
	loadedCalendar.print();

	return 0;
}
