#!/usr/bin/env python
# -*- encoding: UTF-8 -*-
"""
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""

"""
合并两个已排序数组算法实现
提供三种不同的合并策略，适合不同场景和性能需求

算法思路：
1. 双指针法：同时遍历两个数组，逐个比较并合并
2. 插入法：将一个数组的元素逐个插入到另一个数组中
3. 合并排序法：先合并数组再进行排序

时间复杂度：O(n+m) - 双指针法最优
空间复杂度：O(n+m) - 需要额外空间存储结果
稳定性：稳定 - 保持相等元素的相对位置
"""

import time

"""
合并两个已排序数组 - 双指针法

算法思路：
使用两个指针分别指向两个数组的起始位置，同时遍历比较
将较小的元素放入结果数组，并移动相应指针，直到其中一个数组遍历完成
最后将剩余数组元素直接复制到结果数组中

步骤说明：
1. 初始化结果数组和指针
2. 同时遍历两个数组，比较并合并
3. 处理剩余元素

关键点：
- 使用三个指针分别跟踪两个输入数组和一个结果数组
- 比较当前元素，选择较小的放入结果数组
- 保持算法的稳定性

时间复杂度：O(n+m) - 每个元素只被访问一次
空间复杂度：O(n+m) - 需要额外空间存储结果
稳定性：稳定 - 保持相等元素的相对位置

@param list one: 第一个已排序数组
@param list two: 第二个已排序数组
@return list: 合并后的有序数组
"""


def merge_sorted1(one, two):
    # 步骤1：初始化结果数组和指针
    # 关键点：结果数组长度为两个数组长度之和
    i = j = k = 0
    one_len = len(one)
    two_len = len(two)
    result = [None] * (one_len + two_len)

    # 步骤2：同时遍历两个数组，比较并合并
    # 关键点：当两个数组都还有元素时继续比较
    while i < one_len and j < two_len:
        # 步骤2.1：比较当前元素并选择较小的
        # 关键点：两两比较，把小的项追加到新数组中，同时移动小的那个数组指针
        if one[i] < two[j]:
            result[k] = one[i]  # 数组1元素较小，移动到结果数组
            i += 1
        else:
            result[k] = two[j]  # 数组2元素较小，移动到结果数组
            j += 1
        k += 1

    # 步骤3：处理剩余元素
    # 关键点：将未处理完的数组元素直接复制到结果数组
    # 处理数组1剩余的项目
    while i < one_len:
        result[k] = one[i]  # 直接追加剩余元素
        k += 1
        i += 1

    # 处理数组2剩余的项目
    while j < two_len:
        result[k] = two[j]  # 直接追加剩余元素
        k += 1
        j += 1

    return result


"""
合并两个已排序数组 - 插入法

算法思路：
将一个数组的元素逐个插入到另一个数组中
利用Python的insert动态插入特性，在找到合适位置后插入元素

步骤说明：
1. 遍历第一个数组的每个元素
2. 在第二个数组中找到插入位置
3. 插入元素并移动后续元素

关键点：
- 利用Python的insert动态插入特性
- 需要移动后续元素，时间复杂度较高
- 原地操作，空间复杂度低

时间复杂度：O(n*m) - 最坏情况下每个元素需要遍历整个第二个数组
空间复杂度：O(1) - 在原数组基础上操作
稳定性：稳定 - 保持相等元素的相对位置

@param list one: 第一个已排序数组
@param list two: 第二个已排序数组
@return list: 合并后的有序数组
"""


def merge_sorted2(one, two):
    # 步骤1：初始化变量
    # 关键点：获取数组长度，用于边界检查
    one_len = len(one)
    two_len = len(two)
    
    # 步骤2：遍历第一个数组的每个元素
    # 关键点：将每个元素插入到第二个数组合适位置
    for i in range(one_len):
        # 步骤2.1：在第二个数组中找到插入位置
        # 关键点：遍历第二个数组，找到第一个大于等于当前元素的位置
        inserted = False
        for j in range(two_len):
            # 步骤2.2：比较并插入
            # 关键点：如果当前元素小于数组2的成员项，则插入到数组2中
            if one[i] < two[j]:
                # 步骤2.2.1：插入元素
                # 关键点：使用insert在指定位置插入元素
                two.insert(j, one[i])
                two_len += 1
                inserted = True
                break
        # 步骤2.3：处理边界情况
        # 关键点：如果没找到插入位置，添加到末尾
        if not inserted:
            two.append(one[i])
            two_len += 1

    return two


"""
合并两个已排序数组 - 合并排序法

算法思路：
先将两个数组合并成一个数组，然后使用插入排序进行排序
利用第一个数组已排序的特性，从第二个数组开始位置进行排序

步骤说明：
1. 合并两个数组
2. 从第二个数组开始位置进行插入排序
3. 逐个插入元素到已排序部分

关键点：
- 先合并后排序，实现简单
- 利用已排序部分的特性
- 使用插入排序，适合小数据量

时间复杂度：O((n+m)²) - 插入排序的时间复杂度
空间复杂度：O(n+m) - 需要额外空间存储结果
稳定性：稳定 - 插入排序保持相等元素的相对位置

@param list one: 第一个已排序数组
@param list two: 第二个已排序数组
@return list: 合并后的有序数组
"""


def merge_sorted3(one, two):
    # 步骤1：初始化变量
    # 关键点：获取数组长度，用于边界检查
    one_len = len(one)
    two_len = len(two)
    result = one + two  # Python特点：使用+运算符合并列表
    
    # 步骤2：插入排序
    # 关键点：从第二个数组开始位置进行排序，利用第一个数组已排序的特性
    for i in range(one_len, one_len + two_len):
        # 步骤2.1：逐个插入元素到已排序部分
        # 关键点：自后往前把当前项与前一项进行比较
        j = i - 1
        current = result[i]
        
        # 步骤2.2：比较并移动元素
        # 关键点：如果当前项小于已排序的项，则逐个右移1位
        while (j >= 0 and current < result[j]):
            result[j + 1] = result[j]
            j -= 1
            
        # 步骤2.3：插入元素
        # 关键点：空出位置插入比较项
        result[j + 1] = current

    return result


# ==================== 主程序：算法演示和性能测试 ====================

# 测试数据：
arr1 = [-3, 7, 9, 10, 11, 15, 16]
arr2 = [-1, 5, 6, 9, 12]

"""
性能测试辅助函数

@param function sort_func: 排序函数
@param list arr1: 第一个测试数组
@param list arr2: 第二个测试数组
@param str name: 测试名称
"""
def performance_test(sort_func, arr1, arr2, name):
    print(f"\n=== {name} ===")
    print("原始数组1:", arr1)
    print("原始数组2:", arr2)
    
    # 开始计时
    start_time = time.time()
    result = sort_func(arr1.copy(), arr2.copy())
    elapsed_time = (time.time() - start_time) * 1000
    
    print(f"排序耗时: {elapsed_time:.3f}ms")
    print("合并结果:", result)

if __name__ == '__main__':
    # 测试1：双指针法
    performance_test(merge_sorted1, arr1, arr2, 'merge_sorted1 双指针法')

    # 测试2：插入法
    performance_test(merge_sorted2, arr1, arr2, 'merge_sorted2 插入法')

    # 测试3：合并排序法
    performance_test(merge_sorted3, arr1, arr2, 'merge_sorted3 合并排序法')

    print("\n=== 算法对比总结 ===")
    print("1. 双指针法：时间复杂度O(n+m)，空间复杂度O(n+m)，最优选择")
    print("2. 插入法：时间复杂度O(n*m)，空间复杂度O(1)，适合小数据量")
    print("3. 合并排序法：时间复杂度O((n+m)²)，空间复杂度O(n+m)，逻辑简单")


"""
2. 插入法：时间复杂度O(n*m)，空间复杂度O(1)，适合小数据量
3. 合并排序法：时间复杂度O((n+m)²)，空间复杂度O(n+m)，逻辑简单
jarry@Mac mergesort % clear
jarry@Mac mergesort % python merge_sorted_array.py 

=== merge_sorted1 双指针法 ===
原始数组1: [-3, 7, 9, 10, 11, 15, 16]
原始数组2: [-1, 5, 6, 9, 12]
排序耗时: 0.003ms
合并结果: [-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16]

=== merge_sorted2 插入法 ===
原始数组1: [-3, 7, 9, 10, 11, 15, 16]
原始数组2: [-1, 5, 6, 9, 12]
排序耗时: 0.005ms
合并结果: [-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16]

=== merge_sorted3 合并排序法 ===
原始数组1: [-3, 7, 9, 10, 11, 15, 16]
原始数组2: [-1, 5, 6, 9, 12]
排序耗时: 0.003ms
合并结果: [-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16]

=== 算法对比总结 ===
1. 双指针法：时间复杂度O(n+m)，空间复杂度O(n+m)，最优选择
2. 插入法：时间复杂度O(n*m)，空间复杂度O(1)，适合小数据量
3. 合并排序法：时间复杂度O((n+m)²)，空间复杂度O(n+m)，逻辑简单
"""