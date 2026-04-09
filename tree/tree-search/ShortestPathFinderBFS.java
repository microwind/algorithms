/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  树搜索 - BFS最短路径查找器
 * 使用广度优先搜索在矩阵中查找所有最短路径
 * 逐层探索路径，保证找到最优最短路径
 * 包含路径剪枝和多条最短路径处理
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * 矩阵节点类，表示矩阵中的一个元素，包含四个方向的指针
 */
class MatrixNode {
    public int data;         // 节点存储的数据
    public MatrixNode up;    // 上方节点指针
    public MatrixNode down;  // 下方节点指针
    public MatrixNode left;  // 左侧节点指针
    public MatrixNode right; // 右侧节点指针

    /**
     * 构造函数，初始化节点数据
     * @param data 节点数值
     */
    public MatrixNode(int data) {
        this.data = data;
    }

    /**
     * 创建n*n的矩阵网络并返回左上角起始节点
     * 
     * 算法:
     * 1. 创建n x n节点矩阵
     * 2. 用顺序数据初始化每个节点
     * 3. 建立水平连接（左右）
     * 4. 建立垂直连接（上下）
     * 
     * 时间复杂度: O(n²) - 处理n²个节点
     * 空间复杂度: O(n²) - 存储n²个节点
     * 
     * @param n 矩阵维度
     * @return 矩阵左上角起始节点
     */
    public static MatrixNode createMatrix(int n) {
        MatrixNode[][] matrix = new MatrixNode[n][n];
        int counter = 1;

        // 初始化矩阵所有节点
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = new MatrixNode(counter++);
            }
        }

        // 建立水平连接（左右指针）
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1; j++) {
                // 当前节点的right指向右侧节点
                matrix[i][j].right = matrix[i][j + 1];
                // 右侧节点的left指向当前节点
                matrix[i][j + 1].left = matrix[i][j];
            }
        }

        // 建立垂直连接（上下指针）
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n; j++) {
                // 当前节点的down指向下方节点
                matrix[i][j].down = matrix[i + 1][j];
                // 下方节点的up指向当前节点
                matrix[i + 1][j].up = matrix[i][j];
            }
        }
        return matrix[0][0]; // 返回左上角起始节点
    }

    /**
     * 打印矩阵结构
     * 
     * 算法:
     * 1. 使用down指针逐行遍历
     * 2. 使用right指针遍历每行
     * 3. 打印每个节点的数据值
     * 
     * @param n 矩阵维度
     */
    public void printMatrix(int n) {
        MatrixNode rowHead = this; // 当前行头节点
        for (int i = 0; i < n; i++) {
            MatrixNode current = rowHead;
            for (int j = 0; j < n; j++) {
                System.out.print(current.data + " ");
                current = current.right; // 向右移动
            }
            System.out.println();
            rowHead = rowHead.down; // 移动到下一行
        }
    }
}

/**
 * BFS最短路径查找器类
 * 使用广度优先搜索算法在矩阵网络中查找两个节点之间的所有最短路径
 */
public class ShortestPathFinderBFS {
    /**
     * 使用BFS算法查找所有最短路径
     * 
     * 算法:
     * 1. 使用队列进行层次路径探索
     * 2. 跟踪最短路径长度用于剪枝
     * 3. 收集所有最小长度的路径
     * 4. 使用路径跟踪避免循环
     * 
     * 时间复杂度: O(V + E) - V=顶点数, E=边数
     * 空间复杂度: O(V) - 用于队列和路径存储
     * 
     * @param start 起始节点
     * @param end 目标节点
     */
    public static void findShorterDistance(MatrixNode start, MatrixNode end) {
        List<List<MatrixNode>> queue = new ArrayList<>();       // BFS队列，存储待探索路径
        Map<MatrixNode, Integer> distance = new HashMap<>();   // 记录节点到起点的最短距离
        List<List<MatrixNode>> shortestPaths = new ArrayList<>(); // 存储所有最短路径
        int shortestLen = Integer.MAX_VALUE;                    // 当前已知的最短路径长度

        // 初始化队列，添加包含起始节点的路径
        List<MatrixNode> initialPath = new ArrayList<>();
        initialPath.add(start);
        queue.add(initialPath);
        distance.put(start, 1); // 起始节点距离为1（路径节点数）

        // BFS主循环
        while (!queue.isEmpty()) {
            List<MatrixNode> path = queue.remove(0); // 取出队列首条路径
            MatrixNode current = path.get(path.size() - 1); // 当前路径的最后一个节点
            int currentPathLength = path.size();

            // 到达目标节点的处理
            if (current == end) {
                if (currentPathLength < shortestLen) { // 发现更短路径
                    shortestLen = currentPathLength;
                    shortestPaths.clear(); // 清空原有结果
                    shortestPaths.add(new ArrayList<>(path));
                } else if (currentPathLength == shortestLen) { // 等长路径
                    shortestPaths.add(new ArrayList<>(path));
                }
                continue; // 跳过后续处理
            }

            // 路径剪枝：如果当前路径长度已超过最短路径长度，跳过
            if (distance.containsKey(current)) {
                if (currentPathLength > distance.get(current)) {
                    continue;
                }
            } else {
                distance.put(current, currentPathLength); // 记录节点最短距离
            }

            // 获取当前节点的有效邻居（四个方向）
            List<MatrixNode> neighbors = new ArrayList<>();
            if (current.left != null) neighbors.add(current.left);
            if (current.up != null) neighbors.add(current.up);
            if (current.down != null) neighbors.add(current.down);
            if (current.right != null) neighbors.add(current.right);

            // 生成新路径并加入队列
            for (MatrixNode neighbor : neighbors) {
                List<MatrixNode> newPath = new ArrayList<>(path); // 复制当前路径
                newPath.add(neighbor); // 添加邻居节点
                queue.add(newPath);    // 将新路径加入队列
            }
        }

        // 打印所有最短路径
        System.out.println("找到 " + shortestPaths.size() + " 条最短路径:");
        for (List<MatrixNode> path : shortestPaths) {
            System.out.print("路径:");
            for (MatrixNode node : path) {
                System.out.print(" " + node.data);
            }
            System.out.println();
        }
    }

    /**
     * 主函数测试用例
     * 
     * 测试用例:
     * 1. 创建3x3矩阵网络
     * 2. 显示矩阵结构
     * 3. 查找从左上角到右下角的最短路径
     * 4. 演示BFS路径查找功能
     */
    public static void main(String[] args) {
        int n = 3; // 3x3矩阵
        MatrixNode node = MatrixNode.createMatrix(n);
        System.out.println("矩阵结构:");
        node.printMatrix(n);

        // 计算从左上角(1)到右下角(9)的最短路径
        MatrixNode endNode = node.down.right.down.right; // 9号节点
        System.out.println("\n查找从 " + node.data + " 到 " + endNode.data + " 的路径");
        findShorterDistance(node, endNode);
        
        System.out.println("\n=== 算法特性 ===");
        System.out.println("BFS最短路径查找:");
        System.out.println("  - 保证找到最优最短路径");
        System.out.println("  - 逐层探索路径");
        System.out.println("  - 使用队列进行系统化探索");
        System.out.println("  - 时间复杂度: O(V + E)");
        System.out.println("  - 空间复杂度: O(V)");
        
        System.out.println("\n=== 应用场景 ===");
        System.out.println("BFS路径查找用于:");
        System.out.println("  - 网络路由和导航");
        System.out.println("  - 游戏AI和路径查找");
        System.out.println("  - 社交网络分析");
        System.out.println("  - 网络爬虫和索引");
        System.out.println("  - 谜题求解和迷宫导航");
    }
}
