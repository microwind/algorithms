# Copyright © https://github.com/microwind All rights reserved.
# @author: jarryli@gmail.com
# @version: 1.0

"""
树递归算法示例 - 二叉树遍历

算法特点：
- 二叉树的遍历是递归的典型应用
- 包含前序、中序、后序遍历
- 时间复杂度: O(n)，空间复杂度: O(h)

学习重点：理解递归在树结构中的应用
"""

# 定义二叉树节点
class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

def new_node(data):
    """
    创建新节点
    @param data 节点数据
    @return 新节点
    """
    return Node(data)

def pre_order(node):
    """
    前序遍历
    时间复杂度: O(n)，空间复杂度: O(h)
    @param node 根节点
    """
    # 基本情况：空节点
    if node is None:
        return
    
    # 访问根节点
    print(node.data, end=" ")
    
    # 递归遍历左子树
    pre_order(node.left)
    
    # 递归遍历右子树
    pre_order(node.right)

def in_order(node):
    """
    中序遍历
    时间复杂度: O(n)，空间复杂度: O(h)
    @param node 根节点
    """
    # 基本情况：空节点
    if node is None:
        return
    
    # 递归遍历左子树
    in_order(node.left)
    
    # 访问根节点
    print(node.data, end=" ")
    
    # 递归遍历右子树
    in_order(node.right)

def post_order(node):
    """
    后序遍历
    时间复杂度: O(n)，空间复杂度: O(h)
    @param node 根节点
    """
    # 基本情况：空节点
    if node is None:
        return
    
    # 递归遍历左子树
    post_order(node.left)
    
    # 递归遍历右子树
    post_order(node.right)
    
    # 访问根节点
    print(node.data, end=" ")

# 主函数 - 测试二叉树遍历
def main():
    # 测试1：创建二叉树
    root = new_node(1)
    root.left = new_node(2)
    root.right = new_node(3)
    root.left.left = new_node(4)
    root.left.right = new_node(5)
    
    # 测试2：前序遍历
    print("1. 前序遍历:")
    print("   遍历结果:", end=" ")
    pre_order(root)
    print()
    print("===")
    
    # 测试3：中序遍历
    print("2. 中序遍历:")
    print("   遍历结果:", end=" ")
    in_order(root)
    print()
    print("===")
    
    # 测试4：后序遍历
    print("3. 后序遍历:")
    print("   遍历结果:", end=" ")
    post_order(root)
    print()
    print("===")

# 打印结果
"""
jarry@Mac tree-recursion % python tree.py
1. 前序遍历:
   遍历结果: 1 2 4 5 3 
===
2. 中序遍历:
   遍历结果: 4 2 5 1 3 
===
3. 后序遍历:
   遍历结果: 4 5 2 3 1 
===
"""

if __name__ == "__main__":
    main()
