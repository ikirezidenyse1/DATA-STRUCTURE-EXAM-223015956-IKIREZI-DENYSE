
class CircularQueue:
    def __init__(self, size):
        self.size = size
        self.queue = [None] * size
        self.front = self.rear = -1

    def enqueue(self, data):
        if (self.rear + 1) % self.size == self.front:
            print("Queue is full")
            return
        if self.front == -1:
            self.front = 0
        self.rear = (self.rear + 1) % self.size
        self.queue[self.rear] = data

    def dequeue(self):
        if self.front == -1:
            print("Queue is empty")
            return None
        data = self.queue[self.front]
        if self.front == self.rear:
            self.front = self.rear = -1
        else:
            self.front = (self.front + 1) % self.size
        return data

    def display(self):
        if self.front == -1:
            print("Queue is empty")
            return
        temp = self.front
        while True:
            print(self.queue[temp], end=' -> ')
            if temp == self.rear:
                break
            temp = (temp + 1) % self.size
        print("None")

# Example usage
cq = CircularQueue(5)
cq.enqueue("Order #1")
cq.enqueue("Order #2")
cq.enqueue("Order #3")
cq.enqueue("Order #4")
cq.enqueue("Order #5")
cq.display()
cq.dequeue()
cq.display()
