package main

import "fmt"

const MAX_QUEUE_SIZE = 10

// Queue 结构体
type Queue struct {
  data []int
  size int
}

// 初始化队列
func initQueue() *Queue {
  return &Queue{
    data: make([]int, 0, MAX_QUEUE_SIZE),
    size: 0,
  }
}

// 判断队列是否为空
func (q *Queue) isQueueEmpty() bool {
  return q.size == 0
}

// 判断队列是否已满
func (q *Queue) isQueueFull() bool {
  return q.size == MAX_QUEUE_SIZE
}

// 入队操作
func (q *Queue) enqueue(value int) {
  if q.isQueueFull() {
    fmt.Printf("Queue is full! Cannot enqueue %d\n", value)
    return
  }
  q.data = append(q.data, value)
  q.size++
  fmt.Printf("%d enqueued to queue\n", value)
}

// 出队操作
func (q *Queue) dequeue() int {
  if q.isQueueEmpty() {
    fmt.Println("Queue is empty! Cannot dequeue")
    return -1 // 队列为空返回 -1
  }
  value := q.data[0]
  q.data = q.data[1:]
  q.size--
  return value
}

// 获取队头元素
func (q *Queue) peek() int {
  if q.isQueueEmpty() {
    fmt.Println("Queue is empty! Cannot peek")
    return -1 // 队列为空返回 -1
  }
  return q.data[0]
}

// 获取队列大小
func (q *Queue) getQueueSize() int {
  return q.size
}

// 打印队列内容
func (q *Queue) printQueue() {
  if q.isQueueEmpty() {
    fmt.Println("Queue is empty")
    return
  }
  fmt.Print("Queue contents: ")
  for _, value := range q.data {
    fmt.Printf("%d ", value)
  }
  fmt.Println()
}

func main() {
  queue := initQueue()

  queue.enqueue(10)
  queue.enqueue(20)
  queue.enqueue(30)
  queue.enqueue(40)
  queue.enqueue(50)
  queue.printQueue()

  fmt.Println("Dequeued:", queue.dequeue())
  queue.printQueue()

  fmt.Println("Front element:", queue.peek())
  fmt.Println("Queue size:", queue.getQueueSize())

  queue.enqueue(60)
  queue.printQueue()
}

/*
jarry@MacBook-Pro queue % go run queue.go
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
*/
