# AI编程：算法思想与数据结构知识库大全 | [English](./README_en.md)

> AI时代，我们更需要理解算法思想与数据结构，学习不同编程语言特性。

![License](https://img.shields.io/badge/License-MIT-blue.svg) ![Last Updated](https://img.shields.io/github/last-commit/microwind/design-patterns) ![Build Status](https://img.shields.io/badge/build-passing-brightgreen) [![GitHub stars](https://img.shields.io/github/stars/microwind/algorithms.svg?style=social&label=Star)](https://github.com/microwind/algorithms) [![GitHub forks](https://img.shields.io/github/forks/microwind/algorithms.svg?style=social&label=Fork)](https://github.com/microwind/algorithms/fork)

本仓库旨在帮助大学生和程序员**用不同编程语言来学习数据结构和经典算法思想**，包括 `C`、`Java`、`Python`、`JavaScript`、`Go`、`TypeScript`、`Rust` 等，提供充分注释说明。由简入深，让你充分理解算法与数据结构的原理，同时又能掌握不同编程语言的特点，助你**从“编码执行者”转型为“AI驱动者”。** 

AI编程时代已经到来。AI可以替代人工编码工作，但难以替代人的认知与思考。只有在深入理解编程核心（`算法`+`数据结构`、`设计模式`+`系统架构`）的基础上，**人们才能真正驾驭AI，并让AI产生更高的效率与价值。** 

表层的API、框架与应用方案日新月异，而**数据结构、算法以及底层逻辑思维则历久弥新**。表层技术需要快速学习、持续迭代；底层原理与思想则需要反复钻研与沉淀，从而持续提升认知。

## 🚀 本项目特点
1. 涵盖了数值计算、字符查找、树遍历、排序、动态规划等各种经典算法。
2. 每个算法都有多种语言以及不同版本的实现，通过算法与数据结构理解不同语言的特色。
3. 例子丰富，逐一递进，适合学生或程序员学习和分析，不断提升编程水平。

## 新手入门指南

如果你是**编程新手**或**算法初学者**，建议从这里开始：

### [入门指南](./start-here/)
- **[学习路线](./start-here/learning-path.md)** - 从入门到精通的完整学习规划
- **[什么是编程](./start-here/what-is-programming.md)** - 理解编程的本质和核心概念  
- **[算法思想](./start-here/AI-Era-Programmers-Need-Algorithmic-Thinking.md)** - 掌握核心算法思想，应用无穷
- **[环境搭建](./start-here/environment-setup.md)** - 快速配置开发环境
- **[推荐语言](./start-here/recommand-learning-languages.md)** - 选择合适的入门语言
- **[常见问题](./start-here/faq.md)** - 初学者常见问题解答

>**快速开始**：完全新手建议按顺序阅读，有编程基础可直接看算法思想部分。

## 适合大学生与程序员学习
本项目将“**概念理解 → 代码实现 → 对比语言 → 练习进阶**”串成一条清晰路径，适合作为课程补充、自学路线或面试与工程能力提升的长期仓库。

你可以获得：
- 体系化学习路径：从入门到经典算法，再到题库与项目，循序渐进不走弯路。
- 多语言对照：同一算法多语言实现，帮助理解语言差异与工程习惯。
- 可实践与可复用：多数目录提供可运行代码与说明，方便作业、面试与项目中直接参考。
- 强化基础与思维：重视复杂度分析与算法思想，提升解决问题的效率与正确性。

# 算法概览

## 常见的算法有哪些？
- **文本查找**：包括线性搜索、二分搜索、树形搜索、最大公共子序列、回文计算等，主要针对字符串查找。
- **数学计算**：包括进制转换、开平方、斐波那契数列、质因数分解、数字三角形等，主要进行数值计算。
- **排序算法**：包括冒泡、选择、插入、希尔、归并、快速、堆、计数、桶、基数等，用于按顺序排列数据。
- **其他算法**：包括动态规划、贪心算法、分治算法、回溯算法、图算法（如广度优先搜索、深度优先搜索、Dijkstra算法、Kruskal算法等），此外还包括机器学习和人工智能算法，如分类算法、聚类算法、深度学习、强化学习等。

![算法概览](./resources/images/algorithm-structure-cn.png)

## 常见算法思想
- **[贪心算法](./algorithmic-thinking/greedy-algorithm/)**：一种通过每次选择局部最优解来期望得到全局最优解的方法。
- **[分治算法](./algorithmic-thinking/divide-and-conquer/)**：将问题分解为较小的子问题，独立解决后再合并结果。
- **[动态规划](./algorithmic-thinking/dynamic-programming/)**：通过将复杂问题分解为更简单的重叠子问题来求解。
- **[回溯算法](./algorithmic-thinking/backtracking/)**：通过逐步构建候选解并放弃那些无法满足条件的方案来解决问题。
- **[图算法](./algorithmic-thinking/search-algorithms/)**：包括广度优先搜索、深度优先搜索、Dijkstra算法、Kruskal算法等，用于解决图相关问题。
- **[分支限界法](./algorithmic-thinking/branch-and-bound/)**：一种组合优化问题的求解方法，通过系统地探索搜索树的分支来解决问题。

详细请见：[算法思想大全](./algorithmic-thinking)
    
## 10大经典排序算法

| 排序算法 | C | C++ | Java | Py | JS | TS | Go | Rust | Swift | Kotlin | Dart | 适用场景 |
|---------|--------|--------|---------|---------|-------------|-------------|-----|------|------|--------|------|--------|
| [冒泡排序 bubble sort](./sorting/bubblesort/) | [C](./sorting/bubblesort/bubble_sort.c) | [C++](./sorting/bubblesort/bubble_sort.cpp) | [Java](./sorting/bubblesort/BubbleSort.java) | [Py](./sorting/bubblesort/bubble_sort.py) | [JS](./sorting/bubblesort/bubble_sort.js) | [TS](./sorting/bubblesort/BubbleSort.ts) | [Go](./sorting/bubblesort/bubble_sort.go) | [Rust](./sorting/bubblesort/bubble_sort.rs) | [Swift](./sorting/bubblesort/BubbleSort.swift) | [Kotlin](./sorting/bubblesort/BubbleSort.kt) | [Dart](./sorting/bubblesort/BubbleSort.dart) | 适用于小规模数据排序，教学用途 |
| [插入排序 insert sort](./sorting/insertsort/) | [C](./sorting/insertsort/insert_sort.c) | [C++](./sorting/insertsort/insert_sort.cpp) | [Java](./sorting/insertsort/InsertSort.java) | [Py](./sorting/insertsort/insert_sort.py) | [JS](./sorting/insertsort/insert_sort.js) | [TS](./sorting/insertsort/InsertSort.ts) | [Go](./sorting/insertsort/insert_sort.go) | [Rust](./sorting/insertsort/insert_sort.rs) | [Swift](./sorting/insertsort/InsertSort.swift) | [Kotlin](./sorting/insertsort/InsertSort.kt) | [Dart](./sorting/insertsort/InsertSort.dart) | 适用于小规模数据，少量元素已基本有序的情况 |
| [选择排序 selection sort](./sorting/selectionsort/) | [C](./sorting/selectionsort/selection_sort.c) | [C++](./sorting/selectionsort/selection_sort.cpp) | [Java](./sorting/selectionsort/SelectionSort.java) | [Py](./sorting/selectionsort/selection_sort.py) | [JS](./sorting/selectionsort/selection_sort.js) | [TS](./sorting/selectionsort/SelectionSort.ts) | [Go](./sorting/selectionsort/selection_sort.go) | [Rust](./sorting/selectionsort/selection_sort.rs) | [Swift](./sorting/selectionsort/SelectionSort.swift) | [Kotlin](./sorting/selectionsort/SelectionSort.kt) | [Dart](./sorting/selectionsort/SelectionSort.dart) | 适用于小规模数据，数据交换次数较少 |
| [堆排序 heap sort](./sorting/heapsort/) | [C](./sorting/heapsort/heap_sort.c) | [C++](./sorting/heapsort/heap_sort.cpp) | [Java](./sorting/heapsort/HeapSort.java) | [Py](./sorting/heapsort/heap_sort.py) | [JS](./sorting/heapsort/heap_sort.js) | [TS](./sorting/heapsort/HeapSort.ts) | [Go](./sorting/heapsort/heap_sort.go) | [Rust](./sorting/heapsort/heap_sort.rs) | [Swift](./sorting/heapsort/HeapSort.swift) | [Kotlin](./sorting/heapsort/HeapSort.kt) | [Dart](./sorting/heapsort/HeapSort.dart) | 适用于优先队列、TOP K问题 |
| [快速排序 quick sort](./sorting/quicksort/) | [C](./sorting/quicksort/quick_sort.c) | [C++](./sorting/quicksort/quick_sort.cpp) | [Java](./sorting/quicksort/QuickSort.java) | [Py](./sorting/quicksort/quick_sort.py) | [JS](./sorting/quicksort/quick_sort.js) | [TS](./sorting/quicksort/QuickSort.ts) | [Go](./sorting/quicksort/quick_sort.go) | [Rust](./sorting/quicksort/quick_sort.rs) | [Swift](./sorting/quicksort/QuickSort.swift) | [Kotlin](./sorting/quicksort/QuickSort.kt) | [Dart](./sorting/quicksort/QuickSort.dart) | 适用于一般排序场景，性能优异但不稳定 |
| [归并排序 merge sort](./sorting/mergesort/) | [C](./sorting/mergesort/merge_sort.c) | [C++](./sorting/mergesort/merge_sort.cpp) | [Java](./sorting/mergesort/MergeSort.java) | [Py](./sorting/mergesort/merge_sort.py) | [JS](./sorting/mergesort/merge_sort.js) | [TS](./sorting/mergesort/MergeSort.ts) | [Go](./sorting/mergesort/merge_sort.go) | [Rust](./sorting/mergesort/merge_sort.rs) | [Swift](./sorting/mergesort/MergeSort.swift) | [Kotlin](./sorting/mergesort/MergeSort.kt) | [Dart](./sorting/mergesort/MergeSort.dart) | 适用于大数据量排序，适合外部排序 |
| [计数排序 counting sort](./sorting/countingsort/) | [C](./sorting/countingsort/counting_sort.c) | [C++](./sorting/countingsort/counting_sort.cpp) | [Java](./sorting/countingsort/CountingSort.java) | [Py](./sorting/countingsort/counting_sort.py) | [JS](./sorting/countingsort/counting_sort.js) | [TS](./sorting/countingsort/CountingSort.ts) | [Go](./sorting/countingsort/counting_sort.go) | [Rust](./sorting/countingsort/counting_sort.rs) | [Swift](./sorting/countingsort/CountingSort.swift) | [Kotlin](./sorting/countingsort/CountingSort.kt) | [Dart](./sorting/countingsort/CountingSort.dart) | 适用于数据范围有限的整数排序 |
| [基数排序 radix sort](./sorting/radixsort/) | [C](./sorting/radixsort/radix_sort.c) | [C++](./sorting/radixsort/radix_sort.cpp) | [Java](./sorting/radixsort/RadixSort.java) | [Py](./sorting/radixsort/radix_sort.py) | [JS](./sorting/radixsort/radix_sort.js) | [TS](./sorting/radixsort/RadixSort.ts) | [Go](./sorting/radixsort/radix_sort.go) | [Rust](./sorting/radixsort/radix_sort.rs) | [Swift](./sorting/radixsort/RadixSort.swift) | [Kotlin](./sorting/radixsort/RadixSort.kt) | [Dart](./sorting/radixsort/RadixSort.dart) | 适用于大规模整数排序，如身份证号、手机号排序 |
| [桶排序 bucket sort](./sorting/bucketsort/) | [C](./sorting/bucketsort/bucket_sort.c) | [C++](./sorting/bucketsort/bucket_sort.cpp) | [Java](./sorting/bucketsort/BucketSort.java) | [Py](./sorting/bucketsort/bucket_sort.py) | [JS](./sorting/bucketsort/BucketSort.js) | [TS](./sorting/bucketsort/BucketSort.ts) | [Go](./sorting/bucketsort/bucket_sort.go) | [Rust](./sorting/bucketsort/bucket_sort.rs) | [Swift](./sorting/bucketsort/BucketSort.swift) | [Kotlin](./sorting/bucketsort/BucketSort.kt) | [Dart](./sorting/bucketsort/BucketSort.dart) | 适用于数据范围均匀分布的排序 |
| [希尔排序 shell sort](./sorting/shellsort/) | [C](./sorting/shellsort/shell_sort.c) | [C++](./sorting/shellsort/ShellSort.cpp) | [Java](./sorting/shellsort/ShellSort.java) | [Py](./sorting/shellsort/shell_sort.py) | [JS](./sorting/shellsort/shell_sort.js) | [TS](./sorting/shellsort/ShellSort.ts) | [Go](./sorting/shellsort/shell_sort.go) | [Rust](./sorting/shellsort/shell_sort.rs) | [Swift](./sorting/shellsort/ShellSort.swift) | [Kotlin](./sorting/shellsort/ShellSort.kt) | [Dart](./sorting/shellsort/ShellSort.dart) | 适用于中等规模数据排序，适合半有序数据 |

📖 **详细指南**：[十大排序算法全解：多语言源码仓库](./sorting/10-Sorting-Algorithms-Multi-Language.md)


## 字符串搜索与查找

| 算法 | C | C++ | Java | Py | JS | TS | Go | Rust | Swift | Kotlin | Dart | 适用场景 |
|------|--------|--------|---------|---------|-------------|-------------|-----|------|------|--------|------|--------|
| [朴素搜索](./string/nativesearch/) | [C](./string/nativesearch/string_search.c) | [C++](./string/nativesearch/string_search.cpp) | [Java](./string/nativesearch/StringSearch.java) | [Python](./string/nativesearch/string_search.py) | [JS](./string/nativesearch/string_search.js) | [TS](./string/nativesearch/StringSearch.ts) | [Go](./string/nativesearch/string_search.go) | [Rust](./string/nativesearch/string_search.rs) | [Swift](./string/nativesearch/StringSearch.swift) | [Kotlin](./string/nativesearch/StringSearch.kt) | [Dart](./string/nativesearch/StringSearch.dart) | 适用于小规模文本搜索 |
| [二分查找](./searching/binarysearch/) | [C](./searching/binarysearch/binary_search.c) | [C++](./searching/binarysearch/binary_search.cpp) | [Java](./searching/binarysearch/BinarySearch.java) | [Python](./searching/binarysearch/binary_search.py) | [JS](./searching/binarysearch/binary_search.js) | [TS](./searching/binarysearch/BinarySearch.ts) | [Go](./searching/binarysearch/binary_search.go) | [Rust](./searching/binarysearch/binary_search.rs) | [Swift](./searching/binarysearch/BinarySearch.swift) | [Kotlin](./searching/binarysearch/BinarySearch.kt) | [Dart](./searching/binarysearch/BinarySearch.dart) | 适用于已排序数组的查找 |
| [KMP搜索](./string/KMPsearch/) | [C](./string/KMPsearch/kmp_search.c) | [C++](./string/KMPsearch/kmp_search.cpp) | [Java](./string/KMPsearch/KMPSearch.java) | [Python](./string/KMPsearch/kmp_search.py) | [JS](./string/KMPsearch/kmp_search.js) | [TS](./string/KMPsearch/KMPSearch.ts) | [Go](./string/KMPsearch/kmp_search.go) | [Rust](./string/KMPsearch/kmp_search.rs) | [Swift](./string/KMPsearch/KMPSearch.swift) | [Kotlin](./string/KMPsearch/KMPSearch.kt) | [Dart](./string/KMPsearch/KMPSearch.dart) | 适用于大规模文本搜索 |


## 树搜索与遍历

| 算法 | C | C++ | Java | Py | JS | TS | Go | Rust | Swift | Kotlin | Dart | 适用场景 |
|------|--------|--------|---------|---------|-------------|-------------|-----|------|------|--------|------|--------|
| [二叉树遍历](./tree/binarytree/) | [C](./tree/binarytree/binary_tree.c) | [C++](./tree/binarytree/binary_tree.cpp) | [Java](./tree/binarytree/BinaryTree.java) | [Python](./tree/binarytree/binary_tree.py) | [JS](./tree/binarytree/binary_tree.js) | [TS](./tree/binarytree/BinaryTree.ts) | [Go](./tree/binarytree/binary_tree.go) | [Rust](./tree/binarytree/binary_tree.rs) | [Swift](./tree/binarytree/BinaryTree.swift) | [Kotlin](./tree/binarytree/BinaryTree.kt) | [Dart](./tree/binarytree/BinaryTree.dart) | 适用于树结构数据的遍历，如 XML 解析、文件系统遍历 |

## 压缩算法详解

| 算法 | C | C++ | Java | Py | JS | TS | Go | Rust | Swift | Kotlin | Dart | 适用场景 |
|------|--------|--------|---------|---------|-------------|-------------|-----|------|------|--------|------|--------|
| [Huffman编码](./compression/huffman/) | [C](./compression/huffman/huffman.c) | [C++](./compression/huffman/huffman.cpp) | [Java](./compression/huffman/Huffman.java) | [Python](./compression/huffman/huffman.py) | [JS](./compression/huffman/huffman.js) | [TS](./compression/huffman/Huffman.ts) | [Go](./compression/huffman/huffman.go) | [Rust](./compression/huffman/huffman.rs) | [Swift](./compression/huffman/Huffman.swift) | [Kotlin](./compression/huffman/Huffman.kt) | [Dart](./compression/huffman/huffman.dart) | 适用于无损数据压缩、文件压缩 |
| [Run-Length Encoding](./compression/rle/) | [C](./compression/rle/rle.c) | [C++](./compression/rle/rle.cpp) | [Java](./compression/rle/RLE.java) | [Python](./compression/rle/rle.py) | [JS](./compression/rle/rle.js) | [TS](./compression/rle/RLE.ts) | [Go](./compression/rle/rle.go) | [Rust](./compression/rle/rle.rs) | [Swift](./compression/rle/RLE.swift) | [Kotlin](./compression/rle/RLE.kt) | [Dart](./compression/rle/rle.dart) | 适用于简单重复数据压缩 |
| [LZ77算法](./compression/lz77/) | [C](./compression/lz77/lz77.c) | [C++](./compression/lz77/lz77.cpp) | [Java](./compression/lz77/LZ77.java) | [Python](./compression/lz77/lz77.py) | [JS](./compression/lz77/lz77.js) | [TS](./compression/lz77/LZ77.ts) | [Go](./compression/lz77/lz77.go) | [Rust](./compression/lz77/lz77.rs) | [Swift](./compression/lz77/LZ77.swift) | [Kotlin](./compression/lz77/LZ77.kt) | [Dart](./compression/lz77/LZ77.dart) | 适用于文本压缩、ZIP格式基础 |
| [LZW算法](./compression/lzw/) | [C](./compression/lzw/lzw.c) | [C++](./compression/lzw/lzw.cpp) | [Java](./compression/lzw/LZW.java) | [Python](./compression/lzw/lzw.py) | [JS](./compression/lzw/lzw.js) | [TS](./compression/lzw/LZW.ts) | [Go](./compression/lzw/lzw.go) | [Rust](./compression/lzw/lzw.rs) | [Swift](./compression/lzw/LZW.swift) | [Kotlin](./compression/lzw/LZW.kt) | [Dart](./compression/lzw/LZW.dart) | 适用于GIF格式、文本压缩 |

## 加密算法详解

| 算法 | C | C++ | Java | Py | JS | TS | Go | Rust | Swift | Kotlin | Dart | 适用场景 |
|------|--------|--------|---------|---------|-------------|-------------|-----|------|------|--------|------|--------|
| [AES加密](./cryptography/aes/) | [C](./cryptography/aes/aes.c) | [C++](./cryptography/aes/aes.cpp) | [Java](./cryptography/aes/AES.java) | [Python](./cryptography/aes/aes.py) | [JS](./cryptography/aes/aes.js) | [TS](./cryptography/aes/AES.ts) | [Go](./cryptography/aes/aes.go) | [Rust](./cryptography/aes/aes.rs) | [Swift](./cryptography/aes/AES.swift) | [Kotlin](./cryptography/aes/AES.kt) | [Dart](./cryptography/aes/AES.dart) | 适用于对称加密、数据保护 |
| [RSA加密](./cryptography/rsa/) | [C](./cryptography/rsa/rsa.c) | [C++](./cryptography/rsa/rsa.cpp) | [Java](./cryptography/rsa/RSA.java) | [Python](./cryptography/rsa/rsa.py) | [JS](./cryptography/rsa/rsa.js) | [TS](./cryptography/rsa/RSA.ts) | [Go](./cryptography/rsa/rsa.go) | [Rust](./cryptography/rsa/rsa.rs) | [Swift](./cryptography/rsa/RSA.swift) | [Kotlin](./cryptography/rsa/RSA.kt) | [Dart](./cryptography/rsa/RSA.dart) | 适用于非对称加密、数字签名 |
| [SHA哈希](./cryptography/sha/) | [C](./cryptography/sha/sha.c) | [C++](./cryptography/sha/sha.cpp) | [Java](./cryptography/sha/SHA.java) | [Python](./cryptography/sha/sha.py) | [JS](./cryptography/sha/sha.js) | [TS](./cryptography/sha/SHA.ts) | [Go](./cryptography/sha/sha.go) | [Rust](./cryptography/sha/sha.rs) | [Swift](./cryptography/sha/SHA.swift) | [Kotlin](./cryptography/sha/SHA.kt) | [Dart](./cryptography/sha/SHA.dart) | 适用于数据完整性校验、密码存储 |
| [凯撒密码](./cryptography/caesar/) | [C](./cryptography/caesar/caesar.c) | [C++](./cryptography/caesar/caesar.cpp) | [Java](./cryptography/caesar/Caesar.java) | [Python](./cryptography/caesar/caesar.py) | [JS](./cryptography/caesar/caesar.js) | [TS](./cryptography/caesar/Caesar.ts) | [Go](./cryptography/caesar/caesar.go) | [Rust](./cryptography/caesar/caesar.rs) | [Swift](./cryptography/caesar/Caesar.swift) | [Kotlin](./cryptography/caesar/Caesar.kt) | [Dart](./cryptography/caesar/Caesar.dart) | 适用于古典加密、教学演示 |

## 质因数分解

| 语言 | 代码链接 | 复杂度 | 适用场景 |
|------|---------|--------|--------|
| C | [factor.c](./math/factor/factor.c) | O(√n) | 计算大整数的质因数分解 |
| C++ | [factor.cpp](./math/factor/factor.cpp) | O(√n) | 适用于高效数学计算 |
| JavaScript | [factor.js](./math/factor/factor.js) | O(√n) | Web 端数论计算 |
| TypeScript | [PrimeFactor.ts](./math/factor/PrimeFactor.ts) | O(√n) | 适用于前端或 Node.js 计算 |
| Go | [factor.go](./math/factor/factor.go) | O(√n) | 适用于后端服务计算 |
| Python | [factor.py](./math/factor/factor.py) | O(√n) | 适用于科学计算、数据分析 |
| Java | [Factor.java](./math/factor/Factor.java) | O(√n) | 适用于企业级应用计算 |
| Kotlin | [factor.kt](./math/factor/factor.kt) | O(√n) | 适用于 Android 和后端计算 |
| Dart | [factor.dart](./math/factor/factor.dart) | O(√n) | 适用于 Flutter 应用 |
| Swift | [factor.swift](./math/factor/factor.swift) | O(√n) | 适用于 iOS/macOS 开发 |
| Objective-C | [factor.m](./math/factor/factor.m) | O(√n) | 适用于老版本 iOS/macOS |
| Rust | [factor.rs](./math/factor/factor.rs) | O(√n) | 适用于高性能计算 |

## 数组列表去重复项

| 语言 | 代码链接 | 时间复杂度 | 适用场景 |
|------|---------|--------|--------|
| C | [unique.c](./array/unique/unique.c) | O(n log n) | 适用于嵌入式开发 |
| Go | [unique.go](./array/unique/unique.go) | O(n log n) | 适用于高并发场景 |
| JS | [unique.js](./array/unique/unique.js) | O(n) | 适用于前端数据处理 |
| Python | [unique.py](./array/unique/unique.py) | O(n) | 适用于数据清洗、分析 |
| Java | [UniqueArray.java](./array/unique/UniqueArray.java) | O(n log n) | 适用于企业级应用 |
| TypeScript | [UniqueArray.ts](./array/unique/UniqueArray.ts) | O(n) | 适用于前端 TypeScript 项目 |
| Dart | [unique.dart](./array/unique/unique.dart) | O(n) | 适用于 Flutter 应用 |
| Rust | [unique.rs](./array/unique/unique.rs) | O(n) | 适用于高性能计算 |


## 递归

| 算法 | 代码链接 | 时间复杂度 | 空间复杂度 | 适用场景 |
|------|---------|------------|------------|--------|
| [简单递归](./recursion/) | [多语言实现](./recursion/) | O(2^n) | O(n) | 适用于分治算法、树和图的遍历、回溯问题 |

## 数学计算

| 算法 | 代码链接 | 时间复杂度 | 空间复杂度 | 适用场景 |
|------|---------|------------|------------|--------|
| [数学计算](./math/) | [多语言实现](./math/) | O(n) | O(1) | 适用于数论、加法、乘法、大整数计算、质因数分解、GCD、斐波那契等 |

## 日期与日历

| 算法 | 代码链接 | 时间复杂度 | 空间复杂度 | 适用场景 |
|------|---------|------------|------------|--------|
| [日期与日历](./date-time/) | [多语言实现](./date-time/) | O(1) | O(1) | 适用于日期计算、闰年判断、星期计算、日期间隔、时间戳转换等 |

---

# 数据结构

数据结构是数据的组织和存储的方式，通过选择合适的数据结构，可以高效地处理数据。详见：[数据结构概述](./data-structures/README.md)

| 数据结构 | 描述 | 结构特点 | 访问效率 | 插入/删除效率 |
|---------|------|---------|---------|-------------|
| [Array (数组)](./data-structures/array/) | 具有相同数据类型的元素集合，支持按索引随机访问 | 连续内存存储，支持线性或非线性 | O(1) | O(n) |
| [Linked List (链表)](./data-structures/linked/) | 数据以链式结构存储，通过指针连接，分为单向链表、双向链表和循环链表 | 线性结构，内存不连续 | O(n) | O(1) (头部) / O(n) (中间) |
| [Tree (树)](./data-structures/tree/) | 树状数据集合，节点按层级关系组织，常见类型包括二叉树、二叉搜索树、平衡树等| 非线性结构，一个根节点，子节点数量不限 | O(log n) | O(log n) |
| [Heap (堆)](./data-structures/heap/) | 一种特殊的完全二叉树，满足堆序性（最大堆或最小堆），常用于优先队列 | 非线性结构，支持按最值高效操作 | O(1) (取堆顶) | O(log n) |
| [Stack (栈)](./data-structures/stack/) | 后进先出 (LIFO) 的数据集合 | 线性结构，顺序或链式存储，仅允许在栈顶操作 | O(1) | O(1) |
| [Queue (队列)](./data-structures/queue/) | 先进先出 (FIFO) 的数据集合 | 线性结构，顺序或链式存储，支持在队尾插入、队头删除 | O(1) | O(1) |
| [Graph (图)](./data-structures/graph/) | 由节点（顶点）和边组成的图形数据结构，常见存储方式为邻接表或邻接矩阵 | 非线性结构，节点间可多对多连接 | O(1) (邻接矩阵) / O(n) (邻接表) | O(1) (邻接矩阵) / O(n) (邻接表) |
| [Hash (散列)](./data-structures/hash/) | 通过哈希函数将键映射到存储位置的数据结构，支持快速查找、插入和删除 | 线性结构，通过哈希键值映射 | O(1) (均摊) | O(1) (均摊) |
| [Struct (结构体)](./data-structures/struct/) | 组合多种类型的数据，形成一个整体，常用于表示复杂对象 | 自定义结构，字段固定，包含多种数据类型 | O(1) | O(1) |
| [List (列表)](./data-structures/list/) | 有序集合，允许重复元素，支持索引访问 | 线性结构，元素按插入顺序存储 | O(1) (末尾插入)，O(n) (中间插入/删除) | O(1) (索引访问)，O(n) (查找) |
| [Set (集合)](./data-structures/set/) | 无序集合，不允许重复元素，支持高效查找 | 线性结构，基于哈希或树实现 | O(1) (哈希实现)，O(log n) (树实现) | O(1) (哈希实现)，O(log n) (树实现) |
| [Map (映射)](./data-structures/map/) | 存储键值对的数据结构，支持快速查找、插入和删除 | 关联数组，基于哈希或平衡树实现 | O(1) (哈希实现)，O(log n) (树实现) | O(1) (哈希实现)，O(log n) (树实现) |  

---

## 学习文档
- [推荐学习的编程语言](./start-here/recommand-learning-languages.md)
- [不同编程语言有哪些差异？如何选择入门语言？](https://www.toutiao.com/article/7122744261904450063) 
- [如何学好编程？一文彻底搞懂](https://zhuanlan.zhihu.com/p/582174773)

## 相关链接：AI时代程序员成长体系

> AI时代，我们要从编码程序员转变成驱动AI的指挥官，告诉AI该怎么做，什么是好、什么是坏。

- [《AI时代，程序员必备的算法思想指南》](https://github.com/microwind/algorithms/blob/main/start-here/AI-Era-Programmers-Need-Algorithmic-Thinking.md)
- [《AI时代，人人都是Agent应用工程师》](https://github.com/microwind/algorithms/blob/main/start-here/AI-Era-Programmers-as-Agent-Engineers.md)
- ai-prompt - AI编程提示词库：[https://github.com/microwind/ai-prompt](https://github.com/microwind/ai-prompt)
- ai-skills - AI编程Skill库：[https://github.com/microwind/ai-skills](https://github.com/microwind/ai-skills)
- algorithms - 算法思想与数据结构：[https://github.com/microwind/algorithms](https://github.com/microwind/algorithms)
- design-patterns - 设计模式与编程范式：[https://github.com/microwind/design-patterns](https://github.com/microwind/design-patterns)
  
## 欢迎加入共建

`仓库：` [https://github.com/microwind/algorithms](https://github.com/microwind/algorithms)
`站点：` [https://microwind.github.io/algorithms](https://microwind.github.io/algorithms)

如果您对本项目感兴趣请加我，欢迎一起共建！ 
If you are interested in this project, please add me on WeChat. Let’s build it together!

**我是Jarry 李春平, 从业20多年的互联网工程师。**

- 📧 mail: `jarryli@gmail.com`  or `lichunping@buaa.edu.cn`
- 💬 wechat: `springbuild`
- 🌟 如果这个项目对你有帮助，请给个 Star 支持一下！
