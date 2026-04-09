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

// 声明 Node.js process 对象
declare var process: any;

// BST节点结构
class BSTNode {
    data: number;
    left: BSTNode | null;
    right: BSTNode | null;
    
    constructor(data: number) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

// BST类
class BST {
    root: BSTNode | null;
    
    constructor() {
        this.root = null;
    }
    
    /**
     * 插入节点到BST
     */
    insert(node: BSTNode | null, data: number): BSTNode {
        if (node === null) {
            return new BSTNode(data);
        }
        
        if (data < node.data) {
            node.left = this.insert(node.left, data);
        } else if (data > node.data) {
            node.right = this.insert(node.right, data);
        }
        // 重复值不允许
        
        return node;
    }
    
    /**
     * 查找节点
     */
    search(node: BSTNode | null, data: number): boolean {
        if (node === null) {
            return false;
        }
        
        if (data === node.data) {
            return true;
        } else if (data < node.data) {
            return this.search(node.left, data);
        } else {
            return this.search(node.right, data);
        }
    }
    
    /**
     * 中序遍历（升序）
     */
    inOrder(node: BSTNode | null): void {
        if (node !== null) {
            this.inOrder(node.left);
            process.stdout.write(node.data + " ");
            this.inOrder(node.right);
        }
    }
    
    /**
     * 前序遍历
     */
    preOrder(node: BSTNode | null): void {
        if (node !== null) {
            process.stdout.write(node.data + " ");
            this.preOrder(node.left);
            this.preOrder(node.right);
        }
    }
    
    /**
     * 后序遍历
     */
    postOrder(node: BSTNode | null): void {
        if (node !== null) {
            this.postOrder(node.left);
            this.postOrder(node.right);
            process.stdout.write(node.data + " ");
        }
    }
    
    /**
     * 查找最小值
     */
    findMin(node: BSTNode): BSTNode {
        while (node.left !== null) {
            node = node.left;
        }
        return node;
    }
    
    /**
     * 查找最大值
     */
    findMax(node: BSTNode): BSTNode {
        while (node.right !== null) {
            node = node.right;
        }
        return node;
    }
    
    /**
     * 计算树的高度
     */
    height(node: BSTNode | null): number {
        if (node === null) {
            return 0;
        }
        
        const leftHeight = this.height(node.left);
        const rightHeight = this.height(node.right);
        
        return 1 + Math.max(leftHeight, rightHeight);
    }
    
    /**
     * 计算节点数量
     */
    nodeCount(node: BSTNode | null): number {
        if (node === null) {
            return 0;
        }
        
        return 1 + this.nodeCount(node.left) + this.nodeCount(node.right);
    }
    
    // 主函数 - 测试BST
    main(): void {
        console.log("=== 二叉搜索树测试 ===");
        
        // 插入测试数据
        const testData = [50, 30, 70, 20, 40, 60, 80];
        process.stdout.write("插入数据: ");
        for (const data of testData) {
            process.stdout.write(data + " ");
            this.root = this.insert(this.root, data);
        }
        console.log();
        console.log();
        
        // 遍历测试
        console.log("=== 遍历测试 ===");
        process.stdout.write("中序遍历: ");
        this.inOrder(this.root);
        console.log();
        
        process.stdout.write("前序遍历: ");
        this.preOrder(this.root);
        console.log();
        
        process.stdout.write("后序遍历: ");
        this.postOrder(this.root);
        console.log();
        console.log();
        
        // 搜索测试
        console.log("=== 搜索测试 ===");
        const searchKeys = [40, 90];
        for (const key of searchKeys) {
            const found = this.search(this.root, key);
            console.log(`搜索 ${key}: ${found ? "找到" : "未找到"}`);
        }
        console.log();
        
        // 树属性测试
        console.log("=== 树属性测试 ===");
        console.log(`树的高度: ${this.height(this.root)}`);
        console.log(`节点数量: ${this.nodeCount(this.root)}`);
        
        if (this.root !== null) {
            console.log(`最小值: ${this.findMin(this.root).data}`);
            console.log(`最大值: ${this.findMax(this.root).data}`);
        }
        
        console.log();
        console.log("=== BST特点说明 ===");
        console.log("1. 左子树所有节点 < 根节点 < 右子树所有节点");
        console.log("2. 中序遍历得到有序序列");
        console.log("3. 查找、插入、删除平均时间复杂度 O(log n)");
        console.log("4. 最坏情况（退化为链表）时间复杂度 O(n)");
    }
}

// 运行测试
const bst = new BST();
bst.main();

/*打印结果
jarry@Mac bst % npx ts-node bst.ts
=== 二叉搜索树测试 ===
插入数据: 50 30 70 20 40 60 80 

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
