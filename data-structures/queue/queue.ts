/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 队列数据结构 - TypeScript实现
 */

const MAX_QUEUE_SIZE = 10;

// Queue 类
class Queue {
  private data: number[];
  private size: number;

  constructor() {
    this.data = [];
    this.size = 0;
  }

  // 判断队列是否为空
  isQueueEmpty(): boolean {
    return this.size === 0;
  }

  // 判断队列是否已满
  isQueueFull(): boolean {
    return this.size === MAX_QUEUE_SIZE;
  }

  // 入队操作
  enqueue(value: number): void {
    if (this.isQueueFull()) {
      console.log(`Queue is full! Cannot enqueue ${value}`);
      return;
    }
    this.data.push(value);
    this.size++;
    console.log(`${value} enqueued to queue`);
  }

  // 出队操作
  dequeue(): number {
    if (this.isQueueEmpty()) {
      console.log("Queue is empty! Cannot dequeue");
      return -1; // 队列为空返回 -1
    }
    const value = this.data.shift()!;
    this.size--;
    return value;
  }

  // 获取队头元素
  peek(): number {
    if (this.isQueueEmpty()) {
      console.log("Queue is empty! Cannot peek");
      return -1; // 队列为空返回 -1
    }
    return this.data[0];
  }

  // 获取队列大小
  getQueueSize(): number {
    return this.size;
  }

  // 打印队列内容
  printQueue(): void {
    if (this.isQueueEmpty()) {
      console.log("Queue is empty");
      return;
    }
    let output = "Queue contents: ";
    for (const value of this.data) {
      output += value + " ";
    }
    console.log(output.trim());
  }
}

const queue = new Queue();

queue.enqueue(10);
queue.enqueue(20);
queue.enqueue(30);
queue.enqueue(40);
queue.enqueue(50);
queue.printQueue();

console.log("Dequeued:", queue.dequeue());
queue.printQueue();

console.log("Front element:", queue.peek());
console.log("Queue size:", queue.getQueueSize());

queue.enqueue(60);
queue.printQueue();

/*
 * 输出结果：
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
