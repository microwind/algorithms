"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 二叉树数据结构 - Python实现
"""
# 二叉树节点类
class TreeNode:
    def __init__(self, value):
        self.value = value  # 节点值
        self.left = None    # 左子节点
        self.right = None   # 右子节点

# 前序遍历：根 -> 左 -> 右
def preorder_traversal(root):
    if root is None:
        return
    print(root.value, end=" ")  # 访问根
    preorder_traversal(root.left)   # 遍历左子树
    preorder_traversal(root.right)  # 遍历右子树

# 中序遍历：左 -> 根 -> 右
def inorder_traversal(root):
    if root is None:
        return
    inorder_traversal(root.left)    # 遍历左子树
    print(root.value, end=" ")      # 访问根
    inorder_traversal(root.right)   # 遍历右子树

# 后序遍历：左 -> 右 -> 根
def postorder_traversal(root):
    if root is None:
        return
    postorder_traversal(root.left)  # 遍历左子树
    postorder_traversal(root.right) # 遍历右子树
    print(root.value, end=" ")      # 访问根

# 构建示例二叉树
#        1
#       / \
#      2   3
#     / \   /
#    4   5 6
root = TreeNode(1)
root.left = TreeNode(2)
root.right = TreeNode(3)
root.left.left = TreeNode(4)
root.left.right = TreeNode(5)
root.right.left = TreeNode(6)

# 输出三种遍历结果
print("前序遍历：")
preorder_traversal(root)

print("\n中序遍历：")
inorder_traversal(root)

print("\n后序遍历：")
postorder_traversal(root)

"""
jarry@MacBook-Pro tree % python tree.py 
前序遍历：
1 2 4 5 3 6 
中序遍历：
4 2 5 1 6 3 
后序遍历：
4 5 2 6 3 1
"""