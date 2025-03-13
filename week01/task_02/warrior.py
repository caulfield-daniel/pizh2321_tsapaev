# Программирование на языке высокого уровня (Python).
# Задание №0106. Вариант 7
#
# Выполнил: Цапаев Д.Д.
# Группа: ПИЖ-б-о-23-2
# E-mail: danil.tsapaev@bk.ru


class Warrior:
    """Класс, реализующий тип ВОИН"""

    def set_id(self, id):
        """Устанавливает идентификатор (ID) воина"""
        self.ID = id

    def set_health(self, hp):
        """Устанавливает уровень здоровья (HP) воина"""
        self.health = hp

    def hit(self, target):
        """Осуществляет нанесение урона другому воину (объекту target)"""
        target.health -= 20
        print(
            f"ЮНИТ {self.ID} атакует ЮНИТ {target.ID}\
              Здоровье ЮНИТ {target.ID}: {target.health}\n"
        )
