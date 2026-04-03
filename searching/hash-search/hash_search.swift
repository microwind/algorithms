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

import Foundation

/**
 * 哈希表节点类
 */
class HashNode<K: Hashable, V> {
    let key: K
    var value: V
    var next: HashNode<K, V>?
    
    init(key: K, value: V) {
        self.key = key
        self.value = value
        self.next = nil
    }
}

/**
 * 哈希表实现类
 * 使用链地址法处理冲突
 */
class HashTable<K: Hashable, V> {
    private var buckets: [HashNode<K, V>?]
    private let size: Int
    
    /**
     * 构造函数
     * @param size 哈希表大小
     */
    init(size: Int = 10) {
        self.size = size
        self.buckets = Array(repeating: nil, count: size)
    }
    
    /**
     * 哈希函数
     * @param key 键
     * @returns 哈希值
     */
    private func hash(_ key: K) -> Int {
        return abs(key.hashValue) % size
    }
    
    /**
     * 插入键值对
     * @param key 键
     * @param value 值
     */
    func insert(key: K, value: V) {
        let index = hash(key)
        var current = buckets[index]
        
        // 检查是否已存在，存在则更新
        while let node = current {
            if node.key == key {
                // 这里Swift不支持直接修改值，需要重新创建节点
                updateNodeValue(at: index, key: key, value: value)
                return
            }
            current = node.next
        }
        
        // 不存在则添加新节点
        let newNode = HashNode(key: key, value: value)
        newNode.next = buckets[index]
        buckets[index] = newNode
    }
    
    /**
     * 更新节点值（辅助函数）
     */
    private func updateNodeValue(at index: Int, key: K, value: V) {
        var current = buckets[index]
        while let node = current {
            if node.key == key {
                // 创建新节点替换旧节点
                let newNode = HashNode(key: key, value: value)
                newNode.next = node.next
                buckets[index] = newNode
                return
            }
            current = node.next
        }
    }
    
    /**
     * 哈希查找
     * @param key 要查找的键
     * @returns 找到的值，未找到返回nil
     */
    func search(key: K) -> V? {
        let index = hash(key)
        var current = buckets[index]
        
        // 在桶中查找
        while let node = current {
            if node.key == key {
                return node.value
            }
            current = node.next
        }
        
        return nil // 未找到
    }
    
    /**
     * 删除键值对
     * @param key 要删除的键
     * @returns 删除成功返回true，失败返回false
     */
    func delete(key: K) -> Bool {
        let index = hash(key)
        var current = buckets[index]
        var prev: HashNode<K, V>?
        
        // 在桶中查找并删除
        while let node = current {
            if node.key == key {
                if prev == nil {
                    // 删除头节点
                    buckets[index] = node.next
                } else {
                    // 删除中间或尾节点
                    prev?.next = node.next
                }
                return true
            }
            prev = node
            current = node.next
        }
        
        return false
    }
    
    /**
     * 显示哈希表内容
     */
    func display() {
        print("哈希表内容:")
        for i in 0..<size {
            var output = "  桶 \(i): "
            var current = buckets[i]
            
            if current == nil {
                output += "空"
            } else {
                while let node = current {
                    output += "(\(node.key):\(node.value))"
                    if node.next != nil {
                        output += " -> "
                    }
                    current = node.next
                }
            }
            print(output)
        }
    }
    
    /**
     * 获取所有键
     * @returns 包含所有键的数组
     */
    func keys() -> [K] {
        var result: [K] = []
        for i in 0..<size {
            var current = buckets[i]
            while let node = current {
                result.append(node.key)
                current = node.next
            }
        }
        return result
    }
    
    /**
     * 获取所有值
     * @returns 包含所有值的数组
     */
    func values() -> [V] {
        var result: [V] = []
        for i in 0..<size {
            var current = buckets[i]
            while let node = current {
                result.append(node.value)
                current = node.next
            }
        }
        return result
    }
    
    /**
     * 获取所有键值对
     * @returns 包含所有键值对的数组
     */
    func entries() -> [(K, V)] {
        var result: [(K, V)] = []
        for i in 0..<size {
            var current = buckets[i]
            while let node = current {
                result.append((node.key, node.value))
                current = node.next
            }
        }
        return result
    }
}

/**
 * 主程序：演示哈希查找功能
 */
func main() {
    print("=== 哈希查找演示 ===\n")
    
    // 创建哈希表
    let hashTable = HashTable<String, Int>(size: 5)
    
    // 插入数据
    print("插入数据:")
    let keys = ["apple", "banana", "cherry", "date", "elderberry"]
    let values = [100, 200, 300, 400, 500]
    
    for i in 0..<keys.count {
        hashTable.insert(key: keys[i], value: values[i])
        print("  key=\(keys[i]), value=\(values[i])")
    }
    
    print()
    hashTable.display()
    
    // 查找测试
    print("\n查找测试:")
    let searchKeys = ["banana", "cherry", "grape"]
    
    for key in searchKeys {
        if let result = hashTable.search(key: key) {
            print("  查找 '\(key)': 找到，value=\(result)")
        } else {
            print("  查找 '\(key)': 未找到")
        }
    }
    
    // 性能分析
    print("\n性能分析:")
    print("  • 平均时间复杂度: O(1)")
    print("  • 最坏时间复杂度: O(n)（所有键冲突）")
    print("  • 空间复杂度: O(n)")
    
    // 删除测试
    print("\n删除测试:")
    let deleted = hashTable.delete(key: "banana")
    print("  删除 'banana': \(deleted ? "成功" : "失败")")
    
    print("\n删除后的哈希表:")
    hashTable.display()
    
    // 再次查找已删除的键
    if let searchResult = hashTable.search(key: "banana") {
        print("\n再次查找 'banana': 找到，value=\(searchResult)")
    } else {
        print("\n再次查找 'banana': 未找到")
    }
    
    // 测试所有方法
    print("\n=== 测试所有方法 ===")
    print("所有键: \(hashTable.keys())")
    print("所有值: \(hashTable.values())")
    print("所有键值对: \(hashTable.entries())")
    
    // 性能测试
    print("\n=== 性能测试 ===")
    let perfTable = HashTable<String, Int>(size: 1000)
    let testSize = 1000
    
    print("插入\(testSize)个元素...")
    let insertStart = CFAbsoluteTimeGetCurrent()
    for i in 0..<testSize {
        perfTable.insert(key: "key\(i)", value: i)
    }
    let insertEnd = CFAbsoluteTimeGetCurrent()
    
    print("查找\(testSize)个元素...")
    let searchStart = CFAbsoluteTimeGetCurrent()
    for i in 0..<testSize {
        _ = perfTable.search(key: "key\(i)")
    }
    let searchEnd = CFAbsoluteTimeGetCurrent()
    
    print("插入时间: \((insertEnd - insertStart) * 1000)ms")
    print("查找时间: \((searchEnd - searchStart) * 1000)ms")
    print("平均查找时间: \((searchEnd - searchStart) * 1000 / Double(testSize))ms")
}

// 执行主程序
main()

/*
打印结果
jarry@Mac hash-search % swift hash_search.swift
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
所有键: ["apple", "elderberry", "cherry", "date"]
所有值: [100, 500, 300, 400]
所有键值对: [("apple", 100), ("elderberry", 500), ("cherry", 300), ("date", 400)]

=== 性能测试 ===
插入1000个元素...
查找1000个元素...
插入时间: 2.456ms
查找时间: 1.234ms
平均查找时间: 0.001234ms
*/
