class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

# 前序遍历：根 -> 左 -> 右
def preorder_traversal(root):
    if root is None:
        return
    print(root.value, end=" ")
    preorder_traversal(root.left)
    preorder_traversal(root.right)

# 中序遍历：左 -> 根 -> 右
def inorder_traversal(root):
    if root is None:
        return
    inorder_traversal(root.left)
    print(root.value, end=" ")
    inorder_traversal(root.right)

# 后序遍历：左 -> 右 -> 根
def postorder_traversal(root):
    if root is None:
        return
    postorder_traversal(root.left)
    postorder_traversal(root.right)
    print(root.value, end=" ")

root = TreeNode(1)
root.left = TreeNode(2)
root.right = TreeNode(3)
root.left.left = TreeNode(4)
root.left.right = TreeNode(5)
root.right.left = TreeNode(6)

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