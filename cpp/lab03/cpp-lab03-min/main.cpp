#include "event_calendar.cpp"

int main() {
	std::cout << "\n--- Base Event ---\n";
	Event base("2025-05-30", "Base", "Base description");
	base.print();

	std::cout << "\n--- One-Time Event ---\n";
	OneTimeEvent one("2025-06-01", "Exam", "Final exam", "Auditorium");
	one.print();

	std::cout << "\n--- Recurring Event ---\n";
	RecurringEvent repeat("2025-06-10", "Yoga", "Weekly yoga session",
						  "Weekly");
	repeat.print();

	std::cout << "\n--- Array of Events (base + derived) ---\n";
	Event events[3] = {
		Event("2025-07-01", "Simple Event", "Something"),
		OneTimeEvent("2025-07-02", "Meeting", "Team meeting", "Room A"),
		RecurringEvent("2025-07-03", "Standup", "Daily sync", "Daily")};

	for (int i = 0; i < 3; ++i) {
		std::cout << "\nEvent " << i + 1 << ":\n";
		events[i].print();	// будет вызываться метод базового класса
	}

	std::cout << "\n--- Array of RecurringEvent ---\n";
	RecurringEvent rec_events[2] = {
		RecurringEvent("2025-08-01", "Sprint Planning", "Agile", "Bi-weekly"),
		RecurringEvent("2025-08-10", "Review", "Sprint review", "Monthly")};

	for (int i = 0; i < 2; ++i) {
		std::cout << "\nRecurringEvent " << i + 1 << ":\n";
		rec_events[i].print();
	}

	return 0;
}
