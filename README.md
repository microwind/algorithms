# 理解算法与数据结构，学习不同编程语言 [English](./README_en.md)

本仓库帮助你用不同编程语言来学习数据结构和算法，包括 `C` `Java` `Python` `JavaScript` `Go` `TypeScript` 等，提供充分注释说明。

AI时代来临，AI可以替代人们完成大量基础编码工作，但难以替代人们的思考和认知。人们只有在深入理解编程核心（数据结构+算法）的基础上，才能驾驭AI，并让AI产生高效价值。

表层的 API、框架与应用方案等日新月异，而数据结构、算法以及底层逻辑思维则历久弥新。表层技术需要快速地学习、不断追新逐热；底层原理与思想则需要反复钻研、琢磨，持续提升认知。

## 本项目特点：
1. 涵盖了数值计算、字符查找、树遍历、排序、动态规划等不同算法。
2. 每个算法都有多种语言的实现，通过算法与数据结构理解不同语言的特色。
3. 例子丰富，逐一递进，适合学生或程序员学习和分析，不断提升编程水平。

## 面向大学生与程序员的学习价值
本项目将“概念理解 → 代码实现 → 对比语言 → 练习进阶”串成一条清晰路径，适合作为课程补充、自学路线或面试与工程能力提升的长期仓库。

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

![算法概览](https://pic4.zhimg.com/80/v2-43fde0d41df8fba377333a318f428317_1440w.webp)

## 常见算法思想
- **贪心算法**：一种通过每次选择局部最优解来期望得到全局最优解的方法。
- **分治算法**：将问题分解为较小的子问题，独立解决后再合并结果。
- **动态规划**：通过将复杂问题分解为更简单的重叠子问题来求解。
- **回溯算法**：通过逐步构建候选解并放弃那些无法满足条件的方案来解决问题。
- **图算法**：包括广度优先搜索、深度优先搜索、Dijkstra算法、Kruskal算法等，用于解决图相关问题。
- **分支限界法**：一种组合优化问题的求解方法，通过系统地探索搜索树的分支来解决问题。

详细信息见：[10大算法思想](./start-here/algorithmic-thinking.md)
    
## 10大经典排序算法

| 排序算法 | C语言版 | JS版 | Python版 | Java版 | TS版 | Go版 | 时间复杂度（平均/最坏） | 空间复杂度 | 稳定性 | 适用场景 |
|---------|--------|-------------|---------|-------|-------------|-----|--------------------|---------|------|--------|
| [冒泡排序 bubble sort](sorting/bubblesort/) | [C](sorting/bubblesort/bubble_sort.c) | [JS](sorting/bubblesort/bubble_sort.js) | [Python](sorting/bubblesort/bubble_sort.py) | [Java](sorting/bubblesort/BubbleSort.java) | [TS](sorting/bubblesort/BubbleSort.ts) | [Go](sorting/bubblesort/bubble_sort.go) | O(n²) / O(n²) | O(1) | ✅ | 适用于小规模数据排序，教学用途 |
| [插入排序 insert sort](sorting/insertsort/) | [C](sorting/insertsort/insert_sort.c) | [JS](sorting/insertsort/insert_sort.js) | [Python](sorting/insertsort/insert_sort.py) | [Java](sorting/insertsort/InsertSort.java) | [TS](sorting/insertsort/InsertSort.ts) | [Go](sorting/insertsort/insert_sort.go) | O(n²) / O(n²) | O(1) | ✅ | 适用于小规模数据，少量元素已基本有序的情况 |
| [选择排序 selection sort](sorting/selectionsort/) | [C](sorting/selectionsort/selection_sort.c) | [JS](sorting/selectionsort/selection_sort.js) | [Python](sorting/selectionsort/selection_sort.py) | [Java](sorting/selectionsort/SelectionSort.java) | [TS](sorting/selectionsort/SelectionSort.ts) | [Go](sorting/selectionsort/selection_sort.go) | O(n²) / O(n²) | O(1) | ❌ | 适用于小规模数据，数据交换次数较少 |
| [堆排序 heap sort](sorting/heapsort/) | [C](sorting/heapsort/heap_sort.c) | [JS](sorting/heapsort/heap_sort.js) | [Python](sorting/heapsort/heap_sort.py) | [Java](sorting/heapsort/HeapSort.java) | [TS](sorting/heapsort/HeapSort.ts) | [Go](sorting/heapsort/heap_sort.go) | O(n log n) / O(n log n) | O(1) | ❌ | 适用于优先队列、TOP K问题 |
| [快速排序 quick sort](sorting/quicksort/) | [C](sorting/quicksort/quick_sort.c) | [JS](sorting/quicksort/quick_sort.js) | [Python](sorting/quicksort/quick_sort.py) | [Java](sorting/quicksort/QuickSort.java) | [TS](sorting/quicksort/QuickSort.ts) | [Go](sorting/quicksort/quick_sort.go) | O(n log n) / O(n²) | O(log n) | ❌ | 适用于一般排序场景，性能优异但不稳定 |
| [归并排序 merge sort](sorting/mergesort/) | [C](sorting/mergesort/merge_sort.c) | [JS](sorting/mergesort/merge_sort.js) | [Python](sorting/mergesort/merge_sort.py) | [Java](sorting/mergesort/MergeSort.java) | [TS](sorting/mergesort/MergeSort.ts) | [Go](sorting/mergesort/merge_sort.go) | O(n log n) / O(n log n) | O(n) | ✅ | 适用于大数据量排序，适合外部排序 |
| [计数排序 counting sort](sorting/countingsort/) | [C](sorting/countingsort/counting_sort.c) | [JS](sorting/countingsort/counting_sort.js) | [Python](sorting/countingsort/counting_sort.py) | [Java](sorting/countingsort/CountingSort.java) | [TS](sorting/countingsort/CountingSort.ts) | [Go](sorting/countingsort/counting_sort.go) | O(n + k) / O(n + k) | O(k) | ✅ | 适用于数据范围有限的整数排序 |
| [基数排序 radix sort](sorting/radixsort/) | [C](sorting/radixsort/radix_sort.c) | [JS](sorting/radixsort/radix_sort.js) | [Python](sorting/radixsort/radix_sort.py) | [Java](sorting/radixsort/RadixSort.java) | [TS](sorting/radixsort/RadixSort.ts) | [Go](sorting/radixsort/radix_sort.go) | O(nk) / O(nk) | O(n + k) | ✅ | 适用于大规模整数排序，如身份证号、手机号排序 |
| [桶排序 bucket sort](sorting/bucketsort/) | [C](sorting/bucketsort/bucket_sort.c) | [JS](sorting/bucketsort/bucket_sort.js) | [Python](sorting/bucketsort/bucket_sort.py) | [Java](sorting/bucketsort/BuketSort.java) | [TS](sorting/bucketsort/BuketSort.ts) | [Go](sorting/bucketsort/bucket_sort.go) | O(n + k) / O(n²) | O(n + k) | ✅ | 适用于数据范围均匀分布的排序 |
| [希尔排序 shell sort](sorting/shellsort/) | [C](sorting/shellsort/shell_sort.c) | [JS](sorting/shellsort/shell_sort.js) | [Python](sorting/shellsort/shell_sort.py) | [Java](sorting/shellsort/ShellSort.java) | [TS](sorting/shellsort/ShellSort.ts) | [Go](sorting/shellsort/shell_sort.go) | O(n log n) / O(n²) | O(1) | ❌ | 适用于中等规模数据排序，适合半有序数据 |


## 字符串搜索与查找

| 算法 | C语言版 | Go语言版 | JS版 | Python版 | Java版 | TS版 | 时间复杂度（平均/最坏） | 空间复杂度 | 适用场景 |
|------|--------|---------|-------------|---------|-------|-------------|--------------------|---------|--------|
| [朴素搜索](string/nativesearch/) | [C](string/nativesearch/string_search.c) | [Go](string/nativesearch/string_search.go) | [JS](string/nativesearch/string_search.js) | [Python](string/nativesearch/string_search.py) | [Java](string/nativesearch/StringSearch.java) | [TS](string/nativesearch/StringSearch.ts) | O(mn) / O(mn) | O(1) | 适用于小规模文本搜索 |
| [二分查找](searching/binarysearch/) | [C](searching/binarysearch/binary_search.c) | [Go](searching/binarysearch/binary_search.go) | [JS](searching/binarysearch/binary_search.js) | [Python](searching/binarysearch/binary_search.py) | [Java](searching/binarysearch/BinarySearch.java) | [TS](searching/binarysearch/BinarySearch.ts) | O(log n) / O(log n) | O(1) | 适用于已排序数组的查找 |
| [KMP搜索](string/KMPsearch/) | [C](string/KMPsearch/kmp_search.c) | [Go](string/KMPsearch/kmp_search.go) | [JS](string/KMPsearch/kmp_search.js) | [Python](string/KMPsearch/kmp_search.py) | [Java](string/KMPsearch/KMPSearch.java) | [TS](string/KMPsearch/KMPSearch.ts) | O(n + m) / O(n + m) | O(m) | 适用于大规模文本搜索 |


## 树搜索与遍历

| 算法 | C语言版 | JS版 | Python版 | Java版 | TS版 | 时间复杂度（平均/最坏） | 空间复杂度 | 适用场景 |
|------|--------|-------------|---------|-------|-------------|--------------------|---------|--------|
| [二叉树遍历](tree/binarytree/) | [C](tree/binarytree/binary_tree.c) | [JS](tree/binarytree/binary_tree.js) | [Python](tree/binarytree/binary_tree.py) | [Java](tree/binarytree/BinaryTree.java) | [TS](tree/binarytree/BinaryTree.ts) | O(n) / O(n) | O(n) | 适用于树结构数据的遍历，如 XML 解析、文件系统遍历 |

## 质因数分解

| 语言 | 代码链接 | 复杂度 | 适用场景 |
|------|---------|--------|--------|
| C | [factor.c](math/factor/factor.c) | O(√n) | 计算大整数的质因数分解 |
| C++ | [factor.cpp](math/factor/factor.cpp) | O(√n) | 适用于高效数学计算 |
| JavaScript | [factor.js](math/factor/factor.js) | O(√n) | Web 端数论计算 |
| TypeScript | [PrimeFactor.ts](math/factor/PrimeFactor.ts) | O(√n) | 适用于前端或 Node.js 计算 |
| Go | [factor.go](math/factor/factor.go) | O(√n) | 适用于后端服务计算 |
| Python | [factor.py](math/factor/factor.py) | O(√n) | 适用于科学计算、数据分析 |
| Java | [Factor.java](math/factor/Factor.java) | O(√n) | 适用于企业级应用计算 |
| Kotlin | [factor.kt](math/factor/factor.kt) | O(√n) | 适用于 Android 和后端计算 |
| Dart | [factor.dart](math/factor/factor.dart) | O(√n) | 适用于 Flutter 应用 |
| Swift | [factor.swift](math/factor/factor.swift) | O(√n) | 适用于 iOS/macOS 开发 |
| Objective-C | [factor.m](math/factor/factor.m) | O(√n) | 适用于老版本 iOS/macOS |
| Rust | [factor.rs](math/factor/factor.rs) | O(√n) | 适用于高性能计算 |

## 数组列表去重复项

| 语言 | 代码链接 | 时间复杂度 | 适用场景 |
|------|---------|--------|--------|
| C | [unique.c](array/unique/unique.c) | O(n log n) | 适用于嵌入式开发 |
| Go | [unique.go](array/unique/unique.go) | O(n log n) | 适用于高并发场景 |
| JS | [unique.js](array/unique/unique.js) | O(n) | 适用于前端数据处理 |
| Python | [unique.py](array/unique/unique.py) | O(n) | 适用于数据清洗、分析 |
| Java | [UniqueArray.java](array/unique/UniqueArray.java) | O(n log n) | 适用于企业级应用 |
| TypeScript | [UniqueArray.ts](array/unique/UniqueArray.ts) | O(n) | 适用于前端 TypeScript 项目 |
| Dart | [unique.dart](array/unique/unique.dart) | O(n) | 适用于 Flutter 应用 |
| Rust | [unique.rs](array/unique/unique.rs) | O(n) | 适用于高性能计算 |


## 递归

| 算法 | 代码链接 | 时间复杂度 | 空间复杂度 | 适用场景 |
|------|---------|------------|------------|--------|
| [简单递归](./recursion/) | [C](./recursion/) | O(2^n) | O(n) | 适用于分治算法、树和图的遍历、回溯问题 |

## 数学计算

| 算法 | 代码链接 | 时间复杂度 | 空间复杂度 | 适用场景 |
|------|---------|------------|------------|--------|
| [数学计算](math/number/) | [C](math/number/) | O(n) | O(1) | 适用于数论、加法、乘法、大整数计算等 |

## 日期与日历

| 算法 | 代码链接 | 时间复杂度 | 空间复杂度 | 适用场景 |
|------|---------|------------|------------|--------|
| [日期与日历](date-time/) | [C](date-time/) | O(1) | O(1) | 适用于日期计算、节假日推算、日期转换等 |

---

# 数据结构
  数据结构是数据的组织和存储的方式，也就是把数据聚合在一起，以便进行加工整理。不同的数据结构，对其访问、插入、删除等操作的效率不同。通过选择合适的数据结构，可以高效地处理数据。详见：[数据结构概述](./data-structures)

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

## 相关链接
- [推荐学习的编程语言](./start-here/recommand-learning-languages.md)
- [不同编程语言有哪些差异？如何选择入门语言？](https://www.toutiao.com/article/7122744261904450063) | 
- [如何学好编程？一文彻底搞懂](https://zhuanlan.zhihu.com/p/582174773)
  
## 欢迎加入共建

`仓库：` [https://github.com/microwind/algorithms](https://github.com/microwind/algorithms)
`站点：` [https://microwind.github.io/algorithms](https://microwind.github.io/algorithms)

如果您对本项目感兴趣请加我，欢迎一起共建！ 
If you are interested in this project, please add me. I welcome you to build it together!

**wechat:** `springbuild`

**邮件:** `jarryli@gmail.com`  or `lichunping@buaa.edu.cn`
