/**
 * B+树简单实现
 * Java版本
 * 
 * B+树特性:
 * - 多路搜索树，适合磁盘存储
 * - 所有数据都在叶子节点
 * - 叶子节点形成链表，便于范围查询
 * - 内部节点只存储索引
 * 
 * 应用场景:
 * - 数据库索引
 * - 文件系统
 * - 大规模数据存储
 */

import java.util.ArrayList;
import java.util.List;

public class BPlusTree {
    private static final int ORDER = 3;  // B+树阶数
    
    /**
     * 节点类
     * 
     * 属性说明:
     * - keys: 存储键值
     * - children: 子节点指针
     * - next: 叶节点链表指针
     * - isLeaf: 是否为叶子节点
     */
    private class Node {
        List<Integer> keys;           // 键值列表
        List<Node> children;         // 子节点列表
        Node next;                  // 叶节点链表指针
        boolean isLeaf;              // 是否为叶子节点
        
        /**
         * 节点构造函数
         * @param isLeaf 是否为叶子节点
         */
        Node(boolean isLeaf) {
            this.keys = new ArrayList<>();     // 初始化键值列表
            this.children = new ArrayList<>(); // 初始化子节点列表
            this.isLeaf = isLeaf;              // 设置节点类型
            this.next = null;                  // 初始化链表指针
        }
    }
    
    private Node root;  // 根节点
    
    /**
     * B+树构造函数
     */
    public BPlusTree() {
        this.root = new Node(true); // 创建空的叶子节点作为根
    }
    
    /**
     * 插入键值到B+树
     * 
     * 算法步骤:
     * 1. 从根节点开始查找插入位置
     * 2. 如果节点已满，进行分裂
     * 3. 递归向上处理分裂
     * 4. 维护B+树性质
     * 
     * @param key 要插入的键值
     */
    public void insert(int key) {
        Node root = this.root;
        
        // 如果根节点已满且不是叶子节点，需要分裂
        if (root.keys.size() == ORDER - 1 && !root.isLeaf) {
            Node newRoot = new Node(false);
            newRoot.children.add(root);
            splitChild(newRoot, 0);
            this.root = newRoot;
            insertNonFull(this.root, key);
        } else {
            insertNonFull(root, key);
        }
    }
    
    /**
     * 向非满节点插入键值
     * 
     * @param node 当前节点
     * @param key 要插入的键值
     */
    private void insertNonFull(Node node, int key) {
        int i = node.keys.size() - 1;
        
        if (node.isLeaf) {
            // 叶子节点：找到正确位置插入
            node.keys.add(0); // 临时添加
            while (i >= 0 && key < node.keys.get(i)) {
                node.keys.set(i + 1, node.keys.get(i));
                i--;
            }
            node.keys.set(i + 1, key);
        } else {
            // 内部节点：找到合适的子节点
            while (i >= 0 && key < node.keys.get(i)) {
                i--;
            }
            i++;
            
            // 如果子节点已满，先分裂
            if (node.children.get(i).keys.size() == ORDER - 1) {
                splitChild(node, i);
                if (key > node.keys.get(i)) {
                    i++;
                }
            }
            insertNonFull(node.children.get(i), key);
        }
    }
    
    /**
     * 分裂子节点
     * 
     * 算法步骤:
     * 1. 找到中间位置
     * 2. 创建新节点
     * 3. 分配键值和子节点
     * 4. 更新父节点
     * 
     * @param parent 父节点
     * @param index 子节点索引
     */
    private void splitChild(Node parent, int index) {
        Node fullNode = parent.children.get(index);
        Node newNode = new Node(fullNode.isLeaf);
        
        // 分配键值到新节点
        for (int i = 0; i < ORDER / 2 - 1; i++) {
            newNode.keys.add(fullNode.keys.get(ORDER / 2 + i));
        }
        
        if (!fullNode.isLeaf) {
            // 内部节点：分配子节点
            for (int i = 0; i < ORDER / 2; i++) {
                newNode.children.add(fullNode.children.get(ORDER / 2 + i));
            }
        } else {
            // 叶子节点：设置链表指针
            newNode.next = fullNode.next;
            fullNode.next = newNode;
        }
        
        // 更新父节点
        parent.keys.add(index, fullNode.keys.get(ORDER / 2 - 1));
        parent.children.add(index + 1, newNode);
    }
    
    /**
     * 搜索键值
     * 
     * 算法步骤:
     * 1. 从根节点开始
     * 2. 根据键值选择子节点
     * 3. 递归搜索直到叶子节点
     * 4. 在叶子节点中查找
     * 
     * @param key 要搜索的键值
     * @return 是否找到键值
     */
    public boolean search(int key) {
        return search(this.root, key);
    }
    
    private boolean search(Node node, int key) {
        int i = 0;
        
        // 在当前节点中找到合适的范围
        while (i < node.keys.size() && key > node.keys.get(i)) {
            i++;
        }
        
        if (node.isLeaf) {
            // 叶子节点：直接查找
            return i < node.keys.size() && key == node.keys.get(i);
        } else {
            // 内部节点：递归搜索子节点
            return search(node.children.get(i), key);
        }
    }
    
    /**
     * 范围查询
     * 
     * @param start 起始键值
     * @param end 结束键值
     * @return 范围内的键值列表
     */
    public List<Integer> rangeQuery(int start, int end) {
        List<Integer> result = new ArrayList<>();
        Node leaf = findLeaf(start);
        
        // 从叶子节点开始遍历链表
        while (leaf != null) {
            for (int key : leaf.keys) {
                if (key >= start && key <= end) {
                    result.add(key);
                } else if (key > end) {
                    return result;
                }
            }
            leaf = leaf.next;
        }
        
        return result;
    }
    
    /**
     * 查找包含指定键值的叶子节点
     * 
     * @param key 目标键值
     * @return 包含键值的叶子节点
     */
    private Node findLeaf(int key) {
        Node current = this.root;
        
        while (!current.isLeaf) {
            int i = 0;
            while (i < current.keys.size() && key > current.keys.get(i)) {
                i++;
            }
            current = current.children.get(i);
        }
        
        return current;
    }
    
    /**
     * 打印B+树结构
     */
    public void printTree() {
        System.out.println("B+树结构:");
        printTree(this.root, 0);
    }
    
    /**
     * 递归打印树结构
     * 
     * @param node 当前节点
     * @param level 当前层级
     */
    private void printTree(Node node, int level) {
        if (node == null) return;
        
        // 打印缩进
        for (int i = 0; i < level; i++) {
            System.out.print("  ");
        }
        
        // 打印节点信息
        System.out.print("节点" + (node.isLeaf ? "(叶子)" : "(内部)") + ": ");
        System.out.println(node.keys);
        
        // 递归打印子节点
        if (!node.isLeaf) {
            for (Node child : node.children) {
                printTree(child, level + 1);
            }
        }
    }
    
    /**
     * 打印叶子节点链表
     */
    public void printLeafChain() {
        System.out.println("叶子节点链表:");
        Node leaf = findLeaf(Integer.MIN_VALUE);
        
        while (leaf != null) {
            System.out.print(leaf.keys);
            if (leaf.next != null) {
                System.out.print(" -> ");
            }
            leaf = leaf.next;
        }
        System.out.println();
    }
    
    /**
     * 主测试方法
     * 
     * 测试用例:
     * 1. 插入一系列键值
     * 2. 测试搜索功能
     * 3. 测试范围查询
     * 4. 展示树结构
     */
    public static void main(String[] args) {
        BPlusTree tree = new BPlusTree();
        
        System.out.println("=".repeat(60));
        System.out.println("B+树算法测试 - Java实现");
        System.out.println("=".repeat(60));
        System.out.println();
        
        // 插入测试数据
        int[] keys = {10, 20, 5, 6, 12, 30, 7, 17, 25, 35};
        System.out.println("插入键值:");
        for (int key : keys) {
            System.out.print(key + " ");
            tree.insert(key);
        }
        System.out.println("\n");
        
        // 显示树结构
        tree.printTree();
        System.out.println();
        
        // 显示叶子节点链表
        tree.printLeafChain();
        System.out.println();
        
        // 测试搜索
        System.out.println("搜索测试:");
        int[] searchKeys = {6, 15, 30, 40};
        for (int key : searchKeys) {
            boolean found = tree.search(key);
            System.out.println("搜索 " + key + ": " + (found ? "找到" : "未找到"));
        }
        System.out.println();
        
        // 测试范围查询
        System.out.println("范围查询 [10, 25]:");
        List<Integer> rangeResult = tree.rangeQuery(10, 25);
        System.out.println("结果: " + rangeResult);
        System.out.println();
        
        System.out.println("=== 算法特性 ===");
        System.out.println("B+树:");
        System.out.println("  - 多路搜索树，适合磁盘存储");
        System.out.println("  - 所有数据都在叶子节点");
        System.out.println("  - 叶子节点形成有序链表");
        System.out.println("  - 内部节点只存储索引");
        System.out.println("  - 支持高效的范围查询");
        
        System.out.println("\n复杂度分析:");
        System.out.println("  - 查找: O(log n)");
        System.out.println("  - 插入: O(log n)");
        System.out.println("  - 删除: O(log n)");
        System.out.println("  - 范围查询: O(log n + k)，k为结果数量");
        
        System.out.println("\n=== 应用场景 ===");
        System.out.println("B+树用于:");
        System.out.println("  - 数据库索引（MySQL、PostgreSQL等）");
        System.out.println("  - 文件系统（NTFS、ext4等）");
        System.out.println("  - 大规模数据存储系统");
        System.out.println("  - 搜索引擎索引");
        System.out.println("  - 分布式存储系统");
    }
}
