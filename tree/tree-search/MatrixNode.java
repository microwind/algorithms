/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  树搜索 - 矩阵节点实现
 * 矩阵节点，含上、下、左、右四个方向指针
 * 用于构建二维矩阵网络，支持四向遍历
 * 包含矩阵创建和最短路径查找功能
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * 矩阵节点类
 * 表示二维矩阵中的一个节点，包含四个方向的连接指针
 */
public class MatrixNode {
    private int data;           // 节点存储的数据值
    private MatrixNode up;       // 上方节点指针
    private MatrixNode down;     // 下方节点指针
    private MatrixNode left;     // 左侧节点指针
    private MatrixNode right;    // 右侧节点指针

    /**
     * 构造函数 - 初始化矩阵节点
     * @param data 节点数据值
     */
    public MatrixNode(int data) {
        this.data = data; // 设置节点数据
        this.up = null;   // 初始化上方指针为空
        this.down = null; // 初始化下方指针为空
        this.left = null; // 初始化左侧指针为空
        this.right = null; // 初始化右侧指针为空
    }

    // Getter方法
    public int getData() { return data; }
    public MatrixNode getUp() { return up; }
    public MatrixNode getDown() { return down; }
    public MatrixNode getLeft() { return left; }
    public MatrixNode getRight() { return right; }

    // Setter方法
    public void setUp(MatrixNode up) { this.up = up; }
    public void setDown(MatrixNode down) { this.down = down; }
    public void setLeft(MatrixNode left) { this.left = left; }
    public void setRight(MatrixNode right) { this.right = right; }

    /**
     * 创建n×n的矩阵网络并返回左上角起始节点
     * 
     * 算法步骤:
     * 1. 创建n×n的二维节点数组
     * 2. 为每个位置创建节点并赋值
     * 3. 建立水平方向的左右连接
     * 4. 建立垂直方向的上下连接
     * 5. 返回左上角的起始节点
     * 
     * 时间复杂度: O(n²) - 需要处理n²个节点
     * 空间复杂度: O(n²) - 存储n²个节点
     * 
     * @param n 矩阵的维度大小
     * @return 矩阵左上角的起始节点
     */
    public static MatrixNode createMatrix(int n) {
        MatrixNode[][] matrix = new MatrixNode[n][n];
        int counter = 1;

        // 初始化n×n节点矩阵
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = new MatrixNode(counter++);
            }
        }

        // 建立水平连接（左右指针）
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1; j++) {
                matrix[i][j].setRight(matrix[i][j + 1]); // 设置右指针
                matrix[i][j + 1].setLeft(matrix[i][j]);   // 设置左指针
            }
        }

        // 建立垂直连接（上下指针）
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j].setDown(matrix[i + 1][j]); // 设置下指针
                matrix[i + 1][j].setUp(matrix[i][j]);   // 设置上指针
            }
        }

        return matrix[0][0]; // 返回左上角起始节点
    }

    /**
     * 打印矩阵结构
     * 
     * 算法步骤:
     * 1. 从当前节点开始，逐行向下遍历
     * 2. 在每行中从左向右遍历
     * 3. 打印每个节点的数据值
     * 4. 每行结束后换行
     * 
     * @param n 矩阵的维度大小
     */
    public void printMatrix(int n) {
        MatrixNode rowHead = this; // 当前行头节点
        for (int i = 0; i < n; i++) {
            MatrixNode current = rowHead; // 当前列节点
            for (int j = 0; j < n; j++) {
                System.out.print(current.data + " "); // 打印节点数据
                current = current.right; // 移动到右侧节点
            }
            System.out.println(); // 换行
            rowHead = rowHead.down; // 移动到下一行
        }
    }

    /**
     * 使用深度优先搜索查找所有最短路径
     * 
     * 算法步骤:
     * 1. 使用递归进行深度优先搜索
     * 2. 维护当前路径和已访问节点集合
     * 3. 找到目标节点时记录路径长度
     * 4. 只保留最短长度的路径
     * 5. 回溯时清理访问状态
     * 
     * 时间复杂度: O(V + E) - V为顶点数，E为边数
     * 空间复杂度: O(V) - 用于递归栈和路径存储
     * 
     * @param start 起始节点
     * @param end 目标节点
     * @return 所有最短路径的列表
     */
    public static List<List<MatrixNode>> findShortestPaths(MatrixNode start, MatrixNode end) {
        List<List<MatrixNode>> shortestPaths = new ArrayList<>(); // 存储最短路径
        int shortestLength = Integer.MAX_VALUE; // 最短路径长度
        Set<MatrixNode> visited = new HashSet<>(); // 已访问节点集合

        dfs(start, end, new ArrayList<>(), visited, shortestLength, shortestPaths);

        return shortestPaths;
    }

    /**
     * 深度优先搜索的递归辅助方法
     * 
     * @param current 当前节点
     * @param end 目标节点
     * @param currentPath 当前路径
     * @param visited 已访问节点集合
     * @param shortestLength 最短路径长度
     * @param shortestPaths 最短路径列表
     */
    private static void dfs(MatrixNode current, MatrixNode end, List<MatrixNode> currentPath,
                         Set<MatrixNode> visited, int shortestLength, 
                         List<List<MatrixNode>> shortestPaths) {
        if (current == null) {
            return; // 当前节点为空，直接返回
        }

        currentPath.add(current); // 将当前节点添加到路径
        visited.add(current); // 标记当前节点为已访问

        if (current == end) {
            // 到达目标节点，记录路径
            int currentDistance = currentPath.size() - 1;

            if (currentPath.size() < shortestLength) {
                shortestLength = currentPath.size();
                shortestPaths.clear();
                shortestPaths.add(new ArrayList<>(currentPath));
            } else if (currentPath.size() == shortestLength) {
                shortestPaths.add(new ArrayList<>(currentPath));
            }
        } else {
            // 继续搜索邻居节点
            List<MatrixNode> neighbors = getNeighbors(current);
            for (MatrixNode neighbor : neighbors) {
                if (!visited.contains(neighbor)) {
                    dfs(neighbor, end, currentPath, visited, shortestLength, shortestPaths);
                }
            }
        }

        // 回溯：移除当前节点
        currentPath.remove(currentPath.size() - 1);
        visited.remove(current);
    }

    /**
     * 获取节点的所有有效邻居
     * 
     * @param node 当前节点
     * @return 邻居节点列表
     */
    private static List<MatrixNode> getNeighbors(MatrixNode node) {
        List<MatrixNode> neighbors = new ArrayList<>();
        
        if (node.left != null) neighbors.add(node.left);   // 左邻居
        if (node.up != null) neighbors.add(node.up);       // 上邻居
        if (node.down != null) neighbors.add(node.down);     // 下邻居
        if (node.right != null) neighbors.add(node.right);  // 右邻居
        
        return neighbors;
    }

    /**
     * 打印所有找到的路径
     * 
     * @param paths 路径列表
     */
    public static void printPaths(List<List<MatrixNode>> paths) {
        if (paths.isEmpty()) {
            System.out.println("未找到路径"); // 未找到路径提示
            return;
        }

        System.out.println("找到 " + paths.size() + " 条最短路径:");
        for (int i = 0; i < paths.size(); i++) {
            System.out.print("路径 " + (i + 1) + ": ");
            for (int j = 0; j < paths.get(i).size(); j++) {
                System.out.print(paths.get(i).get(j).data);
                if (j < paths.get(i).size() - 1) {
                    System.out.print(" -> ");
                }
            }
            System.out.println();
        }
    }

    /**
     * 主测试方法
     * 
     * 测试用例:
     * 1. 创建3×3矩阵网络
     * 2. 显示矩阵结构
     * 3. 查找从左上角到右下角的最短路径
     * 4. 演示路径查找功能
     */
    public static void main(String[] args) {
        int n = 3; // 3×3矩阵
        MatrixNode startNode = createMatrix(n);
        
        System.out.println("矩阵结构:");
        startNode.printMatrix(n);
        
        // 查找右下角节点
        MatrixNode endNode = startNode;
        for (int i = 0; i < n - 1; i++) {
            endNode = endNode.right; // 向右移动
        }
        for (int i = 0; i < n - 1; i++) {
            endNode = endNode.down; // 向下移动
        }
        
        System.out.println("\n查找从 " + startNode.data + " 到 " + endNode.data + " 的最短路径:");
        List<List<MatrixNode>> shortestPaths = findShortestPaths(startNode, endNode);
        printPaths(shortestPaths);
        
        System.out.println("\n=== 算法特性 ===");
        System.out.println("深度优先搜索路径查找:");
        System.out.println("  - 使用递归和回溯");
        System.out.println("  - 能找到所有可能路径");
        System.out.println("  - 适合探索完整解空间");
        System.out.println("  - 时间复杂度: O(V + E)");
        System.out.println("  - 空间复杂度: O(V)");
        
        System.out.println("\n=== 应用场景 ===");
        System.out.println("矩阵路径查找用于:");
        System.out.println("  - 迷宫求解和路径规划");
        System.out.println("  - 游戏AI和寻路算法");
        System.out.println("  - 网络路由优化");
        System.out.println("  - 电路板布线");
        System.out.println("  - 图像处理和路径分析");
    }

    @Override
    public String toString() {
        return "MatrixNode(" + data + ")"; // 节点字符串表示
    }
}
