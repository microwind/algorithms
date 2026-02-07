import java.util.ArrayList;

class Map {
    private ArrayList<Entry> entries;
    private int size;
    private int capacity;

    private static final int INITIAL_CAPACITY = 10;

    public Map() {
        this.entries = new ArrayList<>();
        this.size = 0;
        this.capacity = INITIAL_CAPACITY;
    }

    // 重新分配容量
    private void resizeMap(int newCapacity) {
        this.capacity = newCapacity;
    }

    // 插入键值对（如果存在则更新）
    public void put(String key, int value) {
        for (Entry entry : entries) {
            if (entry.key.equals(key)) {
                entry.value = value; // 更新值
                return;
            }
        }
        if (size >= capacity) {
            resizeMap(capacity * 2);
        }
        entries.add(new Entry(key, value));
        size++;
    }

    // 查找键
    public int get(String key) {
        for (Entry entry : entries) {
            if (entry.key.equals(key)) {
                return entry.value;
            }
        }
        return -1; // 未找到
    }

    // 删除键
    public void delete(String key) {
        for (int i = 0; i < size; i++) {
            if (entries.get(i).key.equals(key)) {
                entries.remove(i);
                size--;
                return;
            }
        }
    }

    private static class Entry {
        String key;
        int value;

        Entry(String key, int value) {
            this.key = key;
            this.value = value;
        }
    }

    public static void main(String[] args) {
        Map map = new Map();

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
 * jarry@MacBook-Pro map % javac Map.java
 * jarry@MacBook-Pro map % java Map
 * apple: 10
 * banana: 20
 * grape: -1
 * banana after delete: -1
 */