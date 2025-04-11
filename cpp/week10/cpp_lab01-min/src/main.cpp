#include "event_calendar.cpp"
#include <iostream>

int main() {
	Calendar classroom_calendar("Classroom 9-528", "Stavropol, Kulakova prospect, 2");
	classroom_calendar.addEvent(Event("2023-04-26", "Lesson 1", "Individual project practicum. PIZH-b-0-23-2"));
	classroom_calendar.addEvent(Event("2023-04-26", "Lesson 2", "Individual project practicum. PIZH-b-0-23-1"));
	classroom_calendar.print();
	classroom_calendar.removeEvent("Lesson 1");
	classroom_calendar.print();
	return 0;
}
