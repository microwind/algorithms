"""
递归算法示例集合

递归是一种程序设计技巧，在函数中调用自己来解决问题。
特点：
- 必须有基本情况（停止条件）
- 必须向基本情况发展
- 时间复杂度和空间复杂度需要分析
"""

# 1. 阶乘 (Factorial)
# 时间复杂度: O(n), 空间复杂度: O(n)（递归栈深度）
def factorial(n):
    """计算 n 的阶乘"""
    if n <= 1:
        return 1
    return n * factorial(n - 1)

# 2. 斐波那契数列
# 普通递归: 时间复杂度 O(2^n)，空间复杂度 O(n)
def fibonacci(n):
    """计算斐波那契数列第 n 项（普通递归）"""
    if n <= 1:
        return n
    return fibonacci(n - 1) + fibonacci(n - 2)

# 优化版本（记忆化）
def fibonacci_memo(n, memo=None):
    """计算斐波那契数列第 n 项（带记忆化）"""
    if memo is None:
        memo = {}
    
    if n in memo:
        return memo[n]
    
    if n <= 1:
        return n
    
    memo[n] = fibonacci_memo(n - 1, memo) + fibonacci_memo(n - 2, memo)
    return memo[n]

# 3. 汉诺塔问题
# 时间复杂度: O(2^n - 1)，空间复杂度: O(n)
def hanoi(n, source, target, auxiliary):
    """
    解决汉诺塔问题
    将 n 个盘子从 source 柱移动到 target 柱
    """
    if n == 1:
        print(f"Move disk 1 from {source} to {target}")
        return
    
    # 将 n-1 个盘子从 source 移动到 auxiliary
    hanoi(n - 1, source, auxiliary, target)
    
    # 将最后一个盘子从 source 移动到 target
    print(f"Move disk {n} from {source} to {target}")
    
    # 将 n-1 个盘子从 auxiliary 移动到 target
    hanoi(n - 1, auxiliary, target, source)

# 4. 二分查找（递归版本）
# 时间复杂度: O(log n)，空间复杂度: O(log n)
def binary_search(arr, target, low, high):
    """在排序数组中递归查找目标值"""
    if low > high:
        return -1
    
    mid = (low + high) // 2
    
    if arr[mid] == target:
        return mid
    elif arr[mid] > target:
        return binary_search(arr, target, low, mid - 1)
    else:
        return binary_search(arr, target, mid + 1, high)

# 5. 数组求和
# 时间复杂度: O(n)，空间复杂度: O(n)
def array_sum(arr):
    """递归计算数组元素和"""
    if len(arr) == 0:
        return 0
    return arr[0] + array_sum(arr[1:])

# 6. 反转字符串
# 时间复杂度: O(n)，空间复杂度: O(n)
def reverse_string(s):
    """递归反转字符串"""
    if len(s) == 0:
        return ""
    return reverse_string(s[1:]) + s[0]

# 测试代码
if __name__ == "__main__":
    print("=== 递归算法测试 ===\n")
    
    # 测试阶乘
    print("1. 阶乘")
    print(f"5! = {factorial(5)}")
    
    # 测试斐波那契
    print("\n2. 斐波那契数列")
    print(f"fib(10) = {fibonacci(10)}")
    print(f"fib(10) with memo = {fibonacci_memo(10)}")
    
    # 测试汉诺塔
    print("\n3. 汉诺塔问题 (n=3)")
    hanoi(3, 'A', 'C', 'B')
    
    # 测试二分查找
    print("\n4. 二分查找")
    arr = [1, 3, 5, 7, 9, 11, 13]
    print(f"查找 7: 索引 = {binary_search(arr, 7, 0, len(arr)-1)}")
    
    # 测试数组求和
    print("\n5. 数组求和")
    print(f"sum([1,2,3,4,5]) = {array_sum([1,2,3,4,5])}")
    
    # 测试字符串反转
    print("\n6. 字符串反转")
    print(f"reverse('hello') = {reverse_string('hello')}")
