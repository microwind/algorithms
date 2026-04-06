/**
 * 回溯算法 - N皇后问题
 * 在n×n棋盘上放置n个皇后，使其互不攻击
 */
public class NQueen {
    private static final int N = 4; // 棋盘大小
    
    /**
     * 打印棋盘
     * @param board 棋盘数组
     */
    private void printBoard(int[][] board) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                System.out.print(board[i][j] == 1 ? "Q " : ". ");
            }
            System.out.println();
        }
        System.out.println();
    }
    
    /**
     * 检查在(row, col)放置皇后是否安全
     * @param board 棋盘数组
     * @param row 行
     * @param col 列
     * @return 是否安全
     */
    private boolean isSafe(int[][] board, int row, int col) {
        // 检查列
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 1) return false;
        }
        
        // 检查左上对角线
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 1) return false;
        }
        
        // 检查右上对角线
        for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
            if (board[i][j] == 1) return false;
        }
        
        return true;
    }
    
    /**
     * 使用回溯求解N皇后
     * @param board 棋盘数组
     * @param row 当前行
     * @return 是否找到解
     */
    private boolean solveNQueen(int[][] board, int row) {
        // 基础情况：所有皇后都已放置
        if (row >= N) {
            return true;
        }
        
        // 尝试在当前行的每一列放置皇后
        for (int col = 0; col < N; col++) {
            if (isSafe(board, row, col)) {
                // 放置皇后
                board[row][col] = 1;
                
                // 递归：放置下一行的皇后
                if (solveNQueen(board, row + 1)) {
                    return true;
                }
                
                // 回溯：撤销放置
                board[row][col] = 0;
            }
        }
        
        return false;
    }
    
    public static void main(String[] args) {
        NQueen solver = new NQueen();
        int[][] board = new int[N][N];
        
        System.out.println(N + "皇后问题求解:\n");
        
        if (solver.solveNQueen(board, 0)) {
            System.out.println("找到解:");
            solver.printBoard(board);
        } else {
            System.out.println("无解");
        }
    }
}
