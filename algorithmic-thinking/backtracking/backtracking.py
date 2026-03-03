"""
回溯算法 - 探索所有可能的解

特点：
- 逐步构建解
- 发现无法继续时回退
- 适合求所有解或某个解的问题
"""

# 例1: 全排列
def permute(nums):
    """生成数组的所有排列"""
    result = []
    
    def backtrack(current):
        if len(current) == len(nums):
            result.append(current[:])
            return
        
        for num in nums:
            if num not in current:
                current.append(num)
                backtrack(current)
                current.pop()
    
    backtrack([])
    return result

# 例2: 组合
def combine(n, k):
    """从 1 到 n 中选择 k 个数的所有组合"""
    result = []
    
    def backtrack(start, current):
        if len(current) == k:
            result.append(current[:])
            return
        
        for i in range(start, n + 1):
            current.append(i)
            backtrack(i + 1, current)
            current.pop()
    
    backtrack(1, [])
    return result

# 例3: N 皇后问题
def solve_n_queens(n):
    """
    放置 n 个皇后使它们不互相攻击
    返回所有可行的放置方案
    """
    result = []
    board = ['.' * n for _ in range(n)]
    
    def is_safe(row, col):
        # 检查列
        for r in range(row):
            if board[r][col] == 'Q':
                return False
        
        # 检查左上方对角线
        r, c = row - 1, col - 1
        while r >= 0 and c >= 0:
            if board[r][c] == 'Q':
                return False
            r -= 1
            c -= 1
        
        # 检查右上方对角线
        r, c = row - 1, col + 1
        while r >= 0 and c < n:
            if board[r][c] == 'Q':
                return False
            r -= 1
            c += 1
        
        return True
    
    def backtrack(row):
        if row == n:
            result.append([row[:] for row in board])
            return
        
        for col in range(n):
            board_list = list(board[row])
            if is_safe(row, col):
                board_list[col] = 'Q'
                board[row] = ''.join(board_list)
                backtrack(row + 1)
                board_list[col] = '.'
                board[row] = ''.join(board_list)
    
    backtrack(0)
    return result

if __name__ == "__main__":
    print("=== 回溯算法示例 ===\n")
    
    # 全排列
    print("1. 全排列")
    perms = permute([1, 2, 3])
    print(f"[1,2,3] 的排列数: {len(perms)}\n")
    
    # 组合
    print("2. 组合")
    combs = combine(4, 2)
    print(f"从 1-4 中选 2 个的组合: {combs}\n")
    
    # N 皇后
    print("3. 4 皇后问题")
    solutions = solve_n_queens(4)
    print(f"4 皇后的解数: {len(solutions)}")
