#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
@desc
质因数分解python语言示例
一个偶数可以 分解为若干个质数相乘。
"""
import time

def factorize1(num):
  i = 2
  result = []
  while (num > 1):
    while (num % i == 0):
      result.append(i)
      num = num / i
    i = i + 1
  print(result)

def factorize(num):
  i = 2
  result = []
  while (num >= i * i):
    while (num % i == 0):
      result.append(i)
      num = num / i
    i = i + 1
  if (num > 1):
    result.append(num)
  return result

if __name__ == '__main__':

    # 1. factorize1
    num = 20
    print(num)
    start_time = time.time()
    arr = factorize1(num)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")

    # 2. factorize2
    num = 20
    print("%d =") %(num),
    start_time = time.time()
    arr = factorize(num)
    size = len(arr)
    for i in range(size):
      print(arr[i]),
      if (i < size - 1):
        print("*"),

    print("\r\ntime:" + str((time.time() - start_time) * 1000) + " ms")

"""
jarry@jarrys-MacBook-Pro factor % python --version 
Python 2.7.16
jarry@jarrys-MacBook-Pro factor % python factor.py
20
[2, 2, 5]
time:0.014066696167 ms
20 = 2 * 2 * 5 
time:0.00905990600586 ms
*/
"""