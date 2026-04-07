/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 树递归算法示例 - 二叉树遍历
 * 
 * 算法特点：
 * - 二叉树的遍历是递归的典型应用
 * - 包含前序、中序、后序遍历
 * - 时间复杂度: O(n)，空间复杂度: O(h)
 * 
 * 学习重点：理解递归在树结构中的应用
 */

// 定义二叉树节点
class Node {
    int data;
    Node left;
    Node right;
    
    public Node(int data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

public class Tree {
    
    /**
     * 创建新节点
     * @param data 节点数据
     * @return 新节点
     */
    public static Node newNode(int data) {
        return new Node(data);
    }
    
    /**
     * 前序遍历
     * 时间复杂度: O(n)，空间复杂度: O(h)
     * @param node 根节点
     */
    public static void preOrder(Node node) {
        // 基本情况：空节点
        if (node == null) return;
        
        // 访问根节点
        System.out.print(node.data + " ");
        
        // 递归遍历左子树
        preOrder(node.left);
        
        // 递归遍历右子树
        preOrder(node.right);
    }
    
    /**
     * 中序遍历
     * 时间复杂度: O(n)，空间复杂度: O(h)
     * @param node 根节点
     */
    public static void inOrder(Node node) {
        // 基本情况：空节点
        if (node == null) return;
        
        // 递归遍历左子树
        inOrder(node.left);
        
        // 访问根节点
        System.out.print(node.data + " ");
        
        // 递归遍历右子树
        inOrder(node.right);
    }
    
    /**
     * 后序遍历
     * 时间复杂度: O(n)，空间复杂度: O(h)
     * @param node 根节点
     */
    public static void postOrder(Node node) {
        // 基本情况：空节点
        if (node == null) return;
        
        // 递归遍历左子树
        postOrder(node.left);
        
        // 递归遍历右子树
        postOrder(node.right);
        
        // 访问根节点
        System.out.print(node.data + " ");
    }
    
    /**
     * 主函数 - 测试二叉树遍历
     */
    public static void main(String[] args) {
        // 测试1：创建二叉树
        Node root = newNode(1);
        root.left = newNode(2);
        root.right = newNode(3);
        root.left.left = newNode(4);
        root.left.right = newNode(5);
        
        // 测试2：前序遍历
        System.out.println("1. 前序遍历:");
        System.out.print("   遍历结果: ");
        preOrder(root);
        System.out.println();
        System.out.println("===");
        
        // 测试3：中序遍历
        System.out.println("2. 中序遍历:");
        System.out.print("   遍历结果: ");
        inOrder(root);
        System.out.println();
        System.out.println("===");
        
        // 测试4：后序遍历
        System.out.println("3. 后序遍历:");
        System.out.print("   遍历结果: ");
        postOrder(root);
        System.out.println();
        System.out.println("===");
    }
}

/*打印结果
jarry@Mac tree-recursion % javac Tree.java && java Tree
1. 前序遍历:
   遍历结果: 1 2 4 5 3 
===
2. 中序遍历:
   遍历结果: 4 2 5 1 3 
===
3. 后序遍历:
   遍历结果: 4 5 2 3 1 
===
*/
