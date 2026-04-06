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
     * 主函数 - 测试二叉树遍历
     */
    public static void main(String[] args) {
        // 测试1：创建二叉树
        Node root = newNode(1);
        root.left = newNode(2);
        root.right = newNode(3);
        root.left.left = newNode(4);
        root.left.right = newNode(5);
        
        // 输出调用过程示例
        System.out.println("调用过程示例：");
        System.out.println("preOrder(root)");
        System.out.println("   |");
        System.out.println("   v");
        System.out.println("printf(1)");
        System.out.println("preOrder(root.left)");
        System.out.println("   |");
        System.out.println("   v");
        System.out.println("printf(2)");
        System.out.println("preOrder(root.left.left)");
        System.out.println("   |");
        System.out.println("   v");
        System.out.println("printf(4)");
        System.out.println("preOrder(root.left.right)");
        System.out.println("   |");
        System.out.println("   v");
        System.out.println("printf(5)");
        System.out.println("preOrder(root.right)");
        System.out.println("   |");
        System.out.println("   v");
        System.out.println("printf(3)");
        System.out.println();
        
        // 测试2：执行前序遍历
        System.out.println("Preorder traversal of binary tree is");
        preOrder(root);
    }
}

/*打印结果
jarry@Mac tree-recursion % javac Tree.java && java Tree
调用过程示例：
preOrder(root)
   |
   v
printf(1)
preOrder(root.left)
   |
   v
printf(2)
preOrder(root.left.left)
   |
   v
printf(4)
preOrder(root.left.right)
   |
   v
printf(5)
preOrder(root.right)
   |
   v
printf(3)

Preorder traversal of binary tree is
1 2 4 5 3 
*/
