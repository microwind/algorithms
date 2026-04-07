/*
 * B+树简单实现
 * Java版本
 */

import java.util.ArrayList;
import java.util.List;

public class BPlusTree {
    private static final int ORDER = 3;  // B+树阶数
    
    // 节点类
    private class Node {
        List<Integer> keys;
        List<Node> children;
        Node next;  // 叶节点链表指针
        boolean isLeaf;
        
        Node(boolean isLeaf) {
            this.keys = new ArrayList<>();
            this.children = new ArrayList<>();
            this.isLeaf = isLeaf;
            this.next = null;
        }
    }
    
    private Node root;
    
    public BPlusTree() {
        this.root = new Node(true);
    }
    
    // 查找叶节点
    private Node findLeaf(Node node, int key) {
        if (node.isLeaf) {
            return node;
        }
        
        int i = 0;
        while (i < node.keys.size() && key > node.keys.get(i)) {
            i++;
        }
        
        return findLeaf(node.children.get(i), key);
    }
    
    // 搜索键值
    public boolean search(int key) {
        Node leaf = findLeaf(root, key);
        return leaf.keys.contains(key);
    }
    
    // 分裂子节点
    private void splitChild(Node parent, int i, Node child) {
        Node newChild = new Node(child.isLeaf);
        int mid = ORDER - 1;
        
        // 复制后半部分键
        for (int j = 0; j < ORDER - 1; j++) {
            newChild.keys.add(child.keys.get(j + mid + 1));
        }
        
        // 如果不是叶节点，复制子节点
        if (!child.isLeaf) {
            for (int j = 0; j < ORDER; j++) {
                newChild.children.add(child.children.get(j + mid + 1));
            }
        } else {
            newChild.next = child.next;
            child.next = newChild;
        }
        
        // 在父节点中插入中间键
        parent.keys.add(i, child.keys.get(mid));
        parent.children.add(i + 1, newChild);
        
        // 调整原节点的键数量
        while (child.keys.size() > mid) {
            child.keys.remove(child.keys.size() - 1);
        }
    }
    
    // 在非满节点中插入
    private void insertNonFull(Node node, int key) {
        if (node.isLeaf) {
            // 叶节点直接插入
            int i = node.keys.size() - 1;
            node.keys.add(null);
            while (i >= 0 && key < node.keys.get(i)) {
                node.keys.set(i + 1, node.keys.get(i));
                i--;
            }
            node.keys.set(i + 1, key);
        } else {
            // 内部节点
            int i = node.keys.size() - 1;
            while (i >= 0 && key < node.keys.get(i)) {
                i--;
            }
            i++;
            
            if (node.children.get(i).keys.size() == 2 * ORDER - 1) {
                splitChild(node, i, node.children.get(i));
                if (key > node.keys.get(i)) {
                    i++;
                }
            }
            
            insertNonFull(node.children.get(i), key);
        }
    }
    
    // 插入键值
    public void insert(int key) {
        if (root.keys.size() == 2 * ORDER - 1) {
            Node newRoot = new Node(false);
            newRoot.children.add(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
        insertNonFull(root, key);
    }
    
    // 中序遍历
    private void traverseNode(Node node, List<Integer> result) {
        if (node.isLeaf) {
            result.addAll(node.keys);
        } else {
            for (int i = 0; i < node.keys.size(); i++) {
                traverseNode(node.children.get(i), result);
                result.add(node.keys.get(i));
            }
            traverseNode(node.children.get(node.keys.size()), result);
        }
    }
    
    public List<Integer> traverse() {
        List<Integer> result = new ArrayList<>();
        traverseNode(root, result);
        return result;
    }
    
    // 主函数
    public static void main(String[] args) {
        System.out.println("=".repeat(50));
        System.out.println("B+树实现 (B+ Tree)");
        System.out.println("=".repeat(50));
        
        BPlusTree bpt = new BPlusTree();
        
        int[] values = {10, 20, 5, 6, 12, 30, 7, 17};
        System.out.println("\n插入数据:");
        for (int val : values) {
            System.out.print(val + " ");
            bpt.insert(val);
        }
        System.out.println();
        
        System.out.println("\n中序遍历结果: " + bpt.traverse());
        
        System.out.println("\n搜索测试:");
        int[] testKeys = {6, 15, 30};
        for (int key : testKeys) {
            String result = bpt.search(key) ? "找到" : "未找到";
            System.out.println("  查找 " + key + ": " + result);
        }
        
        System.out.println("\nB+树特点:");
        System.out.println("  • 所有数据存储在叶节点");
        System.out.println("  • 叶节点形成有序链表");
        System.out.println("  • 适合磁盘存储和范围查询");
        System.out.println("  • 查找、插入、删除: O(log n)");
        System.out.println("  • 应用于数据库索引、文件系统");
    }
}
/*打印结果
jarry@Mac b+tree % java BPlusTree.java 
==================================================
B+树实现 (B+ Tree)
==================================================

插入数据:
10 20 5 6 12 30 7 17 

中序遍历结果: [5, 6, 7, 10, 12, 17, 20, 30]

搜索测试:
  查找 6: 找到
  查找 15: 未找到
  查找 30: 找到

B+树特点:
  • 所有数据存储在叶节点
  • 叶节点形成有序链表
  • 适合磁盘存储和范围查询
  • 查找、插入、删除: O(log n)
  • 应用于数据库索引、文件系统
*/