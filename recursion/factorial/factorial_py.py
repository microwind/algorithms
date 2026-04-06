"""
递归：代码简洁，逻辑清晰，适合解决分治问题，但可能存在栈溢出风险。
循环：效率更高，避免了函数调用开销，适合解决简单迭代问题，但代码复杂度可能较高。
计算阶乘的递归思维：
n! = n * (n-1)!，直到 n=0 时返回 1 作为递归终止条件。
"""

# 计算阶乘的递归函数，相比循环，递归有时候可以更方便解决遍历的问题。
def factorial(n):
    if n == 0:
        return 1  # 递归终止条件
    return n * factorial(n - 1)  # 递归调用

# 循环版阶乘，以结果作为乘数
def factorial_iterative(n):
    result = 1
    # 从 1 到 n 依次乘以 result，更新 result 的值
    for i in range(1, n + 1):
        result *= i
    return result

"""
factorial(5) 计算过程：
factorial(5) = 5 * factorial(4)
              = 5 * (4 * factorial(3))
              = 5 * (4 * (3 * factorial(2)))
              = 5 * (4 * (3 * (2 * factorial(1))))
              = 5 * (4 * (3 * (2 * (1 * factorial(0)))))
              = 5 * 4 * 3 * 2 * 1 * 1 = 120

=======

调用过程图：
factorial(5)
   ├──> factorial(4)
   │      ├──> factorial(3)
   │      │      ├──> factorial(2)
   │      │      │      ├──> factorial(1)
   │      │      │      │      ├──> factorial(0) = 1
   │      │      │      │      ├──> 1 * 1 = 1
   │      │      │      ├──> 2 * 1 = 2
   │      │      ├──> 3 * 2 = 6
   │      ├──> 4 * 6 = 24
   ├──> 5 * 24 = 120
"""
if __name__ == "__main__":
    num = 5
    print(f"Factorial of {num} is {factorial(num)}")
    
    print(f"Recursive: Factorial of {num} is {factorial_iterative(num)}")
