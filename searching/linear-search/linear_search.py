"""
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
"""

"""
搜索算法 - 线性查找 (Linear Search)
最简单的搜索算法，逐个遍历查找目标元素
"""


def linear_search(arr, target):
    """
    线性查找算法
    时间复杂度: O(n)
    空间复杂度: O(1)
    
    参数:
        arr: 待搜索的列表
        target: 目标元素
    返回:
        找到返回索引，未找到返回-1
    """
    for i in range(len(arr)):
        if arr[i] == target:
            return i
    return -1


def linear_search_all(arr, target):
    """
    查找所有匹配元素的位置
    返回所有匹配项的索引列表
    """
    result = []
    for i in range(len(arr)):
        if arr[i] == target:
            result.append(i)
    return result


# 测试示例
if __name__ == "__main__":
    test_array = [64, 34, 25, 12, 22, 11, 90, 22]
    target = 22
    
    print("=" * 50)
    print("线性查找 (Linear Search)")
    print("=" * 50)
    
    print(f"\n数组: {test_array}")
    print(f"目标元素: {target}")
    
    # 查找第一个匹配
    index = linear_search(test_array, target)
    if index != -1:
        print(f"第一个匹配位置: 索引 {index}")
    else:
        print("未找到元素")
    
    # 查找所有匹配
    all_indices = linear_search_all(test_array, target)
    print(f"所有匹配位置: {all_indices}")
    
    # 查找不存在的元素
    not_found = linear_search(test_array, 100)
    print(f"查找100: {'找到' if not_found != -1 else '未找到'}")
