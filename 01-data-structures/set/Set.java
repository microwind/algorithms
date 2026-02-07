import java.util.*;

public class Set {
    private static final int INITIAL_CAPACITY = 16;  // 初始哈希表容量
    private static final float LOAD_FACTOR = 0.75f;  // 负载因子

    private LinkedList<Object>[] buckets;  // 哈希桶数组，指定为存储 Object 类型的 LinkedList
    private int capacity;  // 哈希表容量
    private int size;  // 当前元素个数

    // FNV-1a 哈希函数（用于计算哈希值）
    private long fnvHash(Object key) {
        byte[] bytes = key.toString().getBytes();  // 将键转换为字节数组
        long hash = 2166136261L;  // 初始哈希值，使用 long 类型
        for (byte b : bytes) {  // 对每个字节进行哈希计算
            hash ^= b;
            hash *= 16777619;
        }
        return hash;
    }

    // 创建 Set 并初始化
    @SuppressWarnings("unchecked")
    public Set() {
        this.capacity = INITIAL_CAPACITY;
        this.size = 0;
        this.buckets = new LinkedList[capacity];  // 创建指定大小的桶数组
        for (int i = 0; i < capacity; i++) {
            buckets[i] = new LinkedList<Object>();  // 初始化每个桶为链表
        }
    }

    // 扩容 Set
    private void resize() {
        int newCapacity = capacity * 2;
        @SuppressWarnings("unchecked")
        LinkedList<Object>[] newBuckets = new LinkedList[newCapacity];

        // 重新哈希所有元素
        for (int i = 0; i < capacity; i++) {
            for (Object key : buckets[i]) {
                int newIndex = (int) (fnvHash(key) % newCapacity);  // 使用新的容量计算索引
                if (newBuckets[newIndex] == null) {
                    newBuckets[newIndex] = new LinkedList<Object>();  // 指定泛型类型
                }
                newBuckets[newIndex].add(key);  // 将元素重新插入到新的桶中
            }
        }

        // 更新容量和桶数组
        capacity = newCapacity;
        buckets = newBuckets;
    }

    // 添加元素到 Set
    public void add(Object key) {
        // 判断是否需要扩容
        if ((float) size / capacity > LOAD_FACTOR) {
            resize();  // 扩容
        }

        int index = (int) (fnvHash(key) % capacity);  // 计算索引
        LinkedList<Object> bucket = buckets[index];

        // 查找桶中是否已经有相同的元素
        if (bucket.contains(key)) {
            System.out.println("Exist node: index=" + index + " key=" + key);
            return;  // 已存在则不添加
        }

        // 没有找到相同的元素，进行插入
        bucket.add(key);
        size++;

        // 打印调试信息：打印插入后的 node
        System.out.println("Adding node: index=" + index + " key=" + key);
    }

    // 检查元素是否在 Set 中
    public boolean contains(Object key) {
        int index = (int) (fnvHash(key) % capacity);
        return buckets[index].contains(key);
    }

    // 删除元素
    public void remove(Object key) {
        int index = (int) (fnvHash(key) % capacity);
        LinkedList<Object> bucket = buckets[index];

        if (bucket.remove(key)) {
            size--;
            System.out.println("Removed node: key=" + key);
        }
    }

    // 获取 Set 中的元素个数
    public int size() {
        return size;
    }

    // 遍历 Set 并打印元素
    public void print() {
        for (int i = 0; i < capacity; i++) {
            for (Object key : buckets[i]) {
                System.out.print(key + " ");
            }
        }
        System.out.println();
    }

    public static void main(String[] args) {
        // 创建 Set 实例
        Set set = new Set();
        Integer[] values = {10, 20, 20, 30, 40, 40, 50};

        // 添加元素
        for (int value : values) {
            set.add(value);
        }

        // 打印 Set 内容
        set.print();

        // 检查元素是否存在
        System.out.println("Contains 30? " + set.contains(30));

        // 删除元素
        set.remove(30);
        set.print();
    }
}
