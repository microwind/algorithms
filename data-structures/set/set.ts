/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 集合数据结构 - TypeScript实现
 */

// CustomSet 类，使用 map 模拟哈希桶
// 提供基本的集合操作，包括添加、删除、查找等

class CustomSet {
  private buckets: Map<number, any[]>;
  private size: number;
  private hashFunc: (key: any) => number;
  private equalsFunc: (a: any, b: any) => boolean;

  constructor() {
    this.buckets = new Map();
    this.size = 0;
    this.hashFunc = this.defaultHashFunc;
    this.equalsFunc = this.defaultEqualsFunc;
  }

  // 默认哈希函数（简单的字符串哈希）
  private defaultHashFunc(key: any): number {
    const str = String(key);
    let hash = 0;
    for (let i = 0; i < str.length; i++) {
      const char = str.charCodeAt(i);
      hash = ((hash << 5) - hash) + char;
      hash = hash & hash; // Convert to 32-bit integer
    }
    return Math.abs(hash);
  }

  // 默认比较函数（直接比较值是否相等）
  private defaultEqualsFunc(a: any, b: any): boolean {
    return a === b;
  }

  // 添加元素到 Set
  add(key: any): void {
    const hash = this.hashFunc(key);
    const bucket = this.buckets.get(hash) || [];
    
    for (const k of bucket) {
      // 如果元素已存在，则不添加
      if (this.equalsFunc(k, key)) {
        console.log(`Exist element: hash=${hash} key=${key} value=${bucket}`);
        return;
      }
    }
    
    bucket.push(key);
    this.buckets.set(hash, bucket);
    this.size++;
    console.log(`Adding element: hash=${hash} key=${key} value=${bucket}`);
  }

  // 检查元素是否在 Set 中
  contains(key: any): boolean {
    const hash = this.hashFunc(key);
    const bucket = this.buckets.get(hash) || [];
    
    for (const k of bucket) {
      if (this.equalsFunc(k, key)) {
        return true;
      }
    }
    return false;
  }

  // 从 Set 中删除元素
  remove(key: any): void {
    const hash = this.hashFunc(key);
    const bucket = this.buckets.get(hash);
    
    if (!bucket) return;
    
    const index = bucket.findIndex(k => this.equalsFunc(k, key));
    if (index !== -1) {
      bucket.splice(index, 1);
      this.size--;
    }
  }

  // 获取 Set 的大小
  getSize(): number {
    return this.size;
  }

  // 打印 Set 中的所有元素
  print(): void {
    let output = "";
    for (const bucket of this.buckets.values()) {
      for (const key of bucket) {
        output += key + " ";
      }
    }
    console.log(output.trim());
  }
}

// 创建一个 CustomSet
const set = new CustomSet();
const values = [10, 20, 20, 30, 40, 40, 50];

// 添加元素
for (const v of values) {
  set.add(v);
}

// 打印 CustomSet 内容
set.print();

// 检查元素是否存在
console.log("Contains 30?", set.contains(30));

// 删除元素
set.remove(30);
set.print();

/*
 * 输出结果：
 * Adding element: hash=... key=10 value=[10]
 * Adding element: hash=... key=20 value=[20]
 * Exist element: hash=... key=20 value=[20]
 * Adding element: hash=... key=30 value=[30]
 * Adding element: hash=... key=40 value=[40]
 * Exist element: hash=... key=40 value=[40]
 * Adding element: hash=... key=50 value=[50]
 * 10 20 30 40 50
 * Contains 30? true
 * 10 20 40 50
 */
