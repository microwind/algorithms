/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
class BinaryTree {
    constructor() { }
    // 1. 先序优先遍历DLR递归版
    preOrderTraverse(tree, result = []) {
        if (tree !== undefined) {
            result.push(tree.value);
            this.preOrderTraverse(tree.left, result);
            this.preOrderTraverse(tree.right, result);
        }
        return result;
    }
    // 2.	中序优先遍历LDR递归版
    inOrderTraverse(tree, result = []) {
        if (tree !== undefined) {
            this.inOrderTraverse(tree.left, result);
            result.push(tree.value);
            this.inOrderTraverse(tree.right, result);
        }
        return result;
    }
    // 3.	后序优先遍历LRD递归版
    postOrderTraverse(tree, result = []) {
        if (tree !== undefined) {
            this.postOrderTraverse(tree.left, result);
            this.postOrderTraverse(tree.right, result);
            result.push(tree.value);
        }
        return result;
    }
    // 4. 广度优先(层级遍历)，自左往右，利用队列暂存数据
    levelOrder(tree) {
        const result = [];
        const queue = [];
        if (tree !== undefined) {
            queue.push(tree);
            while (queue.length) {
                tree = queue.shift();
                result.push(tree.value);
                // append children of current Node
                if (tree.left !== undefined) {
                    queue.push(tree.left);
                }
                if (tree.right !== undefined) {
                    queue.push(tree.right);
                }
            }
        }
        return result;
    }
    // 5. 深度遍历(先序优先非递归版)
    preOrderUnRecursive(tree) {
        const result = [];
        const queue = [];
        if (tree !== undefined) {
            while (queue.length || tree) {
                if (tree) {
                    result.push(tree.value);
                    queue.push(tree);
                    tree = tree.left;
                }
                else {
                    tree = queue.pop();
                    tree = tree.right;
                }
            }
        }
        return result;
    }
    // 6. 深度遍历(中序优先非递归版)
    inOrderUnRecursive(tree) {
        var result = [];
        var queue = [];
        if (tree !== undefined) {
            while (queue.length || tree) {
                if (tree) {
                    queue.push(tree);
                    tree = tree.left;
                }
                else {
                    tree = queue.pop();
                    result.push(tree.value);
                    tree = tree.right;
                }
            }
        }
        return result;
    }
    // 7. 深度遍历(后序优先非递归版)
    postOrderUnRecursive(tree) {
        const result = [];
        const queue = [];
        var item;
        if (tree !== undefined) {
            queue.push(tree);
            while (queue.length) {
                // 先得到最后一项作为比较项
                item = queue[queue.length - 1];
                // 把左子树按深度全部追加到queue
                if (item.left && tree !== item.left && tree !== item.right) {
                    queue.push(item.left);
                    // 把右子树追加到queue
                }
                else if (item.right && tree !== item.right) {
                    queue.push(item.right);
                }
                else {
                    // 左子树到最底层节点，开始打印left与right
                    result.push(queue.pop().value);
                    //  指向上一个节点，直到queue为空，也就是遍历至根节点
                    tree = item;
                }
            }
        }
        return result;
    }
}
(function () {
    // 基本结构
    class Node {
        constructor(value) {
            this.value = value;
        }
    }
    // 二叉树数据
    const data = `
                 1
            /         \
          2              3
        /   \          /   \
      4      5        6     7
           /   \          /    \
          8     9        10    11
        /   \
      12    13
`;
    console.table(data);
    const tree = new Node(1);
    tree.left = new Node(2);
    tree.right = new Node(3);
    let node2 = tree.left;
    let node3 = tree.right;
    node2.left = new Node(4);
    node2.right = new Node(5);
    node3.left = new Node(6);
    node3.right = new Node(7);
    let node5 = node2.right;
    node5.left = new Node(8);
    node5.right = new Node(9);
    let node7 = node3.right;
    node7.left = new Node(10);
    node7.right = new Node(11);
    let node8 = node5.left;
    node8.left = new Node(12);
    node8.right = new Node(13);
    var result;
    console.time("time");
    const binaryTree = new BinaryTree();
    // 1.
    result = binaryTree.preOrderTraverse(tree);
    console.log('1. preOrderTraverse:', result);
    //  [ 1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11 ]
    // 2.
    result = binaryTree.inOrderTraverse(tree);
    // [ 4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11 ]
    console.log('2. inOrderTraverse:', result);
    // 3.
    result = binaryTree.postOrderTraverse(tree);
    // [ 4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1 ]
    console.log('3. postOrderTraverse:', result);
    // 4. 
    result = binaryTree.levelOrder(tree);
    // [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 ]
    console.log('4. levelOrder:', result);
    // 5.
    result = binaryTree.preOrderUnRecursive(tree);
    // [ 1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11 ]
    console.log('5. preOrderUnRecursive:', result);
    // 6.
    result = binaryTree.inOrderUnRecursive(tree);
    // [ 4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11 ]
    console.log('6. inOrderUnRecursive:', result);
    // 7.
    result = binaryTree.postOrderUnRecursive(tree);
    // [ 4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1 ]
    console.log('7. postOrderUnRecursive:', result);
    console.timeEnd("time");
})();
/**
jarry@192 binarytree % tsc BinaryTree.ts -t es2020
jarry@192 binarytree % node BinaryTree.js
1. preOrderTraverse: [ 1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11 ]
2. inOrderTraverse: [ 4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11 ]
3. postOrderTraverse: [ 4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1 ]
4. levelOrder: [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 ]
5. preOrderUnRecursive: [ 1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11 ]
6. inOrderUnRecursive: [ 4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11 ]
7. postOrderUnRecursive: [ 4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1 ]
time: 2.113ms
 */ 
