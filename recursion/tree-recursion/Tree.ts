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

// 声明 Node.js process 对象
declare const process: any;

// 定义二叉树节点
class TreeNode {
    data: number;
    left: TreeNode | null;
    right: TreeNode | null;
    
    constructor(data: number) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

/**
 * 创建新节点
 * @param data 节点数据
 * @return 新节点
 */
function newNode(data: number): TreeNode {
    return new TreeNode(data);
}

/**
 * 前序遍历
 * 时间复杂度: O(n)，空间复杂度: O(h)
 * @param node 根节点
 */
function preOrder(node: TreeNode | null): void {
    // 基本情况：空节点
    if (node === null) return;
    
    // 访问根节点
    process.stdout.write(node.data + " ");
    
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
function inOrder(node: TreeNode | null): void {
    // 基本情况：空节点
    if (node === null) return;
    
    // 递归遍历左子树
    inOrder(node.left);
    
    // 访问根节点
    process.stdout.write(node.data + " ");
    
    // 递归遍历右子树
    inOrder(node.right);
}

/**
 * 后序遍历
 * 时间复杂度: O(n)，空间复杂度: O(h)
 * @param node 根节点
 */
function postOrder(node: TreeNode | null): void {
    // 基本情况：空节点
    if (node === null) return;
    
    // 递归遍历左子树
    postOrder(node.left);
    
    // 递归遍历右子树
    postOrder(node.right);
    
    // 访问根节点
    process.stdout.write(node.data + " ");
}

/**
 * 主函数 - 测试二叉树遍历
 */
function main(): void {
    // 测试1：创建二叉树
    const root = newNode(1);
    root.left = newNode(2);
    root.right = newNode(3);
    root.left.left = newNode(4);
    root.left.right = newNode(5);
    
    // 测试2：前序遍历
    console.log("1. 前序遍历:");
    process.stdout.write("   遍历结果: ");
    preOrder(root);
    console.log();
    console.log("===");
    
    // 测试3：中序遍历
    console.log("2. 中序遍历:");
    process.stdout.write("   遍历结果: ");
    inOrder(root);
    console.log();
    console.log("===");
    
    // 测试4：后序遍历
    console.log("3. 后序遍历:");
    process.stdout.write("   遍历结果: ");
    postOrder(root);
    console.log();
    console.log("===");
}

/*打印结果
jarry@Mac tree-recursion % npx ts-node Tree.ts
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

// 运行主函数
main();
