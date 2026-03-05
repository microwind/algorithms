"""
回溯算法 - 使用选择、探索、撤销模式求解问题

算法核心思想：
- 逐步构建解，每一步都进行选择
- 当发现当前路线无法继续时，撤销最后的选择并尝试其他路线
- 找到所有解或满足条件的解

关键条件：
1. 问题有多个候选解
2. 需要按某种顺序逐个构建解
3. 约束条件可以被逐步验证

时间复杂度：O(n! * n) 或更高，取决于问题
空间复杂度：O(n) 递归调用栈深度

常见应用：
- 排列问题（全排列、N皇后等）
- 组合问题（组合数、子集等）
- 路径问题（迷宫、棋盘等）
"""

# 例1: 全排列
def permute(nums):
    """
    生成列表的所有排列
    
    时间复杂度: O(n! * n)
    空间复杂度: O(n)
    
    参数:
        nums: 待排列的数字列表
    
    返回:
        包含所有排列的列表
    
    示例:
        permute([1, 2, 3]) -> [[1,2,3], [1,3,2], [2,1,3], ...]
    """
    result = []
    
    def backtrack(current):
        # 基础情况：已经用完所有元素，说明找到一个完整排列
        if len(current) == len(nums):
            result.append(current[:])
            return
        
        # 尝试每个元素作为下一个位置的候选
        for num in nums:
            if num not in current:
                # 选择：将当前元素加入排列
                current.append(num)
                # 探索：继续构建剩余排列
                backtrack(current)
                # 撤销：移除该元素，以便尝试其他候选
                current.pop()
    
    backtrack([])
    return result

# 例2: 组合
def combine(n, k):
    """
    从 1 到 n 中选择 k 个数的所有组合
    
    时间复杂度: O(C(n,k) * k)
    空间复杂度: O(k)
    
    参数:
        n: 范围的上界
        k: 需要选择的元素个数
    
    返回:
        包含所有组合的列表
    
    示例:
        combine(4, 2) -> [[1,2], [1,3], [1,4], [2,3], [2,4], [3,4]]
    """
    result = []
    
    def backtrack(start, current):
        # 基础情况：已经选了 k 个元素
        if len(current) == k:
            result.append(current[:])
            return
        
        # 探索范围 [start, n]，避免重复组合
        for i in range(start, n + 1):
            # 选择：将数字 i 加入当前组合
            current.append(i)
            # 探索：继续选择更大的数字（保证组合有序）
            backtrack(i + 1, current)
            # 撤销：移除数字 i
            current.pop()
    
    backtrack(1, [])
    return result

# 例3: N 皇后问题
def solve_n_queens(n):
    """
    在 n×n 的棋盘上放置 n 个皇后，使得它们互不攻击
    
    时间复杂度: O(n!)
    空间复杂度: O(n)
    
    参数:
        n: 棋盘大小
    
    返回:
        所有可行的皇后放置方案
    
    约束条件：
    - 每行恰好一个皇后
    - 每列恰好一个皇后
    - 任意两个皇后不在同一条对角线上
    """
    result = []
    
    # 记录已占用的列和对角线
    cols = set()
    diag1 = set()  # 左上到右下对角线：row - col
    diag2 = set()  # 右上到左下对角线：row + col
    
    def backtrack(row, current_solution):
        # 基础情况：已经放置了所有 n 个皇后
        if row == n:
            result.append([''.join(row_str) for row_str in current_solution])
            return
        
        # 尝试在当前行的每一列放置皇后
        for col in range(n):
            # 检查该位置是否合法（不与已放置的皇后冲突）
            if col not in cols and (row - col) not in diag1 and (row + col) not in diag2:
                # 选择：在 (row, col) 放置皇后
                cols.add(col)
                diag1.add(row - col)
                diag2.add(row + col)
                
                # 构建当前行的字符串表示
                row_chars = ['.' for _ in range(n)]
                row_chars[col] = 'Q'
                current_solution.append(row_chars)
                
                # 探索：在下一行放置皇后
                backtrack(row + 1, current_solution)
                
                # 撤销：移除该皇后及其标记
                current_solution.pop()
                cols.remove(col)
                diag1.remove(row - col)
                diag2.remove(row + col)
    
    backtrack(0, [])
    return result

# 例4: 括号生成
def generate_parentheses(n):
    """
    生成所有 n 对的有效括号组合
    
    时间复杂度: O(4^n / sqrt(n))（Catalan 数列）
    空间复杂度: O(n)
    
    参数:
        n: 括号对数
    
    返回:
        所有有效的括号组合
    
    示例:
        generate_parentheses(2) -> ["(())", "()()"]
    """
    result = []
    
    def backtrack(current, open_count, close_count):
        # 基础情况：生成了完整的括号字符串
        if len(current) == 2 * n:
            result.append(current)
            return
        
        # 如果还能加左括号，尝试加左括号
        if open_count < n:
            # 选择：加左括号
            backtrack(current + '(', open_count + 1, close_count)
        
        # 如果能加右括号（右括号数不能超过左括号数），尝试加右括号
        if close_count < open_count:
            # 选择：加右括号
            backtrack(current + ')', open_count, close_count + 1)
    
    backtrack('', 0, 0)
    return result

# 测试代码
if __name__ == "__main__":
    print("=" * 60)
    print("回溯算法 - 中文注释完整版")
    print("=" * 60)
    
    # 测试排列
    print("\n1. 全排列测试")
    nums = [1, 2, 3]
    perms = permute(nums)
    print(f"   输入: {nums}")
    print(f"   结果数: {len(perms)}")
    print(f"   前三个: {perms[:3]}")
    
    # 测试组合
    print("\n2. 组合测试")
    combs = combine(4, 2)
    print(f"   C(4, 2) 的所有组合:")
    for comb in combs:
        print(f"      {comb}")
    
    # 测试 N 皇后
    print("\n3. 4-皇后问题")
    queens = solve_n_queens(4)
    print(f"   找到 {len(queens)} 个解")
    
    # 测试括号生成
    print("\n4. 括号生成")
    parens = generate_parentheses(2)
    print(f"   2 对括号的有效组合:")
    for p in parens:
        print(f"      {p}")
    
    print("\n" + "=" * 60)
