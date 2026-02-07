# Understanding Algorithms and Data Structures, Learning Different Programming Languages [中文](./README.md)

This repository helps you learn data structures and algorithms with different programming languages, including `C` `Java` `Python` `JavaScript` `Go` `TypeScript`, with rich comments and explanations.

In the AI era, AI can replace a lot of basic coding tasks, but it cannot replace human thinking and understanding. Only by deeply understanding the core of programming (data structures + algorithms) can we truly harness AI and make it produce high-value results.

Surface-level APIs, frameworks, and application solutions change rapidly, while data structures, algorithms, and fundamental logic endure. Surface technologies require fast learning and constant updates; fundamental principles require repeated study and reflection to continuously improve understanding.

## Project Highlights
1. Covers numerical computation, string search, tree traversal, sorting, dynamic programming, and more.
2. Each algorithm has multiple language implementations, helping you understand language features through algorithms and data structures.
3. Examples are rich and progressive, suitable for students and programmers to learn, analyze, and continuously improve their coding skills.

## Learning Value for Students and Engineers
This project connects "concept understanding -> code implementation -> language comparison -> practice and progression" into a clear path, making it a long-term resource for coursework, self-study, interviews, and engineering skill development.

You will gain:
- A systematic learning path: from fundamentals to classic algorithms, then to problem sets and projects, step by step.
- Multi-language comparison: the same algorithm implemented in multiple languages to reveal differences and engineering practices.
- Practical and reusable materials: most directories include runnable code and explanations, useful for coursework, interviews, and real projects.
- Stronger foundations and thinking: emphasis on complexity analysis and algorithmic ideas to improve efficiency and correctness.

# Algorithm Overview

## What are common algorithms?
- **Text search**: linear search, binary search, tree-based search, longest common subsequence, palindrome computation, mainly for string search.
- **Mathematical computation**: base conversion, square roots, Fibonacci sequence, prime factorization, numeric triangles, mainly for numerical computation.
- **Sorting algorithms**: bubble, selection, insertion, shell, merge, quick, heap, counting, bucket, radix, used to order data.
- **Other algorithms**: dynamic programming, greedy algorithms, divide and conquer, backtracking, graph algorithms (e.g., BFS, DFS, Dijkstra, Kruskal), plus machine learning and AI algorithms like classification, clustering, deep learning, and reinforcement learning.

![Algorithm Overview](./07-resources/images/algorithm-structure.png)

## Common algorithmic paradigms
- **Greedy**: chooses the local optimum at each step to reach a global optimum.
- **Divide and conquer**: splits a problem into smaller subproblems, solves them independently, then combines results.
- **Dynamic programming**: breaks a complex problem into overlapping subproblems and solves them with memoization or tabulation.
- **Backtracking**: builds solutions incrementally and abandons those that violate constraints.
- **Graph algorithms**: BFS, DFS, Dijkstra, Kruskal, etc., for graph-related problems.
- **Branch and bound**: explores a search tree with bounds to prune unnecessary branches.

For details, see: [10 Classic Algorithm Ideas](./00-start-here/algorithmic_thinking.md)

## 10 Classic Sorting Algorithms

| Sorting Algorithm | C | JS | Python | Java | TS | Go | Time Complexity (Avg/Worst) | Space Complexity | Stable | Use Cases |
|---------|--------|-------------|---------|-------|-------------|-----|--------------------|---------|------|--------|
| [Bubble Sort](./03-classic-algorithms/sorting/bubblesort/) | [C](./03-classic-algorithms/sorting/bubblesort/bubble_sort.c) | [JS](./03-classic-algorithms/sorting/bubblesort/bubble_sort.js) | [Python](./03-classic-algorithms/sorting/bubblesort/bubble_sort.py) | [Java](./03-classic-algorithms/sorting/bubblesort/BubbleSort.java) | [TS](./03-classic-algorithms/sorting/bubblesort/BubbleSort.ts) | [Go](./03-classic-algorithms/sorting/bubblesort/bubble_sort.go) | O(n^2) / O(n^2) | O(1) | Yes | Suitable for small datasets, educational use |
| [Insertion Sort](./03-classic-algorithms/sorting/insertsort/) | [C](./03-classic-algorithms/sorting/insertsort/insert_sort.c) | [JS](./03-classic-algorithms/sorting/insertsort/insert_sort.js) | [Python](./03-classic-algorithms/sorting/insertsort/insert_sort.py) | [Java](./03-classic-algorithms/sorting/insertsort/InsertSort.java) | [TS](./03-classic-algorithms/sorting/insertsort/InsertSort.ts) | [Go](./03-classic-algorithms/sorting/insertsort/insert_sort.go) | O(n^2) / O(n^2) | O(1) | Yes | Suitable for small datasets or nearly sorted data |
| [Selection Sort](./03-classic-algorithms/sorting/selectionsort/) | [C](./03-classic-algorithms/sorting/selectionsort/selection_sort.c) | [JS](./03-classic-algorithms/sorting/selectionsort/selection_sort.js) | [Python](./03-classic-algorithms/sorting/selectionsort/selection_sort.py) | [Java](./03-classic-algorithms/sorting/selectionsort/SelectionSort.java) | [TS](./03-classic-algorithms/sorting/selectionsort/SelectionSort.ts) | [Go](./03-classic-algorithms/sorting/selectionsort/selection_sort.go) | O(n^2) / O(n^2) | O(1) | No | Suitable for small datasets, fewer swaps |
| [Heap Sort](./03-classic-algorithms/sorting/heapsort/) | [C](./03-classic-algorithms/sorting/heapsort/heap_sort.c) | [JS](./03-classic-algorithms/sorting/heapsort/heap_sort.js) | [Python](./03-classic-algorithms/sorting/heapsort/heap_sort.py) | [Java](./03-classic-algorithms/sorting/heapsort/HeapSort.java) | [TS](./03-classic-algorithms/sorting/heapsort/HeapSort.ts) | [Go](./03-classic-algorithms/sorting/heapsort/heap_sort.go) | O(n log n) / O(n log n) | O(1) | No | Suitable for priority queues and Top K |
| [Quick Sort](./03-classic-algorithms/sorting/quicksort/) | [C](./03-classic-algorithms/sorting/quicksort/quick_sort.c) | [JS](./03-classic-algorithms/sorting/quicksort/quick_sort.js) | [Python](./03-classic-algorithms/sorting/quicksort/quick_sort.py) | [Java](./03-classic-algorithms/sorting/quicksort/QuickSort.java) | [TS](./03-classic-algorithms/sorting/quicksort/QuickSort.ts) | [Go](./03-classic-algorithms/sorting/quicksort/quick_sort.go) | O(n log n) / O(n^2) | O(log n) | No | Suitable for general sorting, fast but unstable |
| [Merge Sort](./03-classic-algorithms/sorting/mergesort/) | [C](./03-classic-algorithms/sorting/mergesort/merge_sort.c) | [JS](./03-classic-algorithms/sorting/mergesort/merge_sort.js) | [Python](./03-classic-algorithms/sorting/mergesort/merge_sort.py) | [Java](./03-classic-algorithms/sorting/mergesort/MergeSort.java) | [TS](./03-classic-algorithms/sorting/mergesort/MergeSort.ts) | [Go](./03-classic-algorithms/sorting/mergesort/merge_sort.go) | O(n log n) / O(n log n) | O(n) | Yes | Suitable for large datasets and external sorting |
| [Counting Sort](./03-classic-algorithms/sorting/countingsort/) | [C](./03-classic-algorithms/sorting/countingsort/counting_sort.c) | [JS](./03-classic-algorithms/sorting/countingsort/counting_sort.js) | [Python](./03-classic-algorithms/sorting/countingsort/counting_sort.py) | [Java](./03-classic-algorithms/sorting/countingsort/CountingSort.java) | [TS](./03-classic-algorithms/sorting/countingsort/CountingSort.ts) | [Go](./03-classic-algorithms/sorting/countingsort/counting_sort.go) | O(n + k) / O(n + k) | O(k) | Yes | Suitable for integers with limited range |
| [Radix Sort](./03-classic-algorithms/sorting/radixsort/) | [C](./03-classic-algorithms/sorting/radixsort/radix_sort.c) | [JS](./03-classic-algorithms/sorting/radixsort/radix_sort.js) | [Python](./03-classic-algorithms/sorting/radixsort/radix_sort.py) | [Java](./03-classic-algorithms/sorting/radixsort/RadixSort.java) | [TS](./03-classic-algorithms/sorting/radixsort/RadixSort.ts) | [Go](./03-classic-algorithms/sorting/radixsort/radix_sort.go) | O(nk) / O(nk) | O(n + k) | Yes | Suitable for large-scale integer sorting, IDs, phone numbers |
| [Bucket Sort](./03-classic-algorithms/sorting/bucketsort/) | [C](./03-classic-algorithms/sorting/bucketsort/bucket_sort.c) | [JS](./03-classic-algorithms/sorting/bucketsort/bucket_sort.js) | [Python](./03-classic-algorithms/sorting/bucketsort/bucket_sort.py) | [Java](./03-classic-algorithms/sorting/bucketsort/BuketSort.java) | [TS](./03-classic-algorithms/sorting/bucketsort/BuketSort.ts) | [Go](./03-classic-algorithms/sorting/bucketsort/bucket_sort.go) | O(n + k) / O(n^2) | O(n + k) | Yes | Suitable for uniformly distributed data |
| [Shell Sort](./03-classic-algorithms/sorting/shellsort/) | [C](./03-classic-algorithms/sorting/shellsort/shell_sort.c) | [JS](./03-classic-algorithms/sorting/shellsort/shell_sort.js) | [Python](./03-classic-algorithms/sorting/shellsort/shell_sort.py) | [Java](./03-classic-algorithms/sorting/shellsort/ShellSort.java) | [TS](./03-classic-algorithms/sorting/shellsort/ShellSort.ts) | [Go](./03-classic-algorithms/sorting/shellsort/shell_sort.go) | O(n log n) / O(n^2) | O(1) | No | Suitable for medium datasets, partially sorted data |

## String Search and Lookup

| Algorithm | C | Go | JS | Python | Java | TS | Time Complexity (Avg/Worst) | Space Complexity | Use Cases |
|------|--------|---------|-------------|---------|-------|-------------|--------------------|---------|--------|
| [Naive Search](./03-classic-algorithms/string/nativesearch/) | [C](./03-classic-algorithms/string/nativesearch/string_search.c) | [Go](./03-classic-algorithms/string/nativesearch/string_search.go) | [JS](./03-classic-algorithms/string/nativesearch/string_search.js) | [Python](./03-classic-algorithms/string/nativesearch/string_search.py) | [Java](./03-classic-algorithms/string/nativesearch/StringSearch.java) | [TS](./03-classic-algorithms/string/nativesearch/StringSearch.ts) | O(mn) / O(mn) | O(1) | Suitable for small-scale text search |
| [Binary Search](./03-classic-algorithms/searching/binarysearch/) | [C](./03-classic-algorithms/searching/binarysearch/binary_search.c) | [Go](./03-classic-algorithms/searching/binarysearch/binary_search.go) | [JS](./03-classic-algorithms/searching/binarysearch/binary_search.js) | [Python](./03-classic-algorithms/searching/binarysearch/binary_search.py) | [Java](./03-classic-algorithms/searching/binarysearch/BinarySearch.java) | [TS](./03-classic-algorithms/searching/binarysearch/BinarySearch.ts) | O(log n) / O(log n) | O(1) | Suitable for searching in sorted arrays |
| [KMP Search](./03-classic-algorithms/string/KMPsearch/) | [C](./03-classic-algorithms/string/KMPsearch/kmp_search.c) | [Go](./03-classic-algorithms/string/KMPsearch/kmp_search.go) | [JS](./03-classic-algorithms/string/KMPsearch/kmp_search.js) | [Python](./03-classic-algorithms/string/KMPsearch/kmp_search.py) | [Java](./03-classic-algorithms/string/KMPsearch/KMPSearch.java) | [TS](./03-classic-algorithms/string/KMPsearch/KMPSearch.ts) | O(n + m) / O(n + m) | O(m) | Suitable for large-scale text search |

## Tree Search and Traversal

| Algorithm | C | JS | Python | Java | TS | Time Complexity (Avg/Worst) | Space Complexity | Use Cases |
|------|--------|-------------|---------|-------|-------------|--------------------|---------|--------|
| [Binary Tree Traversal](./03-classic-algorithms/tree/binarytree/) | [C](./03-classic-algorithms/tree/binarytree/binary_tree.c) | [JS](./03-classic-algorithms/tree/binarytree/binary_tree.js) | [Python](./03-classic-algorithms/tree/binarytree/binary_tree.py) | [Java](./03-classic-algorithms/tree/binarytree/BinaryTree.java) | [TS](./03-classic-algorithms/tree/binarytree/BinaryTree.ts) | O(n) / O(n) | O(n) | Suitable for tree traversal, e.g., XML parsing or file system traversal |

## Prime Factorization

| Language | Code Link | Complexity | Use Cases |
|------|---------|--------|--------|
| C | [factor.c](./03-classic-algorithms/math/factor/factor.c) | O(sqrt(n)) | Prime factorization of large integers |
| C++ | [factor.cpp](./03-classic-algorithms/math/factor/factor.cpp) | O(sqrt(n)) | Efficient mathematical computation |
| JavaScript | [factor.js](./03-classic-algorithms/math/factor/factor.js) | O(sqrt(n)) | Number theory on the web |
| TypeScript | [PrimeFactor.ts](./03-classic-algorithms/math/factor/PrimeFactor.ts) | O(sqrt(n)) | Front-end or Node.js computation |
| Go | [factor.go](./03-classic-algorithms/math/factor/factor.go) | O(sqrt(n)) | Backend service computation |
| Python | [factor.py](./03-classic-algorithms/math/factor/factor.py) | O(sqrt(n)) | Scientific computing and data analysis |
| Java | [Factor.java](./03-classic-algorithms/math/factor/Factor.java) | O(sqrt(n)) | Enterprise application computation |
| Kotlin | [factor.kt](./03-classic-algorithms/math/factor/factor.kt) | O(sqrt(n)) | Android and backend computation |
| Dart | [factor.dart](./03-classic-algorithms/math/factor/factor.dart) | O(sqrt(n)) | Flutter applications |
| Swift | [factor.swift](./03-classic-algorithms/math/factor/factor.swift) | O(sqrt(n)) | iOS/macOS development |
| Objective-C | [factor.m](./03-classic-algorithms/math/factor/factor.m) | O(sqrt(n)) | Legacy iOS/macOS development |
| Rust | [factor.rs](./03-classic-algorithms/math/factor/factor.rs) | O(sqrt(n)) | High-performance computation |

## Removing Duplicate Items from Arrays and Lists

| Language | Code Link | Time Complexity | Use Cases |
|------|---------|--------|--------|
| C | [unique.c](./03-classic-algorithms/array/unique/unique.c) | O(n log n) | Embedded development |
| Go | [unique.go](./03-classic-algorithms/array/unique/unique.go) | O(n log n) | High-concurrency scenarios |
| JS | [unique.js](./03-classic-algorithms/array/unique/unique.js) | O(n) | Front-end data processing |
| Python | [unique.py](./03-classic-algorithms/array/unique/unique.py) | O(n) | Data cleaning and analysis |
| Java | [UniqueArray.java](./03-classic-algorithms/array/unique/UniqueArray.java) | O(n log n) | Enterprise applications |
| TypeScript | [UniqueArray.ts](./03-classic-algorithms/array/unique/UniqueArray.ts) | O(n) | Front-end TypeScript projects |
| Dart | [unique.dart](./03-classic-algorithms/array/unique/unique.dart) | O(n) | Flutter applications |
| Rust | [unique.rs](./03-classic-algorithms/array/unique/unique.rs) | O(n) | High-performance computation |

## Recursion

| Algorithm | Code Link | Time Complexity | Space Complexity | Use Cases |
|------|---------|------------|------------|--------|
| [Basic Recursion](./02-algorithmic-thinking/recursion/) | [C](./02-algorithmic-thinking/recursion/) | O(2^n) | O(n) | Divide and conquer, tree/graph traversal, backtracking |

## Mathematical Computation

| Algorithm | Code Link | Time Complexity | Space Complexity | Use Cases |
|------|---------|------------|------------|--------|
| [Mathematical Computation](./03-classic-algorithms/math/number/) | [C](./03-classic-algorithms/math/number/) | O(n) | O(1) | Number theory, addition, multiplication, big integer computation |

## Date and Calendar

| Algorithm | Code Link | Time Complexity | Space Complexity | Use Cases |
|------|---------|------------|------------|--------|
| [Date and Calendar](./03-classic-algorithms/date-time/) | [C](./03-classic-algorithms/date-time/) | O(1) | O(1) | Date calculation, holiday estimation, date conversion |

---

# Data Structures
Data structures organize and store data, enabling efficient processing. Different data structures have different efficiency for access, insertion, and deletion. Choosing the right structure improves performance. See: [Overview of Data Structures](./01-data-structures)

| Data Structure | Description | Characteristics | Access Complexity | Insert/Delete Complexity |
|---------|------|---------|---------|-------------|
| [Array](./01-data-structures/array/) | A collection of elements of the same type, supports random access by index | Contiguous memory, linear or non-linear | O(1) | O(n) |
| [Linked List](./01-data-structures/linked/) | Nodes connected by pointers; includes singly, doubly, and circular lists | Linear, non-contiguous memory | O(n) | O(1) (head) / O(n) (middle) |
| [Tree](./01-data-structures/tree/) | Hierarchical data; includes binary tree, BST, balanced trees | Non-linear, one root node, multiple children | O(log n) | O(log n) |
| [Heap](./01-data-structures/heap/) | Special complete binary tree with heap property | Non-linear, efficient for extremes | O(1) (peek) | O(log n) |
| [Stack](./01-data-structures/stack/) | LIFO structure | Linear, only top operations | O(1) | O(1) |
| [Queue](./01-data-structures/queue/) | FIFO structure | Linear, enqueue at tail, dequeue at head | O(1) | O(1) |
| [Graph](./01-data-structures/graph/) | Nodes (vertices) and edges; adjacency list or matrix | Non-linear, many-to-many | O(1) (matrix) / O(n) (list) | O(1) (matrix) / O(n) (list) |
| [Hash](./01-data-structures/hash/) | Maps keys to positions via hash functions | Linear, key-value mapping | O(1) (amortized) | O(1) (amortized) |
| [Struct](./01-data-structures/struct/) | Combines multiple fields into one object | Custom, fixed fields, multiple types | O(1) | O(1) |
| [List](./01-data-structures/list/) | Ordered collection allowing duplicates | Linear, insertion order | O(1) (append), O(n) (middle ops) | O(1) (index), O(n) (search) |
| [Set](./01-data-structures/set/) | Unordered collection without duplicates | Linear, based on hash or tree | O(1) (hash) / O(log n) (tree) | O(1) (hash) / O(log n) (tree) |
| [Map](./01-data-structures/map/) | Stores key-value pairs | Associative array, hash or balanced tree | O(1) (hash) / O(log n) (tree) | O(1) (hash) / O(log n) (tree) |

---

## Related Links
- [Recommended Programming Languages](./00-start-here/recommand-learning-languages.md)
- [Differences Between Programming Languages and How to Choose](https://www.toutiao.com/article/7122744261904450063)
- [How to Learn Programming Well](https://zhuanlan.zhihu.com/p/582174773)

## Welcome to Contribute

`Repository:` [https://github.com/microwind/algorithms](https://github.com/microwind/algorithms)
`Site:` [https://microwind.github.io/algorithms](https://microwind.github.io/algorithms)

If you are interested in this project, please add me. I welcome you to build it together.

**wechat:** `springbuild`

**Email:** `jarryli@gmail.com` or `lichunping@buaa.edu.cn`
