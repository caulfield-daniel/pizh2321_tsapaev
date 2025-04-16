# Лабораторная работа №1

## Тема: Утилита WordCount

**Выполнил:** Цапаев Д.Д  
**Курс:** 2  
**Группа:** ПИЖ-б-о-23-2  

***

## Задача

Реализовать [утилиту](https://ru.wikipedia.org/wiki/%D0%A3%D1%82%D0%B8%D0%BB%D0%B8%D1%82%D0%B0) WordCount подсчитывающую количество строк, слов и байт для указанного файла и выводить эту информацию в поток вывода.  
Программа должна поддерживать следующие опции:

**-l, --lines**    вывод только количества строк

**-c, --bytes**    вывод размера файла в байтах

**-w, --words**    вывод количества слов

**-m, --chars**     вывод количества букв*

Название файла и опции передаются через аргументы командной строки в следующем формате:

_**WordCount.exe [OPTION] filename [filename,.....]***_

Формат вывода (без заданных опций):
  lines words bytes filename
  
### Примеры запуска программы

WordCount.exe filename1_

WordCount.exe filename1 filename2_

WordCount.exe --words --lines filename1_

WordCount.exe -l -c filename1_

WordCount.exe -lwc filename1 filename2_

WordCount.exe  filename1 filename2 -lw --bytes_

"  

## 1. Введение

Код реализует утилиту для анализа файлов, аналогичную Unix-утилите `wc`. Состоит из трёх основных классов:

- `FileStats` - сбор статистики по файлу
- `ArgumentParser` - обработка аргументов командной строки
- `ResultPrinter` - форматированный вывод результатов

## 2. Структура классов

### 2.1 Класс FileStats

**Назначение**: Анализ файла и хранение статистики

**Поля**:

| Поле | Тип | Описание |
|-------|------|-------------|
| `lines_` | `size_t` | Количество строк |
| `words_` | `size_t` | Количество слов |
| `chars_` | `size_t` | Количество символов |
| `bytes_` | `size_t` | Размер в байтах |
| `filename_` | `std::string` | Имя файла |

**Основные методы**:

```cpp
void analyze() // Двухпроходной анализ файла
void count_words(const std::string& line) // Логика подсчёта слов
```

### 2.2 Класс ArgumentParser

**Назначение**: Обработка аргументов командной строки

**Поля**:

| Поле | Тип | Описание |
|-------|------|-------------|
| `show_lines_` | `bool` | Флаг показа строк |
| `show_words_` | `bool` | Флаг показа слов |
| `show_bytes_` | `bool` | Флаг показа байтов |
| `show_chars_` | `bool` | Флаг показа символов |
| `filenames_` | `vector<string>` | Список файлов |

**Основные методы**:

```cpp
void parse(int argc, char* argv[]) // Парсинг аргументов
bool show_lines() const // Геттер для флага строк
```

### 2.3 Класс ResultPrinter

**Назначение**: Форматированный вывод результатов

**Методы**:

```cpp
static void print(const FileStats& stats, const ArgumentParser& parser)
```

## 3. Особенности реализации

### 3.1 Основная функциональность

- **Двухпроходной анализ**:
  1. Первый проход: точный подсчёт байтов через `tellg()`
  2. Второй проход: подсчёт строк/слов/символов

- **Определение слов**:

  ```cpp
  if (std::isspace(c)) inWord = false;
  else if (!inWord) { words_++; inWord = true; }
  ```

- **Динамический вывод**:

  ```cpp
  if (parser.show_lines()) cout << stats.get_lines() << " ";
  ```

### 3.2 Обработка аргументов

- Поддержка комбинированных флагов (`-lwc`)
- Автоматический выбор режима:

  ```cpp
  if no flags: показать строки, слова и байты
  ```

## 4. Примеры использования

```bash
wc filename1_

wc filename1 filename2_

wc --words --lines filename1_

wc -l -c filename1_

wc -lwc filename1 filename2_

wc filename1 filename2 -lw --bytes_
```

## 5. Ограничения

- **Размер файла**: Ограничен типом `size_t` (4GB на 32-битных системах)
- **Кодировка**: Оптимизировано для ASCII/UTF-8
- **Разделители слов**: Стандартные пробельные символы
- **Переносы строк**: `\n` считается за 1 символ

## 6. Диаграмма классов

Для отображения необходимо расширение bierner.markdown-mermaid

```Mermaid
classDiagram
    class FileStats {
        -lines_ : size_t
        -words_ : size_t
        -chars_ : size_t
        -bytes_ : size_t
        -filename_ : string
        +analyze()
        +геттеры...
    }
    
    class ArgumentParser {
        -show_lines_ : bool
        -show_words_ : bool
        -show_bytes_ : bool
        -show_chars_ : bool
        -filenames_ : vector<string>
        +parse()
        +геттеры...
    }
    
    class ResultPrinter {
        +print()
    }
    
    ArgumentParser --> FileStats
    ResultPrinter --> FileStats
    ResultPrinter --> ArgumentParser
```
