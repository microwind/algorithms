/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 1. 先序优先遍历DLR递归版
function preOrderTraverse(tree, result) {
  result = result ? result : []
  if (tree !== undefined) {
    result.push(tree.value)
    preOrderTraverse(tree.left, result)
    preOrderTraverse(tree.right, result)
  }
  return result
}

// 2.	中序优先遍历LDR递归版
function inOrderTraverse(tree, result) {
  result = result ? result : []
  if (tree !== undefined) {
    inOrderTraverse(tree.left, result)
    result.push(tree.value)
    inOrderTraverse(tree.right, result)
  }
  return result
}

// 3.	后序优先遍历LRD递归版
function postOrderTraverse(tree, result) {
  result = result ? result : []
  if (tree !== undefined) {
    postOrderTraverse(tree.left, result)
    postOrderTraverse(tree.right, result)
    result.push(tree.value)
  }
  return result
}

// 4. 广度优先(层级遍历)，自左往右，利用队列暂存数据
function levelOrder(tree) {
  const result = []
  const queue = []
  if (tree !== undefined) {
    queue.push(tree)
    while (queue.length) {
      tree = queue.shift()
      result.push(tree.value)
      // append children of current Node
      if (tree.left !== undefined) {
        queue.push(tree.left)
      }
      if (tree.right !== undefined) {
        queue.push(tree.right)
      }
    }
  }
  return result
}

// 5. 深度遍历(先序优先非递归版)
function preOrderUnRecursive(tree) {
  const result = []
  const queue = []
  if (tree !== undefined) {
    while (queue.length || tree) {
      if (tree) {
        result.push(tree.value)
        queue.push(tree)
        tree = tree.left
      } else {
        tree = queue.pop()
        tree = tree.right
      }
    }
  }
  return result
}

// 6. 深度遍历(中序优先非递归版)
function inOrderUnRecursive(tree) {
  var result = []
  var queue = []
  if (tree !== undefined) {
    while (queue.length || tree) {
      if (tree) {
        queue.push(tree)
        tree = tree.left
      } else {
        tree = queue.pop()
        result.push(tree.value)
        tree = tree.right
      }
    }
  }
  return result
}

// 7. 深度遍历(后序优先非递归版)
function postOrderUnRecursive(tree) {
  const result = []
  const queue = []
  var tmp
  if (tree !== undefined) {
    queue.push(tree)
    while (queue.length) {
      // 先得到最后一项作为比较项
      tmp = queue[queue.length - 1]
      // 把左子树按深度全部追加到queue
      if (tmp.left && tree !== tmp.left && tree !== tmp.right) {
        queue.push(tmp.left)
        // 把右子树追加到queue
      } else if (tmp.right && tree !== tmp.right) {
        queue.push(tmp.right)
      } else {
        // 左子树到最底层节点，开始打印left与right
        result.push(queue.pop().value)
        //  指向上一个节点，直到queue为空，也就是遍历至根节点
        tree = tmp
      }
    }
  }
  return result
}

/* === test === */

// 二叉树数据
const data = `
         1
      /      \
    2          3
  /   \      /    \
 4     5    6      7
      /  \
     8    9
`
console.log(data)
const tree = {
  value: 1,
  left: {
    value: 2,
    left: {
      value: 4
    },
    right: {
      value: 5,
      left: {
        value: 8
      },
      right: {
        value: 9
      }
    }
  },
  right: {
    value: 3,
    left: {
      value: 6
    },
    right: {
      value: 7
    }
  }
}
console.log(tree)

var result = []

// 1. 先序优先遍历 DLR
result = preOrderTraverse(tree)
//  [1, 2, 4, 5, 8, 9, 3, 6, 7]
console.log('1. preOrderTraverse:', result)

// 2. 中序优先遍历 LDR
result = inOrderTraverse(tree)
// [4, 2, 8, 5, 9, 1, 6, 3, 7]
console.log('2. inOrderTraverse:', result)

// 3. 后序优先遍历 LRD
result = postOrderTraverse(tree)
//  [4, 8, 9, 5, 2, 6, 7, 3, 1]
console.log('3. postOrderTraverse:', result)

// 4. 广度优先遍历
result = levelOrder(tree)
// [1, 2, 3, 4, 5, 6, 7, 8, 9]
console.log('4. levelOrder:', result)

// 5. 深度遍历（先序非递归）
result = preOrderUnRecursive(tree)
// [1, 2, 4, 5, 8, 9, 3, 6, 7]
console.log('5. preOrderUnRecursive:', result)

// 6. 深度遍历（中序非递归）
result = inOrderUnRecursive(tree)
// [4, 2, 8, 5, 9, 1, 6, 3, 7]
console.log('6. inOrderUnRecursive:', result)

// 7. 深度遍历（后序非递归）
result = postOrderUnRecursive(tree)
// [4, 8, 9, 5, 2, 6, 7, 3, 1]
console.log('7. postOrderUnRecursive:', result)

/**
jarry@jarrys-MacBook-Pro binarytree % node binary_tree.js

         1
      /         2         3
  /         /     4     5    6      7
      /       8    9

{ value: 1,
  left:
   { value: 2,
     left: { value: 4 },
     right: { value: 5, left: [Object], right: [Object] } },
  right: { value: 3, left: { value: 6 }, right: { value: 7 } } }
preOrderTraverse: [ 1, 2, 4, 5, 8, 9, 3, 6, 7 ]
inOrderTraverse: [ 4, 2, 8, 5, 9, 1, 6, 3, 7 ]
postOrderTraverse: [ 4, 8, 9, 5, 2, 6, 7, 3, 1 ]
levelOrder: [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
preOrderUnRecursive: [ 1, 2, 4, 5, 8, 9, 3, 6, 7 ]
inOrderUnRecursive: [ 4, 2, 8, 5, 9, 1, 6, 3, 7 ]
postOrderUnRecursive: [ 4, 8, 9, 5, 2, 6, 7, 3, 1 ]
 */