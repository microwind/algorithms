# Understanding Algorithms and Data Structures, Learning Different Programming Languages [中文](./README.md)

Learn data structures and algorithms based on different programming languages, including `C`, `Java`, `Python`, `JavaScript`, `Go`, `TypeScript`, etc., with ample comments and explanations.

## Project Features:
1. Covers a variety of algorithms such as numerical calculations, string search, tree traversal, sorting, dynamic programming, etc.
2. Each algorithm is implemented in multiple languages to help understand the features of different programming languages.
3. Examples are carefully designed for students or programmers to learn and analyze, improving programming skills.

# Overview of Algorithms

## What are common algorithms?
- **Text Search**: Includes linear search, binary search, tree search, longest common subsequence, palindrome computation, etc., mainly for string searching.
- **Mathematical Computations**: Includes base conversion, square roots, Fibonacci sequence, prime factorization, Pascal’s triangle, etc., mainly for numerical calculations.
- **Sorting Algorithms**: Includes bubble, selection, insertion, shell, merge, quick, heap, counting, bucket, radix, etc., for ordering data.
- **Other Algorithms**: Includes dynamic programming, greedy algorithms, divide and conquer, backtracking, graph algorithms (e.g., breadth-first search, depth-first search, Dijkstra’s algorithm, Kruskal’s algorithm, etc.), and machine learning and artificial intelligence algorithms such as classification, clustering, deep learning, reinforcement learning, etc.

![Algorithm Overview](https://pic4.zhimg.com/80/v2-43fde0d41df8fba377333a318f428317_1440w.webp)

## Common Algorithm Ideas
- **Greedy Algorithm**: A method that expects to find the global optimum by selecting the local optimum at each step.
- **Divide and Conquer**: Breaks a problem into smaller subproblems, solves them independently, and then combines the results.
- **Dynamic Programming**: Solves complex problems by breaking them down into simpler overlapping subproblems.
- **Backtracking**: Solves problems by incrementally building candidate solutions and abandoning those that fail to meet the criteria.
- **Graph Algorithms**: Includes breadth-first search, depth-first search, Dijkstra’s algorithm, Kruskal’s algorithm, etc., for solving graph-related problems.
- **Branch and Bound**: A method for solving combinatorial optimization problems by systematically exploring the branches of the search tree.

For detailed information, see: [10 Classic Algorithm Ideas](./algorithmic_thinking.md)

## 10 Classic Sorting Algorithms

| Sorting Algorithm | C | JavaScript | Python | Java | TypeScript | Go | Time Complexity (Average/Worst) | Space Complexity | Stability | Suitable Scenarios |
|-------------------|-----------|---------------------|----------------|--------------|---------------------|------------|--------------------------------|------------------|-----------|-------------------|
| [Bubble Sort](./sorts/bubblesort/) | [C](./sorts/bubblesort/bubble_sort.c) | [JS](./sorts/bubblesort/bubble_sort.js) | [Python](./sorts/bubblesort/bubble_sort.py) | [Java](./sorts/bubblesort/BubbleSort.java) | [TS](./sorts/bubblesort/BubbleSort.ts) | [Go](./sorts/bubblesort/bubble_sort.go) | O(n²) / O(n²) | O(1) | ✅ | Suitable for small-scale data sorting, educational purposes |
| [Insertion Sort](./sorts/insertsort/) | [C](./sorts/insertsort/insert_sort.c) | [JS](./sorts/insertsort/insert_sort.js) | [Python](./sorts/insertsort/insert_sort.py) | [Java](./sorts/insertsort/InsertSort.java) | [TS](./sorts/insertsort/InsertSort.ts) | [Go](./sorts/insertsort/insert_sort.go) | O(n²) / O(n²) | O(1) | ✅ | Suitable for small-scale data or nearly sorted elements |
| [Selection Sort](./sorts/selectionsort/) | [C](./sorts/selectionsort/selection_sort.c) | [JS](./sorts/selectionsort/selection_sort.js) | [Python](./sorts/selectionsort/selection_sort.py) | [Java](./sorts/selectionsort/SelectionSort.java) | [TS](./sorts/selectionsort/SelectionSort.ts) | [Go](./sorts/selectionsort/selection_sort.go) | O(n²) / O(n²) | O(1) | ❌ | Suitable for small-scale data with fewer swaps |
| [Heap Sort](./sorts/heapsort/) | [C](./sorts/heapsort/heap_sort.c) | [JS](./sorts/heapsort/heap_sort.js) | [Python](./sorts/heapsort/heap_sort.py) | [Java](./sorts/heapsort/HeapSort.java) | [TS](./sorts/heapsort/HeapSort.ts) | [Go](./sorts/heapsort/heap_sort.go) | O(n log n) / O(n log n) | O(1) | ❌ | Suitable for priority queues, TOP K problems |
| [Quick Sort](./sorts/quicksort/) | [C](./sorts/quicksort/quick_sort.c) | [JS](./sorts/quicksort/quick_sort.js) | [Python](./sorts/quicksort/quick_sort.py) | [Java](./sorts/quicksort/QuickSort.java) | [TS](./sorts/quicksort/QuickSort.ts) | [Go](./sorts/quicksort/quick_sort.go) | O(n log n) / O(n²) | O(log n) | ❌ | Suitable for general sorting scenarios, efficient but unstable |
| [Merge Sort](./sorts/mergesort/) | [C](./sorts/mergesort/merge_sort.c) | [JS](./sorts/mergesort/merge_sort.js) | [Python](./sorts/mergesort/merge_sort.py) | [Java](./sorts/mergesort/MergeSort.java) | [TS](./sorts/mergesort/MergeSort.ts) | [Go](./sorts/mergesort/merge_sort.go) | O(n log n) / O(n log n) | O(n) | ✅ | Suitable for large-scale data sorting, external sorting |
| [Counting Sort](./sorts/countingsort/) | [C](./sorts/countingsort/counting_sort.c) | [JS](./sorts/countingsort/counting_sort.js) | [Python](./sorts/countingsort/counting_sort.py) | [Java](./sorts/countingsort/CountingSort.java) | [TS](./sorts/countingsort/CountingSort.ts) | [Go](./sorts/countingsort/counting_sort.go) | O(n + k) / O(n + k) | O(k) | ✅ | Suitable for sorting integers with limited range |
| [Radix Sort](./sorts/radixsort/) | [C](./sorts/radixsort/radix_sort.c) | [JS](./sorts/radixsort/radix_sort.js) | [Python](./sorts/radixsort/radix_sort.py) | [Java](./sorts/radixsort/RadixSort.java) | [TS](./sorts/radixsort/RadixSort.ts) | [Go](./sorts/radixsort/radix_sort.go) | O(nk) / O(nk) | O(n + k) | ✅ | Suitable for large-scale integer sorting, such as ID numbers, phone numbers |
| [Bucket Sort](./sorts/bucketsort/) | [C](./sorts/bucketsort/bucket_sort.c) | [JS](./sorts/bucketsort/bucket_sort.js) | [Python](./sorts/bucketsort/bucket_sort.py) | [Java](./sorts/bucketsort/BuketSort.java) | [TS](./sorts/bucketsort/BuketSort.ts) | [Go](./sorts/bucketsort/bucket_sort.go) | O(n + k) / O(n²) | O(n + k) | ✅ | Suitable for uniformly distributed data range |
| [Shell Sort](./sorts/shellsort/) | [C](./sorts/shellsort/shell_sort.c) | [JS](./sorts/shellsort/shell_sort.js) | [Python](./sorts/shellsort/shell_sort.py) | [Java](./sorts/shellsort/ShellSort.java) | [TS](./sorts/shellsort/ShellSort.ts) | [Go](./sorts/shellsort/shell_sort.go) | O(n log n) / O(n²) | O(1) | ❌ | Suitable for medium-scale data sorting, semi-ordered data |

## String Search and Lookup

| Algorithm | C Language | Go Language | JS Version | Python Version | Java Version | TypeScript Version | Time Complexity (Average/Worst) | Space Complexity | Suitable Scenarios |
|-----------|------------|-------------|------------|----------------|--------------|--------------------|-------------------------------|------------------|--------------------|
| [Naive Search](./string/nativesearch/) | [C](./string/nativesearch/string_search.c) | [Go](./string/nativesearch/string_search.go) | [JS](./string/nativesearch/string_search.js) | [Python](./string/nativesearch/string_search.py) | [Java](./string/nativesearch/StringSearch.java) | [TS](./string/nativesearch/StringSearch.ts) | O(mn) / O(mn) | O(1) | Suitable for small-scale text search |
| [Binary Search](./search/binarysearch/) | [C](./search/binarysearch/binary_search.c) | [Go](./search/binarysearch/binary_search.go) | [JS](./search/binarysearch/binary_search.js) | [Python](./search/binarysearch/binary_search.py) | [Java](./search/binarysearch/BinarySearch.java) | [TS](./search/binarysearch/BinarySearch.ts) | O(log n) / O(log n) | O(1) | Suitable for searching in sorted arrays |
| [KMP Search](./string/KMPsearch/) | [C](./string/KMPsearch/kmp_search.c) | [Go](./string/KMPsearch/kmp_search.go) | [JS](./string/KMPsearch/kmp_search.js) | [Python](./string/KMPsearch/kmp_search.py) | [Java](./string/KMPsearch/KMPSearch.java) | [TS](./string/KMPsearch/KMPSearch.ts) | O(n + m) / O(n + m) | O(m) | Suitable for large-scale text search |

## Tree Search and Traversal

| Algorithm | C Language | JS Version | Python Version | Java Version | TypeScript Version | Time Complexity (Average/Worst) | Space Complexity | Suitable Scenarios |
|-----------|------------|-------------|----------------|--------------|--------------------|-------------------------------|------------------|--------------------|
| [Binary Tree Traversal](./tree/binarytree/) | [C](./tree/binarytree/binary_tree.c) | [JS](./tree/binarytree/binary_tree.js) | [Python](./tree/binarytree/binary_tree.py) | [Java](./tree/binarytree/BinaryTree.java) | [TS](./tree/binarytree/BinaryTree.ts) | O(n) / O(n) | O(n) | Suitable for tree structure data traversal, such as XML parsing, file system traversal |

## Prime Factorization

| Language | Code Link | Complexity | Suitable Scenarios |
|----------|-----------|------------|--------------------|
| C | [factor.c](./factor/factor.c) | O(√n) | For calculating prime factorization of large integers |
| C++ | [factor.cpp](./factor/factor.cpp) | O(√n) | Suitable for efficient mathematical calculations |
| JavaScript | [factor.js](./factor/factor.js) | O(√n) | For number theory calculations on the web |
| TypeScript | [PrimeFactor.ts](./factor/PrimeFactor.ts) | O(√n) | Suitable for front-end or Node.js calculations |
| Go | [factor.go](./factor/factor.go) | O(√n) | Suitable for backend service calculations |
| Python | [factor.py](./factor/factor.py) | O(√n) | Suitable for scientific computations and data analysis |
| Java | [Factor.java](./factor/Factor.java) | O(√n) | Suitable for enterprise-level application calculations |
| Kotlin | [factor.kt](./factor/factor.kt) | O(√n) | Suitable for Android and backend calculations |
| Dart | [factor.dart](./factor/factor.dart) | O(√n) | Suitable for Flutter applications |
| Swift | [factor.swift](./factor/factor.swift) | O(√n) | Suitable for iOS/macOS development |
| Objective-C | [factor.m](./factor/factor.m) | O(√n) | Suitable for older versions of iOS/macOS |
| Rust | [factor.rs](./factor/factor.rs) | O(√n) | Suitable for high-performance computing |

## Removing Duplicate Items from Arrays and Lists

| Language | Code Link | Time Complexity | Suitable Scenarios |
|----------|-----------|-----------------|--------------------|
| C | [unique.c](./unique/unique.c) | O(n log n) | Suitable for embedded development |
| Go | [unique.go](./unique/unique.go) | O(n log n) | Suitable for high-concurrency scenarios |
| JS | [unique.js](./unique/unique.js) | O(n) | Suitable for front-end data processing |
| Python | [unique.py](./unique/unique.py) | O(n) | Suitable for data cleaning and analysis |
| Java | [UniqueArray.java](./unique/UniqueArray.java) | O(n log n) | Suitable for enterprise-level applications |
| TypeScript | [UniqueArray.ts](./unique/UniqueArray.ts) | O(n) | Suitable for front-end TypeScript projects |
| Dart | [unique.dart](./unique/unique.dart) | O(n) | Suitable for Flutter applications |
| Rust | [unique.rs](./unique/unique.rs) | O(n) | Suitable for high-performance computing |

## Recursion

| Algorithm | Code Link | Time Complexity | Space Complexity | Suitable Scenarios |
|-----------|-----------|-----------------|------------------|--------------------|
| [Simple Recursion](./recursion/) | [C](./recursion/) | O(2^n) | O(n) | Suitable for divide-and-conquer algorithms, tree and graph traversal, backtracking problems |

## Mathematical Computation

| Algorithm | Code Link | Time Complexity | Space Complexity | Suitable Scenarios |
|-----------|-----------|-----------------|------------------|--------------------|
| [Mathematical Computation](./number/) | [C](./number/) | O(n) | O(1) | Suitable for number theory, addition, multiplication, large integer computations, etc. |

## Date and Calendar

| Algorithm | Code Link | Time Complexity | Space Complexity | Suitable Scenarios |
|-----------|-----------|-----------------|------------------|--------------------|
| [Date and Calendar](./date/) | [C](./date/) | O(1) | O(1) | Suitable for date calculations, holiday predictions, date conversions, etc. |

---

# Data Structures
Data structures refer to the ways data is organized and stored, aggregating data together for processing and organization. Different data structures have different efficiency for access, insertion, deletion, etc. By selecting the appropriate data structure, data can be processed efficiently. See also: [Overview of Data Structures](./data-structure)

| Data Structure | Description | Structural Features | Access Efficiency | Insertion/Deletion Efficiency |
|----------------|-------------|---------------------|-------------------|------------------------------|
| [Array](./data-structure/array/) | A collection of elements of the same data type, supports random access by index | Continuous memory storage, supports linear or non-linear | O(1) | O(n) |
| [Linked List](./data-structure/linked/) | Data stored in a chain structure, connected by pointers, including singly linked list, doubly linked list, and circular linked list | Linear structure, non-contiguous memory | O(n) | O(1) (head) / O(n) (middle) |
| [Tree](./data-structure/tree/) | A tree-like data structure, nodes are organized in hierarchical relationships, common types include binary tree, binary search tree, balanced tree, etc. | Non-linear structure, one root node, unlimited number of child nodes | O(log n) | O(log n) |
| [Heap](./data-structure/heap/) | A special type of complete binary tree that satisfies the heap property (max-heap or min-heap), often used in priority queues | Non-linear structure, supports efficient operations on extreme values | O(1) (extract top) | O(log n) |
| [Stack](./data-structure/stack/) | A Last-In-First-Out (LIFO) collection of data | Linear structure, sequential or chain storage, only operations at the top of the stack | O(1) | O(1) |
| [Queue](./data-structure/queue/) | A First-In-First-Out (FIFO) collection of data | Linear structure, sequential or chain storage, supports insertion at the rear and deletion at the front | O(1) | O(1) |
| [Graph](./data-structure/graph/) | A data structure consisting of nodes (vertices) and edges, common storage methods include adjacency lists and adjacency matrices | Non-linear structure, nodes can be connected many-to-many | O(1) (adjacency matrix) / O(n) (adjacency list) | O(1) (adjacency matrix) / O(n) (adjacency list) |
| [Hash](./data-structure/hash/) | A data structure that maps keys to storage locations using hash functions, supporting fast lookups, insertions, and deletions | Linear structure, key-value mapping | O(1) (amortized) | O(1) (amortized) |
| [Struct](./data-structure/struct/) | Combines multiple types of data into a whole, often used to represent complex objects | Custom structure, fields fixed, containing various data types | O(1) | O(1) |

---

## Related Links
- [Recommended Programming Languages to Learn](./recommand-learning-languages.md)
- [What are the Differences Between Programming Languages? How to Choose the Right One for Beginners?](https://www.toutiao.com/article/7122744261904450063)
- [How to Learn Programming? A Complete Guide](https://zhuanlan.zhihu.com/p/582174773)

## Join Us in Co-Building

[Link to this document](https://github.com/microwind/algorithms)

If you're interested in this project, please add me. I welcome you to build it together!

**WeChat:** `springbuild`

**Email:** `jarryli@gmail.com` or `lichunping@buaa.edu.cn`
