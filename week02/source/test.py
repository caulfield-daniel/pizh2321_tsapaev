import pytest
from mockito import mock, when, verify
from robot import Robot


class TestRobot:
    def test_move(self):
        robot = Robot(0, 0)
        robot.move("NNNSSSW")
        assert robot.path() == [
            (0, 0),
            (0, 1),
            (0, 2),
            (0, 3),
            (0, 2),
            (0, 1),
            (0, 0),
            (-1, 0),
        ]

    def test_move_with_invalid_input(self):
        robot = Robot(0, 0)
        with pytest.raises(ValueError):
            robot.move("INVALID")

    def test_move_with_empty_input(self):
        robot = Robot(0, 0)
        assert robot.path()[-1] == robot.move("")

    def test_move_with_mock(self):
        robot = mock(Robot)
        when(robot).move("NNNSSSW").thenReturn(None)
        robot.move("NNNSSSW")
        verify(robot).move("NNNSSSW")
