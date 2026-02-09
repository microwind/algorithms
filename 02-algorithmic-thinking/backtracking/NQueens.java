import java.util.*;

/*
N-Queens Problem using Backtracking (Java Implementation)

Algorithm Explanation:
- Place n queens on an n×n chessboard
- No two queens can attack each other (same row, column, or diagonal)
- Use backtracking to explore all possible placements
- For each row, try placing a queen in each column
- Check if placement is safe (not attacked by previously placed queens)
- If safe, place queen and move to next row
- If we place all n queens, we found a solution
- Backtrack and try next column if no solution found

Attack detection:
- Same column: Check column set
- Diagonal (top-left to bottom-right): Check if row - col is same
- Diagonal (top-right to bottom-left): Check if row + col is same

Time Complexity: O(n!)
Space Complexity: O(n)

Example:
    solveNQueens(4) returns 2 solutions
*/

public class NQueens {

    /**
     * Solve the N-Queens problem using backtracking.
     *
     * @param n Size of the chessboard (n queens on n×n board)
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

    /**
     * Recursively place queens row by row.
     *
     * @param result List to store all solutions
     * @param n Size of board
     * @param row Current row to place a queen in
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
        // Base case: all queens placed
        if (row == n) {
            result.add(buildBoard(n, colPlacement));
            return;
        }

        // Try placing a queen in each column of this row
        for (int col = 0; col < n; col++) {
            int diag1Id = row - col;
            int diag2Id = row + col;

            // Check if column or diagonals have a queen
            if (cols.contains(col) || diag1.contains(diag1Id) || diag2.contains(diag2Id)) {
                continue;
            }

            // Place queen
            colPlacement[row] = col;
            cols.add(col);
            diag1.add(diag1Id);
            diag2.add(diag2Id);

            // Explore: try to place queens in remaining rows
            backtrack(result, n, row + 1, colPlacement, cols, diag1, diag2);

            // Backtrack: remove queen
            cols.remove(col);
            diag1.remove(diag1Id);
            diag2.remove(diag2Id);
        }
    }

    /**
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

    /**
     * Count the number of solutions to the N-Queens problem.
     * More efficient than storing all solutions.
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

    /**
     * Test cases for N-Queens problem
     */
    public static void main(String[] args) {
        System.out.println("=== N-Queens Problem using Backtracking ===\n");

        // Test Case 1: 4-Queens
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

        // Test Case 2: 1-Queen
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

        // Test Case 3: Solution counts for various sizes
        System.out.println("Test 3: Solution counts for various N:");
        for (int n = 1; n <= 8; n++) {
            int count = countNQueens(n);
            System.out.println("  N=" + n + ": " + count + " solutions");
        }
        System.out.println();

        // Test Case 4: 5-Queens
        System.out.println("Test 4: solveNQueens(5)");
        List<List<String>> result4 = solveNQueens(5);
        System.out.println("Found " + result4.size() + " solutions for 5-Queens");
        System.out.println("First solution:");
        for (String row : result4.get(0)) {
            System.out.println("  " + row);
        }
    }
}
