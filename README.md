# 理解算法与数据结构，不同编程语言详解

## 常见的算法有哪些？
- 文本，字符串搜索、字符串压缩、最大公共子序列、回文计算等。主要是针对字符串进行查找。
- 数字，进制转换、开平方、斐波那契数列、质因数分解、数字三角形等。主要是进行数值的运算。
- 排序，冒泡、选择、插入、希尔、归并、快速、堆、计数、桶、基数等。这些跟打扑克排序和挑大小差不多，很好理解。
- 其他算法还有很多，什么动态规划、贪心、矩阵、回溯算法等。
  
<img src="https://pic4.zhimg.com/80/v2-43fde0d41df8fba377333a318f428317_1440w.webp">

## 通过不同算法学习来理解不同语言的差异 [English](./README_en.md)    
  本仓库包含 `C Java Python JavaScript Go TypeScript Dart Swift Kotlin` 等各种流行语言，分析不同语言特色，提供详尽注释说明。一边学算法和数据结构，一边理解编程语言特色。
   
### 通过算法来学习不同语言的差异。

    比如质因数分解、字符搜索、二叉树遍历、排序算法等基础算法，以及各种新的leecode题等。
    每个语言都要自己的特色，通过实际算法和数据结构代码，可以让我们深入理解不同编程语言的差异。

    10大经典排序与多种常见算法例子，分别用C, JS, Java, Python, Go, Dart, Rust等最流行的高级语言编写，
    充分利用不同语言的特点，同时增加了详细注释，通过对比既可以学习算法和数据结构，
    又可以了解语言特色，适合用来学习和交流。
    
    The classic `ten sorts` and multiple algorithm examples by most popular programming languages, 
    such as `C, JS, Java, Python, Go, Dart, Rust` etc., which use the special of different languages, and include detailed comments. 
    Through comparison, you can not only learn algorithms and data structures but also understand the language features, 
    which are suitable for learning and communication.


  参见： [不同编程语言有哪些差异？如何选择入门语言？](https://www.toutiao.com/article/7122744261904450063) | 
  [如何学好编程？一文彻底搞懂](https://www.toutiao.com/article/7164336029351821855/)

# 常见算法思想
贪心算法（Greedy Algorithm）、分治算法（Divide and Conquer）、动态规划（Dynamic Programming）、回溯算法（Backtracking）、图算法（Graph Algorithms）、分支界限（Branch and Bound）等。详见：[10大算法思想](./algorithmic_thinking.md)


# 常见算法例子
    
## 质因数分解算法
- [C语言/CPP/Java/Python/JS/TS/Kotlin/Dart/Go/Swift/Objective-c 不同语言实现](./factor)
    
## 10大经典排序算法
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

## 数组列表去重复项
- ### [数组去重复的N种写法](./unique/)
[C语言版](./unique/unique.c ) | [JavaScript版](./unique/unique.js ) | [Python版](./unique/unique.py ) | [Java版](./unique/UniqueArray.java ) | [TypeScript版](./unique/UniqueArray.ts )

## 字符串搜索与查找
- ### [朴素搜索](./string/nativesearch/)
[C语言版](./string/nativesearch/string_search.c ) | [JavaScript版](./string/nativesearch/string_search.js ) | [Python版](./string/nativesearch/string_search.py ) | [Java版](./string/nativesearch/StringSearch.java ) | [TypeScript版](./string/nativesearch/StringSearch.ts )
- ### [二分查找](./search/binarysearch/)
[C语言版](./search/binarysearch/binary_search.c ) | [JavaScript版](./search/binarysearch/binary_search.js ) | [Python版](./search/binarysearch/binary_search.py ) | [Java版](./search/binarysearch/BinarySearch.java ) | [TypeScript版](./search/binarysearch/BinarySearch.ts )

## 树搜索与遍历
- ### [二叉树遍历](./tree/binarytree/)
[C语言版](./tree/binarytree/binary_tree.c ) | [JavaScript版](./tree/binarytree/binary_tree.js ) | [Python版](./tree/binarytree/binary_tree.py ) | [Java版](./tree/binarytree/BinaryTree.java ) | [TypeScript版](./tree/binarytree/BinaryTree.ts )

## 递归
- ### [简单递归](./recursion/)

## 数字计算
- ### [数字计算](./number/)

## 日期与日历
- ### [日期与日历](./date/)

# 数据结构例子
## 数组（Array）
- ### [数组](./data-structure/array/)，聚合数据的集合，可以实现线性和非线性
  
## 链表（Linked List）
- ### [链表](./data-structure/linked/)，线性结构，数据以链式结构存储
  
## 树（Tree）
- ### [树](./data-structure/tree/)，非线性结构，模拟树状结构性质的数据集合，一个顶点
  
## 堆（Heap）
- ### [堆](./data-structure/heap/)，非线性结构，特殊的树形数据结构，一般指完全二叉树
  
## 栈（Stack）
- ### [栈](./data-structure/stack/)，线性结构，后进先出
  
## 队列（Queue）
- ### [队列](./data-structure/queue/)，线性结构，先进先出

## 图（Graph）
- ### [图](./data-structure/graph/)，非线性结构，节点相互连接，每个节点都可以作为顶点

## 散列（Hash）
- ### [散列](./data-structure/hash/)，线性结构，根据键访问储存位置的数据结构

## 结构体（Struct）
- ### [结构体](./data-structure/struct/)，组合一组相关的数据


`本文链接
`[https://github.com/microwind/algorithms](https://github.com/microwind/algorithms)

## 其他
[推荐学习的编程语言](./recommand-learning-languages.md)
## 欢迎加入共建

如果您对这个感兴趣，请加我weixin: springbuild 或者邮件: `jarryli@gmail.com`  `lichunping@buaa.edu.cn` 欢迎一起共建！
