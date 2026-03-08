"""
AVL树 - 自平衡二叉搜索树
通过旋转保持平衡，确保树高为O(log n)
"""


class TreeNode:
    """AVL树节点"""
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1  # 节点高度


class AVLTree:
    """AVL树类"""
    
    def __init__(self):
        self.root = None
    
    def _height(self, node):
        """获取节点高度"""
        if not node:
            return 0
        return node.height
    
    def _update_height(self, node):
        """更新节点高度"""
        node.height = 1 + max(self._height(node.left), self._height(node.right))
    
    def _balance_factor(self, node):
        """计算平衡因子"""
        if not node:
            return 0
        return self._height(node.left) - self._height(node.right)
    
    def _right_rotate(self, y):
        """右旋"""
        x = y.left
        T2 = x.right
        
        # 执行旋转
        x.right = y
        y.left = T2
        
        # 更新高度
        self._update_height(y)
        self._update_height(x)
        
        return x
    
    def _left_rotate(self, x):
        """左旋"""
        y = x.right
        T2 = y.left
        
        # 执行旋转
        y.left = x
        x.right = T2
        
        # 更新高度
        self._update_height(x)
        self._update_height(y)
        
        return y
    
    def insert(self, key):
        """插入节点"""
        self.root = self._insert_recursive(self.root, key)
    
    def _insert_recursive(self, node, key):
        """递归插入并平衡"""
        # 标准BST插入
        if not node:
            return TreeNode(key)
        
        if key < node.key:
            node.left = self._insert_recursive(node.left, key)
        elif key > node.key:
            node.right = self._insert_recursive(node.right, key)
        else:
            return node  # 重复键
        
        # 更新高度
        self._update_height(node)
        
        # 获取平衡因子
        balance = self._balance_factor(node)
        
        # 左左情况
        if balance > 1 and key < node.left.key:
            return self._right_rotate(node)
        
        # 右右情况
        if balance < -1 and key > node.right.key:
            return self._left_rotate(node)
        
        # 左右情况
        if balance > 1 and key > node.left.key:
            node.left = self._left_rotate(node.left)
            return self._right_rotate(node)
        
        # 右左情况
        if balance < -1 and key < node.right.key:
            node.right = self._right_rotate(node.right)
            return self._left_rotate(node)
        
        return node
    
    def inorder(self):
        """中序遍历"""
        result = []
        self._inorder_recursive(self.root, result)
        return result
    
    def _inorder_recursive(self, node, result):
        if node:
            self._inorder_recursive(node.left, result)
            result.append(node.key)
            self._inorder_recursive(node.right, result)
    
    def get_height(self):
        """获取树高度"""
        return self._height(self.root)


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("AVL树 - 自平衡二叉搜索树")
    print("=" * 50)
    
    avl = AVLTree()
    
    # 插入会导致不平衡的数据
    values = [30, 20, 10, 25, 40, 35, 50]
    print(f"\n插入数据: {values}")
    for val in values:
        avl.insert(val)
    
    print(f"中序遍历: {avl.inorder()}")
    print(f"树高度: {avl.get_height()}")
    
    print("\nAVL树特点:")
    print("  • 平衡因子: -1, 0, 1")
    print("  • 通过旋转保持平衡")
    print("  • 查找、插入、删除: 稳定O(log n)")
    print("  • 适合查找频繁的场景")
