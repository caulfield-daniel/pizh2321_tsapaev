#include "event_calendar.cpp"

int main() {
    // Конструктор с параметрами
    Calendar classroom_calendar("Classroom 9-528", "Stavropol, Kulakova prospect, 2");
    
    // Конструктор с параметрами
    Event lesson1("2023-04-26", "Lesson 1", "Individual project practicum. PIZH-b-0-23-2");
    
    // Конструктор копирования
    classroom_calendar.addEvent(lesson1);
    
    // Конструкто по умолчанию
    Calendar default_calendar;
    
    // Конструктор копирования
    Calendar copied_calendar = classroom_calendar;
    
    // Метод с параметрами (создает Event внутри)
    classroom_calendar.addEventWithParams("2023-04-27", "New Event", "Another description");
    
    // Конструктор по умолчанию
    Event default_event;
    
    // Метод с копиями
    classroom_calendar.addCopiesOfEvent(lesson1, 2);
    
    classroom_calendar.print();
    classroom_calendar.removeEvent("Lesson 1");
    classroom_calendar.print();

    return 0;
}