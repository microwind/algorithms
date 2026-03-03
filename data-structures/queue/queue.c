#include <stdio.h>
#include <stdlib.h>

// 定义队列的最大容量
#define MAX_QUEUE_SIZE 10

// 队列结构体
typedef struct
{
  int data[MAX_QUEUE_SIZE]; // 队列数据
  int front;                // 队头指针
  int rear;                 // 队尾指针
  int size;                 // 当前队列大小
} Queue;

// 初始化队列
void initQueue(Queue *queue)
{
  queue->front = 0;
  queue->rear = 0;
  queue->size = 0;
}

// 判断队列是否为空
int isQueueEmpty(Queue *queue)
{
  return queue->size == 0;
}

// 判断队列是否已满
int isQueueFull(Queue *queue)
{
  return queue->size == MAX_QUEUE_SIZE;
}

// 入队操作
void enqueue(Queue *queue, int value)
{
  if (isQueueFull(queue))
  {
    printf("Queue is full! Cannot enqueue %d\n", value);
    return;
  }
  queue->data[queue->rear] = value;
  queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE; // 环形队列处理
  queue->size++;
  printf("%d enqueued to queue\n", value);
}

// 出队操作
int dequeue(Queue *queue)
{
  if (isQueueEmpty(queue))
  {
    printf("Queue is empty! Cannot dequeue\n");
    return -1; // 返回 -1 表示队列为空
  }
  int value = queue->data[queue->front];
  queue->front = (queue->front + 1) % MAX_QUEUE_SIZE; // 环形队列处理
  queue->size--;
  return value;
}

// 获取队头元素
int peek(Queue *queue)
{
  if (isQueueEmpty(queue))
  {
    printf("Queue is empty! Cannot peek\n");
    return -1; // 返回 -1 表示队列为空
  }
  return queue->data[queue->front];
}

// 获取队列大小
int getQueueSize(Queue *queue)
{
  return queue->size;
}

// 打印队列内容
void printQueue(Queue *queue)
{
  if (isQueueEmpty(queue))
  {
    printf("Queue is empty\n");
    return;
  }
  int i = queue->front;
  printf("Queue contents: ");
  for (int count = 0; count < queue->size; count++)
  {
    printf("%d ", queue->data[i]);
    i = (i + 1) % MAX_QUEUE_SIZE; // 环形队列处理
  }
  printf("\n");
}

// 测试队列功能
int main()
{
  Queue queue;
  initQueue(&queue);

  enqueue(&queue, 10);
  enqueue(&queue, 20);
  enqueue(&queue, 30);
  enqueue(&queue, 40);
  enqueue(&queue, 50);

  printQueue(&queue);

  printf("Dequeued: %d\n", dequeue(&queue));
  printQueue(&queue);

  printf("Front element: %d\n", peek(&queue));
  printf("Queue size: %d\n", getQueueSize(&queue));

  enqueue(&queue, 60);
  printQueue(&queue);

  return 0;
}

/*
jarry@MacBook-Pro queue % gcc queue.c
jarry@MacBook-Pro queue % ./a.out
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