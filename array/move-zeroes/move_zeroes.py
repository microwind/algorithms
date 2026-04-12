"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 移动零算法 - Python实现

算法原理：
使用双指针技术。write指针记录非零元素应该写入的位置，read指针遍历数组。
当read遇到非零元素时，将其复制到write位置，然后两个指针都前进。
当read遇到零时，只前进read指针。最后将write之后的位置全部填充为零。

时间复杂度：O(n) - 单次遍历数组
空间复杂度：O(1) - 原地操作
"""


def move_zeroes(nums):
    """
    移动零到数组末尾
    
    参数：
        nums - 待处理的数组
    """
    insert_pos = 0  # 写指针，指向下一个非零元素应该存放的位置

    # 第一遍：将所有非零元素移到前面
    for num in nums:
        if num != 0:
            nums[insert_pos] = num
            insert_pos += 1

    # 第二遍：将insert_pos之后的位置填充为零
    while insert_pos < len(nums):
        nums[insert_pos] = 0
        insert_pos += 1


def print_array(nums, size):
    """打印数组"""
    print("[", end="")
    for i in range(size):
        print(nums[i], end="")
        if i < size - 1:
            print(", ", end="")
    print("]")


if __name__ == '__main__':
    nums = [0, 1, 0, 3, 12, 0, 5]

    print("原始数组: ", end="")
    print_array(nums, len(nums))

    move_zeroes(nums)

    print("移动零后: ", end="")
    print_array(nums, len(nums))

"""
输出结果：
原始数组: [0, 1, 0, 3, 12, 0, 5]
移动零后: [1, 3, 12, 5, 0, 0, 0]
"""
