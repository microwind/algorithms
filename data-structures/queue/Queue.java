public class Queue {
  private static final int MAX_QUEUE_SIZE = 10;
  private int[] data;
  private int size;
  private int front;
  private int rear;

  // 初始化队列
  public Queue() {
    data = new int[MAX_QUEUE_SIZE];
    size = 0;
    front = 0;
    rear = 0;
  }

  // 判断队列是否为空
  public boolean isQueueEmpty() {
    return size == 0;
  }

  // 判断队列是否已满
  public boolean isQueueFull() {
    return size == MAX_QUEUE_SIZE;
  }

  // 入队操作
  public void enqueue(int value) {
    if (isQueueFull()) {
      System.out.println("Queue is full! Cannot enqueue " + value);
      return;
    }
    data[rear] = value;
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    size++;
    System.out.println(value + " enqueued to queue");
  }

  // 出队操作
  public int dequeue() {
    if (isQueueEmpty()) {
      System.out.println("Queue is empty! Cannot dequeue");
      return -1; // 队列为空返回 -1
    }
    int value = data[front];
    front = (front + 1) % MAX_QUEUE_SIZE;
    size--;
    return value;
  }

  // 获取队头元素
  public int peek() {
    if (isQueueEmpty()) {
      System.out.println("Queue is empty! Cannot peek");
      return -1; // 队列为空返回 -1
    }
    return data[front];
  }

  // 获取队列大小
  public int getQueueSize() {
    return size;
  }

  // 打印队列内容
  public void printQueue() {
    if (isQueueEmpty()) {
      System.out.println("Queue is empty");
      return;
    }
    System.out.print("Queue contents: ");
    for (int i = 0; i < size; i++) {
      System.out.print(data[(front + i) % MAX_QUEUE_SIZE] + " ");
    }
    System.out.println();
  }

  public static void main(String[] args) {
    Queue queue = new Queue();

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);
    queue.printQueue();

    System.out.println("Dequeued: " + queue.dequeue());
    queue.printQueue();

    System.out.println("Front element: " + queue.peek());
    System.out.println("Queue size: " + queue.getQueueSize());

    queue.enqueue(60);
    queue.printQueue();
  }
}

/*
 * jarry@MacBook-Pro queue % javac Queue.java
 * jarry@MacBook-Pro queue % java Queue
 * 10 enqueued to queue
 * 20 enqueued to queue
 * 30 enqueued to queue
 * 40 enqueued to queue
 * 50 enqueued to queue
 * Queue contents: 10 20 30 40 50
 * Dequeued: 10
 * Queue contents: 20 30 40 50
 * Front element: 20
 * Queue size: 4
 * 60 enqueued to queue
 * Queue contents: 20 30 40 50 60
 */