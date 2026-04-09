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

// 声明 Node.js process 对象
// declare const process: any;

// AVL节点结构
class AVLNode {
    data: number;
    height: number;
    left: AVLNode | null;
    right: AVLNode | null;
    
    constructor(data: number) {
        this.data = data;
        this.height = 1;
        this.left = null;
        this.right = null;
    }
}

class AVL {
    /**
     * 获取节点高度
     */
    getHeight(node: AVLNode | null): number {
        if (node === null) {
            return 0;
        }
        return node.height;
    }
    
    /**
     * 计算平衡因子
     */
    getBalance(node: AVLNode | null): number {
        if (node === null) {
            return 0;
        }
        return this.getHeight(node.left) - this.getHeight(node.right);
    }
    
    /**
     * 更新节点高度
     */
    updateHeight(node: AVLNode | null): void {
        if (node !== null) {
            const leftHeight = this.getHeight(node.left);
            const rightHeight = this.getHeight(node.right);
            node.height = 1 + Math.max(leftHeight, rightHeight);
        }
    }
    
    /**
     * 右旋转
     */
    rightRotate(y: AVLNode): AVLNode {
        const x = y.left!;
        const T2 = x.right;
        
        // 旋转
        x.right = y;
        y.left = T2;
        
        // 更新高度
        this.updateHeight(y);
        this.updateHeight(x);
        
        return x;
    }
    
    /**
     * 左旋转
     */
    leftRotate(x: AVLNode): AVLNode {
        const y = x.right!;
        const T2 = y.left;
        
        // 旋转
        y.left = x;
        x.right = T2;
        
        // 更新高度
        this.updateHeight(x);
        this.updateHeight(y);
        
        return y;
    }
    
    /**
     * 插入节点
     */
    insert(root: AVLNode | null, data: number): AVLNode {
        // 1. 标准BST插入
        if (root === null) {
            return new AVLNode(data);
        }
        
        if (data < root.data) {
            root.left = this.insert(root.left, data);
        } else if (data > root.data) {
            root.right = this.insert(root.right, data);
        } else {
            // 重复值不允许
            return root;
        }
        
        // 2. 更新高度
        this.updateHeight(root);
        
        // 3. 获取平衡因子
        const balance = this.getBalance(root);
        
        // 4. 如果不平衡，有4种情况
        
        // 左左情况
        if (balance > 1 && data < root.left!.data) {
            return this.rightRotate(root);
        }
        
        // 右右情况
        if (balance < -1 && data > root.right!.data) {
            return this.leftRotate(root);
        }
        
        // 左右情况
        if (balance > 1 && data > root.left!.data) {
            root.left = this.leftRotate(root.left!);
            return this.rightRotate(root);
        }
        
        // 右左情况
        if (balance < -1 && data < root.right!.data) {
            root.right = this.rightRotate(root.right!);
            return this.leftRotate(root);
        }
        
        return root;
    }
    
    /**
     * 中序遍历
     */
    inOrder(root: AVLNode | null): void {
        if (root !== null) {
            this.inOrder(root.left);
            process.stdout.write(root.data + " ");
            this.inOrder(root.right);
        }
    }
    
    /**
     * 打印平衡因子
     */
    printBalanceFactor(root: AVLNode | null): void {
        if (root !== null) {
            this.printBalanceFactor(root.left);
            console.log(`节点 ${root.data}: 平衡因子 = ${this.getBalance(root)}`);
            this.printBalanceFactor(root.right);
        }
    }
    
    /**
     * 主函数 - 测试AVL树
     */
    main(): void {
        const avl = new AVL();
        let root: AVLNode | null = null;
        
        console.log("=== AVL树测试 ===");
        
        // 插入测试数据
        const testData = [10, 20, 30, 40, 50, 25];
        console.log("插入数据:", testData);
        
        for (const data of testData) {
            root = avl.insert(root, data);
            console.log(`插入 ${data} 后的中序遍历:`);
            avl.inOrder(root);
            console.log();
        }
        
        console.log("最终平衡因子:");
        avl.printBalanceFactor(root);
    }
}

// 运行测试
const avl = new AVL();
avl.main();

/*打印结果
jarry@Mac avl % ts-node AVL.ts
=== AVL树测试 ===
插入数据: [ 10, 20, 30, 40, 50, 25 ]
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
节点 30: 平衡因子 = 0
节点 40: 平衡因子 = -1
节点 50: 平衡因子 = 0
*/
