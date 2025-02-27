from robot import Robot


if __name__ == "__main__":

    # Примеры использования:

    robot = Robot(0, 0)
    robot.move("NNNSSS")
    print(robot.path())

    # Вывод:
    # [(0, 0), (0, 1), (0, 2), (0, 3), (0, 2), (0, 1), (0, 0)]

    robot = Robot(0, 0)
    print(robot)

    # Вывод:
    # Robot(x=0, y=0)

    robot = Robot(0, 0)
    print(robot("NNNN"))

    # Вывод:
    # (0, 4)
