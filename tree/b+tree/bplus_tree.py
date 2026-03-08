"""
B+树 - 多路搜索树实现
支持高效的范围查询和磁盘存储
"""


class BPlusTreeNode:
    """B+树节点"""
    def __init__(self, is_leaf=True):
        self.is_leaf = is_leaf
        self.keys = []
        self.children = []
        self.next = None  # 叶节点链表指针


class BPlusTree:
    """B+树实现 (阶数为3的简单版本)"""
    
    def __init__(self, order=3):
        self.order = order
        self.root = BPlusTreeNode()
        self.root.is_leaf = True
    
    def insert(self, key):
        """插入键值"""
        root = self.root
        
        if len(root.keys) == (2 * self.order) - 1:
            new_root = BPlusTreeNode(is_leaf=False)
            new_root.children.append(self.root)
            self._split_child(new_root, 0)
            self.root = new_root
        
        self._insert_non_full(self.root, key)
    
    def _insert_non_full(self, node, key):
        """在非满节点中插入"""
        if node.is_leaf:
            # 叶节点直接插入
            i = len(node.keys) - 1
            node.keys.append(None)
            while i >= 0 and key < node.keys[i]:
                node.keys[i + 1] = node.keys[i]
                i -= 1
            node.keys[i + 1] = key
        else:
            # 内部节点，找到合适的子节点
            i = len(node.keys) - 1
            while i >= 0 and key < node.keys[i]:
                i -= 1
            i += 1
            
            if len(node.children[i].keys) == (2 * self.order) - 1:
                self._split_child(node, i)
                if key > node.keys[i]:
                    i += 1
            
            self._insert_non_full(node.children[i], key)
    
    def _split_child(self, parent, i):
        """分裂子节点"""
        order = self.order
        child = parent.children[i]
        new_child = BPlusTreeNode(is_leaf=child.is_leaf)
        
        # 将child的后半部分移到new_child
        mid = order - 1
        new_child.keys = child.keys[mid + 1:]
        child.keys = child.keys[:mid]
        
        if not child.is_leaf:
            new_child.children = child.children[mid + 1:]
            child.children = child.children[:mid + 1]
        else:
            new_child.next = child.next
            child.next = new_child
        
        # 在parent中插入中间键
        parent.keys.insert(i, child.keys[mid])
        parent.children.insert(i + 1, new_child)
    
    def search(self, key):
        """搜索键值"""
        return self._search_node(self.root, key)
    
    def _search_node(self, node, key):
        """递归搜索节点"""
        i = 0
        while i < len(node.keys) and key > node.keys[i]:
            i += 1
        
        if i < len(node.keys) and key == node.keys[i]:
            return True
        
        if node.is_leaf:
            return False
        
        return self._search_node(node.children[i], key)
    
    def range_query(self, start, end):
        """范围查询"""
        result = []
        leaf = self._find_leaf(self.root, start)
        
        while leaf:
            for key in leaf.keys:
                if start <= key <= end:
                    result.append(key)
                elif key > end:
                    return result
            leaf = leaf.next
        
        return result
    
    def _find_leaf(self, node, key):
        """找到应该包含key的叶节点"""
        if node.is_leaf:
            return node
        
        i = 0
        while i < len(node.keys) and key > node.keys[i]:
            i += 1
        
        return self._find_leaf(node.children[i], key)
    
    def traverse(self):
        """遍历所有键（中序遍历）"""
        result = []
        self._traverse_node(self.root, result)
        return result
    
    def _traverse_node(self, node, result):
        """递归遍历节点"""
        if node.is_leaf:
            result.extend(node.keys)
        else:
            for i in range(len(node.keys)):
                self._traverse_node(node.children[i], result)
                result.append(node.keys[i])
            self._traverse_node(node.children[-1], result)


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("B+树实现 (B+ Tree)")
    print("=" * 50)
    
    bpt = BPlusTree(order=3)
    
    # 插入数据
    values = [10, 20, 5, 6, 12, 30, 7, 17]
    print(f"\n插入数据: {values}")
    for val in values:
        bpt.insert(val)
    
    print(f"中序遍历结果: {bpt.traverse()}")
    
    # 搜索测试
    print("\n搜索测试:")
    for key in [6, 15, 30]:
        result = "找到" if bpt.search(key) else "未找到"
        print(f"  查找 {key}: {result}")
    
    # 范围查询
    print("\n范围查询 [10, 20]:")
    result = bpt.range_query(10, 20)
    print(f"  结果: {result}")
    
    print("\nB+树特点:")
    print("  • 所有数据存储在叶节点")
    print("  • 叶节点形成有序链表")
    print("  • 适合磁盘存储和范围查询")
    print("  • 查找、插入、删除: O(log n)")
    print("  • 应用于数据库索引、文件系统")
