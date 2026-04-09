# Copyright © https://github.com/microwind All rights reserved.
# @author: jarryli@gmail.com
# @version: 1.0

"""
递归排序算法示例 - 归并排序

算法特点：
- 分治法将数组分成两半
- 递归排序后合并
- 时间复杂度: O(n log n)，空间复杂度: O(n)

学习重点：理解递归在排序算法中的应用
"""

def merge(left, right):
    """
    合并两个有序数组
    时间复杂度: O(n)，空间复杂度: O(n)
    @param left 左数组
    @param right 右数组
    @return 合并后的有序数组
    """
    result = []
    i = j = 0
    
    # 比较并合并
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    
    # 添加剩余元素
    result.extend(left[i:])
    result.extend(right[j:])
    
    return result

def merge_sort(arr):
    """
    递归归并排序
    时间复杂度: O(n log n)，空间复杂度: O(n)
    @param arr 要排序的数组
    @return 排序后的数组
    """
    # 基本情况：单个元素或空数组
    if len(arr) <= 1:
        return arr
    
    # 分治：将数组分成两半
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    
    # 递归排序并合并
    left_sorted = merge_sort(left_half)
    right_sorted = merge_sort(right_half)
    
    return merge(left_sorted, right_sorted)

# 主函数 - 测试归并排序
def main():
    # 测试1：普通数组
    test_array = [64, 34, 25, 12, 22, 11, 90, 88]
    print("1. 递归归并排序:")
    print(f"   原数组: {test_array}")
    sorted_array = merge_sort(test_array)
    print(f"   排序后: {sorted_array}")
    print("===")
    
    # 测试2：已排序数组
    sorted_input = [1, 2, 3, 4, 5, 6, 7, 8]
    print("2. 边界测试 - 已排序数组:")
    print(f"   原数组: {sorted_input}")
    sorted_result = merge_sort(sorted_input)
    print(f"   排序后: {sorted_result}")
    print("===")
    
    # 测试3：单个元素
    single_element = [42]
    print("3. 边界测试 - 单个元素:")
    print(f"   原数组: {single_element}")
    single_result = merge_sort(single_element)
    print(f"   排序后: {single_result}")
    print("===")
    
    # 测试4：空数组
    empty_array = []
    print("4. 边界测试 - 空数组:")
    print(f"   原数组: {empty_array}")
    empty_result = merge_sort(empty_array)
    print(f"   排序后: {empty_result}")
    print("===")

# 打印结果
"""
jarry@Mac sorting-recursion % python merge_sort.py
1. 递归归并排序:
   原数组: [64, 34, 25, 12, 22, 11, 90, 88]
   排序后: [11, 12, 22, 25, 34, 64, 88, 90]
===
2. 边界测试 - 已排序数组:
   原数组: [1, 2, 3, 4, 5, 6, 7, 8]
   排序后: [1, 2, 3, 4, 5, 6, 7, 8]
===
3. 边界测试 - 单个元素:
   原数组: [42]
   排序后: [42]
===
4. 边界测试 - 空数组:
   原数组: []
   排序后: []
===
"""

if __name__ == "__main__":
    main()
