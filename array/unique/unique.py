#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 数组去重算法 - Python实现

算法原理：
- 通过比较元素，找出数组中只出现一次的元素
- 移除或跳过重复出现的元素
- 保留元素的相对顺序（取决于具体实现）

本文件提供20种不同的去重实现：
- 方法1-5: 新建列表，检查是否包含
- 方法6-7: 在原列表上删除重复项
- 方法8: 使用index比较
- 方法9-10: 使用字典去重
- 方法11-13: 使用filter、map等高阶函数
- 方法14: 使用set数据结构
- 方法15-16: 排序后去重
- 方法17: 使用reduce函数
- 方法18: 使用numpy库
- 方法19-20: 使用递归

时间复杂度:
- 双层循环方法: O(n²)
- 排序方法: O(n log n)
- 哈希表/set方法: O(n)
空间复杂度: O(n) - 需要额外列表或字典存储

应用场景：
- 数据清洗
- 统计唯一值
- 数据库去重
"""
import time

# the multi method for list unique
# Python list去重复项的N种方法


## 1. 新建列表，如果新列表中不存在，则添加到新列表
def unique(data):
    new_list = []
    for item in data:
        if item not in new_list:
            new_list.append(item)
    return new_list


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("new_list + not in data:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 2. 新建列表。根据下标判断是否存在新列表中，如果新列表中不存在则添加到新列表
def unique(data):
    new_list = []
    for i in range(len(data)):
        if data[i] not in new_list:
            new_list.append(data[i])
    return new_list


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("for range + not in. data:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 3. 新建列表，使用列表推导来去重。是前一种的简写。
def unique(data):
    new_list = []
    [new_list.append(i) for i in data if not i in new_list]
    return new_list


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("for i in data if not i new_list:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 4. 通过index找不到该项时抛 ValueError，借此判断"未出现过"，再追加到新列表
def unique(data):
    new_list = []
    for i in range(len(data)):
        item = data[i]
        try:
            # index 找到则什么也不做；找不到会抛 ValueError，由 except 捕获
            new_list.index(item)
        except ValueError:
            new_list.append(item)
    return new_list


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("list index + except:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 5. 新建列表，两个循环。如果内循环与外循环项相同，且下标相同就添加到新列表，其余忽略
def unique(data):
    new_list = []
    for i in range(len(data)):
        j = 0
        while j <= i:
            if data[i] == data[j]:
                if i == j:
                    new_list.append(data[i])
                break
            j += 1
    return new_list


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("new list + for. data[i] == data[j] and i == j:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 6. 在原有列表上移除重复项目。自后往前遍历，逐个与前面项比较，如果值相同则移除当前项。
def unique(data):
    l = len(data)
    while (l > 0):
        l -= 1
        i = l
        while i > 0:
            i -= 1
            if data[i] == data[l]:
                del data[l]
                break
    return data


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("one list while. last -> first result. data:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 7. 在原有列表上移除重复项目。自前往后遍历，逐个与后面项比较，值相同则删除后一项
def unique(data):
    l = len(data)
    i = 0
    while i < l:
        j = i + 1
        while j < l:
            if data[i] == data[j]:
                del data[j]
                l -= 1
                # i 自减再外层自加，相当于不变；下一轮重新从 j=i+1 开始扫
                i -= 1
                break
            j += 1
        i += 1
    return data


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("one list while. first -> last result. data:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 8. 新建列表。遍历列表，利用index比较出现的位置，如果出现在第一次的位置则追加到新数组
def unique(data):
    new_list = []
    for i in range(len(data)):
        if i == data.index(data[i]):
            new_list.append(data[i])
    return new_list


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("for range + index. data:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 9. 利用字典属性唯一性来实现去重复。
def unique(data):
    obj = {}
    for item in data:
        obj[item] = item
    # Python 3 中 dict.values() 返回视图，需 list() 包一下才是列表
    return list(obj.values())


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("list + dict:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

## 10. 利用dict的fromkeys来实现去重
# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
# Python 3 中 dict.keys() 返回视图，需 list() 转为列表；其实直接 list(dict) 也行
print("dict fromkeys:", list(dict.fromkeys(data)))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 11. 利用filter函数，即把不符合条件的过滤掉。
## 这里filter不支持下标，因此需要借助外部列表存储不重复项
def uniq(item):
    if (item not in new_list):
        new_list.append(item)
        return True
    return False


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
new_list = []
# Python 3 中 filter() 返回迭代器，需 list() 才能拿到具体列表
print('filter + list + not in: ', list(filter(uniq, data)))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 12. 利用字典结合过滤来实现去重复。
def unique(item):
    # 用 is None 判断更符合 Python 风格；== None 在某些类型上会被覆写
    if obj.get(item) is None:
        obj[item] = item
        return True
    return False


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
obj = {}
print("filter + dict + get:", list(filter(unique, data)))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 13. 利用map来实现去重复。与map与filter类似，是一个高阶函数。可以针对其中项逐个修改操作。
## 与filter不同map会保留原有项目，并不会删除，因此值可以改为None，然后再过滤掉。
def unique(item):
    if item not in new_list:
        new_list.append(item)
        return item
    return None


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
new_list = []
start_time = time.time()
# `is not None` 比 `!= None` 更规范；外层 list() 把迭代器物化成列表
print("list from Map:", list(filter(lambda item: item is not None, map(unique, data))))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

## 14. 利用set数据结构里key的唯一性来去重复
# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
# set 不保证顺序，每次运行结果顺序可能不同
print("from Set:", list(set(data)))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 15. 提前排序，从后向前遍历，将当前项与前一项对比，如果重复则移除当前项
def unique(data):
    # 注意 sort 要求元素可比较；这里只保留字符串避免 Py3 下 int/str 混排报错
    # 转换了data为字符串列表，确保所有元素都是字符串
    data = [x for x in data if isinstance(x, str)]
    data.sort()
    l = len(data)
    while (l > 0):
        l -= 1
        # 关键安全检查 l > 0：避免 l=0 时 data[l-1] 回环到末尾导致误删
        if l > 0 and data[l] == data[l - 1]:
            # 用 del 按下标删除，比 remove(value) 更高效（remove 还要按值线性查找）
            del data[l]
    return data


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("sort + remove:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 16. 提前排序，自前往后遍历，将当前项与后一项对比，如果重复则移除当前项
def unique(data):
    """
    在 Python 3 中：int 和 str 不能直接比较大小
    in python 3: TypeError: '<' not supported between instances of 'int' and 'str'
    need to keep the same Type of member in List
    """
    # 转换了data为整数列表，确保所有元素都是整数
    data = [x for x in data if isinstance(x, int)]
    data.sort()
    l = len(data) - 1
    i = 0
    while i < l:
        if (data[i] == data[i + 1]):
            del data[i]
            i -= 1
            l -= 1
        i += 1
    return data


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("sort+del ASE:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

## 17. 利用reduce函数来去重复。reduce具有累计的作用，判断如果不在累计结果中出现，则追加到结果中。
import functools

def unique(data):
    def foo(result, item):
        # 不在结果中则追加，否则原样返回。每次（result + [item]），开销很大
        return result if item in result else result + [item]
    # 传入初始值 []，reduce 从空列表开始累积
    # 同时也能正确处理 data 为空或只有一个元素的情况
    return functools.reduce(foo, data, [])

# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("functools.reduce:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

## 18. 利用numpy lib库. 需提前安装 `pip install numpy`
import numpy as np


def unique(data):
    res = np.array(data)
    return list(np.unique(res))


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
start_time = time.time()
print("import numpy as np.unique:", unique(data))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 19. 利用递归调用来去重复。递归自后往前逐个调用，当长度为1时终止。
## 当后一项与前任一项相同说明有重复，则删除当前项。相当于利用自我调用来替换循环
def recursion_unique(data, length):
    # 参数命名 length 而非 len，避免遮蔽内置函数 len()
    if (length <= 1):
        return data

    l = length
    last = l - 1
    is_repeat = False

    # 在 [0, last) 区间内查找是否存在与 data[last] 相同的元素
    while (l > 1):
        l -= 1
        if (data[last] == data[l - 1]):
            is_repeat = True
            break

    if (is_repeat):
        del data[last]

    # 递归处理前 length-1 项（注意 last 已可能被删，但前面的部分没变）
    return recursion_unique(data, length - 1)


# test
data = ['a', 'a', 1, 1, 2, 2, 'b', 'b', 2, 1]
# data = [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
start_time = time.time()
print("recursion_unique:", recursion_unique(data, len(data)))
print("time:" + str((time.time() - start_time) * 1000) + " ms")


## 20. 利用递归调用来去重复的另外一种方式。递归自后往前逐个调用，当长度为1时终止。
## 与上一个递归不同，这里将不重复的项目作为结果拼接起来
def recursion_unique_new(data, length):
    if (length <= 1):
        return data

    last = length - 1
    last_item = data[last]
    l = last - 1
    is_repeat = False

    # 在 [0, last) 内找一遍是否已出现过 last_item
    while (l >= 0):
        if (last_item == data[l]):
            is_repeat = True
            break
        l -= 1

    # 不论是否重复，都把末尾元素从 data 里摘掉，缩短下一轮的处理范围
    del data[last]
    # 不重复才把 last_item 加入最终结果
    result = [] if is_repeat else [last_item]

    # 递归处理剩余前缀，结果拼到尾部以保持原顺序
    return recursion_unique_new(data, length - 1) + result


# test
data = [1, 1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
start_time = time.time()
print("recursion_unique_new:", recursion_unique_new(data, len(data)))
print("time:" + str((time.time() - start_time) * 1000) + " ms")

"""
## 运行示例（Python 3）
jarry@Mac unique % python -V                  
Python 3.11.15
jarry@Mac unique % python unique.py 
new_list + not in data: ['a', 1, 2, 'b']
time:0.041961669921875 ms
for range + not in. data: ['a', 1, 2, 'b']
time:0.019788742065429688 ms
for i in data if not i new_list: ['a', 1, 2, 'b']
time:0.024080276489257812 ms
list index + except: ['a', 1, 2, 'b']
time:0.051975250244140625 ms
new list + for. data[i] == data[j] and i == j: ['a', 1, 2, 'b']
time:0.019073486328125 ms
one list while. last -> first result. data: ['a', 1, 2, 'b']
time:0.007152557373046875 ms
one list while. first -> last result. data: ['a', 1, 2, 'b']
time:0.0069141387939453125 ms
for range + index. data: ['a', 1, 2, 'b']
time:0.0059604644775390625 ms
list + dict: ['a', 1, 2, 'b']
time:0.007867813110351562 ms
dict fromkeys: ['a', 1, 2, 'b']
time:0.004291534423828125 ms
filter + list + not in:  ['a', 1, 2, 'b']
time:0.006198883056640625 ms
filter + dict + get: ['a', 1, 2, 'b']
time:0.0050067901611328125 ms
list from Map: ['a', 1, 2, 'b']
time:0.00476837158203125 ms
from Set: [1, 2, 'b', 'a']
time:0.0040531158447265625 ms
sort + remove: ['a', 'b']
time:0.036716461181640625 ms
sort+del ASE: [1, 2]
time:0.016927719116210938 ms
functools.reduce: ['a', 1, 2, 'b']
time:0.007152557373046875 ms
import numpy as np.unique: [np.str_('1'), np.str_('2'), np.str_('a'), np.str_('b')]
time:13.677120208740234 ms
recursion_unique: ['a', 1, 2, 'b']
time:0.0171661376953125 ms
recursion_unique_new: [1, 3, -1, 2, 4]
time:0.013113021850585938 ms
"""
