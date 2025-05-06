import java.util.ArrayList;
import java.util.List;

class MatrixNode {
    int data;
    MatrixNode left;
    MatrixNode up;
    MatrixNode down;
    MatrixNode right;

    public MatrixNode(int data) {
        this.data = data;
    }
}

public class ShortestPathFinderDFS {
    private static int shortestLen = Integer.MAX_VALUE;
    private static List<List<MatrixNode>> allShortestPaths = new ArrayList<>();

    public static void findShorterDistance(MatrixNode start, MatrixNode end) {
        shortestLen = Integer.MAX_VALUE;
        allShortestPaths.clear();
        List<MatrixNode> currentPath = new ArrayList<>();
        currentPath.add(start);
        dfs(start, end, currentPath);

        // 打印所有最短路径
        int count = 1;
        for (List<MatrixNode> shortestPath : allShortestPaths) {
            System.out.print(count + ") ");
            for (MatrixNode node : shortestPath) {
                System.out.print(" " + node.data);
            }
            System.out.println();
            count++;
        }
    }

    private static void dfs(MatrixNode current, MatrixNode end, List<MatrixNode> currentPath) {
        if (current == end) {
            int pathLength = currentPath.size();
            if (pathLength < shortestLen) {
                shortestLen = pathLength;
                allShortestPaths.clear();
                allShortestPaths.add(new ArrayList<>(currentPath));
            } else if (pathLength == shortestLen) {
                allShortestPaths.add(new ArrayList<>(currentPath));
            }
            return;
        }

        // 获取当前节点的邻居节点
        List<MatrixNode> neighbors = new ArrayList<>();
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

        for (MatrixNode neighbor : neighbors) {
            currentPath.add(neighbor);
            dfs(neighbor, end, currentPath);
            currentPath.remove(currentPath.size() - 1);
        }
    }

    public static void main(String[] args) {
        // 构建示例矩阵
        MatrixNode node = new MatrixNode(1);
        node.right = new MatrixNode(2);
        node.right.right = new MatrixNode(3);
        node.down = new MatrixNode(4);
        node.down.right = new MatrixNode(5);
        node.down.right.right = new MatrixNode(6);
        node.down.down = new MatrixNode(7);
        node.down.down.right = new MatrixNode(8);
        node.down.down.right.right = new MatrixNode(9);

        // 设置节点连接
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

        System.out.println("");
        System.out.println(node.data + " to " + node.down.right.down.right.data);
        findShorterDistance(node, node.down.right.down.right);
    }
}    