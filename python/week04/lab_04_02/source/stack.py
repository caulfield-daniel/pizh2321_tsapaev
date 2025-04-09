import json
from typing import Any, Dict, List


class Stack:
    """
    Класс, реализующий стек.
    """

    def __init__(self, *args: Any) -> None:
        """
        Инициализация стека.
        """
        self._items: List[Any] = list(args)

    def is_empty(self) -> bool:
        """
        Проверяет, пуст ли стек.

        Возвращает:
          - True, если стек пуст.
          - False, если стек не пуст.
        """
        return len(self._items) == 0

    def push(self, item: Any) -> None:
        """
        Добавляет элемент на вершину стека.

        Параметры:
          - item: элемент, который нужно добавить в стек.
        """
        self._items.append(item)

    def pop(self) -> Any:
        """
        Удаляет и возвращает элемент с вершины стека.

        Возвращает:
          - элемент с вершины стека.

        Исключения:
          - IndexError: если стек пуст.
        """
        if self.is_empty():
            raise IndexError("Попытка удалить элемент из пустого стека.")
        return self._items.pop()

    def peek(self) -> Any:
        """
        Возвращает элемент с вершины стека без его удаления.

        Возвращает:
          - элемент с вершины стека.

        Исключения:
          - IndexError: если стек пуст.
        """
        if self.is_empty():
            raise IndexError("Стек пуст, нет элементов для просмотра.")
        return self._items[-1]

    def size(self) -> int:
        """
        Возвращает количество элементов в стеке.

        Возвращает:
          - количество элементов в стеке.
        """
        return len(self._items)

    def from_string(self, string: str) -> None:
        """
        Создает стек из строки.

        Параметры:
          - string: строка, содержащая элементы стека.
        """
        self._items = string.split()

    def save(self, filename: str) -> None:
        """
        Сохраняет данные в файл в формате JSON.

        Параметры:
            filename (str): Имя файла, в который будут сохранены данные.
        """
        with open(filename, "w") as file:
            json.dump(self.to_object(), file)

    def load(self, filename: str) -> None:
        """
        Загружает данные из файла в формате JSON.

        Параметры:
            filename (str): Имя файла, из которого будут загружены данные.
        """
        with open(filename, "r") as file:
            self._items = json.load(file)

    def to_object(self) -> Dict[str, List[Any]]:
        """
        Преобразует стек в JSON-объект.

        Возвращает:
          - JSON-объект, представляющий стек.
        """
        return {"stack": self._items}

    @staticmethod
    def get_stack_from_object(data: Dict[str, List[Any]]) -> "Stack":
        """
        Преобразует JSON-объект в объект класса Stack.

        Параметры:
          - data: JSON-объект, представляющий стек.

        Возвращает:
          - объект класса Stack, созданный из JSON-объекта.
        """
        stack = Stack()
        stack._items = data["stack"]
        return stack

    def __str__(self) -> str:
        """
        Возвращает строковое представление стека. (Начиная с вершины стека)

        Возвращает:
          - строковое представление стека.
        """
        return "Stack(" + ", ".join(repr(item) for item in reversed(self._items)) + ")"
