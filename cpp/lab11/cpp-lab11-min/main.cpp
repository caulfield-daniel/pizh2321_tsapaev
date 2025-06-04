#include "event_calendar.cpp"

int main() {
	Calendar cal("My Calendar");

	// Добавим события
	cal.addEvent(
		new OneTimeEvent("2025-06-01", "Exam", "Final exams", "Auditorium"));
	cal.addEvent(new RecurringEvent("2025-06-15", "Yoga", "Weekly yoga class",
									"Weekly"));
	cal.addEvent(new OneTimeEvent("2025-07-20", "Doctor appointment",
								  "Visit to Dr. Smith", "Clinic"));

	// 1. Вывод всех событий
	cal.print();

	// 2. Сортировка по убыванию даты
	cal.sortDescending();
	std::cout << "\n=== Events after sorting by descending date ===\n";
	cal.print();

	// 3. Поиск первого события, где имя содержит "Yoga"
	Event* found = cal.findEventByName("Yoga");
	if (found) {
		std::cout << "\n=== Found event: ===\n";
		found->printShort();
	}

	// 4. Копирование повторяющихся событий в list
	std::list<Event*> recurringList = cal.filterRecurringEvents();

	// Сортируем list по возрастанию даты
	recurringList.sort([](const Event* a, const Event* b) {
		return a->getDate() < b->getDate();
	});

	// 5. Вывод событий из списка
	std::cout << "\n=== Filtered events (in list) ===\n";
	for (auto e : recurringList) e->printShort();

	// 6. Сортируем вектор по возрастанию и выводим
	cal.sortAscending();
	std::cout << "\n=== Sorting by ascending (vector) ===\n";
	cal.print();

	// Вывод списка отсортированного (уже сделан выше)

	return 0;
}
