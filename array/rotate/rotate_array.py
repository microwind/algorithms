# 旋转数组
def rotate_array(arr, d):
    n = len(arr)
    temp = arr[:d]
    arr = arr[d:] + temp
    return arr

arr = [1, 2, 3, 4, 5, 6, 7]
d = 2
arr = rotate_array(arr, d)
print("Rotated array:", arr)

"""
jarry@jarrys-MacBook-Pro rotate % python rotate_array.py
Rotated array: [3, 4, 5, 6, 7, 1, 2]
  """