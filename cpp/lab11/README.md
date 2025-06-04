# Лабораторная работа №11

**Вариант:** 5
**Тема:** Алгоритмы STL

---

## Цель

1. Изучить и применить алгоритмы STL для работы с контейнерами.
2. Научиться сортировать, фильтровать, искать элементы и копировать по условию.
3. Продемонстрировать работу с контейнерами объектов пользовательского типа.

---

## Что сделано

| № | Реализация                                                       |
| - | ---------------------------------------------------------------- |
| 1 | Создан вектор объектов пользовательского класса `Event`          |
| 2 | Контейнер отсортирован по убыванию с использованием `std::sort`  |
| 3 | Найден первый элемент по условию с `std::find_if`                |
| 4 | Перемещены подходящие элементы во второй контейнер (`std::list`) |
| 5 | Оба контейнера отсортированы по возрастанию                      |
| 6 | Реализован просмотр содержимого контейнеров                      |

---

## Пример вывода

```bash
=== My Calendar ===
[One-Time] Exam on 2025-06-01 at Auditorium
[Recurring] Yoga every Weekly starting from 2025-06-15
[One-Time] Doctor appointment on 2025-07-20 at Clinic

=== Events after sorting by descending date ===

=== My Calendar ===
[One-Time] Doctor appointment on 2025-07-20 at Clinic
[Recurring] Yoga every Weekly starting from 2025-06-15
[One-Time] Exam on 2025-06-01 at Auditorium

=== Found event: ===
[Recurring] Yoga every Weekly starting from 2025-06-15

=== Filtered events (in list) ===
[Recurring] Yoga every Weekly starting from 2025-06-15

=== Sorting by ascending (vector) ===

=== My Calendar ===
[One-Time] Exam on 2025-06-01 at Auditorium
[Recurring] Yoga every Weekly starting from 2025-06-15
[One-Time] Doctor appointment on 2025-07-20 at Clinic
```
