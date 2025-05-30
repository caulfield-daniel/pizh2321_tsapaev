#include <stdexcept>
#include <string>

#include "event_calendar.cpp"

int main() {
	try {
		Calendar calendar;

		calendar.generateLocalCatchDemo();	// локальная обработка

		calendar.addEvent(
			new OneTimeEvent("2025-06-01", "Exam", "Final exam", "Hall A"));
		calendar.addEvent(new RecurringEvent("2025-06-10", "Yoga",
											 "Weekly session", "Weekly"));

		// Исключения пользовательских типов
		try {
			calendar.addEvent(
				new OneTimeEvent("2025-07-01", "", "No name", "Room X"));
		} catch (const EmptyEventNameError& e) {
			std::cout << "[Custom Error] " << e.what() << "\n";
		}

		// Исключения стандартного типа
		try {
			calendar.addEvent(new OneTimeEvent("bad", "Invalid date",
											   "Bad date format", "Room X"));
		} catch (const InvalidDateError& e) {
			std::cout << "[Custom Error] " << e.what() << "\n";
		}

		// Исключения стандартных типов
		try {
			calendar.generateStandardException();
		} catch (const std::length_error& e) {
			std::cout << "[Standard Error] " << e.what() << "\n";
		}

		// Исключения встроенных типов
		try {
			throw 404;
		} catch (int code) {
			std::cout << "[Built-in int Exception] code = " << code << "\n";
		}

		try {
			throw std::string("Something went wrong");
		} catch (std::string& msg) {
			std::cout << "[Built-in string Exception] " << msg << "\n";
		}

		// catch-all
		try {
			throw 3.14;
		} catch (...) {
			std::cout << "[Catch all] Unknown exception caught\n";
		}

		std::cout << "\n--- Calendar Events ---\n";
		calendar.print();

	} catch (const std::exception& e) {
		std::cout << "[Main catch] " << e.what() << "\n";
	}

	return 0;
}
