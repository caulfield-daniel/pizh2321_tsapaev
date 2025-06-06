# Лабораторная работа №4

**Вариант:** 5  
**Тема:** Календарь планирования мероприятий (доработка с полиморфизмом)

---

## Цель

Добавить в базовый класс `Event` виртуальную функцию и использовать полиморфизм при работе с массивами и классом `Calendar`.

---

## Изменения

1. В базовом классе `Event` определена чисто виртуальная функция `print()`.
2. В `OneTimeEvent` и `RecurringEvent` эта функция перегружена.
3. В `main()` создан массив указателей `Event*`, содержащий объекты разных классов.
4. Модифицирован класс `Calendar` — теперь он может хранить указатели на любые производные от `Event`.
5. Реализован метод `print()` для класса `Calendar`, вызывающий `print()` всех объектов через полиморфизм.

---

## Пример вывода

```bash

\[One-Time Event]
Name: Exam
Date: 2025-06-01
Description: Final exam
Location: Auditorium

\[Recurring Event]
Name: Yoga
Date: 2025-06-10
Description: Weekly yoga
Recurrence: Weekly

```

---

## ⚠️ Сравнение с предыдущей лабораторной

| Функциональность | Лаб. №3 | Лаб. №4 |
|------------------|---------|---------|
| Наследование     | ✅      | ✅      |
| Полиморфизм      | ❌      | ✅      |
| Виртуальные методы | ❌    | ✅      |
| Массив указателей | ❌     | ✅      |
| Класс `Calendar` хранит производные | ❌ | ✅ |

---

## Выводы

- Реализован полноценный полиморфизм.
- Использование `Event*` позволило обрабатывать разные типы объектов в одном массиве.
- Класс `Calendar` теперь может работать с любыми видами мероприятий.
- Код остался простым и читаемым, без сложных конструкций.

---
