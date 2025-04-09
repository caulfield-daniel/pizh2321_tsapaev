import json
from stack import Stack
from typing import List


class StackCollection:
    """
    Класс, реализующий контейнер для хранения объектов класса Stack.
    """

    def __init__(self, *args: Stack) -> None:
        """
        Инициализация контейнера.

        Параметры:
        *args (Stack): Объекты класса Stack, которые будут добавлены в контейнер.
        """
        self._data: List[Stack] = list(args)

    def __str__(self) -> str:
        """
        Возвращает строковое представление контейнера, показывающее количество стеков и их содержимое.
        """
        return f"Контейнер, содержащий {len(self._data)} стеков: {[str(stack) for stack in self._data]}"

    def __getitem__(self, index: int) -> Stack:
        """
        Позволяет использовать индексацию для доступа к элементам контейнера.

        Параметры:
          - index: индекс элемента.
        """
        return self._data[index]

    def add(self, value: Stack) -> None:
        """
        Добавляет объект Stack в контейнер.

        Параметры:
          - value: объект Stack, который нужно добавить в контейнер.
        """
        if isinstance(value, Stack):
            self._data.append(value)
        else:
            raise ValueError("Могут быть добавлены только объекты класса Stack")

    def remove(self, index: int) -> None:
        """
        Удаляет элемент из контейнера по индексу.

        Параметры:
          - index: индекс элемента, который нужно удалить.
        """
        if 0 <= index < len(self._data):
            del self._data[index]
        else:
            raise IndexError("Индекс выходит за пределы диапазона")

    def save(self, filename: str) -> None:
        """
        Сохраняет содержимое контейнера в JSON-файл.

        Параметры:
          - filename: имя файла для сохранения.
        """
        with open(filename, "w") as file:
            json.dump([stack.to_object() for stack in self._data], file)

    def load(self, filename: str) -> None:
        """
        Загружает содержимое из JSON-файла и создает объекты Stack.

        Параметры:
          - filename: имя файла для загрузки.
        """
        with open(filename, "r") as file:
            self._data = [Stack.get_stack_from_object(obj) for obj in json.load(file)]
