// JS基于数组模拟内置Map对象，为了演示数据结构
// 采用数组存储数据，建立键值映射，提升性能
class Map {
  constructor() {
      this.entries = []; // 存储键值对
      this.indexMap = {}; // 键到索引的映射
      this.size = 0; // 当前键值对数量
      this.capacity = 10; // 初始容量
  }

  // 重新分配容量（JS动态数组，无需调整容量，这里仅为模拟）
  resizeMap(newCapacity) {
      this.capacity = newCapacity;
  }

  // 插入键值对（如果存在则更新）
  put(key, value) {
      if (this.indexMap.hasOwnProperty(key)) {
          // 如果键已存在，更新值
          const index = this.indexMap[key];
          this.entries[index].value = value;
      } else {
          // 如果键不存在，插入新键值对
          if (this.size >= this.capacity) {
              this.resizeMap(this.capacity * 2); // 扩容
          }
          const index = this.size;
          this.entries[index] = { key, value };
          this.indexMap[key] = index; // 更新索引映射
          this.size++;
      }
  }

  // 查找键，查找根据索引，效率会很高
  get(key) {
      if (this.indexMap.hasOwnProperty(key)) {
          const index = this.indexMap[key];
          return this.entries[index].value;
      }
      return -1; // 未找到
  }

  // 删除键，删除时效率会变低
  delete(key) {
      if (this.indexMap.hasOwnProperty(key)) {
          const index = this.indexMap[key];
          // 从数组中移除键值对
          this.entries.splice(index, 1);
          // 删除索引映射
          delete this.indexMap[key];
          // 更新后续键的索引
          for (let i = index; i < this.size - 1; i++) {
              this.indexMap[this.entries[i].key] = i;
          }
          this.size--;
      }
  }

  // 判断键是否存在
  has(key) {
      return this.indexMap.hasOwnProperty(key);
  }

  // 获取键值对个数
  getSize() {
      return this.size;
  }

  // 清空所有数据
  clear() {
      this.entries = [];
      this.indexMap = {};
      this.size = 0;
  }

  // 遍历所有键值对
  forEach(callback) {
      this.entries.forEach(({ key, value }) => callback(value, key, this));
  }
}

// 测试
const map = new Map();

map.put("apple", 10);
map.put("banana", 20);
map.put("orange", 30);

console.log("apple:", map.get("apple")); // 10
console.log("banana:", map.get("banana")); // 20
console.log("grape:", map.get("grape")); // -1

map.delete("banana");
console.log("banana after delete:", map.get("banana")); // -1

map.forEach((value, key) => {
  console.log(`${key}: ${value}`);
});

/*
jarry@MacBook-Pro map % node map2.js 
apple: 10
banana: 20
grape: -1
banana after delete: -1
apple: 10
orange: 30
*/