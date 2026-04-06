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
    constructor(data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

/**
 * 创建新节点
 * @param {number} data 节点数据
 * @return {Node} 新节点
 */
function newNode(data) {
    return new Node(data);
}

/**
 * 前序遍历
 * 时间复杂度: O(n)，空间复杂度: O(h)
 * @param {Node} node 根节点
 */
function preOrder(node) {
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
 * 主函数 - 测试二叉树遍历
 */
function main() {
    // 测试1：创建二叉树
    const root = newNode(1);
    root.left = newNode(2);
    root.right = newNode(3);
    root.left.left = newNode(4);
    root.left.right = newNode(5);
    
    // 输出调用过程示例
    console.log("调用过程示例：");
    console.log("preOrder(root)");
    console.log("   |");
    console.log("   v");
    console.log("printf(1)");
    console.log("preOrder(root.left)");
    console.log("   |");
    console.log("   v");
    console.log("printf(2)");
    console.log("preOrder(root.left.left)");
    console.log("   |");
    console.log("   v");
    console.log("printf(4)");
    console.log("preOrder(root.left.right)");
    console.log("   |");
    console.log("   v");
    console.log("printf(5)");
    console.log("preOrder(root.right)");
    console.log("   |");
    console.log("   v");
    console.log("printf(3)");
    console.log();
    
    // 测试2：执行前序遍历
    console.log("Preorder traversal of binary tree is");
    preOrder(root);
    console.log();
}

/*打印结果
jarry@Mac tree-recursion % node tree.js
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

// 运行主函数
main();
