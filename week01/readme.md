# Отчет по практической работе №01

## Программирование на языке высокого уровня (Python)

### Задание №0106. Вариант 7

### Выполнил: Цапаев Д.Д.

### Группа: ПИЖ-б-о-23-2

### E-mail: [danil.tsapaev@bk.ru](mailto:danil.tsapaev@bk.ru)

## Урок 2. Задача 1

### 1. Создание класса
 - Класс "Воин" реализован в отдельном модуле warrior.py

```py
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
```
### 2. Создание экземпляров класса
 - Созданы два юнита - first и second
 - Каждому присвоен свой идентификатор и установлено здоровье в 100 очков

```py
first = Warrior()
second = Warrior()

first.set_id(1)
second.set_id(2)

first.set_health(100)
second.set_health(100)
```

### 3. Реализация основного алгоритма
 - Создан основной цикл while True, работающий, пока здоровье одного из юнитов не станет равным нулю
 - С помощью random.choice осуществлен случайный выбор атакующего и атакуемого юнита соответственно
 - По окончанию цикла, происходит проверка на победителя. Его идентификатор выводится в консоль

```py
    while True:
        if not (first.health == 0 or second.health == 0):
            if choice((0, 1)) == 1:
                first.hit(second)
            else:
                second.hit(first)
        else:
            break
    print(
        f"ЮНИТ {first.ID if first.health > second.health
                else second.ID} победил."
    )
```
