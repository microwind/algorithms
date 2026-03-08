"""
二叉搜索树 (Binary Search Tree - BST)
实现BST的基本操作：插入、删除、查找
"""


class TreeNode:
    """BST节点"""
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None


class BST:
    """二叉搜索树类"""
    
    def __init__(self):
        self.root = None
    
    def insert(self, key):
        """插入节点"""
        if not self.root:
            self.root = TreeNode(key)
        else:
            self._insert_recursive(self.root, key)
    
    def _insert_recursive(self, node, key):
        """递归插入"""
        if key < node.key:
            if node.left is None:
                node.left = TreeNode(key)
            else:
                self._insert_recursive(node.left, key)
        else:
            if node.right is None:
                node.right = TreeNode(key)
            else:
                self._insert_recursive(node.right, key)
    
    def search(self, key):
        """查找节点"""
        return self._search_recursive(self.root, key)
    
    def _search_recursive(self, node, key):
        """递归查找"""
        if node is None or node.key == key:
            return node
        
        if key < node.key:
            return self._search_recursive(node.left, key)
        else:
            return self._search_recursive(node.right, key)
    
    def delete(self, key):
        """删除节点"""
        self.root = self._delete_recursive(self.root, key)
    
    def _delete_recursive(self, node, key):
        """递归删除"""
        if node is None:
            return node
        
        if key < node.key:
            node.left = self._delete_recursive(node.left, key)
        elif key > node.key:
            node.right = self._delete_recursive(node.right, key)
        else:
            # 找到要删除的节点
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            
            # 有两个子节点：找到后继节点
            min_node = self._find_min(node.right)
            node.key = min_node.key
            node.right = self._delete_recursive(node.right, min_node.key)
        
        return node
    
    def _find_min(self, node):
        """找到最小节点"""
        current = node
        while current.left:
            current = current.left
        return current
    
    def inorder(self):
        """中序遍历（返回排序结果）"""
        result = []
        self._inorder_recursive(self.root, result)
        return result
    
    def _inorder_recursive(self, node, result):
        """递归中序遍历"""
        if node:
            self._inorder_recursive(node.left, result)
            result.append(node.key)
            self._inorder_recursive(node.right, result)


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("二叉搜索树 (BST)")
    print("=" * 50)
    
    bst = BST()
    
    # 插入数据
    values = [50, 30, 70, 20, 40, 60, 80]
    print(f"\n插入数据: {values}")
    for val in values:
        bst.insert(val)
    
    print(f"中序遍历（排序结果）: {bst.inorder()}")
    
    # 查找
    search_keys = [40, 100]
    print("\n查找测试:")
    for key in search_keys:
        result = bst.search(key)
        print(f"  查找 {key}: {'找到' if result else '未找到'}")
    
    # 删除
    print("\n删除测试:")
    delete_key = 30
    print(f"  删除 {delete_key}")
    bst.delete(delete_key)
    print(f"  删除后中序遍历: {bst.inorder()}")
    
    print("\nBST特点:")
    print("  • 左子树所有节点 < 根节点 < 右子树所有节点")
    print("  • 查找、插入、删除: 平均O(log n)，最坏O(n)")
    print("  • 中序遍历得到有序序列")
