"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 两数之和算法 - Python实现

算法原理：
使用哈希表辅助查找。遍历数组时，对于每个元素，计算目标值与当前元素的差值（补数），
检查补数是否已在哈希表中。如果在，则找到答案；否则将当前元素存入哈希表。

时间复杂度：O(n) - 只需遍历数组一次
空间复杂度：O(n) - 哈希表存储
"""


def two_sum(nums, target):
    """
    两数之和
    使用哈希表查找补数
    
    参数：
        nums - 输入数组
        target - 目标和
    
    返回：
        两个数的索引数组
    """
    seen = {}  # 哈希表，存储元素值到索引的映射
    for i, num in enumerate(nums):
        need = target - num  # 计算补数
        # 检查补数是否已在哈希表中
        if need in seen:
            return [seen[need], i]  # 找到答案，返回两个索引
        seen[num] = i  # 将当前元素存入哈希表
    return []  # 未找到答案


if __name__ == '__main__':
    nums = [2, 7, 11, 15]
    target = 9
    
    result = two_sum(nums, target)
    
    if len(result) > 0:
        print(f"目标值: {target}")
        print(f"结果索引: [{result[0]}, {result[1]}]")
        print(f"对应数值: {nums[result[0]]} + {nums[result[1]]} = {target}")
    else:
        print("未找到答案")

"""
输出结果：
目标值: 9
结果索引: [0, 1]
对应数值: 2 + 7 = 9
"""
