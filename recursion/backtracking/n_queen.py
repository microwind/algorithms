"""
回溯算法 - N皇后问题
在n×n棋盘上放置n个皇后，使其互不攻击
"""

N = 4  # 棋盘大小

def print_board(board):
    """打印棋盘"""
    for i in range(N):
        row = ""
        for j in range(N):
            row += "Q " if board[i][j] == 1 else ". "
        print(row)
    print()

def is_safe(board, row, col):
    """检查在(row, col)放置皇后是否安全"""
    # 检查列
    for i in range(row):
        if board[i][col] == 1:
            return False
    
    # 检查左上对角线
    for i, j in range(row-1, col-1, -1), range(row-1, col-1, -1):
        if i >= 0 and j >= 0 and board[i][j] == 1:
            return False
    
    # 检查右上对角线
    for i, j in zip(range(row-1, -1, -1), range(col+1, N)):
        if board[i][j] == 1:
            return False
    
    return True

def solve_n_queen(board, row):
    """使用回溯求解N皇后"""
    # 基础情况：所有皇后都已放置
    if row >= N:
        return True
    
    # 尝试在当前行的每一列放置皇后
    for col in range(N):
        if is_safe(board, row, col):
            # 放置皇后
            board[row][col] = 1
            
            # 递归：放置下一行的皇后
            if solve_n_queen(board, row + 1):
                return True
            
            # 回溯：撤销放置
            board[row][col] = 0
    
    return False

def main():
    board = [[0 for _ in range(N)] for _ in range(N)]
    
    print(f"{N}皇后问题求解:\n")
    
    if solve_n_queen(board, 0):
        print("找到解:")
        print_board(board)
    else:
        print("无解")

if __name__ == "__main__":
    main()
