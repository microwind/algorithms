#!/usr/bin/env python
# -*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time


def makePMT(pattern):
    patternLen = len(pattern)
    pmt = [0]*patternLen
    for i in range(patternLen):
        # 递增取出全部模式字串。子串从第1个字符开始，每次递增1个字符，直到全部完成。
        subPattern = pattern[0:i + 1]
        j = 0
        # 共有成员长度，即部分匹配最大值
        # 将当前项与后项逐一比较
        pmtValue = 0
        prefixArr = []
        postfixArr = []
        while j < i:
            # 遍历同时得到每一个前后缀，自前往后获得每一个前缀
            prefix = subPattern[0:j + 1]
            # 自后往前获得当前的后缀
            postfix = subPattern[i - j:i + 1]
            prefixArr.append(prefix)
            postfixArr.append(postfix)
            # 比较是否有共同项，如果有则更新匹配值，如果遇到更大的则更新最大值
            if prefix == postfix and len(prefix) > pmtValue:
                pmtValue = len(prefix)
            j += 1

        # 将部分匹配最大值更新到对应位置中
        pmt[i] = pmtValue
        print(i, subPattern, ' | ', prefixArr,
              ' | ', postfixArr, ' | ', pmtValue)

    print('makePMT(:pmt:', pmt)
    return pmt


def makePMT2(pattern):
    patternLen = len(pattern)
    pmt = [0]*patternLen
    # 用于记录当前已经匹配的前缀长度
    pmtValue = 0
    # 从模式串的第二个字符开始遍历，因为PMT[0]总是0
    for i in range(1, patternLen):
        # 当前字符与已匹配前缀的下一个字符不匹配
        while pmtValue > 0 and pattern[i] != pattern[pmtValue]:
            # 使用PMT中前一个位置的值来回溯，更新pmtValue为更短的前缀长度
            pmtValue = pmt[pmtValue - 1]

        # 如果当前字符与已匹配的前缀的下一个字符匹配
        if pattern[i] == pattern[pmtValue]:
            # 增加pmtValue的值，表示前缀长度增加
            pmtValue += 1

        # 更新PMT数组
        pmt[i] = pmtValue

        # 以下为打印前后缀测试[可选]
        subPattern = pattern[0:i + 1]
        prefixArr = []
        postfixArr = []
        j = 0
        while j < i:
            prefix = pattern[0:j + 1]
            postfix = subPattern[i - j:i + 1]
            prefixArr.append(prefix)
            postfixArr.append(postfix)
            j += 1

        print(i, subPattern, ' | ', prefixArr,
              ' | ', postfixArr, ' | ', pmtValue)

    print('makePMT2 pmt:', pmt)
    return pmt


"""
查找 `pattern` 在 `text` 中出现的位置。

:param pattern: 要在文本中搜索的模式字符串。
:param text: 搜索 `pattern` 的目标文本。
:return: 如果匹配，则返回其在文本中出现的索引位置；否则返回空数组。
"""


def kmpSearch(pattern, text):
    # 输出原始的模式串和文本
    print(' pattern:', pattern, 'text:', text)

    # 用于存储匹配到的模式串在文本中的起始位置
    matches = []

    # 生成模式串的部分匹配表
    # pmtTable = makePMT(pattern)
    pmtTable = makePMT2(pattern)

    # j 是模式串的当前匹配位置
    j = 0

    # 输出生成的部分匹配表
    print('根据模式串获取pmtTable:', pmtTable)

    # 遍历文本
    for i in range(len(text)):
        # 当文本字符与模式串字符不匹配，并且模式串的当前匹配位置不是0时
        # 回到模式串的部分匹配表的前一个位置继续匹配
        while j > 0 and text[i] != pattern[j]:
            j = pmtTable[j - 1]

        # 如果文本字符与模式串字符匹配
        if text[i] == pattern[j]:
            # 继续匹配模式串的下一个字符
            j += 1

        # 如果模式串的所有字符都已匹配成功
        if j == len(pattern):
            # 将匹配到的模式串在文本中的起始位置添加到结果数组中
            matches.append(i - j + 1)

            # 根据部分匹配表，调整模式串的当前匹配位置
            j = pmtTable[j - 1]

    print('匹配结果：', matches)
    # 返回匹配结果
    return matches


# test
if __name__ == '__main__':

    start_time = time.time()
    print('KMP搜索测试：')
    pattern = 'ABCABAB'
    print('pattern:', pattern)
    makePMT(pattern)
    makePMT2(pattern)
    kmpSearch(pattern, 'AAABABCABABCDABABCABAB')  # [4, 15]
    kmpSearch(pattern, 'ABAAABABCABABCDABABCABAB')  # [6, 17]
    print("time:" + str((time.time() - start_time) * 1000) + " ms")

"""
jarry@jarrys-MacBook-Pro KMPsearch % python kmp_search.py
KMP搜索测试：
pattern: ABCABAB
0 A  |  []  |  []  |  0
1 AB  |  ['A']  |  ['B']  |  0
2 ABC  |  ['A', 'AB']  |  ['C', 'BC']  |  0
3 ABCA  |  ['A', 'AB', 'ABC']  |  ['A', 'CA', 'BCA']  |  1
4 ABCAB  |  ['A', 'AB', 'ABC', 'ABCA']  |  ['B', 'AB', 'CAB', 'BCAB']  |  2
5 ABCABA  |  ['A', 'AB', 'ABC', 'ABCA', 'ABCAB']  |  ['A', 'BA', 'ABA', 'CABA', 'BCABA']  |  1
6 ABCABAB  |  ['A', 'AB', 'ABC', 'ABCA', 'ABCAB', 'ABCABA']  |  ['B', 'AB', 'BAB', 'ABAB', 'CABAB', 'BCABAB']  |  2
makePMT(:pmt: [0, 0, 0, 1, 2, 1, 2]
1 AB  |  ['A']  |  ['B']  |  0
2 ABC  |  ['A', 'AB']  |  ['C', 'BC']  |  0
3 ABCA  |  ['A', 'AB', 'ABC']  |  ['A', 'CA', 'BCA']  |  1
4 ABCAB  |  ['A', 'AB', 'ABC', 'ABCA']  |  ['B', 'AB', 'CAB', 'BCAB']  |  2
5 ABCABA  |  ['A', 'AB', 'ABC', 'ABCA', 'ABCAB']  |  ['A', 'BA', 'ABA', 'CABA', 'BCABA']  |  1
6 ABCABAB  |  ['A', 'AB', 'ABC', 'ABCA', 'ABCAB', 'ABCABA']  |  ['B', 'AB', 'BAB', 'ABAB', 'CABAB', 'BCABAB']  |  2
makePMT2 pmt: [0, 0, 0, 1, 2, 1, 2]
 pattern: ABCABAB text: AAABABCABABCDABABCABAB
1 AB  |  ['A']  |  ['B']  |  0
2 ABC  |  ['A', 'AB']  |  ['C', 'BC']  |  0
3 ABCA  |  ['A', 'AB', 'ABC']  |  ['A', 'CA', 'BCA']  |  1
4 ABCAB  |  ['A', 'AB', 'ABC', 'ABCA']  |  ['B', 'AB', 'CAB', 'BCAB']  |  2
5 ABCABA  |  ['A', 'AB', 'ABC', 'ABCA', 'ABCAB']  |  ['A', 'BA', 'ABA', 'CABA', 'BCABA']  |  1
6 ABCABAB  |  ['A', 'AB', 'ABC', 'ABCA', 'ABCAB', 'ABCABA']  |  ['B', 'AB', 'BAB', 'ABAB', 'CABAB', 'BCABAB']  |  2
makePMT2 pmt: [0, 0, 0, 1, 2, 1, 2]
根据模式串获取pmtTable: [0, 0, 0, 1, 2, 1, 2]
匹配结果： [4, 15]
 pattern: ABCABAB text: ABAAABABCABABCDABABCABAB
1 AB  |  ['A']  |  ['B']  |  0
2 ABC  |  ['A', 'AB']  |  ['C', 'BC']  |  0
3 ABCA  |  ['A', 'AB', 'ABC']  |  ['A', 'CA', 'BCA']  |  1
4 ABCAB  |  ['A', 'AB', 'ABC', 'ABCA']  |  ['B', 'AB', 'CAB', 'BCAB']  |  2
5 ABCABA  |  ['A', 'AB', 'ABC', 'ABCA', 'ABCAB']  |  ['A', 'BA', 'ABA', 'CABA', 'BCABA']  |  1
6 ABCABAB  |  ['A', 'AB', 'ABC', 'ABCA', 'ABCAB', 'ABCABA']  |  ['B', 'AB', 'BAB', 'ABAB', 'CABAB', 'BCABAB']  |  2
makePMT2 pmt: [0, 0, 0, 1, 2, 1, 2]
根据模式串获取pmtTable: [0, 0, 0, 1, 2, 1, 2]
匹配结果： [6, 17]
time:0.49424171447753906 ms
"""
