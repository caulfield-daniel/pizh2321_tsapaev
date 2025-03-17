from container import StackCollection
from stack import Stack

if __name__ == "__main__":
    stack1 = Stack()
    stack1.push(1)
    stack1.push(2)

    stack2 = Stack()
    stack2.push(3)

    container = StackCollection()
    container.add(stack1)
    container.add(stack2)
    print(container)

    container.save("stack_collection.json")

    loaded_container = StackCollection()
    loaded_container.load("stack_collection.json")

    print(loaded_container)
