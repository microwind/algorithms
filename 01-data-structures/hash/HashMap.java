// import java.util.LinkedList;

public class HashMap {
  private static final int INITIAL_CAPACITY = 10;
  private static final double LOAD_FACTOR = 0.75;

  private Entry[] table;
  private int size;
  private int capacity;

  // 哈希表的元素结构体
  public class Entry {
    String key;
    int value;
    Entry next; // 用于链表解决冲突

    public Entry(String key, int value) {
      this.key = key;
      this.value = value;
      this.next = null;
    }
  }

  // 初始化 HashMap
  public HashMap() {
    this.size = 0;
    this.capacity = INITIAL_CAPACITY;
    this.table = new Entry[this.capacity];
  }

  // 哈希函数
  private int hash(String key) {
    int hashValue = 0;
    for (int i = 0; i < key.length(); i++) {
      hashValue = (hashValue * 31) + key.charAt(i);
    }
    return Math.abs(hashValue) % this.capacity;
  }

  // 扩容
  private void resize() {
    int newCapacity = this.capacity * 2;
    Entry[] newTable = new Entry[newCapacity];

    // 迁移原表的数据到新表
    for (int i = 0; i < this.capacity; i++) {
      Entry entry = this.table[i];
      while (entry != null) {
        int newIndex = hash(entry.key) % newCapacity;
        Entry newEntry = new Entry(entry.key, entry.value);
        newEntry.next = newTable[newIndex];
        newTable[newIndex] = newEntry;

        entry = entry.next;
      }
    }

    this.capacity = newCapacity;
    this.table = newTable;
  }

  // 插入键值对（如果存在则更新）
  public void put(String key, int value) {
    // 判断是否需要扩容
    if ((double) this.size / this.capacity > LOAD_FACTOR) {
      resize();
    }

    int index = hash(key);
    Entry entry = this.table[index];

    // 遍历链表，检查是否已经存在相同的键
    while (entry != null) {
      if (entry.key.equals(key)) {
        entry.value = value; // 更新值
        return;
      }
      entry = entry.next;
    }

    // 如果没有找到相同的键，插入新键值对
    Entry newEntry = new Entry(key, value);
    newEntry.next = this.table[index];
    this.table[index] = newEntry;
    this.size++;
  }

  // 查找键
  public int get(String key) {
    int index = hash(key);
    Entry entry = this.table[index];

    while (entry != null) {
      if (entry.key.equals(key)) {
        return entry.value;
      }
      entry = entry.next;
    }
    return -1; // 返回 -1 表示未找到
  }

  // 删除键
  public void delete(String key) {
    int index = hash(key);
    Entry entry = this.table[index];
    Entry prev = null;

    while (entry != null) {
      if (entry.key.equals(key)) {
        if (prev == null) {
          this.table[index] = entry.next;
        } else {
          prev.next = entry.next;
        }
        this.size--;
        return;
      }
      prev = entry;
      entry = entry.next;
    }
  }

  // 测试
  public static void main(String[] args) {
    HashMap map = new HashMap();
    map.put("apple", 10);
    map.put("banana", 20);
    map.put("orange", 30);

    System.out.println("apple: " + map.get("apple"));
    System.out.println("banana: " + map.get("banana"));
    System.out.println("grape: " + map.get("grape"));

    map.delete("banana");
    System.out.println("banana after delete: " + map.get("banana"));
  }
}

/*
 * jarry@MacBook-Pro hash % javac HashMap.java
 * jarry@MacBook-Pro hash % java HashMap
 * apple: 10
 * banana: 20
 * grape: -1
 * banana after delete: -1
 */