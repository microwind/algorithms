const INITIAL_CAPACITY = 10;
const LOAD_FACTOR = 0.75;

class Entry {
  constructor(key, value) {
    this.key = key;
    this.value = value;
    this.next = null;
  }
}

class HashMap {
  constructor() {
    this.size = 0;
    this.capacity = INITIAL_CAPACITY;
    this.table = new Array(this.capacity).fill(null);
  }

  hash(key) {
    let hashValue = 0;
    for (let i = 0; i < key.length; i++) {
      hashValue = (hashValue * 31) + key.charCodeAt(i);
    }
    return hashValue % this.capacity;
  }

  resize() {
    // JS动态数组本身无需调整容量，此处仅为演示
    const newCapacity = this.capacity * 2;
    const newTable = new Array(newCapacity).fill(null);

    for (let i = 0; i < this.capacity; i++) {
      let entry = this.table[i];
      while (entry) {
        const newIndex = this.hash(entry.key);
        const newEntry = new Entry(entry.key, entry.value);
        newEntry.next = newTable[newIndex];
        newTable[newIndex] = newEntry;
        entry = entry.next;
      }
    }

    this.table = newTable;
    this.capacity = newCapacity;
  }

  put(key, value) {
    if ((this.size / this.capacity) > LOAD_FACTOR) {
      this.resize();
    }

    const index = this.hash(key);
    let entry = this.table[index];

    while (entry) {
      if (entry.key === key) {
        entry.value = value;
        return;
      }
      entry = entry.next;
    }

    const newEntry = new Entry(key, value);
    newEntry.next = this.table[index];
    this.table[index] = newEntry;
    this.size++;
  }

  get(key) {
    const index = this.hash(key);
    let entry = this.table[index];
    while (entry) {
      if (entry.key === key) {
        return entry.value;
      }
      entry = entry.next;
    }
    return -1;
  }

  delete(key) {
    const index = this.hash(key);
    let entry = this.table[index];
    let prev = null;

    while (entry) {
      if (entry.key === key) {
        if (prev) {
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
}

// 测试
const map = new HashMap();
map.put('apple', 10);
map.put('banana', 20);
map.put('orange', 30);

console.log("apple:", map.get('apple'));
console.log("banana:", map.get('banana'));
console.log("grape:", map.get('grape'));

map.delete('banana');
console.log("banana after delete:", map.get('banana'));

/*
jarry@MacBook-Pro hash % node hash_map.js
apple: 10
banana: 20
grape: -1
banana after delete: -1
*/