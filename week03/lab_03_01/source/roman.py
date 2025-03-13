from typing import Union


class Roman:
   """
   Класс Roman реализует работу с римскими числами.

   Ограничения: число должно быть в пределах [1; 3999].
   """

   ARABIC_MIN: int = 1
   ARABIC_MAX: int = 3999

   LETTERS: list[str] = [
       "M",
       "CM",
       "D",
       "CD",
       "C",
       "XC",
       "L",
       "XL",
       "X",
       "IX",
       "V",
       "IV",
       "I",
   ]
   NUMBERS: list[int] = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]

   def __init__(self, value: Union[int, str]) -> None:
       """
       Создает экземпляр класса Roman.

       :param value: Значение римского числа, может быть арабским числом или строкой.
       :raises TypeError: Если значение не является арабским числом или строкой.
       """
       if isinstance(value, int):
           self.__check_arabic(value)
           self._arabic: int = value
       elif isinstance(value, str):
           self.__check_roman(value)
           self._arabic: int = self.to_arabic(value)
       else:
           raise TypeError(f"Не могу создать римское число из {type(value)}.")

   def __add__(self, other: Union["Roman", int]) -> "Roman":
       """
       Складывает текущее римское число с другим римским числом или арабским числом.

       :param other: Другое римское число или арабское число.
       :return: Результат сложения в виде римского числа.
       """
       return self.__operate(other, lambda x, y: x + y)

   def __sub__(self, other: Union["Roman", int]) -> "Roman":
       """
       Вычитает из текущего римского числа другое римское число или арабское число.

       :param other: Другое римское число или арабское число.
       :return: Результат вычитания в виде римского числа.
       """
       return self.__operate(other, lambda x, y: x - y)

   def __mul__(self, other: Union["Roman", int]) -> "Roman":
       """
       Умножает текущее римское число на другое римское число или арабское число.

       :param other: Другое римское число или арабское число.
       :return: Результат умножения в виде римского числа.
       """
       return self.__operate(other, lambda x, y: x * y)

   def __floordiv__(self, other: Union["Roman", int]) -> "Roman":
       """
       Выполняет целочисленное деление текущего римского числа на другое римское число или арабское число.

       :param other: Другое римское число или арабское число.
       :return: Результат деления в виде римского числа.
       """
       return self.__operate(other, lambda x, y: x // y)

   def __truediv__(self, other: Union["Roman", int]) -> "Roman":
       """
       Выполняет деление текущего римского числа на другое римское число или арабское число.

       :param other: Другое римское число или арабское число.
       :return: Результат деления в виде римского числа.
       """
       return self.__floordiv__(other)

   def __str__(self) -> str:
       """
       Возвращает строковое представление римского числа.

       :return: Строковое представление римского числа.
       """
       return self.to_roman(self._arabic)

   @staticmethod
   def __check_arabic(value: int) -> None:
       """
       Проверяет, что арабское число находится в допустимом диапазоне.

       :param value: Арабское число.
       :raises ValueError: Если арабское число не находится в допустимом диапазоне.
       """
       if not (Roman.ARABIC_MIN <= value <= Roman.ARABIC_MAX):
           raise ValueError(
               f"Арабское число должно быть в диапазоне от {Roman.ARABIC_MIN} до {Roman.ARABIC_MAX}."
           )

   @staticmethod
   def __check_roman(value: str) -> None:
       """
       Проверяет, что римское число содержит только допустимые символы.

       :param value: Римское число.
       :raises ValueError: Если римское число содержит недопустимые символы.
       """
       valid_chars = set(Roman.LETTERS)
       for char in str(value):
           if char.upper() not in valid_chars:
               raise ValueError(f"Недопустимый символ '{char}' в римском числе.")

   def __operate(self, other: Union["Roman", int], operation) -> "Roman":
       """
       Выполняет операцию над текущим римским числом и другим римским числом или арабским числом.

       :param other: Другое римское число или арабское число.
       :param operation: Функция, реализующая операцию.
       :return: Результат операции в виде римского числа.
       :raises TypeError: Если другой операнд не является римским числом или арабским числом.
       """
       if isinstance(other, Roman):
           result = operation(self._arabic, other._arabic)
       elif isinstance(other, int):
           result = operation(self._arabic, other)
       else:
           raise TypeError(f"Не могу выполнить операцию с {type(other)}.")

       self.__check_arabic(result)
       return Roman(result)

   @property
   def arabic(self) -> int:
       """
       Возвращает арабское представление римского числа.

       :return: Арабское представление римского числа.
       """
       return self._arabic

   @staticmethod
   def to_arabic(roman: Union[str, "Roman"]) -> int:
       """
       Преобразует римское число в арабское.

       :param roman: Римское число.
       :return: Арабское представление римского числа.
       :raises ValueError: Если римское число содержит недопустимые символы.
       """
       Roman.__check_roman(roman)

       def letter_to_number(letter: str) -> int:
           if letter not in Roman.LETTERS:
               raise ValueError(f"Недопустимый символ '{letter}' в римском числе.")
           return Roman.NUMBERS[Roman.LETTERS.index(letter.upper())]

       i, value = 0, 0
       roman = str(roman)

       while i < len(roman):
           number = letter_to_number(roman[i])
           i += 1

           if i < len(roman):
               next_number = letter_to_number(roman[i])
               if next_number > number:
                   value += next_number - number
                   i += 1
               else:
                   value += number
           else:
               value += number

       Roman.__check_arabic(value)
       return value

   @staticmethod
   def to_roman(arabic: int) -> str:
       """
       Преобразует арабское число в римское.

       :param arabic: Арабское число.
       :return: Римское представление арабского числа.
       :raises ValueError: Если арабское число не находится в допустимом диапазоне.
       """
       Roman.__check_arabic(arabic)

       roman = ""
       for i, number in enumerate(Roman.NUMBERS):
           while arabic >= number:
               roman += Roman.LETTERS[i]
               arabic -= number

       return roman