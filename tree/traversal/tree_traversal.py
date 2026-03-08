"""
树算法 - 二叉树遍历
实现二叉树的前序、中序、后序遍历（递归和迭代）
"""


class TreeNode:
    """二叉树节点"""
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def preorder_recursive(root):
    """前序遍历 - 递归：根-左-右"""
    result = []
    
    def traverse(node):
        if not node:
            return
        result.append(node.val)  # 访问根
        traverse(node.left)       # 遍历左子树
        traverse(node.right)      # 遍历右子树
    
    traverse(root)
    return result


def inorder_recursive(root):
    """中序遍历 - 递归：左-根-右"""
    result = []
    
    def traverse(node):
        if not node:
            return
        traverse(node.left)       # 遍历左子树
        result.append(node.val)   # 访问根
        traverse(node.right)      # 遍历右子树
    
    traverse(root)
    return result


def postorder_recursive(root):
    """后序遍历 - 递归：左-右-根"""
    result = []
    
    def traverse(node):
        if not node:
            return
        traverse(node.left)       # 遍历左子树
        traverse(node.right)      # 遍历右子树
        result.append(node.val)   # 访问根
    
    traverse(root)
    return result


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("二叉树遍历 (Binary Tree Traversal)")
    print("=" * 50)
    
    # 构建示例树
    #       1
    #      / \
    #     2   3
    #    / \   /
    #   4   5 6
    
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.left.left = TreeNode(4)
    root.left.right = TreeNode(5)
    root.right.left = TreeNode(6)
    
    print("\n树结构:")
    print("      1")
    print("     / \\")
    print("    2   3")
    print("   / \  /")
    print("  4   5 6")
    
    print(f"\n前序遍历 (根-左-右): {preorder_recursive(root)}")
    print(f"中序遍历 (左-根-右): {inorder_recursive(root)}")
    print(f"后序遍历 (左-右-根): {postorder_recursive(root)}")
