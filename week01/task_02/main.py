# Программирование на языке высокого уровня (Python).
# Задание №0102. Вариант 7
#
# Выполнил: Цапаев Д.Д.
# Группа: ПИЖ-б-о-23-2
# E-mail: danil.tsapaev@bk.ru

from random import choice
from warrior import Warrior

if __name__ == "__main__":
    first = Warrior()
    second = Warrior()

    first.set_id(1)
    second.set_id(2)

    first.set_health(100)
    second.set_health(100)

    while True:
        if not (first.health == 0 or second.health == 0):
            if choice((0, 1)):
                first.hit(second)
            else:
                second.hit(first)
        else:
            break
    print(
        f"ЮНИТ {first.ID if first.health > second.health
                else second.ID} победил."
    )
