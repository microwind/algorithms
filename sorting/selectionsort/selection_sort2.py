"""
选择排序双向选择优化版本

算法原理：
1. 每轮同时选择最小和最大元素
2. 将最小元素放到左侧，最大元素放到右侧
3. 减少排序轮数，提高效率

## 实现步骤
1. 初始化左右边界指针
2. 外循环控制排序轮数，同时处理两端
3. 内循环在未排序区域查找最小和最大元素
4. 交换最小元素到左侧，最大元素到右侧
5. 调整边界指针

@param arr - 待排序的整数列表
@return list - 排序后的列表
"""
import time

def selection_sort(arr):
    """
    选择排序双向选择优化版本
    """
    print('selectionSort bidirectional:')
    arr_len = len(arr)
    
    for i in range(arr_len - 1):
        min_idx = i
        min_value = arr[min_idx]
        max_idx = i
        max_value = arr[max_idx]
        min_list_idx = min_idx
        max_list_idx = arr_len - 1 - i
        
        if min_list_idx == max_list_idx:
            break

        j = i + 1
        while j < arr_len - i:
            if arr[j] < min_value:
                min_idx = j
                min_value = arr[min_idx]
            elif arr[j] > max_value:
                max_idx = j
                max_value = arr[max_idx]
            j += 1

        if arr[min_idx] == arr[min_list_idx] and arr[max_idx] == arr[max_list_idx]:
            continue

        print(" i=", i, " j=", j, " min=", min_value, " max=", max_value, " min_idx=", min_idx, " max_idx=", max_idx, " min_list_idx=", min_list_idx, " max_list_idx=", max_list_idx, " arr[]=[" + ", ".join(map(str, arr)) + "]")

        arr[min_idx], arr[min_list_idx] = arr[min_list_idx], arr[min_idx]
        
        if arr[min_idx] == max_value:
            max_idx = min_idx
        
        arr[max_idx], arr[max_list_idx] = arr[max_list_idx], arr[max_idx]
    
    return arr

# 测试数据
test_data = [7, 11, 9, 10, 12, 13, 8]

# 性能测试方法
def performance_test(sort_function, data, version_name):
    test_arr = data.copy()
    print(f"{version_name}原始数组: {test_arr}")
    
    start_time = time.time()
    result = sort_function(test_arr)
    end_time = time.time()
    
    print(f"{version_name}: {(end_time - start_time) * 1000:.3f}ms")
    print(f"{version_name}排序结果: {result}")
    print()

if __name__ == '__main__':
    # 测试：双向选择优化版本
    performance_test(selection_sort, test_data, "双向选择优化版本")

    print("=== 算法对比总结 ===")
    print("1. 双向选择优化版本：同时选择最大最小，效率提升")

"""打印结果
jarry@Mac selectionsort % python selection_sort2.py 
双向选择优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort bidirectional:
 i= 0  j= 7  min= 7  max= 13  min_idx= 0  max_idx= 5  min_list_idx= 0  max_list_idx= 6  arr[]=[7, 11, 9, 10, 12, 13, 8]
 i= 1  j= 6  min= 8  max= 12  min_idx= 5  max_idx= 4  min_list_idx= 1  max_list_idx= 5  arr[]=[7, 11, 9, 10, 12, 8, 13]
双向选择优化版本: 0.014ms
双向选择优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 双向选择优化版本：同时选择最大最小，效率提升
"""