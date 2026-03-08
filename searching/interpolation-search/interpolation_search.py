"""
插值查找 - Interpolation Search
适用于均匀分布的有序数组
"""


def interpolation_search(arr, target):
    """
    插值查找算法
    通过估算目标位置进行查找
    
    时间复杂度: 平均O(log log n)，最坏O(n)
    空间复杂度: O(1)
    """
    low = 0
    high = len(arr) - 1
    
    while low <= high and target >= arr[low] and target <= arr[high]:
        # 如果范围只有一个元素
        if low == high:
            if arr[low] == target:
                return low
            return -1
        
        # 计算插值位置
        # 公式: pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
        pos = low + int((target - arr[low]) / (arr[high] - arr[low]) * (high - low))
        
        if arr[pos] == target:
            return pos
        
        if arr[pos] < target:
            low = pos + 1
        else:
            high = pos - 1
    
    return -1


def interpolation_search_recursive(arr, target, low=0, high=None):
    """插值查找 - 递归实现"""
    if high is None:
        high = len(arr) - 1
    
    if low > high or target < arr[low] or target > arr[high]:
        return -1
    
    if low == high:
        return low if arr[low] == target else -1
    
    # 计算插值位置
    pos = low + int((target - arr[low]) / (arr[high] - arr[low]) * (high - low))
    
    if arr[pos] == target:
        return pos
    
    if arr[pos] < target:
        return interpolation_search_recursive(arr, target, pos + 1, high)
    else:
        return interpolation_search_recursive(arr, target, low, pos - 1)


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("插值查找 (Interpolation Search)")
    print("=" * 50)
    
    # 插值查找适用于均匀分布的数据
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    print(f"\n数组 (均匀分布): {arr}")
    
    targets = [30, 85, 10, 100]
    
    print("\n查找结果:")
    for target in targets:
        result = interpolation_search(arr, target)
        status = f"索引 {result}" if result != -1 else "未找到"
        print(f"  查找 {target}: {status}")
    
    print("\n与二分查找对比:")
    print("  • 二分查找: 总是取中间位置")
    print("  • 插值查找: 根据值估算位置")
    print("  • 对于均匀数据，插值查找更快")
    print("  • 对于非均匀数据，可能退化为线性查找")
