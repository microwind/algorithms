class Set {
  constructor(hashFunc = Set.defaultHashFunc, equalsFunc = Set.defaultEqualsFunc) {
    this.capacity = 16; // 初始容量
    this.size = 0; // 当前元素个数
    this.buckets = new Array(this.capacity).fill(null); // 初始化桶
    this.hashFunc = hashFunc; // 哈希函数
    this.equalsFunc = equalsFunc; // 比较函数
  }

  // FNV-1a 哈希函数
  static defaultHashFunc(key) {
    let str = key.toString();
    let hash = 2166136261;
    for (let i = 0; i < str.length; i++) {
      hash ^= str.charCodeAt(i);
      hash *= 16777619;
    }
    return hash >>> 0; // 保证返回正数
  }

  // 默认比较函数（假设 key 是数字）
  static defaultEqualsFunc(a, b) {
    return a === b;
  }

  // 扩容 Set
  resize() {
    const newCapacity = this.capacity * 2;
    const newBuckets = new Array(newCapacity).fill(null);

    // 重新哈希所有元素
    for (let i = 0; i < this.capacity; i++) {
      let node = this.buckets[i];
      while (node) {
        const index = this.hashFunc(node.key) % newCapacity;
        const nextNode = node.next;
        node.next = newBuckets[index];
        newBuckets[index] = node;
        node = nextNode;
      }
    }

    this.buckets = newBuckets;
    this.capacity = newCapacity;
  }

  // 添加元素到 Set
  add(key) {
    if (this.size / this.capacity > 0.75) {
      this.resize(); // JS数组无需扩容，这里仅作演示
    }

    const index = this.hashFunc(key) % this.capacity;
    let node = this.buckets[index];

    // 检查是否已经存在
    while (node) {
      if (this.equalsFunc(node.key, key)) {
        console.log(`Exist node: index=${index} key=${key}`);
        return;
      }
      node = node.next;
    }

    // 插入新元素
    node = {
      key,
      next: this.buckets[index]
    };
    this.buckets[index] = node;
    this.size++;

    console.log(`Adding node: index=${index} key=${key}`);
  }

  // 检查元素是否在 Set 中
  contains(key) {
    const index = this.hashFunc(key) % this.capacity;
    let node = this.buckets[index];
    while (node) {
      if (this.equalsFunc(node.key, key)) return true;
      node = node.next;
    }
    return false;
  }

  // 从 Set 中删除元素
  remove(key) {
    const index = this.hashFunc(key) % this.capacity;
    let node = this.buckets[index];
    let prev = null;
    while (node) {
      if (this.equalsFunc(node.key, key)) {
        if (prev) {
          prev.next = node.next;
        } else {
          this.buckets[index] = node.next;
        }
        this.size--;
        console.log(`Removed node: index=${index} key=${key}`);
        return;
      }
      prev = node;
      node = node.next;
    }
  }

  // 获取 Set 中的元素个数
  getSize() {
    return this.size;
  }

  // 打印 Set 中的所有元素
  print() {
    for (let i = 0; i < this.capacity; i++) {
      let node = this.buckets[i];
      while (node) {
        console.log(node.key);
        node = node.next;
      }
    }
    console.log();
  }
}

// 测试代码
const set = new Set();
const values = [10, 20, 20, 30, 40, 40, 50];

// 添加元素
for (let v of values) {
  set.add(v);
}

// 打印 Set 内容
set.print();

// 检查元素是否存在
console.log("Contains 30?", set.contains(30));

// 删除元素
set.remove(30);
set.print();
console.log(set);

/*
jarry@MacBook-Pro set % node set.js
Adding node: index=4 key=10
Adding node: index=12 key=20
Exist node: index=12 key=20
Adding node: index=0 key=30
Adding node: index=12 key=40
Exist node: index=12 key=40
Adding node: index=0 key=50
50
30
10
40
20

Contains 30? true
Removed node: index=0 key=30
50
10
40
20
*/