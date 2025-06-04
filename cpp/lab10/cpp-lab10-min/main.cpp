#include "event_calendar.cpp"

int main() {
	Calendar myCalendar("My Events");

	myCalendar.addEvent(
		new OneTimeEvent("2025-06-01", "Exam", "Final exam in math", "Hall A"));
	myCalendar.addEvent(new RecurringEvent("2025-06-15", "Yoga",
										   "Weekly yoga class", "Weekly"));

	myCalendar.print();
	myCalendar.saveToFile("calendar.txt");

	Calendar loadedCalendar;
	loadedCalendar.loadFromFile("calendar.txt");
	loadedCalendar.print();

	return 0;
}
