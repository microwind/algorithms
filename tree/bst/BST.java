/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 树算法 - 二叉搜索树实现 (Binary Search Tree)
 * 有序二叉树，左子树 < 根节点 < 右子树
 * 用于快速查找、插入、删除
 */

// BST节点结构
class BSTNode {
    int data;
    BSTNode left;
    BSTNode right;
    
    public BSTNode(int data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

// BST类
class BST {
    private BSTNode root;
    
    public BST() {
        this.root = null;
    }
    
    /**
     * 插入节点到BST
     */
    public BSTNode insert(BSTNode node, int data) {
        if (node == null) {
            return new BSTNode(data);
        }
        
        if (data < node.data) {
            node.left = insert(node.left, data);
        } else if (data > node.data) {
            node.right = insert(node.right, data);
        }
        // 重复值不允许
        
        return node;
    }
    
    /**
     * 查找节点
     */
    public boolean search(BSTNode node, int data) {
        if (node == null) {
            return false;
        }
        
        if (data == node.data) {
            return true;
        } else if (data < node.data) {
            return search(node.left, data);
        } else {
            return search(node.right, data);
        }
    }
    
    /**
     * 中序遍历（升序）
     */
    public void inOrder(BSTNode node) {
        if (node != null) {
            inOrder(node.left);
            System.out.print(node.data + " ");
            inOrder(node.right);
        }
    }
    
    /**
     * 前序遍历
     */
    public void preOrder(BSTNode node) {
        if (node != null) {
            System.out.print(node.data + " ");
            preOrder(node.left);
            preOrder(node.right);
        }
    }
    
    /**
     * 后序遍历
     */
    public void postOrder(BSTNode node) {
        if (node != null) {
            postOrder(node.left);
            postOrder(node.right);
            System.out.print(node.data + " ");
        }
    }
    
    /**
     * 查找最小值
     */
    public BSTNode findMin(BSTNode node) {
        while (node.left != null) {
            node = node.left;
        }
        return node;
    }
    
    /**
     * 查找最大值
     */
    public BSTNode findMax(BSTNode node) {
        while (node.right != null) {
            node = node.right;
        }
        return node;
    }
    
    /**
     * 计算树的高度
     */
    public int height(BSTNode node) {
        if (node == null) {
            return 0;
        }
        
        int leftHeight = height(node.left);
        int rightHeight = height(node.right);
        
        return 1 + Math.max(leftHeight, rightHeight);
    }
    
    /**
     * 计算节点数量
     */
    public int nodeCount(BSTNode node) {
        if (node == null) {
            return 0;
        }
        
        return 1 + nodeCount(node.left) + nodeCount(node.right);
    }
    
    // Getter方法
    public BSTNode getRoot() {
        return root;
    }
    
    // Setter方法
    public void setRoot(BSTNode root) {
        this.root = root;
    }
    
    // 主函数 - 测试BST
    public static void main(String[] args) {
        BST bst = new BST();
        
        System.out.println("=== 二叉搜索树测试 ===");
        
        // 插入测试数据
        int[] testData = {50, 30, 70, 20, 40, 60, 80};
        System.out.println("插入数据: ");
        for (int data : testData) {
            System.out.print(data + " ");
            bst.setRoot(bst.insert(bst.getRoot(), data));
        }
        System.out.println();
        System.out.println();
        
        // 遍历测试
        System.out.println("=== 遍历测试 ===");
        System.out.print("中序遍历: ");
        bst.inOrder(bst.getRoot());
        System.out.println();
        
        System.out.print("前序遍历: ");
        bst.preOrder(bst.getRoot());
        System.out.println();
        
        System.out.print("后序遍历: ");
        bst.postOrder(bst.getRoot());
        System.out.println();
        System.out.println();
        
        // 搜索测试
        System.out.println("=== 搜索测试 ===");
        int[] searchKeys = {40, 90};
        for (int key : searchKeys) {
            boolean found = bst.search(bst.getRoot(), key);
            System.out.println("搜索 " + key + ": " + (found ? "找到" : "未找到"));
        }
        System.out.println();
        
        // 树属性测试
        System.out.println("=== 树属性测试 ===");
        System.out.println("树的高度: " + bst.height(bst.getRoot()));
        System.out.println("节点数量: " + bst.nodeCount(bst.getRoot()));
        
        if (bst.getRoot() != null) {
            System.out.println("最小值: " + bst.findMin(bst.getRoot()).data);
            System.out.println("最大值: " + bst.findMax(bst.getRoot()).data);
        }
        
        System.out.println();
        System.out.println("=== BST特点说明 ===");
        System.out.println("1. 左子树所有节点 < 根节点 < 右子树所有节点");
        System.out.println("2. 中序遍历得到有序序列");
        System.out.println("3. 查找、插入、删除平均时间复杂度 O(log n)");
        System.out.println("4. 最坏情况（退化为链表）时间复杂度 O(n)");
    }
}

/*打印结果
jarry@Mac bst % javac bst.java && java bst
=== 二叉搜索树测试 ===
插入数据: 
50 30 70 20 40 60 80 

=== 遍历测试 ===
中序遍历: 20 30 40 50 60 70 80 
前序遍历: 50 30 20 40 70 60 80 
后序遍历: 20 40 30 60 80 70 50 

=== 搜索测试 ===
搜索 40: 找到
搜索 90: 未找到

=== 树属性测试 ===
树的高度: 3
节点数量: 7
最小值: 20
最大值: 80

=== BST特点说明 ===
1. 左子树所有节点 < 根节点 < 右子树所有节点
2. 中序遍历得到有序序列
3. 查找、插入、删除平均时间复杂度 O(log n)
4. 最坏情况（退化为链表）时间复杂度 O(n)
*/
