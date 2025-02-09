class TreeNode {
    int value;
    TreeNode left, right;

    public TreeNode(int value) {
        this.value = value;
        this.left = this.right = null;
    }
}

public class Tree {
    public static void main(String[] args) {

        // 创建树
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

        System.out.print("前序遍历：");
        preorderTraversal(root);
        System.out.println();

        System.out.print("中序遍历：");
        inorderTraversal(root);
        System.out.println();

        System.out.print("后序遍历：");
        postorderTraversal(root);
        System.out.println();
    }

    // 前序遍历：根 -> 左 -> 右
    public static void preorderTraversal(TreeNode root) {
        if (root == null) {
            return;
        }
        System.out.print(root.value + " ");
        preorderTraversal(root.left);
        preorderTraversal(root.right);
    }

    // 中序遍历：左 -> 根 -> 右
    public static void inorderTraversal(TreeNode root) {
        if (root == null) {
            return;
        }
        inorderTraversal(root.left);
        System.out.print(root.value + " ");
        inorderTraversal(root.right);
    }

    // 后序遍历：左 -> 右 -> 根
    public static void postorderTraversal(TreeNode root) {
        if (root == null) {
            return;
        }
        postorderTraversal(root.left);
        postorderTraversal(root.right);
        System.out.print(root.value + " ");
    }
}

/*
 * jarry@MacBook-Pro tree % javac Tree.java
 * jarry@MacBook-Pro tree % java Tree
 * 前序遍历：1 2 4 5 3 6
 * 中序遍历：4 2 5 1 6 3
 * 后序遍历：4 5 2 6 3 1
 */