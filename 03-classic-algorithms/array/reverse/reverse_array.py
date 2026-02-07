# 反转数组的函数
def reverse_array(arr):
    n = len(arr)
    # 交换数组的前后元素
    for i in range(n // 2):
        arr[i], arr[n - i - 1] = arr[n - i - 1], arr[i]

arr = [1, 2, 3, 4, 5] # 初始化数组
reverse_array(arr) # 调用反转函数
print(arr) # 输出反转后的数组