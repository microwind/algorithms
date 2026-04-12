"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 满二叉树数据结构 - Python实现
"""

# 树节点类
class TreeNode:
    def __init__(self, value):
        self.left = None
        self.right = None
        self.parent = None
        self.next = None
        self.value = value

# 按 idx 作为根节点的"占位"值，buildHeight 为层数构造满二叉树，并设置 parent 指针
def build_full_tree(idx, height):
    if height <= 0:
        return None
    node = TreeNode(idx)
    node.left = build_full_tree(idx * 2, height - 1)
    if node.left is not None:
        node.left.parent = node
    node.right = build_full_tree(idx * 2 + 1, height - 1)
    if node.right is not None:
        node.right.parent = node
    return node

# 先序遍历（根→左→右）
def print_pre_order(node):
    if node is None:
        return
    print("value:", node.value)
    print_pre_order(node.left)
    print_pre_order(node.right)

# 广度优先遍历（BFS）打印
def print_bfs(root):
    if root is None:
        return
    queue = [root]
    for i in range(len(queue)):
        n = queue[i]
        print(n.value, end=" ")
        if n.left is not None:
            queue.append(n.left)
        if n.right is not None:
            queue.append(n.right)
    print()

# 找到当前节点所在树的根
def find_root(node):
    while node.parent is not None:
        node = node.parent
    return node

# 无额外空间遍历单棵树（含 parent 指针），中序风格打印
def traverse_tree(root):
    prev = None
    current = root
    while current is not None:
        if prev == current.parent:
            # 从 parent 下来：优先下探左子
            if current.left is not None:
                next_node = current.left
            else:
                # 否则中序访问自己
                print(current.value, end=" ")
                next_node = current.right if current.right is not None else current.parent
        elif prev == current.left:
            # 从左子回到 current：中序访问自己
            print(current.value, end=" ")
            next_node = current.right if current.right is not None else current.parent
        else:
            # 从右子回到 current：回父节点
            next_node = current.parent
        prev = current
        current = next_node

# 从任意节点开始遍历串联在一起的多棵树
def traverse_from_any_node(any_node):
    root = find_root(any_node)
    while root is not None:
        traverse_tree(root)
        root = root.next
    print()

# 对单棵树按层序（BFS）重新赋连续值
def assign_level_order_values(root, start_val):
    queue = [root]
    val = start_val
    while len(queue) > 0:
        n = queue.pop(0)
        n.value = val
        val += 1
        if n.left is not None:
            queue.append(n.left)
        if n.right is not None:
            queue.append(n.right)
    return val

def main():
    height = 4

    # 1) 构造形状（value暂时无意义）
    T1 = build_full_tree(1, height)
    T2 = build_full_tree(1, height)
    T3 = build_full_tree(1, height)

    # 2) 按层序给每棵树分别连续编号：T1 → 1..15, T2 → 16..30, T3 → 31..45
    next_id = assign_level_order_values(T1, 1)
    next_id = assign_level_order_values(T2, next_id)
    assign_level_order_values(T3, next_id)

    # 3) 串联根：T1 → T2 → T3
    T1.next = T2
    T2.next = T3
    T3.next = None

    print("=== 先序遍历 T1 ===")
    print_pre_order(T1)

    print("\n=== 广度优先遍历 T1 ===")
    print_bfs(T1)

    # 4) 从任意节点遍历
    print("\n=== 从任意节点遍历 ===")
    traverse_from_any_node(T3.left)

    # 5) 从 T2 的某个子节点开始，无额外空间遍历整片"森林"
    any_node = T2.left.left
    print("\n=== 从节点", any_node.value, "开始无栈遍历 ===")
    traverse_from_any_node(any_node)

if __name__ == "__main__":
    main()
