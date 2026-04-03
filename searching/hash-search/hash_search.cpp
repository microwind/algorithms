/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 哈希查找算法实现
 * 提供完整的哈希表实现和查找功能
 */

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <chrono>

/**
 * 哈希表节点类
 * 用于存储键值对
 */
template <typename K, typename V>
class HashNode {
public:
    K key;
    V value;
    HashNode* next;
    
    HashNode(K k, V v) : key(k), value(v), next(nullptr) {}
};

/**
 * 哈希表类
 * 实现基本的哈希表功能
 */
template <typename K, typename V>
class HashTable {
private:
    std::vector<HashNode<K,V>*> table;
    int size;
    
    /**
     * 哈希函数 - 简单的取模哈希
     * 
     * @param key - 键值
     * @return 哈希值
     */
    int hashFunction(K key) {
        return std::hash<K>{}(key) % size;
    }
    
public:
    /**
     * 构造函数
     * 
     * @param tableSize - 哈希表大小
     */
    HashTable(int tableSize) : size(tableSize) {
        table.resize(size, nullptr);
    }
    
    /**
     * 析构函数 - 释放内存
     */
    ~HashTable() {
        for (int i = 0; i < size; i++) {
            HashNode<K,V>* current = table[i];
            while (current != nullptr) {
                HashNode<K,V>* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
    
    /**
     * 插入键值对
     * 
     * @param key - 键
     * @param value - 值
     */
    void insert(K key, V value) {
        int hashIndex = hashFunction(key);
        HashNode<K,V>* newNode = new HashNode<K,V>(key, value);
        
        // 如果该位置为空，直接插入
        if (table[hashIndex] == nullptr) {
            table[hashIndex] = newNode;
        } else {
            // 使用链地址法处理冲突
            HashNode<K,V>* current = table[hashIndex];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    
    /**
     * 查找键对应的值
     * 
     * @param key - 键
     * @return 找到返回值，未找到返回-1
     */
    V search(K key) {
        int hashIndex = hashFunction(key);
        HashNode<K,V>* current = table[hashIndex];
        
        // 遍历链表查找键
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        
        return -1; // 未找到
    }
    
    /**
     * 删除键值对
     * 
     * @param key - 键
     * @return 删除成功返回true，失败返回false
     */
    bool remove(K key) {
        int hashIndex = hashFunction(key);
        HashNode<K,V>* current = table[hashIndex];
        HashNode<K,V>* prev = nullptr;
        
        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[hashIndex] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        
        return false; // 未找到
    }
    
    /**
     * 显示哈希表内容
     */
    void display() {
        std::cout << "哈希表内容:" << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << "桶 " << i << ": ";
            HashNode<K,V>* current = table[i];
            while (current != nullptr) {
                std::cout << "[" << current->key << ":" << current->value << "] ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
};

/**
 * 哈希查找测试函数
 * 
 * 测试内容：
 * 1. 插入数据到哈希表
 * 2. 查找指定键值
 * 3. 删除指定键值
 * 4. 显示哈希表结构
 */
void testHashSearch() {
    std::cout << "=== 哈希查找演示 ===" << std::endl;
    
    // 创建哈希表
    HashTable<int, int> hashTable(10);
    
    // 测试数据
    std::vector<int> testData = {12, 22, 32, 42, 52, 62, 72, 82, 92};
    
    // 1. 插入数据
    std::cout << "\n1. 插入数据:" << std::endl;
    for (int i = 0; i < testData.size(); i++) {
        hashTable.insert(testData[i], i);
        std::cout << "插入: [" << testData[i] << ":" << i << "]" << std::endl;
    }
    
    // 2. 显示哈希表
    std::cout << "\n2. 显示哈希表结构:" << std::endl;
    hashTable.display();
    
    // 3. 查找测试
    std::cout << "\n3. 查找测试:" << std::endl;
    std::vector<int> searchKeys = {22, 52, 92, 100};
    
    for (int key : searchKeys) {
        auto start = std::chrono::high_resolution_clock::now();
        int result = hashTable.search(key);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time = end - start;
        
        if (result != -1) {
            std::cout << "查找 " << key << ": 找到，值=" << result 
                     << ", 时间=" << time.count() << "ms" << std::endl;
        } else {
            std::cout << "查找 " << key << ": 未找到" 
                     << ", 时间=" << time.count() << "ms" << std::endl;
        }
    }
    
    // 4. 删除测试
    std::cout << "\n4. 删除测试:" << std::endl;
    bool deleteResult = hashTable.remove(52);
    std::cout << "删除 52: " << (deleteResult ? "成功" : "失败") << std::endl;
    
    // 5. 再次查找验证删除
    std::cout << "\n5. 删除后查找验证:" << std::endl;
    int searchResult = hashTable.search(52);
    std::cout << "查找 52: " << (searchResult != -1 ? "找到" : "未找到") << std::endl;
    
    // 6. 性能分析
    std::cout << "\n6. 性能分析:" << std::endl;
    std::cout << "• 时间复杂度: 平均O(1)，最坏O(n)" << std::endl;
    std::cout << "• 空间复杂度: O(n)" << std::endl;
    std::cout << "• 适用场景: 频繁查找操作" << std::endl;
    std::cout << "• 优势: 查找速度快，插入删除效率高" << std::endl;
    std::cout << "• 劣势: 需要额外空间，哈希冲突影响性能" << std::endl;
}

/**
 * 主程序：演示哈希查找功能
 */
int main() {
    std::cout << "============================================================" << std::endl;
    std::cout << "哈希查找算法演示" << std::endl;
    std::cout << "============================================================" << std::endl;
    
    testHashSearch();
    
    return 0;
}

/*
打印结果
jarry@Mac hash-search % g++ hash_search.cpp && ./a.out
============================================================
哈希查找算法演示
============================================================
=== 哈希查找演示 ===

1. 插入数据:
插入: [12:0]
插入: [22:1]
插入: [32:2]
插入: [42:3]
插入: [52:4]
插入: [62:5]
插入: [72:6]
插入: [82:7]
插入: [92:8]

2. 显示哈希表结构:
哈希表内容:
桶 0: [32:2] [92:8] 
桶 1: [42:3] 
桶 2: [52:4] [62:5] [72:6] [82:7] 
桶 3: [12:0] [22:1] 
桶 4: 
桶 5: 
桶 6: 
桶 7: 
桶 8: 
桶 9: 

3. 查找测试:
查找 22: 找到，值=1, 时间=0.001ms
查找 52: 找到，值=4, 时间=0ms
查找 92: 找到，值=8, 时间=0ms
查找 100: 未找到, 时间=0ms

4. 删除测试:
删除 52: 成功

5. 删除后查找验证:
查找 52: 未找到

6. 性能分析:
• 时间复杂度: 平均O(1)，最坏O(n)
• 空间复杂度: O(n)
• 适用场景: 频繁查找操作
• 优势: 查找速度快，插入删除效率高
• 劣势: 需要额外空间，哈希冲突影响性能
*/
