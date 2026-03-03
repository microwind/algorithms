class HashTable {
  constructor() {
    this.table = new Array(10);
  }

  // 构建简单的hash函数
  hash(key) {
    let hash = 0;
    const base = 31;
    while (key > 0) {
      hash = (hash * base + (key % 10)) % 10;
      key = Math.floor(key / 10);
    }
    return hash;
  }

  insert(key, value) {
    const index = this.hash(key);
    if (!this.table[index]) {
      this.table[index] = [];
    }
    for (let i = 0; i < this.table[index].length; i++) {
      if (this.table[index][i].key === key) {
        this.table[index][i].value = value; // 更新值
        return;
      }
    }
    this.table[index].push({
      key,
      value
    });
  }

  search(key) {
    const index = this.hash(key);
    if (this.table[index]) {
      for (let i = 0; i < this.table[index].length; i++) {
        if (this.table[index][i].key === key) {
          return this.table[index][i].value;
        }
      }
    }
    return -1; // 键未找到
  }

  delete(key) {
    const index = this.hash(key);
    if (this.table[index]) {
      this.table[index] = this.table[index].filter(item => item.key !== key);
    }
  }

  printTable() {
    this.table.forEach((bucket, index) => {
      if (bucket) {
        console.log(`Index ${index}: ${bucket.map(item => `[${item.key}:${item.value}]`).join(' ')}`);
      }
    });
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
jarry@MacBook-Pro hash % node hash_table.js
Search key 2: 200
After deleting key 2:
Index 1: [1:100]
Index 2: 
Index 3: [3:300]
*/