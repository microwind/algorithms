
//  矩阵节点，含up, down, left, right

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class MatrixNode {
    private int data;
    private MatrixNode up;
    private MatrixNode down;
    private MatrixNode left;
    private MatrixNode right;

    public MatrixNode(int data) {
        this.data = data;
    }

    public static MatrixNode createMatrix(int n) {
        MatrixNode[][] matrix = new MatrixNode[n][n];
        int counter = 1;

        // 初始化n*n
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = new MatrixNode(counter++);
            }
        }

        // left,right
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1; j++) {
                // 最后一列，right 指向第一列
                matrix[i][j + 1].left = matrix[i][j];
                matrix[i][j].right = matrix[i][j + 1];
            }
        }

        // up,down
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n; j++) {
                // 最后一行，down 指向第一行
                matrix[i + 1][j].up = matrix[i][j];
                matrix[i][j].down = matrix[i + 1][j];
            }
        }
        return matrix[0][0];
    }

    public void printMatrix(int n) {
        MatrixNode head = this;
        for (int i = 0; i < n; i++) {
            MatrixNode current = head;
            for (int j = 0; j < n; j++) {
                System.out.print(current.data + " ");
                current = current.right;
            }
            System.out.println("");
            head = head.down;
        }
    }

    public static void findShorterDistance(MatrixNode start, MatrixNode end) {
        // 广度优先搜索 - 查找所有最短路径
        List<List<MatrixNode>> pathList = new ArrayList<>();
        Set<MatrixNode> visited = new HashSet<>();
        Map<MatrixNode, List<List<MatrixNode>>> parentMap = new HashMap<>();
        // 记录到达每个节点的最短距离
        Map<MatrixNode, Integer> minDistance = new HashMap<>();
        int shortestLen = Integer.MAX_VALUE;

        List<MatrixNode> initialPath = new ArrayList<>();
        initialPath.add(start);
        pathList.add(initialPath);
        minDistance.put(start, 0);

        while (!pathList.isEmpty()) {
            List<MatrixNode> path = pathList.remove(0);
            MatrixNode current = path.get(path.size() - 1);
            int currentDistance = path.size() - 1;

            // 这里注释掉了，因为我们需要找到所有最短路径
            // if (visited.contains(current)) {
            //     continue;
            // }
            // visited.add(current);

            // 如果当前节点是目标节点
            if (current == end) {
                // 如果当前路径比之前找到的路径更短，更新最短路径
                if (currentDistance < shortestLen) {
                    shortestLen = currentDistance;
                    parentMap.clear();
                    List<List<MatrixNode>> paths = new ArrayList<>();
                    paths.add(new ArrayList<>(path));
                    parentMap.put(current, paths);
                } else if (currentDistance == shortestLen) {
                    // 如果当前路径长度等于最短路径长度，则也保留该路径
                    // 如果还没有保存过该节点的路径，先创建一个列表
                    if (!parentMap.containsKey(current)) {
                        parentMap.put(current, new ArrayList<>());
                    }
                    parentMap.get(current).add(new ArrayList<>(path));
                }
                continue;
            }

            // 获取当前节点的邻居节点
            List<MatrixNode> neighbors = new ArrayList<>();
            if (current.left != null)
                neighbors.add(current.left);
            if (current.up != null)
                neighbors.add(current.up);
            if (current.down != null)
                neighbors.add(current.down);
            if (current.right != null)
                neighbors.add(current.right);

            for (MatrixNode neighbor : neighbors) {
                int newDistance = currentDistance + 1;
                /**
                 * 如果这个邻居还没有被访问过，或者新路径长度小于等于已有最短路径，
                 * 就继续探索这条路径。
                 */
                if (!minDistance.containsKey(neighbor) || newDistance <= minDistance.get(neighbor)) {
                    minDistance.put(neighbor, newDistance);
                    List<MatrixNode> newPath = new ArrayList<>(path);
                    newPath.add(neighbor);
                    pathList.add(newPath);
                }
            }
        }

        // 打印所有最短路径
        int count = 1;
        for (List<List<MatrixNode>> paths : parentMap.values()) {
            for (List<MatrixNode> shortestPath : paths) {
                System.out.print(count + ") ");
                for (MatrixNode node : shortestPath) {
                    System.out.print(" " + node.data);
                }
                System.out.println();
                count++;
            }
        }
    }

    public static void main(String[] args) {
        /**
         * 打印结构：
         * 1 2 3
         * 4 5 6
         * 7 8 9
         */
        int n = 3;
        MatrixNode node = MatrixNode.createMatrix(n);
        node.printMatrix(n);

        /**
         * 打印全部最短路径：
         * 2 to 9
         * 1) 2 5 8 9
         * 2) 2 3 6 9
         * 3) 2 5 6 9
         */
        System.out.println("");
        System.out.println(node.right.data + " to " + node.down.right.down.right.data);
        findShorterDistance(node.right, node.down.right.down.right);
    }

}
