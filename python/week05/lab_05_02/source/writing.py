from abc import ABC, abstractmethod
from stack import Stack
from typing import Dict


class WritingTool(ABC):
    """
    Абстрактный класс, представляющий письменную принадлежность.
    Определяет основные методы и атрибуты, которые должны реализовывать конкретные инструменты для письма.
    """

    TEXT_STYLES: Dict[str, str] = dict(
        DEFAULT="\033[0m",  # Стандартный текст
        BOLD="\033[1m",  # Жирный текст
        UNDERLINE="\033[4m",  # Подчеркнутый текст
        ITALIC="\033[3m",  # Курсив
    )

    PENCIL_COLOR = "\033[90m"  # Серый для карандаша
    PEN_COLOR = "\033[34m"  # Синий для ручки
    GEL_PEN_COLOR = "\033[35m"  # Фиолетовый для гелевой ручки

    def __init__(self):
        """
        Инициализация инструмента для письма.
        Устанавливает стандартный стиль письма и инициализирует стек для хранения текста.
        """
        self._writing_style: str = self.TEXT_STYLES[
            "DEFAULT"
        ]  # По умолчанию стандартный стиль
        self.__text_cache: Stack = Stack()  # Инициализируем стек для хранения текста

    def last_written_text(self) -> str:
        """
        Получает последний написанный текст.

        Returns:
            str: Последний текст, записанный в стек.
        """
        try:
            return self.__text_cache.peek()
        except Exception as e:
            print(f"Ошибка при получении последнего текста: {e}")
            return ""

    def undo(self) -> None:
        """
        Отменяет последнее действие, удаляя последний элемент из стека.
        """
        try:
            self.__text_cache.pop()
        except Exception as e:
            print(f"Ошибка при отмене последнего действия: {e}")

    def clear_cache(self) -> None:
        """
        Очищает стек, удаляя все записанные тексты.
        """
        try:
            self.__text_cache.clear()
        except Exception as e:
            print(f"Ошибка при очистке стека: {e}")

    def set_writing_style(self, style: str) -> None:
        """
        Устанавливает стиль письма.

        Args:
            style (str): Стиль письма. Может быть одним из следующих значений:
                - DEFAULT: Стандартный текст
                - BOLD: Жирный текст
                - UNDERLINE: Подчеркнутый текст
                - ITALIC: Курсив
        """
        try:
            self._writing_style = self.TEXT_STYLES[style.upper()]
        except KeyError:
            print(
                f"Ошибка: стиль '{style}' не поддерживается. Установлен стандартный стиль."
            )
            self._writing_style = self.TEXT_STYLES["DEFAULT"]

    def get_writing_style(self) -> str:
        """
        Получает текущий стиль письма.

        Returns:
            str: Текущий стиль письма.
        """
        return self._writing_style

    @abstractmethod
    def write(self, text: str) -> None:
        """
        Абстрактный метод для записи текста. Должен быть реализован в подклассах.

        Args:
            text (str): Текст для записи.
        """
        pass


class Pencil(WritingTool):
    """
    Класс, представляющий карандаш. Унаследован от WritingTool.
    """

    def __init__(self):
        """
        Инициализация карандаша. Устанавливает цвет для карандаша.
        """
        super().__init__()

    def write(self, text: str) -> None:
        """
        Записывает текст с использованием карандаша.

        Args:
            text (str): Текст для записи.
        """
        try:
            self._WritingTool__text_cache.push(text)
            print(
                f"{self._writing_style}{self.PENCIL_COLOR}{text}{self.TEXT_STYLES['DEFAULT']}"
            )
        except Exception as e:
            print(f"Ошибка при записи текста карандашом: {e}")


class Pen(WritingTool):
    """
    Класс, представляющий ручку. Унаследован от WritingTool.
    """

    def __init__(self):
        """
        Инициализация ручки. Устанавливает цвет для ручки.
        """
        super().__init__()

    def write(self, text: str) -> None:
        """
        Записывает текст с использованием ручки.

        Args:
            text (str): Текст для записи.
        """
        try:
            self._WritingTool__text_cache.push(text)
            print(
                f"{self._writing_style}{self.PEN_COLOR}{text}{self.TEXT_STYLES['DEFAULT']}"
            )
        except Exception as e:
            print(f"Ошибка при записи текста ручкой: {e}")


class GelPen(Pen):
    """
    Класс, представляющий гелевую ручку. Унаследован от Pen.
    """

    def __init__(self):
        """
        Инициализация гелевой ручки. Устанавливает цвет для гелевой ручки.
        """
        super().__init__()
        self._writing_style = self.GEL_PEN_COLOR

    def write(self, text: str) -> None:
        """
        Записывает текст с использованием гелевой ручки.

        Args:
            text (str): Текст для записи.
        """
        try:
            self._WritingTool__text_cache.push(text)
            print(f"{self._writing_style}{text}{self.TEXT_STYLES['DEFAULT']}")
        except Exception as e:
            print(f"Ошибка при записи текста гелевой ручкой: {e}")
