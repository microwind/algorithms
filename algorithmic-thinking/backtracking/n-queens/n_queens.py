"""
使用回溯算法的N皇后问题

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
- 同列：检查列数组
- 对角线（左上到右下）：检查row - col是否相同
- 对角线（右上到左下）：检查row + col是否相同

时间复杂度：O(n!) - 指数级，很多分支被剪枝
空间复杂度：O(n) - 递归深度 + 列/对角线跟踪

示例:
    solveNQueens(4) 返回2个解（有2种方式放置4个皇后）
"""

def solve_n_queens(n):
    """
    使用回溯算法解决N皇后问题.

    参数:
        n: 棋盘大小（n个皇后放在n×n棋盘上）

    返回:
        解决方案列表，每个解决方案是一个棋盘配置列表
        每个棋盘表示为一个包含'Q'和'.'的字符串列表
    """
    result = []
    board = [['.'] * n for _ in range(n)]
    cols = set()  # 跟踪包含皇后的列
    diag1 = set()  # 跟踪对角线（左上到右下）
    diag2 = set()  # 跟踪对角线（右上到左下）

    def backtrack(row):
        """
        递归地逐行放置皇后.

        参数:
            row: 当前要放置皇后的行
        """
        # 基本情况：所有皇后都已放置
        if row == n:
            # 将棋盘转换为字符串格式
            result.append([''.join(row) for row in board])
            return

        # 尝试在此行的每一列放置一个皇后
        for col in range(n):
            # 检查此列和两条对角线是否安全
            diag1_id = row - col  # 对每条对角线唯一
            diag2_id = row + col  # 对每条对角线唯一

            if col in cols or diag1_id in diag1 or diag2_id in diag2:
                # 列或对角线上已有皇后，跳过
                continue

            # 放置皇后
            board[row][col] = 'Q'
            cols.add(col)
            diag1.add(diag1_id)
            diag2.add(diag2_id)

            # 探索：尝试在剩余行放置皇后
            backtrack(row + 1)

            # 回溯：移除皇后
            board[row][col] = '.'
            cols.remove(col)
            diag1.remove(diag1_id)
            diag2.remove(diag2_id)

    backtrack(0)
    return result


def count_n_queens(n):
    """
    计算N皇后问题的解的数量.
    比存储所有解更高效.

    Time Complexity: O(n!)
    Space Complexity: O(n)
    """
    count = 0
    cols = set()
    diag1 = set()
    diag2 = set()

    def backtrack(row):
        nonlocal count

        if row == n:
            count += 1
            return

        for col in range(n):
            diag1_id = row - col
            diag2_id = row + col

            if col in cols or diag1_id in diag1 or diag2_id in diag2:
                continue

            cols.add(col)
            diag1.add(diag1_id)
            diag2.add(diag2_id)

            backtrack(row + 1)

            cols.remove(col)
            diag1.remove(diag1_id)
            diag2.remove(diag2_id)

    backtrack(0)
    return count


# 测试用例
if __name__ == "__main__":
    print("=== N-Queens Problem using Backtracking ===\n")

    # 测试用例 1: 4-Queens (classic problem with 2 solutions)
    print("Test 1: solveNQueens(4)")
    result1 = solve_n_queens(4)
    print(f"Found {len(result1)} solutions:\n")
    for idx, solution in enumerate(result1, 1):
        print(f"Solution {idx}:")
        for row in solution:
            print(f"  {row}")
        print()

    # 测试用例 2: 1-Queen (trivial case)
    print("Test 2: solveNQueens(1)")
    result2 = solve_n_queens(1)
    print(f"Found {len(result2)} solution(s):\n")
    for idx, solution in enumerate(result2, 1):
        print(f"Solution {idx}:")
        for row in solution:
            print(f"  {row}")
        print()

    # 测试用例 3: 8-Queens (classic problem with 92 solutions)
    print("Test 3: countNQueens(8)")
    count3 = count_n_queens(8)
    print(f"Found {count3} solutions for 8-Queens\n")

    # 测试用例 4: Various sizes
    print("Test 4: Solution counts for various N:")
    for n in range(1, 9):
        count = count_n_queens(n)
        print(f"  N={n}: {count} solutions")
    print()

    # 测试用例 5: 5-Queens
    print("Test 5: solveNQueens(5)")
    result5 = solve_n_queens(5)
    print(f"Found {len(result5)} solutions for 5-Queens")
    print("First solution:")
    for row in result5[0]:
        print(f"  {row}")
