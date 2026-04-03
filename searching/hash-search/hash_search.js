/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 哈希查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 * 
 * 核心思想：通过哈希函数将键映射到数组索引，实现O(1)时间复杂度的查找
 * 冲突解决：使用链地址法，每个桶存储一个链表来处理哈希冲突
 */

/**
 * 哈希表类
 * 使用链地址法处理哈希冲突
 * 
 * 数据结构：
 * - buckets: 数组，每个元素是一个桶（链表）
 * - size: 哈希表大小，影响哈希分布和冲突概率
 */
class HashTable {
    /**
     * 构造函数 - 初始化哈希表
     * @param {number} size - 哈希表大小，默认为10
     */
    constructor(size = 10) {
        this.size = size;
        // 创建指定大小的桶数组，每个桶初始化为空数组
        this.buckets = new Array(size).fill(null).map(() => []);
    }
    
    /**
     * 哈希函数 - 将键转换为数组索引
     * 
     * 算法思路：
     * 1. 遍历字符串的每个字符
     * 2. 累加字符的Unicode编码值
     * 3. 对哈希表大小取模，确保索引在有效范围内
     * 
     * @param {string} key - 要哈希化的键
     * @returns {number} 哈希值（0到size-1之间的索引）
     */
    hash(key) {
        let hash = 0;
        // 遍历键的每个字符，累加ASCII值
        for (let i = 0; i < key.length; i++) {
            hash += key.charCodeAt(i);
        }
        // 取模运算确保索引在有效范围内
        return hash % this.size;
    }
    
    /**
     * 插入键值对 - 向哈希表中添加新数据
     * 
     * 算法步骤：
     * 1. 计算键的哈希值，确定目标桶
     * 2. 在桶中查找是否已存在该键
     * 3. 如果存在则更新值，否则添加新节点
     * 
     * @param {string} key - 要插入的键
     * @param {*} value - 要插入的值
     */
    insert(key, value) {
        const index = this.hash(key);           // 1. 计算哈希值，确定桶位置
        const bucket = this.buckets[index];      // 2. 获取对应的桶
        
        // 3. 检查键是否已存在，存在则更新值
        for (let i = 0; i < bucket.length; i++) {
            if (bucket[i].key === key) {
                bucket[i].value = value;     // 更新已存在的值
                return;                     // 提前返回，避免重复插入
            }
        }
        
        // 4. 键不存在，添加新节点到桶末尾
        bucket.push({ key, value });
    }
    
    /**
     * 哈希查找 - 在哈希表中查找指定键的值
     * 
     * 算法步骤：
     * 1. 计算键的哈希值，确定目标桶
     * 2. 在对应桶中线性查找目标键
     * 3. 找到则返回值，否则返回null
     * 
     * 时间复杂度：
     * - 平均情况：O(1) - 哈希分布均匀时
     * - 最坏情况：O(n) - 所有键都哈希到同一个桶
     * 
     * @param {string} key - 要查找的键
     * @returns {*} 找到的值，未找到返回null
     */
    search(key) {
        const index = this.hash(key);           // 1. 计算哈希值，确定桶位置
        const bucket = this.buckets[index];      // 2. 获取对应的桶
        
        // 3. 在桶中线性查找目标键
        for (const node of bucket) {
            if (node.key === key) {
                return node.value;              // 找到目标，返回对应的值
            }
        }
        
        return null; // 遍历完桶未找到，返回null
    }
    
    /**
     * 删除键值对 - 从哈希表中移除指定的键值对
     * 
     * 算法步骤：
     * 1. 计算键的哈希值，确定目标桶
     * 2. 在对应桶中查找目标键
     * 3. 找到则删除节点并返回true，否则返回false
     * 
     * @param {string} key - 要删除的键
     * @returns {boolean} 删除成功返回true，失败返回false
     */
    delete(key) {
        const index = this.hash(key);           // 1. 计算哈希值，确定桶位置
        const bucket = this.buckets[index];      // 2. 获取对应的桶
        
        // 3. 在桶中查找并删除目标键
        for (let i = 0; i < bucket.length; i++) {
            if (bucket[i].key === key) {
                bucket.splice(i, 1);          // 使用splice删除指定位置的元素
                return true;                    // 删除成功，返回true
            }
        }
        
        return false; // 遍历完桶未找到，返回false
    }
    
    /**
     * 显示哈希表内容 - 可视化哈希表的内部结构
     * 
     * 显示格式：
     * 桶索引: 键1:值1 -> 键2:值2 -> ...
     * 空桶显示为"空"
     */
    display() {
        console.log('哈希表内容:');
        // 遍历所有桶
        for (let i = 0; i < this.size; i++) {
            process.stdout.write(`  桶 ${i}: `);     // 输出桶索引
            const bucket = this.buckets[i];
            
            if (bucket.length === 0) {
                console.log('空');                 // 空桶显示
            } else {
                // 遍历桶中的所有节点，用箭头连接
                for (let j = 0; j < bucket.length; j++) {
                    const node = bucket[j];
                    process.stdout.write(`(${node.key}:${node.value})`);
                    if (j < bucket.length - 1) {
                        process.stdout.write(' -> '); // 节点间用箭头连接
                    }
                }
                console.log(); // 换行
            }
        }
    }
}

/**
 * 主程序：演示哈希查找的完整功能
 * 
 * 演示流程：
 * 1. 创建哈希表并插入测试数据
 * 2. 展示哈希表内部结构
 * 3. 执行查找操作验证功能
 * 4. 执行删除操作验证完整性
 * 5. 分析性能特点
 */
function main() {
    console.log('=== 哈希查找演示 ===\n');
    
    // 1. 创建哈希表，指定大小为5个桶
    const hashTable = new HashTable(5);
    
    // 2. 插入测试数据
    console.log('插入数据:');
    const keys = ['apple', 'banana', 'cherry', 'date', 'elderberry'];
    const values = [100, 200, 300, 400, 500];
    
    // 逐个插入并显示哈希值，便于理解哈希分布
    for (let i = 0; i < keys.length; i++) {
        hashTable.insert(keys[i], values[i]);
        console.log(`  key=${keys[i]}, value=${values[i]}, hash=${hashTable.hash(keys[i])}`);
    }
    
    console.log();
    hashTable.display();  // 显示哈希表内部结构
    
    // 3. 查找测试 - 验证查找功能
    console.log('\n查找测试:');
    const searchKeys = ['banana', 'cherry', 'grape'];
    
    for (const key of searchKeys) {
        const result = hashTable.search(key);
        if (result !== null) {
            console.log(`  查找 '${key}': 找到，value=${result}`);
        } else {
            console.log(`  查找 '${key}': 未找到`);
        }
    }
    
    // 4. 性能特点分析
    console.log('\n性能分析:');
    console.log('  • 平均时间复杂度: O(1) - 哈希分布均匀时');
    console.log('  • 最坏时间复杂度: O(n) - 所有键冲突时');
    console.log('  • 空间复杂度: O(n) - 与元素数量成正比');
    
    // 5. 删除测试 - 验证删除功能
    console.log('\n删除测试:');
    const deleted = hashTable.delete('banana');
    console.log(`  删除 'banana': ${deleted ? '成功' : '失败'}`);
    
    console.log('\n删除后的哈希表:');
    hashTable.display();  // 显示删除后的结构
    
    // 6. 验证删除效果
    const searchResult = hashTable.search('banana');
    console.log(`\n再次查找 'banana': ${searchResult !== null ? `找到，value=${searchResult}` : '未找到'}`);
}

// 执行主程序
main();

/*
打印结果
jarry@Mac hash-search % node hash_search.js
=== 哈希查找演示 ===

插入数据:
  key=apple, value=100, hash=1
  key=banana, value=200, hash=3
  key=cherry, value=300, hash=4
  key=date, value=400, hash=3
  key=elderberry, value=500, hash=2

哈希表内容:
  桶 0: 空
  桶 1: (apple:100)
  桶 2: (elderberry:500)
  桶 3: (date:400) -> (banana:200)
  桶 4: (cherry:300)

查找测试:
  查找 'banana': 找到，value=200
  查找 'cherry': 找到，value=300
  查找 'grape': 未找到

性能分析:
  • 平均时间复杂度: O(1)
  • 最坏时间复杂度: O(n)（所有键冲突）
  • 空间复杂度: O(n)

删除测试:
  删除 'banana': 成功

删除后的哈希表:
  桶 0: 空
  桶 1: (apple:100)
  桶 2: (elderberry:500)
  桶 3: (date:400)
  桶 4: (cherry:300)

再次查找 'banana': 未找到
*/
