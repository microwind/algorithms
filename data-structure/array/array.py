# 定义一个包含5个整数的数组（列表）
arr = [1, 2, 3, 4, 5]

# 访问数组元素
print("Element at index 2:", arr[2])

# 修改数组元素
arr[2] = 10
print("Modified element at index 2:", arr[2])

# 遍历数组
for i in arr:
    print(i, end=" ")
print()

"""jarry@MacBook-Pro array % python -V
Python 3.9.6
jarry@MacBook-Pro array % python array.py
Element at index 2: 3
Modified element at index 2: 10
1 2 10 4 5 
"""
