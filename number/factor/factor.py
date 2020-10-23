#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time

class Factor:
  def factor1(self, num):
    i = 2
    result = []
    while (num > 1):
      while (num % i == 0):
        result.append(i)
        num = num / i
      i = i + 1
    print(result)

  def factor2(self, num):
    i = 2
    result = []
    while (num >= i * i):
      while (num % i == 0):
        result.append(i)
        num = num / i
      i = i + 1
    if (num > 1):
      result.append(num)
    print(result)

if __name__ == '__main__':

    # 1. factor1
    num = 20
    print(num)
    f = Factor()
    start_time = time.time()
    arr = f.factor1(num)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")

    # 2. factor2
    num = 20
    print(num)
    f = Factor()
    start_time = time.time()
    arr = f.factor2(num)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")