"""
阶乘递归示例
n! = n × (n-1) × (n-2) × ... × 1
"""

# 方法1: 递归版本
def factorial_recursive(n):
    """递归计算阶乘，O(n) 时间复杂度，O(n) 空间复杂度"""
    if n <= 1:
        return 1
    return n * factorial_recursive(n - 1)

# 方法2: 迭代版本
def factorial_iterative(n):
    """迭代计算阶乘，O(n) 时间复杂度，O(1) 空间复杂度"""
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result

# 方法3: 尾递归（Python 不优化尾递归）
def factorial_tail(n, acc=1):
    """尾递归版本"""
    if n <= 1:
        return acc
    return factorial_tail(n - 1, n * acc)

if __name__ == "__main__":
    print("=== 阶乘计算 ===\n")
    
    for n in [5, 10, 20]:
        print(f"{n}! = {factorial_recursive(n)}")
