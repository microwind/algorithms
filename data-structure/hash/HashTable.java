import java.util.LinkedList;

class HashTable {
  private static final int TABLE_SIZE = 10;
  private LinkedList<Entry>[] table;

  @SuppressWarnings("unchecked")
  public HashTable() {
    table = new LinkedList[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
      table[i] = new LinkedList<>();
    }
  }

  private int hash(int key) {
    return key % TABLE_SIZE;
  }

  public void insert(int key, int value) {
    int index = hash(key);
    for (Entry entry : table[index]) {
      if (entry.key == key) {
        entry.value = value; // 更新值
        return;
      }
    }
    table[index].add(new Entry(key, value));
  }

  public int search(int key) {
    int index = hash(key);
    for (Entry entry : table[index]) {
      if (entry.key == key) {
        return entry.value;
      }
    }
    return -1; // 键未找到
  }

  public void delete(int key) {
    int index = hash(key);
    table[index].removeIf(entry -> entry.key == key);
  }

  public void printTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
      System.out.print("Index " + i + ": ");
      for (Entry entry : table[i]) {
        System.out.print("[" + entry.key + ":" + entry.value + "] ");
      }
      System.out.println();
    }
  }

  static class Entry {
    int key;
    int value;

    Entry(int key, int value) {
      this.key = key;
      this.value = value;
    }
  }

  public static void main(String[] args) {
    HashTable hashTable = new HashTable();

    hashTable.insert(1, 100);
    hashTable.insert(2, 200);
    hashTable.insert(3, 300);

    System.out.println("Search key 2: " + hashTable.search(2));

    hashTable.delete(2);
    System.out.println("After deleting key 2:");
    hashTable.printTable();
  }
}

/*
 * jarry@MacBook-Pro hash % javac HashTable.java
 * jarry@MacBook-Pro hash % java HashTable
 * Search key 2: 200
 * After deleting key 2:
 * Index 0:
 * Index 1: [1:100]
 * Index 2:
 * Index 3: [3:300]
 * Index 4:
 * Index 5:
 * Index 6:
 * Index 7:
 * Index 8:
 * Index 9:
 */