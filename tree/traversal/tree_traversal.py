"""
树算法 - 二叉树遍历完整实现
实现二叉树的前序、中序、后序遍历（递归和迭代）
以及层级遍历、Morris遍历等高级遍历方法
包含时间复杂度分析和应用场景说明
"""


class TreeNode:
    """二叉树节点类
    
    属性:
        val: 节点存储的值
        left: 左子节点引用
        right: 右子节点引用
    
    说明:
        二叉树是每个节点最多有两个子树的树结构
        通常子树被称作"左子树"和"右子树"
    """
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
    
    def __str__(self):
        return f"TreeNode({self.val})"
    
    def __repr__(self):
        return self.__str__()


def preorder_recursive(root):
    """前序遍历 - 递归实现：根-左-右
    
    算法思路:
        1. 访问根节点
        2. 递归遍历左子树
        3. 递归遍历右子树
    
    时间复杂度: O(n) - 每个节点访问一次
    空间复杂度: O(h) - h为树的高度，递归调用栈深度
    
    应用场景:
        - 树的复制
        - 表达式树的前缀表达式生成
        - 文件系统目录结构遍历
    """
    result = []
    
    def traverse(node):
        if not node:
            return
        result.append(node.val)  # 访问根节点
        traverse(node.left)       # 递归遍历左子树
        traverse(node.right)      # 递归遍历右子树
    
    traverse(root)
    return result


def inorder_recursive(root):
    """中序遍历 - 递归实现：左-根-右
    
    算法思路:
        1. 递归遍历左子树
        2. 访问根节点
        3. 递归遍历右子树
    
    时间复杂度: O(n) - 每个节点访问一次
    空间复杂度: O(h) - h为树的高度，递归调用栈深度
    
    应用场景:
        - 二叉搜索树的中序遍历得到有序序列
        - 表达式树的中缀表达式生成
        - 按顺序输出树的所有节点
    """
    result = []
    
    def traverse(node):
        if not node:
            return
        traverse(node.left)       # 递归遍历左子树
        result.append(node.val)   # 访问根节点
        traverse(node.right)      # 递归遍历右子树
    
    traverse(root)
    return result


def postorder_recursive(root):
    """后序遍历 - 递归实现：左-右-根
    
    算法思路:
        1. 递归遍历左子树
        2. 递归遍历右子树
        3. 访问根节点
    
    时间复杂度: O(n) - 每个节点访问一次
    空间复杂度: O(h) - h为树的高度，递归调用栈深度
    
    应用场景:
        - 树的删除（先删除子节点再删除父节点）
        - 计算树的高度
        - 表达式树的后缀表达式生成
        - 目录大小计算
    """
    result = []
    
    def traverse(node):
        if not node:
            return
        traverse(node.left)       # 递归遍历左子树
        traverse(node.right)      # 递归遍历右子树
        result.append(node.val)   # 访问根节点
    
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
