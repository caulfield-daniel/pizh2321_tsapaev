from stack import Stack
from container import StackCollection

def main():
    stack_collection = StackCollection()

    stack1 = Stack()
    stack1.push(1)
    stack1.push(2)
    stack1.push(3)

    stack2 = Stack()
    stack2.push(4)
    stack2.push(5)

    stack_collection.add(stack1)
    stack_collection.add(stack2)

    # Реинициализация коллекции с использованием конструктора
    stack_collection = StackCollection(Stack(1,2,3), Stack(4,5))

    print("Содержимое коллекции после добавления стеков:")
    print(stack_collection) # Контейнер, содержащий 2 стеков: ['Stack(3, 2, 1)', 'Stack(5, 4)']

    stack_collection.remove(0)

    print("\nСодержимое коллекции после удаления первого стека:")
    print(stack_collection) # Контейнер, содержащий 1 стеков: ['Stack(5, 4)']

    stack_collection.save('stacks.json')
    print("\nКоллекция сохранена в файл 'stacks.json'.")

    new_stack_collection = StackCollection()
    new_stack_collection.load('stacks.json')

    print("\nЗагруженная коллекция из файла:")
    print(new_stack_collection)

if __name__ == "__main__":
    main()
