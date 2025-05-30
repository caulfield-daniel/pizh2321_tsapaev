#include "event_calendar.cpp"

int main() {
	std::cout << "\n--- Статистика до создания объектов ---\n";
	std::cout << "Event objects: " << Event::getObjectCount() << "\n";
	std::cout << "Calendar event entries: " << Calendar::getCalendarEventCount()
			  << "\n";

	Calendar calendar("Room 203", "Main Campus");

	calendar.addEvent(
		new OneTimeEvent("2025-06-01", "Exam", "Final", "Hall A"));
	calendar.addEvent(
		new RecurringEvent("2025-06-10", "Yoga", "Weekly class", "Weekly"));
	calendar.addEvent(new OneTimeEvent("2025-07-15", "Conference", "IT event",
									   "Conference Hall"));

	std::cout << "\n--- Статистика после добавления ---\n";
	std::cout << "Event objects: " << Event::getObjectCount() << "\n";
	std::cout << "Calendar event entries: " << Calendar::getCalendarEventCount()
			  << "\n";

	std::cout << "\n--- Содержимое календаря ---\n";
	calendar.print();

	return 0;
}
