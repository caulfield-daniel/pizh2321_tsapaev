#include "event_calendar.cpp"

int main() {
	std::cout << "\n=== Массив Event* (базовый тип) ===\n";

	Event* eventArray[3];
	eventArray[0] =
		new OneTimeEvent("2025-06-01", "Exam", "Final exam", "Auditorium");
	eventArray[1] =
		new RecurringEvent("2025-06-10", "Yoga", "Weekly yoga", "Weekly");
	eventArray[2] =
		new OneTimeEvent("2025-07-01", "Meeting", "Team sync", "Room B");

	for (int i = 0; i < 3; ++i) {
		std::cout << "\nEvent " << i + 1 << ":\n";
		eventArray[i]->print();
	}

	std::cout << "\n=== Работа с Calendar ===\n";

	Calendar c("Room 301", "Main Campus");
	c.addEvent(
		new RecurringEvent("2025-08-01", "Scrum", "Sprint Scrum", "Daily"));
	c.addEvent(
		new OneTimeEvent("2025-08-15", "Defense", "Project defense", "Hall 1"));
	c.print();

	// Очистка вручную eventArray
	for (int i = 0; i < 3; ++i) {
		delete eventArray[i];
	}

	return 0;
}
