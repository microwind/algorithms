#!/usr/bin/env python
# -*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time


def find(str, text):
    text_len = len(text)
    str_len = len(str)
    # 两个循环，外层是被查找文本，内循环是查找字符串
    for i in range(text_len):
        j = 0
        while j < str_len:
            # 当遇到不有不相等时，跳出从文本下一个字符开始比较
            if str[j] != text[i + j]:
                break
            j += 1
        # 如果查找字符串全部比较完成表示成功匹配
        if j == str_len:
            return i

    # 如果文本全部比较完还是没有查找到，则返回-1
    return -1


def find2(str, text):
    text_len = len(text)
    str_len = len(str)
    # 两个循环，外层是被查找文本，内循环是查找字符串
    l = text_len - str_len + 1
    for i in range(l):
        for j in range(str_len):
            # 循环长度优化+剩余字符优化
            if text_len - i < str_len - j:
                return -1
            if str[j] != text[i + j]:
                break
            j += 1
        # 如果查找字符串全部比较完成表示成功匹配
        if j == str_len:
            return i
    # 如果文本全部比较完还是没有查找到，则返回-1
    return -1


start_time = time.time()
result = find('ABC', 'AABABC')  # 3
print("find('ABC', 'AABABC')", result)
result = find('AAB', 'AAAABC')  # 2
print("find('AAB', 'AAAABC')", result)
result = find('ABC', 'AABAC')  # -1
print("find('ABC', 'AABAC')", result)
print("time:" + str((time.time() - start_time) * 1000) + " ms")

start_time = time.time()
result = find2('ABC', 'AABABC')  # 3
print("find2('ABC', 'AABABC')", result)
result = find2('AAB', 'AAAABC')  # 2
print("find2('AAB', 'AAAABC')", result)
result = find2('ABC', 'AABAC')  # -1
print("find2('ABC', 'AABAC')", result)
print("time:" + str((time.time() - start_time) * 1000) + " ms")

"""
jarry@jarrys-MacBook-Pro nativesearch % python string_search.py
("find('ABC', 'AABABC')", 3)
("find('AAB', 'AAAABC')", 2)
("find('ABC', 'AABAC')", -1)
time:0.0531673431396 ms
("find2('ABC', 'AABABC')", 3)
("find2('AAB', 'AAAABC')", 2)
("find2('ABC', 'AABAC')", -1)
time:0.0209808349609 ms
"""
