import pytest
from unittest.mock import MagicMock
from stack import Stack

def test_push():
    stack = Stack()
    stack.push(1)
    assert stack.peek() == 1

def test_pop():
    stack = Stack()
    stack.push(1)
    assert stack.pop() == 1
    assert stack.is_empty()

def test_peek():
    stack = Stack()
    stack.push(1)
    assert stack.peek() == 1

def test_size():
    stack = Stack()
    stack.push(1)
    stack.push(2)
    assert stack.size() == 2

def test_is_empty():
    stack = Stack()
    assert stack.is_empty()
    stack.push(1)
    assert not stack.is_empty()
