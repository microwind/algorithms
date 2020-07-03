#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time
import json

class BinaryTree:
    # 1. 先序优先遍历DLR递归版
    def preOrderTraverse(self, tree, result=[]):
        if tree is not None:
            result.append(tree.value)
            self.preOrderTraverse(tree.left, result)
            self.preOrderTraverse(tree.right, result)
        return result

    # 2. 中序优先遍历LDR递归版
    def inOrderTraverse(self, tree, result=[]):
        if tree is not None:
            self.inOrderTraverse(tree.left, result)
            result.append(tree.value)
            self.inOrderTraverse(tree.right, result)
        return result

    # 3. 后序优先遍历LRD递归版
    def postOrderTraverse(self, tree, result=[]):
        if tree is not None:
            self.postOrderTraverse(tree.left, result)
            self.postOrderTraverse(tree.right, result)
            result.append(tree.value)
        return result

    # 4. 广度优先(层级遍历)，自左往右，利用队列暂存数据
    def levelOrder(self, tree):
        result = []
        queue = []

        if (tree is not None):
            queue.append(tree)
            while (len(queue) > 0):
                tree = queue.pop(0)
                result.append(tree.value)
                # append children of current Node
                if tree.left is not None:
                    queue.append(tree.left)
                if tree.right is not None:
                    queue.append(tree.right)
        return result

    # 5. 深度遍历(先序优先非递归版)
    def preOrderUnRecursive(self, tree):
        result = []
        stack = []
        if tree is not None:
            while (len(stack) > 0 or tree is not None):
                if tree is not None:
                    result.append(tree.value)
                    stack.append(tree)
                    tree = tree.left
                else:
                    tree = stack.pop()
                    tree = tree.right
        return result

    # 6. 深度遍历(中序优先非递归版)
    def inOrderUnRecursive(self, tree):
        result = []
        stack = []
        if (tree is not None):
            while (len(stack) > 0 or tree is not None):
                if tree is not None:
                    stack.append(tree)
                    tree = tree.left
                else:
                    tree = stack.pop()
                    result.append(tree.value)
                    tree = tree.right
        return result

    # 7. 深度遍历(后序优先非递归版)
    def postOrderUnRecursive(self, tree):
      result = []
      queue = []
      tmp = None
      if (tree is not None):
        queue.append(tree)
        while len(queue) > 0:
          # 先得到最后一项作为比较项
          tmp = queue[len(queue) - 1]
          # 把左子树按深度全部追加到queue
          if (tmp.left is not None and tree != tmp.left and tree != tmp.right):
            queue.append(tmp.left)
            # 把右子树追加到queue
          elif (tmp.right and tree != tmp.right):
            queue.append(tmp.right)
          else:
            # 左子树到最底层节点，开始打印left与right
            result.append(queue.pop().value)
            #  指向上一个节点，直到queue为空，也就是遍历至根节点
            tree = tmp
      return result

# test
class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right
    def __str__(self):
        return "value: %s" % (self.value)


"""
data = 
                 1
            /         \
          2              3
        /   \          /   \
      4      5        6     7
           /   \          /    \
          8     9        10    11
        /   \
      12    13
"""
tree = Node(1)
tree.left = Node(2)
tree.right = Node(3)
node2 = tree.left
node3 = tree.right
node2.left = Node(4)
node2.right = Node(5)
node3.left = Node(6)
node3.right = Node(7)
node5 = node2.right
node5.left = Node(8)
node5.right = Node(9)
node7 = node3.right
node7.left = Node(10)
node7.right = Node(11)
node8 = node5.left
node8.left = Node(12)
node8.right = Node(13)
start_time = time.time()
# print origin
# print('origin tree:', json.dumps(tree.__dict__))
print('origin tree:', tree)
# start
binaryTree = BinaryTree()

# 1.
result = binaryTree.preOrderTraverse(tree)
print('1. preOrderTraverse:', result)
#  [1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11]

# 2.
result = binaryTree.inOrderTraverse(tree)
print('2. inOrderTraverse:', result)
# 4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11]

# 3.
result = binaryTree.postOrderTraverse(tree)
# [4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1]
print('3. postOrderTraverse:', result)

# 4.
result = binaryTree.levelOrder(tree)
# [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
print('4. levelOrder:', result)

# 5.
result = binaryTree.preOrderUnRecursive(tree)
# [1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11]
print('5. preOrderUnRecursive:', result)

# 6.
result = binaryTree.inOrderUnRecursive(tree)
# 4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11]
print('6. inOrderUnRecursive:', result)

# 7.
result = binaryTree.postOrderUnRecursive(tree)
# [4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1]
print('7. postOrderUnRecursive:', result)

print("time:" + str((time.time() - start_time) * 1000) + " ms")

"""
('1. preOrderTraverse:', [1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11])
('2. inOrderTraverse:', [4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11])
('3. postOrderTraverse:', [4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1])
('4. levelOrder:', [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13])
('5. preOrderUnRecursive:', [1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11])
('6. inOrderUnRecursive:', [4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11])
('7. postOrderUnRecursive:', [4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1])
time:0.270128250122 ms
"""