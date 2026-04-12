/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 映射数据结构 - TypeScript实现
 */

interface Entry {
  key: string;
  value: number;
}

class CustomMap {
  private entries: Entry[];
  private size: number;
  private capacity: number;

  constructor() {
    this.capacity = 10;
    this.entries = [];
    this.size = 0;
  }

  // 重新分配容量
  private resizeMap(newCapacity: number): void {
    this.capacity = newCapacity;
  }

  // 插入键值对（如果存在则更新）
  put(key: string, value: number): void {
    for (let i = 0; i < this.size; i++) {
      if (this.entries[i].key === key) {
        this.entries[i].value = value; // 更新值
        return;
      }
    }
    if (this.size >= this.capacity) {
      this.resizeMap(this.capacity * 2);
    }
    this.entries.push({ key, value });
    this.size++;
  }

  // 查找键
  get(key: string): number {
    for (let i = 0; i < this.size; i++) {
      if (this.entries[i].key === key) {
        return this.entries[i].value;
      }
    }
    return -1; // 未找到
  }

  // 删除键
  delete(key: string): void {
    for (let i = 0; i < this.size; i++) {
      if (this.entries[i].key === key) {
        this.entries.splice(i, 1);
        this.size--;
        return;
      }
    }
  }
}

const mapObj = new CustomMap();
mapObj.put("apple", 10);
mapObj.put("banana", 20);
mapObj.put("orange", 30);

console.log("apple:", mapObj.get("apple"));
console.log("banana:", mapObj.get("banana"));
console.log("grape:", mapObj.get("grape"));

mapObj.delete("banana");
console.log("banana after delete:", mapObj.get("banana"));

/*
 * 输出结果：
 * apple: 10
 * banana: 20
 * grape: -1
 * banana after delete: -1
 */
