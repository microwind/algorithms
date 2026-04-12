import java.util.HashMap;
import java.util.Map;

/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  LRU (Least Recently Used) 缓存实现（Java）
 *  功能：使用哈希表+双向链表实现O(1) get/put操作的缓存
 *  用途：学习经典算法题，理解缓存淘汰策略和链表应用
 *  
 *  核心操作：
 *  - get(key): 获取值并将节点移到最近使用位置
 *  - put(key, value): 插入新值，满时淘汰最久未使用项
 */
public class LRUCache {
  private final int capacity;
  private final Map<Integer, Node> map;
  private final Node head, tail;

  private static class Node {
    int key, val;
    Node prev, next;

    Node(int k, int v) {
      key = k;
      val = v;
    }
  }

  public LRUCache(int capacity) {
    this.capacity = capacity;
    map = new HashMap<>(capacity);
    head = new Node(0, 0);
    tail = new Node(0, 0);
    head.next = tail;
    tail.prev = head;
  }

  public int get(int key) {
    Node node = map.get(key);
    if (node == null)
      return -1;
    moveToHead(node);
    return node.val;
  }

  public void put(int key, int value) {
    Node node = map.get(key);
    if (node != null) {
      node.val = value;
      moveToHead(node);
    } else {
      if (map.size() == capacity) {
        Node lru = tail.prev;
        removeNode(lru);
        map.remove(lru.key);
      }
      Node newNode = new Node(key, value);
      addNode(newNode);
      map.put(key, newNode);
    }
  }

  private void addNode(Node node) {
    node.next = head.next;
    node.prev = head;
    head.next.prev = node;
    head.next = node;
  }

  private void removeNode(Node node) {
    node.prev.next = node.next;
    node.next.prev = node.prev;
  }

  private void moveToHead(Node node) {
    removeNode(node);
    addNode(node);
  }

  public static void main(String[] args) {
    System.out.println("=== LRU Cache 测试 ===");
    
    // 创建容量为2的LRU缓存
    LRUCache lruCache = new LRUCache(2);
    
    System.out.println("1. 测试put操作:");
    lruCache.put(1, 1);
    System.out.println("put(1, 1) - 缓存内容: " + getCacheContent(lruCache));
    
    lruCache.put(2, 2);
    System.out.println("put(2, 2) - 缓存内容: " + getCacheContent(lruCache));
    
    System.out.println("\n2. 测试get操作:");
    int result1 = lruCache.get(1);
    System.out.println("get(1) = " + result1 + " - 缓存内容: " + getCacheContent(lruCache));
    
    System.out.println("\n3. 测试缓存满时的LRU淘汰:");
    lruCache.put(3, 3);
    System.out.println("put(3, 3) - 缓存内容: " + getCacheContent(lruCache));
    System.out.println("注意: 键2被淘汰，因为键1最近被访问过");
    
    int result2 = lruCache.get(2);
    System.out.println("get(2) = " + result2 + " (应该返回-1，因为键2已被淘汰)");
    
    System.out.println("\n4. 测试更新已存在的键:");
    lruCache.put(1, 10);
    System.out.println("put(1, 10) - 缓存内容: " + getCacheContent(lruCache));
    
    System.out.println("\n5. 测试访问顺序影响淘汰:");
    lruCache.put(4, 4);
    System.out.println("put(4, 4) - 缓存内容: " + getCacheContent(lruCache));
    System.out.println("注意: 键3被淘汰，因为键1最近被更新过");
    
    System.out.println("\n=== 测试完成 ===");
  }
  
  // 辅助方法：获取缓存内容的字符串表示（仅用于测试）
  private static String getCacheContent(LRUCache cache) {
    try {
      // 通过反射获取map的内容（仅用于测试）
      java.lang.reflect.Field mapField = LRUCache.class.getDeclaredField("map");
      mapField.setAccessible(true);
      @SuppressWarnings("unchecked")
      Map<Integer, Node> map = (Map<Integer, Node>) mapField.get(cache);
      
      StringBuilder sb = new StringBuilder();
      sb.append("{");
      boolean first = true;
      for (Map.Entry<Integer, Node> entry : map.entrySet()) {
        if (!first) sb.append(", ");
        sb.append(entry.getKey()).append(":").append(entry.getValue().val);
        first = false;
      }
      sb.append("}");
      return sb.toString();
    } catch (Exception e) {
      return "[无法显示缓存内容]";
    }
  }
}

/**
jarry@Mac map % java LRUCache.java
=== LRU Cache 测试 ===
1. 测试put操作:
put(1, 1) - 缓存内容: {1:1}
put(2, 2) - 缓存内容: {1:1, 2:2}

2. 测试get操作:
get(1) = 1 - 缓存内容: {1:1, 2:2}

3. 测试缓存满时的LRU淘汰:
put(3, 3) - 缓存内容: {1:1, 3:3}
注意: 键2被淘汰，因为键1最近被访问过
get(2) = -1 (应该返回-1，因为键2已被淘汰)

4. 测试更新已存在的键:
put(1, 10) - 缓存内容: {1:10, 3:3}

5. 测试访问顺序影响淘汰:
put(4, 4) - 缓存内容: {4:4, 1:10}
注意: 键3被淘汰，因为键1最近被更新过

=== 测试完成 ===
 */