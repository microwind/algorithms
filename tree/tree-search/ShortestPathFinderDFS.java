/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  树搜索 - DFS最短路径查找器
 * 使用深度优先搜索在矩阵中查找所有最短路径
 * 探索所有可能的路径并记录最短的路径
 * 包含回溯和路径优化
 */

import java.util.ArrayList;
import java.util.List;

/**
 * DFS路径查找器的矩阵节点类
 * 表示矩阵中的一个元素，包含四个方向的指针
 */
class MatrixNodeDFS {
    int data;           // 节点存储的数据
    MatrixNodeDFS left;    // 左指针
    MatrixNodeDFS up;      // 上指针
    MatrixNodeDFS down;    // 下指针
    MatrixNodeDFS right;   // 右指针

    /**
     * 构造函数 - 初始化节点数据
     * @param data 节点值
     */
    public MatrixNodeDFS(int data) {
        this.data = data;
    }
}

/**
 * DFS最短路径查找器类
 * 使用深度优先搜索算法在矩阵网络中查找两个节点之间的所有最短路径
 */
public class ShortestPathFinderDFS {
    private static int shortestLen = Integer.MAX_VALUE;  // 当前最短路径长度
    private static List<List<MatrixNodeDFS>> allShortestPaths = new ArrayList<>();  // 找到的所有最短路径

    /**
     * 查找起始节点和结束节点之间的最短路径
     * 
     * 算法:
     * 1. 初始化搜索参数
     * 2. 从起始节点开始DFS搜索
     * 3. 收集所有最短路径
     * 4. 打印结果
     * 
     * 时间复杂度: O(n!) - 最坏情况探索所有可能路径
     * 空间复杂度: O(n) - 用于递归栈和路径存储
     * 
     * @param start 起始节点
     * @param end 结束节点
     */
    public static void findShorterDistance(MatrixNodeDFS start, MatrixNodeDFS end) {
        shortestLen = Integer.MAX_VALUE;  // 重置最短长度
        allShortestPaths.clear();         // 清除之前的结果
        List<MatrixNodeDFS> currentPath = new ArrayList<>();  // 当前探索路径
        currentPath.add(start);          // 从起点开始
        dfs(start, end, currentPath);    // 开始DFS搜索

        // 打印找到的所有最短路径
        int count = 1;
        for (List<MatrixNodeDFS> shortestPath : allShortestPaths) {
            System.out.print(count + ") ");
            for (MatrixNodeDFS node : shortestPath) {
                System.out.print(" " + node.data);
            }
            System.out.println();
            count++;
        }
    }

    /**
     * 深度优先搜索辅助函数
     * 
     * 算法:
     * 1. 如果到达目的地，更新最短路径
     * 2. 收集所有有效邻居（未访问过）
     * 3. 递归探索每个邻居
     * 4. 探索后回溯
     * 
     * @param current 当前正在探索的节点
     * @param end 目的地节点
     * @param currentPath 到目前为止走过的路径
     */
    private static void dfs(MatrixNodeDFS current, MatrixNodeDFS end, List<MatrixNodeDFS> currentPath) {
        // 基本情况：到达目的地
        if (current == end) {
            int pathLength = currentPath.size();
            if (pathLength < shortestLen) {
                // 找到更短路径，更新记录
                shortestLen = pathLength;
                allShortestPaths.clear();
                allShortestPaths.add(new ArrayList<>(currentPath));
            } else if (pathLength == shortestLen) {
                // 找到另一条最短路径
                allShortestPaths.add(new ArrayList<>(currentPath));
            }
            return;
        }

        // 获取当前节点的邻居节点
        List<MatrixNodeDFS> neighbors = new ArrayList<>();
        if (current.left != null && !currentPath.contains(current.left)) {
            neighbors.add(current.left);
        }
        if (current.up != null && !currentPath.contains(current.up)) {
            neighbors.add(current.up);
        }
        if (current.down != null && !currentPath.contains(current.down)) {
            neighbors.add(current.down);
        }
        if (current.right != null && !currentPath.contains(current.right)) {
            neighbors.add(current.right);
        }

        // 递归探索每个邻居
        for (MatrixNodeDFS neighbor : neighbors) {
            currentPath.add(neighbor);     // 将邻居添加到当前路径
            dfs(neighbor, end, currentPath);  // 递归探索
            currentPath.remove(currentPath.size() - 1);  // 回溯
        }
    }

    /**
     * 主函数 - 测试DFS最短路径查找器
     * 
     * 测试用例:
     * 创建3x3矩阵网络
     * 查找从左上角到右下角的最短路径
     * 演示带障碍物的路径查找
     */
    public static void main(String[] args) {
        // 构建示例矩阵
        MatrixNodeDFS node = new MatrixNodeDFS(1);
        node.right = new MatrixNodeDFS(2);
        node.right.right = new MatrixNodeDFS(3);
        node.down = new MatrixNodeDFS(4);
        node.down.right = new MatrixNodeDFS(5);
        node.down.right.right = new MatrixNodeDFS(6);
        node.down.down = new MatrixNodeDFS(7);
        node.down.down.right = new MatrixNodeDFS(8);
        node.down.down.right.right = new MatrixNodeDFS(9);

        // 设置节点连接（双向）
        node.right.left = node;
        node.right.right.left = node.right;
        node.down.up = node;
        node.down.right.left = node.down;
        node.down.right.right.left = node.down.right;
        node.down.down.up = node.down;
        node.down.down.right.left = node.down.down;
        node.down.down.right.right.left = node.down.down.right;

        node.right.down = node.down.right;
        node.right.right.down = node.down.right.right;
        node.down.right.down = node.down.down.right;
        node.down.right.right.down = node.down.down.right.right;

        System.out.println("=".repeat(50));
        System.out.println("DFS最短路径查找器 - Java实现");
        System.out.println("=".repeat(50));
        
        System.out.println("\n矩阵结构:");
        System.out.println("  1  2  3");
        System.out.println("  4  5  6");
        System.out.println("  7  8  9");
        
        System.out.println("\n查找从 " + node.data + " 到 " + node.down.right.down.right.data + " 的最短路径");
        findShorterDistance(node, node.down.right.down.right);
        
        System.out.println("\n=== 算法特性 ===");
        System.out.println("DFS路径查找:");
        System.out.println("  - 探索所有可能的路径");
        System.out.println("  - 使用回溯避免循环");
        System.out.println("  - 记录所有最短路径");
        System.out.println("  - 时间复杂度: 最坏情况O(n!)");
        System.out.println("  - 空间复杂度: 递归使用O(n)");
        
        System.out.println("\n=== 应用场景 ===");
        System.out.println("DFS最短路径查找用于:");
        System.out.println("  - 迷宫求解");
        System.out.println("  - 网络路由");
        System.out.println("  - 游戏寻路");
        System.out.println("  - 谜题求解");
        System.out.println("  - 电路设计");
    }
}
