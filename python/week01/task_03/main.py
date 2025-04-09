# Программирование на языке высокого уровня (Python).
# Задание №03. Вариант 7
#
# Выполнил: Цапаев Д.Д.
# Группа: ПИЖ-б-о-23-2
# E-mail: danil.tsapaev@bk.ru

from person import Person

if __name__ == "__main__":

    employees = [
        Person("Иван", "Иванов", 3),
        Person("Василий", "Васильев", 2),
        Person("John", "Smith", 10),
    ]

    employees.pop(1)
    input()
