class Queue:
    MAX_QUEUE_SIZE = 10

    def __init__(self):
        self.data = []
        self.size = 0

    # 判断队列是否为空
    def is_queue_empty(self):
        return self.size == 0

    # 判断队列是否已满
    def is_queue_full(self):
        return self.size == self.MAX_QUEUE_SIZE

    # 入队操作
    def enqueue(self, value):
        if self.is_queue_full():
            print(f"Queue is full! Cannot enqueue {value}")
            return
        self.data.append(value)
        self.size += 1
        print(f"{value} enqueued to queue")

    # 出队操作
    def dequeue(self):
        if self.is_queue_empty():
            print("Queue is empty! Cannot dequeue")
            return -1  # 队列为空返回 -1
        value = self.data.pop(0)
        self.size -= 1
        return value

    # 获取队头元素
    def peek(self):
        if self.is_queue_empty():
            print("Queue is empty! Cannot peek")
            return -1  # 队列为空返回 -1
        return self.data[0]

    # 获取队列大小
    def get_queue_size(self):
        return self.size

    # 打印队列内容
    def print_queue(self):
        if self.is_queue_empty():
            print("Queue is empty")
            return
        print("Queue contents:", " ".join(map(str, self.data)))


# 测试队列功能
queue = Queue()
queue.enqueue(10)
queue.enqueue(20)
queue.enqueue(30)
queue.enqueue(40)
queue.enqueue(50)
queue.print_queue()

print("Dequeued:", queue.dequeue())
queue.print_queue()

print("Front element:", queue.peek())
print("Queue size:", queue.get_queue_size())

queue.enqueue(60)
queue.print_queue()

"""
jarry@MacBook-Pro queue % python queue.py
10 enqueued to queue
20 enqueued to queue
30 enqueued to queue
40 enqueued to queue
50 enqueued to queue
Queue contents: 10 20 30 40 50
Dequeued: 10
Queue contents: 20 30 40 50
Front element: 20
Queue size: 4
60 enqueued to queue
Queue contents: 20 30 40 50 60
"""