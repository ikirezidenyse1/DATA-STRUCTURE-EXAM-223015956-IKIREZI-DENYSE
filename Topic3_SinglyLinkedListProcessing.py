
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class SinglyLinkedList:
    def __init__(self):
        self.head = None

    def append(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            return
        temp = self.head
        while temp.next:
            temp = temp.next
        temp.next = new_node

    def process(self):
        temp = self.head
        while temp:
            print(f"Processing: {temp.data}")
            temp = temp.next

# Example usage
sll = SinglyLinkedList()
sll.append("Order #1")
sll.append("Order #2")
sll.append("Order #3")
sll.append("Order #4")
sll.append("Order #5")
sll.process()
