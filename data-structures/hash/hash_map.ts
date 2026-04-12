/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 哈希表数据结构 - TypeScript实现
 */

const INITIAL_CAPACITY = 10;
const LOAD_FACTOR = 0.75;

interface Entry {
  key: string;
  value: number;
  next: Entry | null;
}

class HashMap {
  private table: (Entry | null)[];
  private size: number;
  private capacity: number;

  constructor() {
    this.capacity = INITIAL_CAPACITY;
    this.table = new Array(INITIAL_CAPACITY).fill(null);
    this.size = 0;
  }

  private hash(key: string): number {
    let hash = 0;
    for (let i = 0; i < key.length; i++) {
      const char = key.charCodeAt(i);
      hash = ((hash << 5) - hash) + char;
      hash = hash & hash; // Convert to 32-bit integer
    }
    return Math.abs(hash) % this.capacity;
  }

  private resizeMap(): void {
    const newCapacity = this.capacity * 2;
    const newTable: (Entry | null)[] = new Array(newCapacity).fill(null);

    for (let i = 0; i < this.capacity; i++) {
      let entry = this.table[i];
      while (entry !== null) {
        const newIndex = this.hash(entry.key);
        const newEntry: Entry = {
          key: entry.key,
          value: entry.value,
          next: newTable[newIndex]
        };
        newTable[newIndex] = newEntry;
        entry = entry.next;
      }
    }

    this.table = newTable;
    this.capacity = newCapacity;
  }

  put(key: string, value: number): void {
    if (this.size / this.capacity > LOAD_FACTOR) {
      this.resizeMap();
    }

    const index = this.hash(key);
    let entry = this.table[index];

    while (entry !== null) {
      if (entry.key === key) {
        entry.value = value;
        return;
      }
      entry = entry.next;
    }

    const newEntry: Entry = {
      key: key,
      value: value,
      next: this.table[index]
    };
    this.table[index] = newEntry;
    this.size++;
  }

  get(key: string): number {
    const index = this.hash(key);
    let entry = this.table[index];

    while (entry !== null) {
      if (entry.key === key) {
        return entry.value;
      }
      entry = entry.next;
    }
    return -1;
  }

  delete(key: string): void {
    const index = this.hash(key);
    let entry = this.table[index];
    let prev: Entry | null = null;

    while (entry !== null) {
      if (entry.key === key) {
        if (prev !== null) {
          prev.next = entry.next;
        } else {
          this.table[index] = entry.next;
        }
        this.size--;
        return;
      }
      prev = entry;
      entry = entry.next;
    }
  }

  freeHashMap(): void {
    for (let i = 0; i < this.capacity; i++) {
      let entry = this.table[i];
      while (entry !== null) {
        const next = entry.next;
        entry = next;
      }
    }
  }
}

const hashMapObj = new HashMap();

hashMapObj.put("apple", 10);
hashMapObj.put("banana", 20);
hashMapObj.put("orange", 30);

console.log("apple:", hashMapObj.get("apple"));
console.log("banana:", hashMapObj.get("banana"));
console.log("grape:", hashMapObj.get("grape"));

hashMapObj.delete("banana");
console.log("banana after delete:", hashMapObj.get("banana"));

hashMapObj.freeHashMap();

/*
 * 输出结果：
 * apple: 10
 * banana: 20
 * grape: -1
 * banana after delete: -1
 */
