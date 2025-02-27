from robot import Robot


if __name__ == "__main__":
    robot = Robot(0, 0)

    # Примеры использования:

    robot.move("WWSSNNEE")
    print(robot.path())
    # Результат:
    # [(0, 0), (-1, 0), ... (-1, 0), (0, 0)]

    print(robot.move(""))
    # Результат:
    # (0, 0)

    print(robot(["N", "E", "S", "W"]))
    # Результат:
    # (10, 10)

    print(robot(["N", "E", "E", "W"]))
    # Результат:
    # (1, 1)

    print(robot)
    # Результат:
    # Robot(x=1, y=1)

    robot = Robot(0, 0)
    robot.move("SW")
    print(robot.path())
