import time

"""
本模块展示普通递归与尾递归的区别
1. 普通递归：递归调用后仍有计算操作，需要保留当前栈帧
2. 尾递归：最后一步是递归调用，无后续操作
"""

def factorial(n, accumulator):
    """
    普通递归计算阶乘
    
    参数:
        n: 待计算阶乘的整数
        accumulator: 用于跟踪中间结果
        
    返回:
        int: 阶乘计算结果
    """
    print(f"\ncurrent number: {n}, accumulator: {accumulator}")
    
    # 递归终止条件
    if n <= 1:
        return 1
    
    # 递归调用后还有乘法操作，不是尾递归
    return n * factorial(n - 1, n * accumulator)

def tail_factorial(n, accumulator):
    """
    尾递归计算阶乘
    
    参数:
        n: 待计算阶乘的整数
        accumulator: 累加器，用于存储中间计算结果
        
    返回:
        int: 阶乘计算结果
    """
    print(f"\ncurrent number: {n}, accumulator: {accumulator}")
    
    # 递归终止条件
    if n <= 1:
        return accumulator
    
    # 最后一步是递归调用，无其他操作，符合尾递归特征
    return tail_factorial(n - 1, n * accumulator)

def factorial_tail(n):
    """尾递归包装函数，提供更友好的接口"""
    return tail_factorial(n, 1)

if __name__ == "__main__":
    # 测试普通递归
    start_time = time.perf_counter()
    print(f"\nfactorial(5) result: {factorial(5, 1)}")
    elapsed_time = (time.perf_counter() - start_time) * 1000  # 转换为毫秒
    print(f"time: {elapsed_time:.6f} ms.")
    
    # 测试尾递归
    start_time2 = time.perf_counter()
    print("\n===============")
    print(f"\nfactorial_tail(5) result: {factorial_tail(5)}")
    elapsed_time2 = (time.perf_counter() - start_time2) * 1000
    print(f"time: {elapsed_time2:.6f} ms.")
  

"""
jarry@Mac tail-recursion % python tail_factorial.py

current number: 5, accumulator: 1

current number: 4, accumulator: 5

current number: 3, accumulator: 20

current number: 2, accumulator: 60

current number: 1, accumulator: 120

factorial(5) result: 120
time: 0.019584 ms.

===============

current number: 5, accumulator: 1

current number: 4, accumulator: 5

current number: 3, accumulator: 20

current number: 2, accumulator: 60

current number: 1, accumulator: 120

factorial_tail(5) result: 120
time: 0.008708 ms.
  """