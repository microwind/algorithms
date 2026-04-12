"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 合并有序数组算法 - Python实现

算法原理：
从两个数组的末尾开始向前合并。使用三个指针：
- i: 指向nums1有效元素的末尾
- j: 指向nums2的末尾
- k: 指向合并后数组的末尾

每次比较nums1[i]和nums2[j]，将较大的放到nums1[k]位置。
这样可以避免覆盖nums1中未处理的元素。

时间复杂度：O(m+n) - m和n分别是两个数组的长度
空间复杂度：O(1) - 原地合并
"""


def merge_sorted_array(nums1, m, nums2, n):
    """
    合并两个有序数组
    
    参数：
        nums1 - 第一个数组（足够空间容纳两个数组元素）
        m - nums1中有效元素数量
        nums2 - 第二个数组
        n - nums2中元素数量
    """
    # 从末尾开始合并
    i = m - 1        # nums1有效元素末尾
    j = n - 1        # nums2末尾
    k = m + n - 1    # 合并后数组末尾

    # 当nums2还有元素时
    while j >= 0:
        # 如果nums1还有元素且nums1[i]大于nums2[j]
        if i >= 0 and nums1[i] > nums2[j]:
            nums1[k] = nums1[i]
            i -= 1
        else:
            nums1[k] = nums2[j]
            j -= 1
        k -= 1
    # nums1剩余元素已经在正确位置，无需处理


def print_array(nums, size):
    """打印数组"""
    print("[", end="")
    for i in range(size):
        print(nums[i], end="")
        if i < size - 1:
            print(", ", end="")
    print("]")


if __name__ == '__main__':
    nums1 = [1, 2, 3, 0, 0, 0]
    nums2 = [2, 5, 6]
    m = 3
    n = 3

    print("nums1: ", end="")
    print_array(nums1, m)
    print("nums2: ", end="")
    print_array(nums2, n)

    merge_sorted_array(nums1, m, nums2, n)

    print("合并后: ", end="")
    print_array(nums1, m + n)

"""
输出结果：
nums1: [1, 2, 3]
nums2: [2, 5, 6]
合并后: [1, 2, 2, 3, 5, 6]
"""
