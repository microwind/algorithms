// JS基于数组模拟内置Map对象，为了演示数据结构
// 实际JS引擎采取使用 哈希表 + 链地址法 或用 红黑树
class Map {
    constructor() {
        this.entries = [];
        this.size = 0;
        this.capacity = 10;
    }

    // 重新分配容量，JS动态数组，无需调整容量
    resizeMap(newCapacity) {
        this.capacity = newCapacity;
    }

    // 插入键值对（如果存在则更新）
    put(key, value) {
        for (let i = 0; i < this.size; i++) {
            if (this.entries[i].key === key) {
                this.entries[i].value = value; // 更新值
                return;
            }
        }
        if (this.size >= this.capacity) {
            this.resizeMap(this.capacity * 2);
        }
        // 或push追加新键值对
        // this.entries.push({ key, value });
        this.entries[this.size] = {
            key,
            value
        };
        this.size++;
    }

    // 查找键
    get(key) {
        for (let i = 0; i < this.size; i++) {
            if (this.entries[i].key === key) {
                return this.entries[i].value;
            }
        }
        return -1; // 未找到
    }

    // 删除键
    delete(key) {
        for (let i = 0; i < this.size; i++) {
            if (this.entries[i].key === key) {
                this.entries.splice(i, 1);
                this.size--;
                return;
            }
        }
    }

    // 判断键是否存在
    has(key) {
        return this.entries.some(entry => entry.key === key);
    }

    // 获取键值对个数
    getSize() {
        return this.entries.length;
    }

    // 清空所有数据
    clear() {
        this.entries = [];
    }

    // 遍历所有键值对
    forEach(callback) {
        this.entries.forEach(({
            key,
            value
        }) => callback(value, key, this));
    }
}

// 测试
const map = new Map();

map.put("apple", 10);
map.put("banana", 20);
map.put("orange", 30);

console.log("apple:", map.get("apple"));
console.log("banana:", map.get("banana"));
console.log("grape:", map.get("grape"));

map.delete("banana");
console.log("banana after delete:", map.get("banana"));

/*
jarry@MacBook-Pro map %  node map.js 
apple: 10
banana: 20
grape: -1
banana after delete: -1
*/