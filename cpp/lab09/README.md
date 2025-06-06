# Лабораторная работа №9

**Вариант:** 5  
**Тема:** Сериализация и глобальные операторы

---

## Цель

1. Добавить перегрузку глобальных операторов `>>` и `<<` для базового класса `Event`.
2. Реализовать сохранение данных `Calendar` в файл.
3. Реализовать чтение данных из файла обратно в `Calendar`.

---

## Что сделано

| № | Реализация |
|---|------------|
| 1 | Глобальные операторы `>>` и `<<` для класса `Event` |
| 2 | Методы `saveToFile()` и `loadFromFile()` в `Calendar` |
| 3 | Поддержка разных типов событий при загрузке из файла |
| 4 | Простое текстовое форматирование, легко читаемое |

---

## Пример вывода

```bash

\=== My Events ===
\[One-Time] Exam on 2025-06-01 at Hall A
\[Recurring] Yoga every Weekly starting from 2025-06-15

Calendar saved to file.

\=== Loaded Calendar ===
\[One-Time] Exam on 2025-06-01 at Hall A
\[Recurring] Yoga every Weekly starting from 2025-06-15

```

---

## Выводы

- Операторы `>>` и `<<` облегчают работу с пользовательским вводом/выводом.
- Чтение и запись в файл позволяют сохранять данные между запусками.
- Файл легко читаем и может быть редактирован вручную.
- Расширяемая структура (поддержка разных типов событий при чтении).

---
