/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 哈希表数据结构（整数键） - TypeScript实现
 */

const TABLE_SIZE = 10;

interface HashNode {
  key: number;
  value: number;
  next: HashNode | null;
}

class HashTable {
  private table: (HashNode | null)[];

  constructor() {
    this.table = new Array(TABLE_SIZE).fill(null);
  }

  // 多项式哈希函数
  private hash(key: number): number {
    let hash = 0;
    const base = 31;
    let tempKey = key;
    while (tempKey > 0) {
      hash = (hash * base + tempKey % 10) % TABLE_SIZE;
      tempKey = Math.floor(tempKey / 10);
    }
    return hash;
  }

  insert(key: number, value: number): void {
    const index = this.hash(key);
    const newNode: HashNode = { key, value, next: this.table[index] };
    this.table[index] = newNode;
  }

  search(key: number): number {
    const index = this.hash(key);
    let current: HashNode | null = this.table[index];
    while (current !== null) {
      if (current.key === key) {
        return current.value;
      }
      current = current.next;
    }
    return -1;
  }

  delete(key: number): void {
    const index = this.hash(key);
    let current: HashNode | null = this.table[index];
    let prev: HashNode | null = null;
    while (current !== null) {
      if (current.key === key) {
        if (prev === null) {
          this.table[index] = current.next;
        } else {
          prev.next = current.next;
        }
        return;
      }
      prev = current;
      current = current.next;
    }
  }

  printTable(): void {
    for (let i = 0; i < TABLE_SIZE; i++) {
      const node: HashNode | null = this.table[i];
      if (node !== null) {
        let output = `Index ${i}: `;
        let current: HashNode | null = node;
        while (current !== null) {
          output += `[${current.key}:${current.value}] `;
          current = current.next;
        }
        console.log(output.trim());
      }
    }
  }
}

const hashTable = new HashTable();

hashTable.insert(1, 100);
hashTable.insert(2, 200);
hashTable.insert(3, 300);

console.log("Search key 2:", hashTable.search(2));

hashTable.delete(2);
console.log("After deleting key 2:");
hashTable.printTable();

/*
 * 输出结果：
 * Search key 2: 200
 * After deleting key 2:
 * Index 1: [1:100]
 * Index 3: [3:300]
 */
