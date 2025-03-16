# Программирование на языке высокого уровня (Python).
# Задание №04_02. Вариант 7
#
# Выполнил: Цапаев Д.Д.
# Группа: ПИЖ-б-о-23-2
# E-mail: danil.tsapaev@bk.ru

from stack import Stack

if __name__ == "__main__":
    stack = Stack()
    stack.push(1)
    stack.push(2)
    stack.push(3)

    print(stack)  # Stack(3, 2, 1)
    print("Вершина стека:", stack.peek())  # Вершина стека: 3
    print("Размер стека:", stack.size())  # Размер стека: 3

    print("Удаляем элемент 3: ", stack.pop())  # Удаляем элемент: 3
    print(stack)  # Stack(2, 1)

    print("Стек пуст?", stack.is_empty())  # Стек пуст? False
    print("Удаляем элемент: ", stack.pop())  # Удаляем элемент: 2
    print(stack)  # Stack(1)
    print("Удаляем элемент: ", stack.pop())  # Удаляем элемент: 1
    print(stack)  # Stack()
    print("Стек пуст?", stack.is_empty())  # Стек пуст? True
