import java.util.*;

/*
使用回溯算法的N皇后问题 (Java Implementation)

算法说明:
- 在n×n棋盘上放置n个皇后
- 任意两个皇后不能相互攻击（不在同一行、列或对角线上）
- 使用回溯探索所有可能的放置方案
- 对于每一行，尝试在每一列放置一个皇后
- 检查放置是否安全（不被之前放置的皇后攻击）
- 如果安全，则放置皇后并移到下一行
- 如果所有n个皇后都被放置，则找到一个解
- 如果没有找到解，回溯并尝试下一列

攻击检测:
- Same column: Check column set
- 对角线（左上到右下）：检查row - col是否相同
- 对角线（右上到左下）：检查row + col是否相同

Time Complexity: O(n!)
Space Complexity: O(n)

示例:
    solveNQueens(4) returns 2 solutions
*/

public class NQueens {

    /*
*
     * 使用回溯算法解决N皇后问题.
     *
     * @param n 棋盘大小（n个皇后放在n×n棋盘上）
     * @return List of solutions, each solution is a list of board strings
*/
    public static List<List<String>> solveNQueens(int n) {
        List<List<String>> result = new ArrayList<>();
        int[] colPlacement = new int[n];  // colPlacement[row] = col
        Set<Integer> cols = new HashSet<>();
        Set<Integer> diag1 = new HashSet<>();  // row - col
        Set<Integer> diag2 = new HashSet<>();  // row + col

        backtrack(result, n, 0, colPlacement, cols, diag1, diag2);
        return result;
    }

    /*
*
     * 递归地逐行放置皇后.
     *
     * @param result List to store all solutions
     * @param n Size of board
     * @param row 当前要放置皇后的行
     * @param colPlacement Array tracking queen column positions
     * @param cols Set of columns with queens
     * @param diag1 Set of diagonals (top-left to bottom-right)
     * @param diag2 Set of diagonals (top-right to bottom-left)
*/
    private static void backtrack(List<List<String>> result,
                                   int n,
                                   int row,
                                   int[] colPlacement,
                                   Set<Integer> cols,
                                   Set<Integer> diag1,
                                   Set<Integer> diag2) {
        // 基本情况：所有皇后都已放置
        if (row == n) {
            result.add(buildBoard(n, colPlacement));
            return;
        }

        // 尝试在此行的每一列放置一个皇后
        for (int col = 0; col < n; col++) {
            int diag1Id = row - col;
            int diag2Id = row + col;

            // Check if column or diagonals have a queen
            if (cols.contains(col) || diag1.contains(diag1Id) || diag2.contains(diag2Id)) {
                continue;
            }

            // 放置皇后
            colPlacement[row] = col;
            cols.add(col);
            diag1.add(diag1Id);
            diag2.add(diag2Id);

            // 探索：尝试在剩余行放置皇后
            backtrack(result, n, row + 1, colPlacement, cols, diag1, diag2);

            // 回溯：移除皇后
            cols.remove(col);
            diag1.remove(diag1Id);
            diag2.remove(diag2Id);
        }
    }

    /*
*
     * Build the board representation from column placements.
*/
    private static List<String> buildBoard(int n, int[] colPlacement) {
        List<String> board = new ArrayList<>();
        for (int row = 0; row < n; row++) {
            StringBuilder sb = new StringBuilder();
            for (int col = 0; col < n; col++) {
                sb.append(col == colPlacement[row] ? 'Q' : '.');
            }
            board.add(sb.toString());
        }
        return board;
    }

    /*
*
     * 计算N皇后问题的解的数量.
     * 比存储所有解更高效.
     *
     * @param n Size of board
     * @return Number of solutions
*/
    public static int countNQueens(int n) {
        int[] count = {0};
        Set<Integer> cols = new HashSet<>();
        Set<Integer> diag1 = new HashSet<>();
        Set<Integer> diag2 = new HashSet<>();

        countBacktrack(n, 0, cols, diag1, diag2, count);
        return count[0];
    }

    private static void countBacktrack(int n,
                                        int row,
                                        Set<Integer> cols,
                                        Set<Integer> diag1,
                                        Set<Integer> diag2,
                                        int[] count) {
        if (row == n) {
            count[0]++;
            return;
        }

        for (int col = 0; col < n; col++) {
            int diag1Id = row - col;
            int diag2Id = row + col;

            if (cols.contains(col) || diag1.contains(diag1Id) || diag2.contains(diag2Id)) {
                continue;
            }

            cols.add(col);
            diag1.add(diag1Id);
            diag2.add(diag2Id);

            countBacktrack(n, row + 1, cols, diag1, diag2, count);

            cols.remove(col);
            diag1.remove(diag1Id);
            diag2.remove(diag2Id);
        }
    }

    /*
*
     * Test cases for N-Queens problem
*/
    public static void main(String[] args) {
        System.out.println("=== N-Queens Problem using Backtracking ===\n");

        // 测试用例 1: 4-Queens
        System.out.println("Test 1: solveNQueens(4)");
        List<List<String>> result1 = solveNQueens(4);
        System.out.println("Found " + result1.size() + " solutions:\n");
        for (int i = 0; i < result1.size(); i++) {
            System.out.println("Solution " + (i + 1) + ":");
            for (String row : result1.get(i)) {
                System.out.println("  " + row);
            }
            System.out.println();
        }

        // 测试用例 2: 1-Queen
        System.out.println("Test 2: solveNQueens(1)");
        List<List<String>> result2 = solveNQueens(1);
        System.out.println("Found " + result2.size() + " solution(s):\n");
        for (int i = 0; i < result2.size(); i++) {
            System.out.println("Solution " + (i + 1) + ":");
            for (String row : result2.get(i)) {
                System.out.println("  " + row);
            }
            System.out.println();
        }

        // 测试用例 3: Solution counts for various sizes
        System.out.println("Test 3: Solution counts for various N:");
        for (int n = 1; n <= 8; n++) {
            int count = countNQueens(n);
            System.out.println("  N=" + n + ": " + count + " solutions");
        }
        System.out.println();

        // 测试用例 4: 5-Queens
        System.out.println("Test 4: solveNQueens(5)");
        List<List<String>> result4 = solveNQueens(5);
        System.out.println("Found " + result4.size() + " solutions for 5-Queens");
        System.out.println("First solution:");
        for (String row : result4.get(0)) {
            System.out.println("  " + row);
        }
    }
}
