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

import java.util.ArrayList;
import java.util.List;

/**
 * 哈希表节点类
 */
class HashNode<K, V> {
    K key;
    V value;
    HashNode<K, V> next;
    
    public HashNode(K key, V value) {
        this.key = key;
        this.value = value;
        this.next = null;
    }
}

/**
 * 哈希表实现类
 * 使用链地址法处理冲突
 */
class HashTable<K, V> {
    private List<HashNode<K, V>>[] buckets;
    private int size;
    
    /**
     * 构造函数
     * @param size 哈希表大小
     */
    @SuppressWarnings("unchecked")
    public HashTable(int size) {
        this.size = size;
        this.buckets = new ArrayList[size];
        
        // 初始化所有桶
        for (int i = 0; i < size; i++) {
            buckets[i] = new ArrayList<>();
        }
    }
    
    /**
     * 哈希函数
     * @param key 键
     * @return 哈希值
     */
    private int hash(K key) {
        return Math.abs(key.hashCode()) % size;
    }
    
    /**
     * 插入键值对
     * @param key 键
     * @param value 值
     */
    public void insert(K key, V value) {
        int index = hash(key);
        List<HashNode<K, V>> bucket = buckets[index];
        
        // 检查是否已存在，存在则更新
        for (HashNode<K, V> node : bucket) {
            if (node.key.equals(key)) {
                node.value = value;
                return;
            }
        }
        
        // 不存在则添加新节点
        HashNode<K, V> newNode = new HashNode<>(key, value);
        bucket.add(newNode);
    }
    
    /**
     * 哈希查找
     * @param key 要查找的键
     * @return 找到的值，未找到返回null
     */
    public V search(K key) {
        int index = hash(key);
        List<HashNode<K, V>> bucket = buckets[index];
        
        // 在桶中查找
        for (HashNode<K, V> node : bucket) {
            if (node.key.equals(key)) {
                return node.value;
            }
        }
        
        return null; // 未找到
    }
    
    /**
     * 删除键值对
     * @param key 要删除的键
     * @return 删除成功返回true，失败返回false
     */
    public boolean delete(K key) {
        int index = hash(key);
        List<HashNode<K, V>> bucket = buckets[index];
        
        // 在桶中查找并删除
        for (int i = 0; i < bucket.size(); i++) {
            if (bucket.get(i).key.equals(key)) {
                bucket.remove(i);
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * 显示哈希表内容
     */
    public void display() {
        System.out.println("哈希表内容:");
        for (int i = 0; i < size; i++) {
            System.out.print("  桶 " + i + ": ");
            List<HashNode<K, V>> bucket = buckets[i];
            
            if (bucket.isEmpty()) {
                System.out.print("空");
            } else {
                for (int j = 0; j < bucket.size(); j++) {
                    HashNode<K, V> node = bucket.get(j);
                    System.out.print("(" + node.key + ":" + node.value + ")");
                    if (j < bucket.size() - 1) {
                        System.out.print(" -> ");
                    }
                }
            }
            System.out.println();
        }
    }
}

/**
 * 哈希查找演示类
 */
public class HashSearch {
    
    /**
     * 主程序：演示哈希查找功能
     */
    public static void main(String[] args) {
        System.out.println("=== 哈希查找演示 ===\n");
        
        // 创建哈希表
        HashTable<String, Integer> hashTable = new HashTable<>(5);
        
        // 插入数据
        System.out.println("插入数据:");
        String[] keys = {"apple", "banana", "cherry", "date", "elderberry"};
        Integer[] values = {100, 200, 300, 400, 500};
        
        for (int i = 0; i < keys.length; i++) {
            hashTable.insert(keys[i], values[i]);
            System.out.println("  key=" + keys[i] + ", value=" + values[i]);
        }
        
        System.out.println();
        hashTable.display();
        
        // 查找测试
        System.out.println("\n查找测试:");
        String[] searchKeys = {"banana", "cherry", "grape"};
        
        for (String key : searchKeys) {
            Integer result = hashTable.search(key);
            if (result != null) {
                System.out.println("  查找 '" + key + "': 找到，value=" + result);
            } else {
                System.out.println("  查找 '" + key + "': 未找到");
            }
        }
        
        // 性能分析
        System.out.println("\n性能分析:");
        System.out.println("  • 平均时间复杂度: O(1)");
        System.out.println("  • 最坏时间复杂度: O(n)（所有键冲突）");
        System.out.println("  • 空间复杂度: O(n)");
        
        // 删除测试
        System.out.println("\n删除测试:");
        boolean deleted = hashTable.delete("banana");
        System.out.println("  删除 'banana': " + (deleted ? "成功" : "失败"));
        
        System.out.println("\n删除后的哈希表:");
        hashTable.display();
        
        // 再次查找已删除的键
        Integer searchResult = hashTable.search("banana");
        System.out.println("\n再次查找 'banana': " + (searchResult != null ? "找到，value=" + searchResult : "未找到"));
    }
}

/*
打印结果
jarry@Mac hash-search % javac HashSearch.java && java HashSearch
=== 哈希查找演示 ===

插入数据:
  key=apple, value=100
  key=banana, value=200
  key=cherry, value=300
  key=date, value=400
  key=elderberry, value=500

哈希表内容:
  桶 0: 空
  桶 1: 空
  桶 2: (banana:200) -> (cherry:300)
  桶 3: (date:400)
  桶 4: (elderberry:500) -> (apple:100)

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
  桶 1: 空
  桶 2: (cherry:300)
  桶 3: (date:400)
  桶 4: (elderberry:500) -> (apple:100)

再次查找 'banana': 未找到
*/
