/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 列表数据结构 - TypeScript实现
 */

// List 类
class List {
  private data: number[];
  private size: number;
  private capacity: number;

  constructor() {
    this.capacity = 10;
    this.data = [];
    this.size = 0;
  }

  // 扩展 List 容量
  private resize(newCapacity: number): void {
    if (newCapacity > this.capacity) {
      const newData = new Array(newCapacity);
      for (let i = 0; i < this.size; i++) {
        newData[i] = this.data[i];
      }
      this.data = newData;
      this.capacity = newCapacity;
    }
  }

  // 添加元素
  add(value: number): void {
    if (this.size === this.capacity) {
      this.resize(this.capacity * 2);
    }
    this.data[this.size] = value;
    this.size++;
  }

  // 删除最后一个元素
  remove(): void {
    if (this.size > 0) {
      this.size--;
    }
  }

  // 获取元素
  get(index: number): number {
    if (index < 0 || index >= this.size) {
      throw new Error("Index out of range");
    }
    return this.data[index];
  }

  // 获取大小
  getSize(): number {
    return this.size;
  }

  // 获取容量
  getCapacity(): number {
    return this.capacity;
  }

  // 打印列表
  print(): void {
    console.log("List:", this.data.slice(0, this.size));
  }
}

const list = new List();
list.add(10);
list.add(20);
list.add(30);
list.print(); // List: [10, 20, 30]

console.log("Element at index 1:", list.get(1)); // 20

list.remove();
list.print(); // List: [10, 20]

console.log("Size:", list.getSize());         // 2
console.log("Capacity:", list.getCapacity()); // 10

/*
 * 输出结果：
 * List: [10, 20, 30]
 * Element at index 1: 20
 * List: [10, 20]
 * Size: 2
 * Capacity: 10
 * New Capacity: 20
 */
