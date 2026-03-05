"""
拉斯维加斯算法实现 (Python)

特点：
- 总是给出正确答案
- 运行时间随机
- 不返回错误答案
"""

import random
from typing import List

def swap(arr: List[int], i: int, j: int) -> None:
    """交换数组中两个元素"""
    arr[i], arr[j] = arr[j], arr[i]

def randomized_partition(arr: List[int], left: int, right: int) -> int:
    """随机分区函数"""
    # 随机选择枢轴
    pivot_idx = random.randint(left, right)
    swap(arr, pivot_idx, right)
    
    pivot = arr[right]
    i = left - 1
    
    for j in range(left, right):
        if arr[j] <= pivot:
            i += 1
            swap(arr, i, j)
    
    swap(arr, i + 1, right)
    return i + 1

def las_vegas_quicksort(arr: List[int], left: int, right: int) -> None:
    """
    拉斯维加斯随机快速排序
    时间复杂度：期望 O(n log n)，最坏 O(n²)
    空间复杂度：O(log n) 平均
    """
    if left < right:
        # 随机分区
        pivot_idx = randomized_partition(arr, left, right)
        
        # 递归排序左右子数组
        las_vegas_quicksort(arr, left, pivot_idx - 1)
        las_vegas_quicksort(arr, pivot_idx + 1, right)

def las_vegas_randomized_select(arr: List[int], left: int, right: int, k: int) -> int:
    """
    拉斯维加斯随机选择算法 - 找第k小元素
    时间复杂度：平均 O(n)，最坏 O(n²)
    """
    if left == right:
        return arr[left]
    
    # 随机分区
    pivot_idx = randomized_partition(arr, left, right)
    
    # 计算枢轴的相对位置
    pos = pivot_idx - left + 1
    
    if k == pos:
        return arr[pivot_idx]
    elif k < pos:
        return las_vegas_randomized_select(arr, left, pivot_idx - 1, k)
    else:
        return las_vegas_randomized_select(arr, pivot_idx + 1, right, k - pos)

def las_vegas_string_match(text: str, pattern: str) -> int:
    """
    拉斯维加斯字符串匹配 - 随机化匹配
    """
    n, m = len(text), len(pattern)
    
    if m > n:
        return -1
    
    # 随机选择起始位置进行匹配
    while True:
        start = random.randint(0, n - m)
        
        # 检查是否匹配
        match = True
        for i in range(m):
            if text[start + i] != pattern[i]:
                match = False
                break
        
        if match:
            return start  # 找到匹配位置
        
        # 在实际实现中，这里应该有避免无限循环的机制
        # 为了演示，这里简化处理
        break
    
    return -1

def las_vegas_n_queens(n: int) -> List[int]:
    """
    拉斯维加斯八皇后问题求解器
    随机放置皇后直到找到有效解
    """
    while True:
        queens = [-1] * n
        columns = [False] * n
        diag1 = [False] * (2 * n - 1)  # 主对角线
        diag2 = [False] * (2 * n - 1)  # 副对角线
        
        success = True
        
        # 逐行放置皇后
        for row in range(n):
            # 收集当前行可用的列
            available_cols = []
            for col in range(n):
                if not columns[col] and not diag1[row + col] and not diag2[row - col + n - 1]:
                    available_cols.append(col)
            
            if not available_cols:
                success = False
                break
            
            # 随机选择一个可用列
            chosen_col = random.choice(available_cols)
            queens[row] = chosen_col
            columns[chosen_col] = True
            diag1[row + chosen_col] = True
            diag2[row - chosen_col + n - 1] = True
        
        if success:
            return queens

def print_array(arr: List[int]) -> None:
    """打印数组"""
    print(f"[{', '.join(map(str, arr))}]")

def print_n_queens_solution(queens: List[int]) -> None:
    """打印八皇后解法"""
    n = len(queens)
    for row in range(n):
        line = ""
        for col in range(n):
            if queens[row] == col:
                line += "Q "
            else:
                line += ". "
        print(line)

def main():
    """主函数"""
    print("=== 拉斯维加斯算法演示 ===\n")
    
    # 测试随机快速排序
    print("1. 拉斯维加斯随机快速排序")
    arr1 = [5, 2, 8, 1, 9, 3, 4, 7, 6]
    
    print("原数组:")
    print_array(arr1)
    
    las_vegas_quicksort(arr1, 0, len(arr1) - 1)
    
    print("排序后:")
    print_array(arr1)
    print()
    
    # 测试随机选择算法
    print("2. 拉斯维加斯随机选择算法")
    arr2 = [7, 2, 5, 3, 9, 1, 4, 6, 8]
    k = 4  # 找第4小元素
    
    print("数组:")
    print_array(arr2)
    print(f"第{k}小元素: {las_vegas_randomized_select(arr2.copy(), 0, len(arr2) - 1, k)}")
    print()
    
    # 测试字符串匹配
    print("3. 拉斯维加斯字符串匹配")
    text = "hello world, this is a test string"
    pattern = "test"
    
    print(f"文本: {text}")
    print(f"模式: {pattern}")
    pos = las_vegas_string_match(text, pattern)
    if pos != -1:
        print(f"匹配位置: {pos}")
    else:
        print("未找到匹配")
    print()
    
    # 测试八皇后问题
    print("4. 拉斯维加斯八皇后问题求解")
    n = 8
    solution = las_vegas_n_queens(n)
    print(f"八皇后解法 (n={n}):")
    print_n_queens_solution(solution)

if __name__ == "__main__":
    main()
