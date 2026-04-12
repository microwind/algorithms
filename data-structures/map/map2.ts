/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 映射数据结构（带索引优化） - TypeScript实现
 */

interface Entry {
  key: string;
  value: number;
}

class CustomMapWithIndex {
  private entries: Entry[];
  private indexMap: Map<string, number>;
  private size: number;
  private capacity: number;

  constructor() {
    this.size = 0;
    this.capacity = 10;
    this.entries = new Array(this.capacity);
    this.indexMap = new Map();
  }

  // 扩容
  private resizeMap(): void {
    this.capacity *= 2;
  }

  // 插入键值对
  put(key: string, value: number): void {
    if (this.indexMap.has(key)) {
      // 更新值
      const index = this.indexMap.get(key)!;
      this.entries[index].value = value;
    } else {
      // 如果容量已满，扩容
      if (this.size >= this.capacity) {
        this.resizeMap();
      }

      // 插入新键值对
      this.entries[this.size] = { key, value };
      this.indexMap.set(key, this.size);
      this.size++;
    }
  }

  // 查找键
  get(key: string): number {
    if (this.indexMap.has(key)) {
      const index = this.indexMap.get(key)!;
      return this.entries[index].value;
    }
    return -1; // 未找到
  }

  // 删除键
  delete(key: string): void {
    if (this.indexMap.has(key)) {
      const index = this.indexMap.get(key)!;
      // 从数组中移除
      this.entries.splice(index, 1);
      this.indexMap.delete(key);
      // 更新索引
      for (let i = index; i < this.size - 1; i++) {
        this.indexMap.set(this.entries[i].key, i);
      }
      this.size--;
    }
  }

  // 判断键是否存在
  has(key: string): boolean {
    return this.indexMap.has(key);
  }

  // 获取键值对个数
  getSize(): number {
    return this.size;
  }

  // 清空所有数据
  clear(): void {
    this.entries = [];
    this.indexMap = new Map();
    this.size = 0;
  }

  // 遍历所有键值对
  forEach(callback: (value: number, key: string) => void): void {
    for (let i = 0; i < this.size; i++) {
      callback(this.entries[i].value, this.entries[i].key);
    }
  }
}

const printEntry = (value: number, key: string): void => {
  console.log(`${key}: ${value}`);
};

const map2Obj = new CustomMapWithIndex();

map2Obj.put("apple", 10);
map2Obj.put("banana", 20);
map2Obj.put("orange", 30);

console.log("apple:", map2Obj.get("apple"));
console.log("banana:", map2Obj.get("banana"));
console.log("grape:", map2Obj.get("grape"));

map2Obj.delete("banana");
console.log("banana after delete:", map2Obj.get("banana"));

map2Obj.forEach(printEntry);

map2Obj.clear();

/*
 * 输出结果：
 * apple: 10
 * banana: 20
 * grape: -1
 * banana after delete: -1
 * apple: 10
 * orange: 30
 */
