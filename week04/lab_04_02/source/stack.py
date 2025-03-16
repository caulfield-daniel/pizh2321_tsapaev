class Stack:
    """Класс, реализующий стек."""

    def __init__(self):
        """Инициализация стека."""
        self.items = []

    def is_empty(self) -> bool:
        """Проверяет, пуст ли стек."""
        return len(self.items) == 0

    def push(self, item) -> None:
        """Добавляет элемент на вершину стека.

        Параметры:
          - item: элемент, который нужно добавить в стек.
        """
        self.items.append(item)

    def pop(self):
        """Удаляет и возвращает элемент с вершины стека.

        Возвращает:
          - элемент с вершины стека.
        """
        if self.is_empty():
            raise IndexError("Попытка удалить элемент из пустого стека.")
        return self.items.pop()

    def peek(self):
        """Возвращает элемент с вершины стека без его удаления.

        Возвращает:
          - элемент с вершины стека.
        """
        if self.is_empty():
            raise IndexError("Стек пуст, нет элементов для просмотра.")
        return self.items[-1]

    def size(self) -> int:
        """Возвращает количество элементов в стеке."""
        return len(self.items)

    def __str__(self) -> str:
        """Возвращает строковое представление стека."""
        return "Stack(" + ", ".join(repr(item) for item in reversed(self.items)) + ")"