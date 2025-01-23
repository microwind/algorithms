# 理解算法与数据结构，学习不同编程语言 [English](./README_en.md)    

不同语言实现算法与数据结构，包括 `C Java Python JavaScript Go TypeScript Dart Swift Kotlin` 等，提供充分注释说明。
   
1. 包括数值计算、字符查找、树遍历、排序、动态规划等不同算法。
2. 每个算法均由多种语言实现，通过实际例子，理解不同语言的特色。
3. 样例均精心打造，适合学生或程序员学习和分析，提升编程水平。

## 常见的算法有哪些？
- **文本查找**：包括线性搜索、二分搜索、树形搜索、最大公共子序列、回文计算等。主要是针对字符串进行查找。
- **数学计算**：包括进制转换、开平方、斐波那契数列、质因数分解、数字三角形等。主要是进行数值的运算。
- **排序算法**：包括冒泡、选择、插入、希尔、归并、快速、堆、计数、桶、基数等。用于按顺序排列成员。
- **其他算法**：包括动态规划、贪心算法、分治算法、回溯算法、图算法（如广度优先搜索、深度优先搜索、Dijkstra算法、Kruskal算法等）。此外，还有机器学习和人工智能算法，包括分类算法、聚类算法、深度学习、强化学习等。

<img src="https://pic4.zhimg.com/80/v2-43fde0d41df8fba377333a318f428317_1440w.webp">

## 常见算法思想
  贪心算法（Greedy Algorithm）、分治算法（Divide and Conquer）、动态规划（Dynamic Programming）、回溯算法（Backtracking）、图算法（Graph Algorithms）、分支界限（Branch and Bound）等。详见：[10大算法思想](./algorithmic_thinking.md)

## 常见算法例子
    
### 10大经典排序算法
- ### [冒泡排序 bubble sort](./sorts/bubblesort/)
  [C语言版](./sorts/bubblesort/bubble_sort.c ) | [JavaScript版](./sorts/bubblesort/bubble_sort.js ) | [Python版](./sorts/bubblesort/bubble_sort.py ) | [Java版](./sorts/bubblesort/BubbleSort.java ) | [TypeScript版](./sorts/bubblesort/BubbleSort.ts ) | [Go版](./sorts/bubblesort/bubble_sort.go ) | [Dart版](./sorts/bubblesort/bubble_sort.dart ) | [Rust版](./sorts/bubblesort/bubble_sort.rs )

- ### [插入排序 insert sort](./sorts/insertsort/)
  [C语言版](./sorts/insertsort/insert_sort.c ) | [JavaScript版](./sorts/insertsort/insert_sort.js ) | [Python版](./sorts/insertsort/insert_sort.py ) | [Java版](./sorts/insertsort/InsertSort.java ) | [TypeScript版](./sorts/insertsort/InsertSort.ts ) | [Go版](./sorts/insertsort/insert_sort.go ) 

- ### [选择排序 selection sort](./sorts/selectionsort/)
  [C语言版](./sorts/selectionsort/selection_sort.c ) | [JavaScript版](./sorts/selectionsort/selection_sort.js ) | [Python版](./sorts/selectionsort/selection_sort.py ) | [Java版](./sorts/selectionsort/SelectionSort.java ) | [TypeScript版](./sorts/selectionsort/SelectionSort.ts ) | [Go版](./sorts/selectionsort/selection_sort.go ) 

- ### [堆排序 heap sort](./sorts/heapsort/)
  [C语言版](./sorts/heapsort/heap_sort.c ) | [JavaScript版](./sorts/heapsort/heap_sort.js ) | [Python版](./sorts/heapsort/heap_sort.py ) | [Java版](./sorts/heapsort/HeapSort.java ) | [TypeScript版](./sorts/heapsort/HeapSort.ts ) | [Go版](./sorts/heapsort/heap_sort.go ) 

- ### [快速排序 quick sort](./sorts/quicksort/)
  [C语言版](./sorts/quicksort/quick_sort.c ) | [JavaScript版](./sorts/quicksort/quick_sort.js ) | [Python版](./sorts/quicksort/quick_sort.py ) | [Java版](./sorts/quicksort/QuickSort.java ) | [TypeScript版](./sorts/quicksort/QuickSort.ts ) | [Go版](./sorts/quicksort/quick_sort.go ) 

- ### [归并排序 merge sort](./sorts/mergesort/)
  [C语言版](./sorts/mergesort/merge_sort.c ) | [JavaScript版](./sorts/mergesort/merge_sort.js ) | [Python版](./sorts/mergesort/merge_sort.py ) | [Java版](./sorts/mergesort/MergeSort.java ) | [TypeScript版](./sorts/mergesort/MergeSort.ts ) | [Go版](./sorts/mergesort/merge_sort.go ) 

- ### [计数排序 counting sort](./sorts/countingsort/)
  [C语言版](./sorts/countingsort/counting_sort.c ) | [JavaScript版](./sorts/countingsort/counting_sort.js ) | [Python版](./sorts/countingsort/counting_sort.py ) | [Java版](./sorts/countingsort/CountingSort.java ) | [TypeScript版](./sorts/countingsort/CountingSort.ts ) | [Go版](./sorts/countingsort/counting_sort.go ) 

- ### [基数排序 radix sort](./sorts/radixsort/)
  [C语言版](./sorts/radixsort/radix_sort.c ) | [JavaScript版](./sorts/radixsort/radix_sort.js ) | [Python版](./sorts/radixsort/radix_sort.py ) | [Java版](./sorts/radixsort/RadixSort.java ) | [TypeScript版](./sorts/radixsort/RadixSort.ts ) | [Go版](./sorts/radixsort/radix_sort.go ) 

- ### [桶排序 bucket sort](./sorts/bucketsort/)
  [C语言版](./sorts/bucketsort/bucket_sort.c ) | [JavaScript版](./sorts/bucketsort/bucket_sort.js ) | [Python版](./sorts/bucketsort/bucket_sort.py ) | [Java版](./sorts/bucketsort/BuketSort.java ) | [TypeScript版](./sorts/bucketsort/BuketSort.ts ) | [Go版](./sorts/bucketsort/bucket_sort.go ) 

- ### [希尔排序 shell sort](./sorts/shellsort/)
  [C语言版](./sorts/shellsort/shell_sort.c ) | [JavaScript版](./sorts/shellsort/shell_sort.js ) | [Python版](./sorts/shellsort/shell_sort.py ) | [Java版](./sorts/shellsort/ShellSort.java ) | [TypeScript版](./sorts/shellsort/ShellSort.ts ) | [Go版](./sorts/shellsort/shell_sort.go )

### 字符串搜索与查找
- ### [朴素搜索](./string/nativesearch/)
  [C语言版](./string/nativesearch/string_search.c ) | [Go语言版](./string/nativesearch/string_search.go ) | [JavaScript版](./string/nativesearch/string_search.js ) | [Python版](./string/nativesearch/string_search.py ) | [Java版](./string/nativesearch/StringSearch.java ) | [TypeScript版](./string/nativesearch/StringSearch.ts )
- ### [二分查找](./search/binarysearch/)
  [C语言版](./search/binarysearch/binary_search.c ) | [Go语言版](./search/binarysearch/binary_search.go ) | [JavaScript版](./search/binarysearch/binary_search.js ) | [Python版](./search/binarysearch/binary_search.py ) | [Java版](./search/binarysearch/BinarySearch.java ) | [TypeScript版](./search/binarysearch/BinarySearch.ts )
- ### [KMP搜索](./string/KMPsearch/)
  [C语言版](./string/KMPsearch/kmp_search.c ) | [Go语言版](./string/KMPsearch/kmp_search.go ) | [JavaScript版](./string/KMPsearch/kmp_search.js ) | [Python版](./string/KMPsearch/kmp_search.py ) | [Java版](./string/KMPsearch/KMPSearch.java ) | [TypeScript版](./string/KMPsearch/KMPSearch.ts )

### 树搜索与遍历
- ### [二叉树遍历](./tree/binarytree/)
  [C语言版](./tree/binarytree/binary_tree.c ) | [JavaScript版](./tree/binarytree/binary_tree.js ) | [Python版](./tree/binarytree/binary_tree.py ) | [Java版](./tree/binarytree/BinaryTree.java ) | [TypeScript版](./tree/binarytree/BinaryTree.ts )

### 质因数分解
- ### [C语言/CPP/Java/Python/JS/TS/Kotlin/Dart/Go/Swift/Objective-C/Rust不同语言质因数分解算法](./factor)
  [C语言版](./factor/factor.c ) | [C++语言版](./factor/factor.cpp ) | [JavaScript版](./factor/factor.js ) |  [TypeScript版](./factor/PrimeFactor.ts ) | [Go语言版](./factor/factor.go )| [Python版](./factor/factor.py ) | [Java版](./factor/Factor.java ) | [Kotlin版](./factor/factor.kt ) | [Dart版](./factor/factor.dart )  | [Swift版](./factor/factor.swift ) | [Objective-C版](./factor/factor.m )  | [Rust版](./factor/factor.rs ) 

### 数组列表去重复项
- ### [数组去重复的N种写法](./unique/)
  [C语言版](./unique/unique.c ) | [Go版](./unique/unique.go ) | [JavaScript版](./unique/unique.js ) | [Python版](./unique/unique.py ) | [Java版](./unique/UniqueArray.java ) | [TypeScript版](./unique/UniqueArray.ts ) | [Dart版](./unique/unique.dart ) | [Rust版](./unique/unique.rs )|

### 递归
- ### [简单递归](./recursion/)

### 数学计算
- ### [数学计算](./number/)

### 日期与日历
- ### [日期与日历](./date/)


## 数据结构
  数据结构就是数据组织与存储方式，也就是把数据聚合在一起，以便进行加工整理。把数据从一种结构换成另一种结构就是数据处理，这是编程最常见的工作。详见：[数据结构概述](./data-structure)

### 数组（Array）
- ### [数组](./data-structure/array/)，聚合数据的集合，可以实现线性和非线性
  
### 链表（Linked List）
- ### [链表](./data-structure/linked/)，线性结构，数据以链式结构存储
  
### 树（Tree）
- ### [树](./data-structure/tree/)，非线性结构，模拟树状结构性质的数据集合，一个顶点
  
### 堆（Heap）
- ### [堆](./data-structure/heap/)，非线性结构，特殊的树形数据结构，一般指完全二叉树
  
### 栈（Stack）
- ### [栈](./data-structure/stack/)，线性结构，后进先出
  
### 队列（Queue）
- ### [队列](./data-structure/queue/)，线性结构，先进先出

### 图（Graph）
- ### [图](./data-structure/graph/)，非线性结构，节点相互连接，每个节点都可以作为顶点

### 散列（Hash）
- ### [散列](./data-structure/hash/)，线性结构，根据键访问储存位置的数据结构

### 结构体（Struct）
- ### [结构体](./data-structure/struct/)，组合一组相关的数据


## 相关链接
- [推荐学习的编程语言](./recommand-learning-languages.md)
- [不同编程语言有哪些差异？如何选择入门语言？](https://www.toutiao.com/article/7122744261904450063) | 
- [如何学好编程？一文彻底搞懂](https://www.toutiao.com/article/7164336029351821855/)
  
## 欢迎加入共建

`本文链接
`[https://github.com/microwind/algorithms](https://github.com/microwind/algorithms)

如果您对这个感兴趣，请加我weixin: springbuild 或者邮件: `jarryli@gmail.com`  `lichunping@buaa.edu.cn` 欢迎一起共建！
