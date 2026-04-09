"""
版权所有 © https://github.com/microwind 保留所有权利
@author: jarryli@gmail.com
@version: 1.0

树搜索算法 - 矩阵节点路径查找
实现BFS和DFS用于二维矩阵中的最短路径查找
用于路径查找、迷宫求解、图遍历等
支持4方向移动和多条最短路径
"""

from collections import deque
from typing import List, Optional, Set


class MatrixNode:
    """具有4方向连接的矩阵节点"""
    
    def __init__(self, data: int):
        self.data = data  # 节点存储的数据
        self.up: Optional['MatrixNode'] = None    # 上方节点连接
        self.down: Optional['MatrixNode'] = None  # 下方节点连接
        self.left: Optional['MatrixNode'] = None  # 左侧节点连接
        self.right: Optional['MatrixNode'] = None # 右侧节点连接
    
    def __repr__(self):
        return f"MatrixNode({self.data})" # 节点字符串表示


class MatrixSearch:
    """矩阵搜索类，实现BFS和DFS路径查找"""
    
    def __init__(self):
        self.head: Optional[MatrixNode] = None  # 矩阵头节点
    
    def create_matrix(self, n: int) -> MatrixNode:
        """
        创建n x n的互连矩阵节点
        
        算法:
        1. 创建n x n的节点矩阵
        2. 用顺序数据初始化每个节点
        3. 建立水平连接（左右）
        4. 建立垂直连接（上下）
        
        时间复杂度: O(n²) - 处理n²个节点
        空间复杂度: O(n²) - 存储n²个节点
        
        @param n 矩阵维度 (n x n)
        @return 头节点（左上角）
        """
        matrix = [[None for _ in range(n)] for _ in range(n)]
        
        # 初始化n x n节点矩阵
        for i in range(n):
            for j in range(n):
                matrix[i][j] = MatrixNode(i * n + j + 1)
        
        # 连接左右（水平连接）
        for i in range(n):
            for j in range(n - 1):
                matrix[i][j + 1].left = matrix[i][j]   # 设置左连接
                matrix[i][j].right = matrix[i][j + 1] # 设置右连接

        # 连接上下
        for i in range(n - 1):
            for j in range(n):
                matrix[i + 1][j].up = matrix[i][j]   # 设置上连接
                matrix[i][j].down = matrix[i + 1][j] # 设置下连接

        self.head = matrix[0][0]  # 设置头节点（左上角）
        return self.head
    
    def print_matrix(self, n: int) -> None:
        """
        从头节点开始打印矩阵
        
        算法:
        1. 从头节点开始逐行遍历
        2. 使用down指针移动到下一行
        3. 使用right指针在每行内遍历
        4. 打印每个节点的数据值
        
        @param n 矩阵维度
        """
        if not self.head:
            print("矩阵未创建")
            return
            
        current_row = self.head
        
        for i in range(n):
            current = current_row
            for j in range(n):
                print(f"{current.data} ", end="")
                current = current.right
            print()
            current_row = current_row.down
    
    def find_shortest_paths_bfs(self, start: MatrixNode, end: MatrixNode) -> List[List[MatrixNode]]:
        """
        使用BFS查找最短路径
        
        算法:
        1. 使用队列进行层序遍历
        2. 跟踪最短路径长度
        3. 探索所有最小长度路径
        4. 使用路径跟踪避免循环
        
        时间复杂度: O(V + E) - V=顶点数, E=边数
        空间复杂度: O(V) - 用于队列和路径存储
        
        @param start 起始节点
        @param end 目标节点
        @return 最短路径数组
        """
        queue = deque([[start]])
        paths: List[List[MatrixNode]] = []
        shortest_length = -1
        
        while queue:
            current_path = queue.popleft()
            current = current_path[-1]
            
            # 检查是否到达目标
            if current == end:
                if shortest_length == -1 or len(current_path) < shortest_length:
                    shortest_length = len(current_path)
                    paths = [current_path]
                elif len(current_path) == shortest_length:
                    paths.append(current_path)
                continue
            
            # 如果已找到最短路径且当前路径更长，跳过
            if shortest_length != -1 and len(current_path) >= shortest_length:
                continue
            
            # 探索邻居节点
            neighbors = [current.left, current.up, current.down, current.right]
            
            for neighbor in neighbors:
                if neighbor and neighbor not in current_path:
                    new_path = current_path + [neighbor]
                    queue.append(new_path)
        
        return paths
    
    def print_paths(self, paths: List[List[MatrixNode]]) -> None:
        """
        打印所有找到的路径
        
        @param paths 路径数组
        """
        if not paths:
            print("未找到路径")
            return
        
        print(f"最短路径（长度 {len(paths[0])}）:")
        for i, path in enumerate(paths):
            print(f"  路径 {i + 1}: ", end="")
            for j, node in enumerate(path):
                print(f"{node.data}", end="")
                if j < len(path) - 1:
                    print(" -> ", end="")
            print()
    
    def print_separator(self) -> None:
        """打印分隔线"""
        print("=" * 60)


def main():
    """主测试函数"""
    
    # 测试用例:
    # 1. 创建3x3矩阵网络
    # 2. 演示矩阵结构
    # 3. 使用BFS查找最短路径
    # 4. 比较算法特性
    
    n = 3
    search = MatrixSearch()
    head = search.create_matrix(n)
    
    search.print_separator()
    print("树搜索算法 - 矩阵节点路径查找")
    search.print_separator()
    print()
    
    print(f"矩阵结构 ({n}x{n}):")
    search.print_matrix(n)
    print()
    
    # 查找特定节点用于演示
    node2 = head.right  # 值为2的节点
    node9 = head        # 从头节点开始
    # 导航到节点9（右下角）
    for _ in range(n - 1):
        node9 = node9.down
    for _ in range(n - 1):
        node9 = node9.right
    
    if node2 and node9:
        # BFS搜索
        print(f"从 {node2.data} 到 {node9.data} 的BFS最短路径:")
        bfs_paths = search.find_shortest_paths_bfs(node2, node9)
        search.print_paths(bfs_paths)
        print()
    else:
        print("无法找到所需节点")
    
    print("=== 算法特性 ===")
    print("BFS（广度优先搜索）:")
    print("  - 保证在无权图中找到最短路径")
    print("  - 使用队列进行层序遍历")
    print("  - 适用于最短路径查找")
    
    print("\n复杂度分析:")
    print("  - 时间复杂度: O(V + E)，其中V是顶点数，E是边数")
    print("  - 空间复杂度: O(V)，用于队列/递归栈")
    print("  - 矩阵导航: 4方向移动（上、下、左、右）")
    
    print("\n=== 应用场景 ===")
    print("矩阵路径查找用于:")
    print("  - 迷宫求解和益智游戏")
    print("  - 网络路由和导航")
    print("  - 游戏AI和路径查找")
    print("  - 电路板设计")
    print("  - 图像处理和分析")


if __name__ == "__main__":
    main()
