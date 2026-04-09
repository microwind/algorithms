/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 树算法 - AVL树实现 (Adelson-Velsky and Landis Tree)
 * 自平衡二叉搜索树，确保高度差不超过1
 * 保证查找、插入、删除都是O(log n)时间复杂度
 */

public class AVL {
    
    // AVL节点结构
    static class AVLNode {
        int data;
        int height;
        AVLNode left;
        AVLNode right;
        
        public AVLNode(int data) {
            this.data = data;
            this.height = 1;
            this.left = null;
            this.right = null;
        }
    }
    
    /**
     * 获取节点高度
     */
    private int getHeight(AVLNode node) {
        if (node == null) {
            return 0;
        }
        return node.height;
    }
    
    /**
     * 计算平衡因子
     */
    private int getBalance(AVLNode node) {
        if (node == null) {
            return 0;
        }
        return getHeight(node.left) - getHeight(node.right);
    }
    
    /**
     * 更新节点高度
     */
    private void updateHeight(AVLNode node) {
        if (node != null) {
            int leftHeight = getHeight(node.left);
            int rightHeight = getHeight(node.right);
            node.height = 1 + Math.max(leftHeight, rightHeight);
        }
    }
    
    /**
     * 右旋转
     */
    private AVLNode rightRotate(AVLNode y) {
        AVLNode x = y.left;
        AVLNode T2 = x.right;
        
        // 旋转
        x.right = y;
        y.left = T2;
        
        // 更新高度
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    /**
     * 左旋转
     */
    private AVLNode leftRotate(AVLNode x) {
        AVLNode y = x.right;
        AVLNode T2 = y.left;
        
        // 旋转
        y.left = x;
        x.right = T2;
        
        // 更新高度
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    /**
     * 插入节点
     */
    public AVLNode insert(AVLNode root, int data) {
        // 1. 标准BST插入
        if (root == null) {
            return new AVLNode(data);
        }
        
        if (data < root.data) {
            root.left = insert(root.left, data);
        } else if (data > root.data) {
            root.right = insert(root.right, data);
        } else {
            // 重复值不允许
            return root;
        }
        
        // 2. 更新高度
        updateHeight(root);
        
        // 3. 获取平衡因子
        int balance = getBalance(root);
        
        // 4. 如果不平衡，有4种情况
        
        // 左左情况
        if (balance > 1 && data < root.left.data) {
            return rightRotate(root);
        }
        
        // 右右情况
        if (balance < -1 && data > root.right.data) {
            return leftRotate(root);
        }
        
        // 左右情况
        if (balance > 1 && data > root.left.data) {
            root.left = leftRotate(root.left);
            return rightRotate(root);
        }
        
        // 右左情况
        if (balance < -1 && data < root.right.data) {
            root.right = rightRotate(root.right);
            return leftRotate(root);
        }
        
        return root;
    }
    
    /**
     * 中序遍历
     */
    private void inOrder(AVLNode root) {
        if (root != null) {
            inOrder(root.left);
            System.out.print(root.data + " ");
            inOrder(root.right);
        }
    }
    
    /**
     * 主函数 - 测试AVL树
     */
    public static void main(String[] args) {
        AVL avl = new AVL();
        AVLNode root = null;
        
        System.out.println("=== AVL树测试 ===");
        
        // 插入测试数据
        int[] testData = {10, 20, 30, 40, 50, 25};
        System.out.println("插入数据: " + java.util.Arrays.toString(testData));
        
        for (int data : testData) {
            root = avl.insert(root, data);
            System.out.println("插入 " + data + " 后的中序遍历:");
            avl.inOrder(root);
            System.out.println();
        }
        
        System.out.println("最终平衡因子:");
        avl.printBalanceFactor(root);
    }
    
    /**
     * 打印平衡因子
     */
    private void printBalanceFactor(AVLNode root) {
        if (root != null) {
            printBalanceFactor(root.left);
            System.out.println("节点 " + root.data + ": 平衡因子 = " + getBalance(root));
            printBalanceFactor(root.right);
        }
    }
}

/*打印结果
jarry@Mac avl % javac avl.java && java AVL
=== AVL树测试 ===
插入数据: [10, 20, 30, 40, 50, 25]
插入 10 后的中序遍历:
10 
插入 20 后的中序遍历:
10 20 
插入 30 后的中序遍历:
10 20 30 
插入 40 后的中序遍历:
10 20 30 40 
插入 50 后的中序遍历:
10 20 30 40 50 
插入 25 后的中序遍历:
10 20 25 30 40 50 
最终平衡因子:
节点 10: 平衡因子 = 0
节点 20: 平衡因子 = 0
节点 25: 平衡因子 = 0
节点 30: 平衡因子 = -1
节点 40: 平衡因子 = 0
节点 50: 平衡因子 = 0
*/
