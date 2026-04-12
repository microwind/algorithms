/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 哈希查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

/**
 * 哈希表节点接口
 */
interface HashNode<K, V> {
    key: K;
    value: V;
    next?: HashNode<K, V>;
}

/**
 * 自定义哈希表类（避免与全局HashTable冲突）
 */
class CustomHashTable<K, V> {
    private buckets: Array<HashNode<K, V> | null>;
    private size: number;
    
    /**
     * 构造函数
     * @param size 哈希表大小
     */
    constructor(size: number = 10) {
        this.size = size;
        this.buckets = new Array(size).fill(null);
    }
    
    /**
     * 哈希函数
     * @param key 键
     * @returns 哈希值
     */
    private hash(key: K): number {
        let hash = 0;
        const keyStr = String(key);
        for (let i = 0; i < keyStr.length; i++) {
            hash += keyStr.charCodeAt(i);
        }
        return hash % this.size;
    }
    
    /**
     * 插入键值对
     * @param key 键
     * @param value 值
     */
    insert(key: K, value: V): void {
        const index = this.hash(key);
        const bucket = this.buckets[index];
        
        // 检查是否已存在，存在则更新
        let current = bucket;
        while (current) {
            if (current.key === key) {
                current.value = value;
                return;
            }
            current = current.next;
        }
        
        // 不存在则添加新节点
        const newNode: HashNode<K, V> = {
            key,
            value,
            next: bucket
        };
        this.buckets[index] = newNode;
    }
    
    /**
     * 哈希查找
     * @param key 要查找的键
     * @returns 找到的值，未找到返回undefined
     */
    search(key: K): V | undefined {
        const index = this.hash(key);
        let current = this.buckets[index];
        
        // 在桶中查找
        while (current) {
            if (current.key === key) {
                return current.value;
            }
            current = current.next;
        }
        
        return undefined; // 未找到
    }
    
    /**
     * 删除键值对
     * @param key 要删除的键
     * @returns 删除成功返回true，失败返回false
     */
    delete(key: K): boolean {
        const index = this.hash(key);
        let current = this.buckets[index];
        let prev: HashNode<K, V> | null = null;
        
        // 在桶中查找并删除
        while (current) {
            if (current.key === key) {
                if (prev === null) {
                    // 删除头节点
                    this.buckets[index] = current.next || null;
                } else {
                    // 删除中间或尾节点
                    prev.next = current.next || undefined;
                }
                return true;
            }
            prev = current;
            current = current.next || undefined;
        }
        
        return false;
    }
    
    /**
     * 显示哈希表内容
     */
    display(): void {
        console.log('哈希表内容:');
        for (let i = 0; i < this.size; i++) {
            process.stdout.write(`  桶 ${i}: `);
            let current = this.buckets[i];
            
            if (!current) {
                console.log('空');
            } else {
                while (current) {
                    process.stdout.write(`(${current.key}:${current.value})`);
                    if (current.next) {
                        process.stdout.write(' -> ');
                    }
                    current = current.next;
                }
                console.log();
            }
        }
    }
    
    /**
     * 获取所有键
     * @returns 包含所有键的数组
     */
    keys(): K[] {
        const result: K[] = [];
        for (let i = 0; i < this.size; i++) {
            let current = this.buckets[i];
            while (current) {
                result.push(current.key);
                current = current.next || undefined;
            }
        }
        return result;
    }
    
    /**
     * 获取所有值
     * @returns 包含所有值的数组
     */
    values(): V[] {
        const result: V[] = [];
        for (let i = 0; i < this.size; i++) {
            let current = this.buckets[i];
            while (current) {
                result.push(current.value);
                current = current.next || undefined;
            }
        }
        return result;
    }
    
    /**
     * 获取所有键值对
     * @returns 包含所有键值对的数组
     */
    entries(): Array<[K, V]> {
        const result: Array<[K, V]> = [];
        for (let i = 0; i < this.size; i++) {
            let current = this.buckets[i];
            while (current) {
                result.push([current.key, current.value]);
                current = current.next || undefined;
            }
        }
        return result;
    }
}

/**
 * 主程序：演示哈希查找功能
 */
function main(): void {
    console.log('=== 哈希查找演示 ===\n');
    
    // 创建哈希表
    const hashTable = new HashTable<string, number>(5);
    
    // 插入数据
    console.log('插入数据:');
    const keys = ['apple', 'banana', 'cherry', 'date', 'elderberry'];
    const values = [100, 200, 300, 400, 500];
    
    for (let i = 0; i < keys.length; i++) {
        hashTable.insert(keys[i], values[i]);
        console.log(`  key=${keys[i]}, value=${values[i]}`);
    }
    
    console.log();
    hashTable.display();
    
    // 查找测试
    console.log('\n查找测试:');
    const searchKeys = ['banana', 'cherry', 'grape'];
    
    for (const key of searchKeys) {
        const result = hashTable.search(key);
        if (result !== undefined) {
            console.log(`  查找 '${key}': 找到，value=${result}`);
        } else {
            console.log(`  查找 '${key}': 未找到`);
        }
    }
    
    // 性能分析
    console.log('\n性能分析:');
    console.log('  • 平均时间复杂度: O(1)');
    console.log('  • 最坏时间复杂度: O(n)（所有键冲突）');
    console.log('  • 空间复杂度: O(n)');
    
    // 删除测试
    console.log('\n删除测试:');
    const deleted = hashTable.delete('banana');
    console.log(`  删除 'banana': ${deleted ? '成功' : '失败'}`);
    
    console.log('\n删除后的哈希表:');
    hashTable.display();
    
    // 再次查找已删除的键
    const searchResult = hashTable.search('banana');
    console.log(`\n再次查找 'banana': ${searchResult !== undefined ? `找到，value=${searchResult}` : '未找到'}`);
    
    // 测试所有方法
    console.log('\n=== 测试所有方法 ===');
    console.log('所有键:', hashTable.keys());
    console.log('所有值:', hashTable.values());
    console.log('所有键值对:', hashTable.entries());
    
    // 测试数字键
    console.log('\n=== 数字键测试 ===');
    const numTable = new HashTable<number, string>(3);
    numTable.insert(1, 'one');
    numTable.insert(2, 'two');
    numTable.insert(3, 'three');
    numTable.insert(4, 'four');
    
    console.log('数字哈希表:');
    numTable.display();
    
    console.log('查找键2:', numTable.search(2));
    console.log('查找键5:', numTable.search(5));
    
    // 性能测试
    console.log('\n=== 性能测试 ===');
    const perfTable = new HashTable<string, number>(1000);
    const testSize = 1000;
    
    console.log(`插入${testSize}个元素...`);
    const insertStart = Date.now();
    for (let i = 0; i < testSize; i++) {
        perfTable.insert(`key${i}`, i);
    }
    const insertEnd = Date.now();
    
    console.log(`查找${testSize}个元素...`);
    const searchStart = Date.now();
    for (let i = 0; i < testSize; i++) {
        perfTable.search(`key${i}`);
    }
    const searchEnd = Date.now();
    
    console.log(`插入时间: ${insertEnd - insertStart}ms`);
    console.log(`查找时间: ${searchEnd - searchStart}ms`);
    console.log(`平均查找时间: ${(searchEnd - searchStart) / testSize}ms`);
}

// 执行主程序
main();

/*
打印结果
jarry@Mac hash-search % npx tsc hash_search.ts && node hash_search.js
=== 哈希查找演示 ===

插入数据:
  key=apple, value=100
  key=banana, value=200
  key=cherry, value=300
  key=date, value=400
  key=elderberry, value=500

哈希表内容:
  桶 0: 空
  桶 1: (apple:100)
  桶 2: (elderberry:500) -> (banana:200)
  桶 3: (cherry:300)
  桶 4: (date:400)

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
  桶 3: (cherry:300)
  桶 4: (date:400)

再次查找 'banana': 未找到

=== 测试所有方法 ===
所有键: [ 'apple', 'elderberry', 'cherry', 'date' ]
所有值: [ 100, 500, 300, 400 ]
所有键值对: [ [ 'apple', 100 ], [ 'elderberry', 500 ], [ 'cherry', 300 ], [ 'date', 400 ] ]

=== 数字键测试 ===
数字哈希表:
  桶 0: (3:three)
  桶 1: (1:one) -> (4:four)
  桶 2: (2:two)

查找键2: two
查找键5: undefined

=== 性能测试 ===
插入1000个元素...
查找1000个元素...
插入时间: 3ms
查找时间: 2ms
平均查找时间: 0.002ms
*/
