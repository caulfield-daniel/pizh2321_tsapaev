from abc import ABC, abstractmethod
from typing import List, Tuple


class RobotBase(ABC):
    """
    Абстрактный класс для робота.
    """

    def __init__(self, x: int, y: int):
        """
        Инициализация робота.

        :param x: координата x
        :param y: координата y
        """
        self.__x = x
        self.__y = y

    @abstractmethod
    def move(self, moves: List[str]) -> Tuple[int, int]:
        """
        Абстрактный метод для перемещения робота.

        :param moves: список команд для перемещения
        """
        pass


class Robot(RobotBase):
    """
    Класс для робота, который может перемещаться по координатам.
    """

    def __init__(self, x: int, y: int):
        """
        Инициализация робота.

        :param x: координата x
        :param y: координата y
        """
        if (0 <= x <= 100) and (0 <= y <= 100):
            super().__init__(x, y)
            self.__path_cache = [(self._RobotBase__x, self._RobotBase__y)]
        else:
            raise ValueError("Робот должен располагаться в пределах диапазона")

    def move(self, moves: List[str]) -> Tuple[int, int]:
        """
        Перемещение робота по командам.

        :param moves: список команд для перемещения
        :return: последняя координата робота
        """
        for m in moves:
            if (self._RobotBase__x > 100 or self._RobotBase__y > 100) or (
                self._RobotBase__x < 0 or self._RobotBase__y < 0
            ):
                raise ValueError("Робот выходит за границы диапазона")
            if m == "N":
                self._RobotBase__y += 1
            elif m == "S":
                self._RobotBase__y -= 1
            elif m == "W":
                self._RobotBase__x -= 1
            elif m == "E":
                self._RobotBase__x += 1
            elif m == "":
                continue
            else:
                raise ValueError("Неверный символ!")

            self.__path_cache.append((self._RobotBase__x, self._RobotBase__y))

        return self.__path_cache[-1]

    def path(self) -> List[Tuple[int, int]]:
        """
        Возвращает путь, пройденный роботом.

        :return: список координат, пройденных роботом
        """
        return self.__path_cache

    def __str__(self) -> str:
        """
        Возвращает строковое представление робота.

        :return: строковое представление робота
        """
        return f"Robot(x={self._RobotBase__x}, y={self._RobotBase__y})"

    def __call__(self, moves: List[str]) -> Tuple[int, int]:
        """
        Вызываемый метод для перемещения робота.

        :param moves: список команд для перемещения
        :return: последняя координата робота
        """
        return self.move(moves)
