# Программирование на языке высокого уровня (Python).
# Задание №04_02. Вариант 7
#
# Выполнил: Цапаев Д.Д.
# Группа: ПИЖ-б-о-23-2
# E-mail: danil.tsapaev@bk.ru

from stack import Stack

if __name__ == "__main__":

    # Создаем новый стек
    s = Stack()

    # Проверяем, пуст ли стек
    print(s.is_empty())  # Вывод: True

    # Добавляем элементы в стек
    s.push(1)
    s.push(2)
    s.push(3)
    
    # Проверяем размер стека
    print(s.size())  # Вывод: 3

    # Проверяем верхний элемент стека
    print(s.peek())  # Вывод: 3

    # Удаляем верхний элемент стека
    print(s.pop())  # Вывод: 3

    # Проверяем размер стека после удаления элемента
    print(s.size())  # Вывод: 2

    # Проверяем, пуст ли стек после удаления элементов
    print(s.is_empty())  # Вывод: False

    # Создаем стек из строки
    s.from_string("4 5 6 7 8 9")

    # Проверяем размер стека после создания из строки
    print(s.size())  # Вывод: 3

    # Сохраняем стек в файл
    s.save("stack.json")

    # Загружаем стек из файла
    s.load("stack.json")

    # Проверяем размер стека после загрузки из файла
    print(s.size())  # Вывод: 3

    # Выводим строковое представление стека
    print(s)  # Вывод: Stack('6', '5', '4')
