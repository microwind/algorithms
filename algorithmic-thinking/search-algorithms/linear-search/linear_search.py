# 线性搜索 - Python 实现

"""
线性搜索算法
时间复杂度: O(n)
空间复杂度: O(1)
"""

def linear_search(arr, target):
    """
    线性搜索：逐个遍历数组查找目标值
    返回目标值的索引，未找到返回 -1
    """
    for i in range(len(arr)):
        if arr[i] == target:
            return i
    return -1

def linear_search_all(arr, target):
    """
    查找数组中所有等于目标值的索引
    返回索引列表
    """
    indices = []
    for i in range(len(arr)):
        if arr[i] == target:
            indices.append(i)
    return indices

def linear_search_with_condition(arr, condition):
    """
    根据条件函数查找第一个满足条件的元素
    condition: 接收元素，返回 True/False 的函数
    """
    for i in range(len(arr)):
        if condition(arr[i]):
            return i
    return -1

if __name__ == "__main__":
    print("=" * 50)
    print("线性搜索 - Python 实现")
    print("=" * 50)
    
    # 测试用例 1
    print("\n测试 1: 查找单个元素")
    arr = [5, 2, 8, 1, 9, 3, 7]
    target = 8
    result = linear_search(arr, target)
    print(f"数组: {arr}")
    print(f"查找: {target}")
    print(f"结果: {result}")
    
    # 测试用例 2
    print("\n测试 2: 查找不存在的元素")
    target = 10
    result = linear_search(arr, target)
    print(f"查找: {target}")
    print(f"结果: {result}")
    
    # 测试用例 3
    print("\n测试 3: 查找所有匹配元素")
    arr = [1, 2, 3, 2, 4, 2, 5]
    target = 2
    results = linear_search_all(arr, target)
    print(f"数组: {arr}")
    print(f"查找所有 {target}: {results}")
    
    # 测试用例 4
    print("\n测试 4: 条件查找")
    arr = [1, 2, 3, 4, 5, 6, 7, 8]
    result = linear_search_with_condition(arr, lambda x: x > 5)
    print(f"数组: {arr}")
    print(f"查找第一个 > 5 的元素")
    print(f"结果: {result} (值: {arr[result] if result != -1 else '未找到'})")
    
    print("\n" + "=" * 50)
