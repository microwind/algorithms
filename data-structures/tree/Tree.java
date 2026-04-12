/**
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 二叉树数据结构 - Java实现
 */
// 二叉树节点类
class TreeNode {
    int value;          // 节点值
    TreeNode left;      // 左子节点
    TreeNode right;     // 右子节点

    // 构造函数：初始化节点值，左右子节点置空
    public TreeNode(int value) {
        this.value = value;
        this.left = this.right = null;
    }
}

public class Tree {
    public static void main(String[] args) {
        // 构建示例二叉树
        //        1
        //       / \
        //      2   3
        //     / \   /
        //    4   5 6
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.left = new TreeNode(6);

        // 前序遍历（根左右）
        System.out.print("前序遍历：");
        preorderTraversal(root);
        System.out.println();

        // 中序遍历（左根右）
        System.out.print("中序遍历：");
        inorderTraversal(root);
        System.out.println();

        // 后序遍历（左右根）
        System.out.print("后序遍历：");
        postorderTraversal(root);
        System.out.println();
    }

    // 前序遍历：根 -> 左 -> 右
    public static void preorderTraversal(TreeNode root) {
        if (root == null) return;
        System.out.print(root.value + " "); // 访问根
        preorderTraversal(root.left);       // 遍历左子树
        preorderTraversal(root.right);      // 遍历右子树
    }

    // 中序遍历：左 -> 根 -> 右
    public static void inorderTraversal(TreeNode root) {
        if (root == null) return;
        inorderTraversal(root.left);        // 遍历左子树
        System.out.print(root.value + " "); // 访问根
        inorderTraversal(root.right);       // 遍历右子树
    }

    // 后序遍历：左 -> 右 -> 根
    public static void postorderTraversal(TreeNode root) {
        if (root == null) return;
        postorderTraversal(root.left);      // 遍历左子树
        postorderTraversal(root.right);     // 遍历右子树
        System.out.print(root.value + " "); // 访问根
    }
}

/*
 * jarry@MacBook-Pro tree % javac Tree.java
 * jarry@MacBook-Pro tree % java Tree
 * 前序遍历：1 2 4 5 3 6
 * 中序遍历：4 2 5 1 6 3
 * 后序遍历：4 5 2 6 3 1
 */