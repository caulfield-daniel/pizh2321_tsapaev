#include <algorithm>
#include <iostream>
#include <list>

#include "event_calendar.cpp"

int main() {
	Calendar c("My Calendar");

	// Создание вектора указателей на события (динамически создаются разные типы
	// событий)
	std::vector<Event*> events = {
		new OneTimeEvent("2025-06-01", "Exam", "Math exam", "Room 101"),
		new RecurringEvent("2025-06-15", "Yoga", "Morning yoga", "Weekly"),
		new OneTimeEvent("2025-07-20", "Doctor", "Visit doctor", "Clinic")};

	// Вывод всех событий на экран
	std::cout << "All events:\n";
	for (auto e : events) e->print();

	// Поиск первого события с именем "Yoga" с помощью лямбда-функции и	
	// std::find_if
	auto found = std::find_if(events.begin(), events.end(),
							  [](auto e) { return e->name_ == "Yoga"; });

	// Если событие найдено, выводим его
	if (found != events.end()) {
		std::cout << "\nFound event:\n";
		(*found)->print();
	}

	// Создание списка для хранения только повторяющихся событий
	std::list<Event*> recurring;

	// Копирование только объектов типа RecurringEvent в список с помощью
	// std::copy_if и лямбда-функции
	std::copy_if(events.begin(), events.end(), std::back_inserter(recurring),
				 [](auto e) { return dynamic_cast<RecurringEvent*>(e); });

	// Вывод повторяющихся событий
	std::cout << "\nRecurring events:\n";
	for (auto e : recurring) e->print();

	// Сортировка вектора событий по имени с помощью std::sort и лямбда-функции
	std::sort(events.begin(), events.end(),
			  [](auto a, auto b) { return a->name_ < b->name_; });

	// Вывод отсортированных событий из вектора
	std::cout << "\nSorted events (vector):\n";
	for (auto e : events) e->print();

	// Сортировка списка повторяющихся событий по имени с помощью list::sort и
	// лямбда-функции
	recurring.sort([](auto a, auto b) { return a->name_ < b->name_; });

	// Вывод отсортированных повторяющихся событий
	std::cout << "\nSorted recurring events (list):\n";
	for (auto e : recurring) e->print();

	// Очистка динамически выделенной памяти
	for (auto e : events) delete e;
}
