# 《算法》Algorithms
> "This is the best book on algorithms and data structures available today." — Daniel Spielman, Yale University

## 📖 基本信息

| 项目 | 内容 |
|------|------|
| 书名 | Algorithms, 4th Edition |
| 作者 | Robert Sedgewick, Kevin Wayne |
| 版本 | 第 4 版（2011 年） |
| 出版社 | Addison-Wesley / 中文版：人民邮电出版社 |
| 页数 | ~976 页 |
| ISBN | 978-0321573513 |
| 难度 | 中级（Intermediate） |

---

## 一、内容概要（Content Summary）

这本书是 Princeton 大学算法课程的配套教材，由 Sedgewick 和 Wayne 合著。Sedgewick 师从 Knuth，在算法分析领域深耕数十年，而 Wayne 长期负责 Princeton 的算法教学。两人的合作使这本书在理论严谨性和教学友好性之间取得了少见的平衡。

全书以 Java 为实现语言，围绕六大主题展开：基础知识（Fundamentals）、排序（Sorting）、查找（Searching）、图（Graphs）、字符串（Strings）和应用场景（Context）。每个主题从基本概念入手，逐步推进到高效的实现方案。例如排序部分从基础排序（Selection Sort、Insertion Sort）讲起，经过 Mergesort 和 Quicksort，最终到 Priority Queue 和 Heapsort，形成完整的知识链条。

与多数算法教材不同，这本书不追求覆盖面的广度，而是对选定的主题做深入、透彻的讲解。每个算法都配有完整的 Java 实现，这些代码不是伪代码或简化示例，而是可以直接编译运行的工程级代码。书中大量使用可视化图示来展示算法的执行过程，对于理解排序、图遍历等动态过程尤其有帮助。

这本书真正的杀手锏是其配套生态：algs4.cs.princeton.edu 网站提供了全部代码库、可视化演示和练习题，Coursera 上的 "Algorithms, Part I" 和 "Algorithms, Part II" 两门免费课程由 Sedgewick 本人主讲。书 + 视频 + 代码三位一体，构成了目前最完善的中级算法学习体系之一。

---

## 二、内容点评（Review）

### 这本书的亮点

**Coursera 课程的加持效果巨大。** 单看书可能觉得节奏平稳，但配合 Sedgewick 的视频讲解，很多概念会豁然开朗。Sedgewick 讲课语速不快，逻辑清晰，对关键步骤会反复演示。这两门免费课程让这本书成为中级水平学习者最容易上手的系统性教材。

**Java 实现干净利落。** 书中的代码风格统一、命名规范、结构清晰，没有过度抽象，也没有为了教学目的过度简化。algs4 标准库提供了输入输出、随机数、统计等基础设施，让读者可以专注于算法本身。这套代码在实际项目中可以直接参考，不像某些教材的伪代码需要大量"翻译"工作。

**可视化是真正的教学利器。** 排序算法的 trace 图、图算法的遍历过程图、字符串算法的状态转换图——书中几乎每个重要算法都有逐步执行的图解。对于视觉型学习者来说，这些图比看十遍代码都管用。

**科学方法论贯穿全书。** 第 1 章就引入了实验性能分析（Empirical Analysis）的方法：先提出假设（Hypothesis），再通过实验验证，用 doubling test 来预测算法的增长阶数（Order of Growth）。这种"科学实验"式的思维方式比直接给出 Big-O 分析更有说服力，也更贴近工程实践。

### 不足之处

**动态规划（Dynamic Programming）的缺失是最大遗憾。** 这本书几乎没有系统讲解 DP，而 DP 是算法学习的核心主题之一，也是面试和竞赛的高频考点。如果只读这一本书，DP 方面会有明显的知识盲区。

**数学分析偏浅。** 与 CLRS 相比，这本书在算法正确性证明和复杂度分析上着墨不多。对于需要严格数学推导的读者来说，可能会觉得不够深入。当然，这也是作者有意为之的取舍——降低理论门槛，换取更好的可读性。

**内容更新滞后。** 2011 年出版至今未出新版，缺少近十余年来的重要进展。例如并发数据结构（Concurrent Data Structures）、概率数据结构（Bloom Filter、Count-Min Sketch 等）、现代哈希技术等内容均未涉及。

**习题缺少参考答案。** 书中习题分为练习（Exercises）、创造性问题（Creative Problems）和实验题（Experiments），但多数没有官方答案，自学者验证思路比较困难。

### 适合什么人看（Target Audience）

| 读者类型 | 推荐指数 | 说明 |
|---------|---------|------|
| CS 本科在读学生 | ★★★★★ | 配合 Coursera 课程，是系统学习算法的最佳路径之一 |
| 有 Java 基础的自学者 | ★★★★★ | 代码可直接运行，学习曲线平缓 |
| 准备技术面试的工程师 | ★★★★☆ | 覆盖了多数面试主题，但缺 DP 需要补充 |
| 非 Java 背景的开发者 | ★★★☆☆ | Java 实现不难读，但需要适应语法和 algs4 库 |
| 追求理论深度的研究者 | ★★☆☆☆ | 数学分析深度不足，建议选 CLRS |
| 算法竞赛选手 | ★★☆☆☆ | 竞赛常见的 DP、数论、计算几何等缺失 |

### 解决什么问题（Problems Solved）

- **"学了理论不会实现"**：每个算法都有完整、可运行的 Java 代码，从抽象到具体无缝衔接
- **"看书看不懂"**：Coursera 视频讲解弥补了纯文字的不足，书和课互为补充
- **"不知道算法在实际中怎么用"**：每章开头都有应用场景引入，如网络连通性（Union-Find）、事件驱动模拟（Event-Driven Simulation）等
- **"学完就忘"**：大量可视化图示帮助建立直觉记忆，比死记代码效果好得多
- **"基础不扎实"**：从 Bag、Stack、Queue 等基础数据结构讲起，不跳步，不默认你已经会了

---

## 三、主要章节简介（Chapter Overview）

| 章节 | 标题 | 主要内容 |
|------|------|---------|
| Chapter 1 | Fundamentals | 基础编程模型（Basic Programming Model）、数据抽象（Data Abstraction）、Bag/Queue/Stack、Union-Find 算法、算法分析（Analysis of Algorithms） |
| Chapter 2 | Sorting | Selection Sort、Insertion Sort、Shellsort、Mergesort（自顶向下和自底向上）、Quicksort（含三向切分 3-Way Partitioning）、Priority Queue 与 Heapsort |
| Chapter 3 | Searching | 符号表（Symbol Table）API、二叉查找树（BST）、平衡查找树（Red-Black BST）、哈希表（Separate Chaining 和 Linear Probing） |
| Chapter 4 | Graphs | 无向图（Undirected Graph）的 DFS/BFS、有向图（Digraph）与拓扑排序（Topological Sort）、最小生成树（MST：Prim 和 Kruskal）、最短路径（Dijkstra、Bellman-Ford） |
| Chapter 5 | Strings | 字符串排序（LSD/MSD Radix Sort、Three-Way String Quicksort）、Trie 与 TST、子串查找（KMP、Boyer-Moore、Rabin-Karp）、正则表达式（NFA）、数据压缩（Huffman、LZW） |
| Chapter 6 | Context | 事件驱动模拟（Event-Driven Simulation）、B-Tree、后缀数组（Suffix Array）、网络流（Maximum Flow / Ford-Fulkerson）、问题归约（Reduction）与不可解性（Intractability） |

---

## 四、图书链接（Book Links）

### 英文版（English Edition）
- [Amazon - Algorithms, 4th Edition](https://www.amazon.com/Algorithms-4th-Robert-Sedgewick/dp/032157351X)
- [InformIT（出版社官方）](https://www.informit.com/store/algorithms-9780321573513)

### 中文版（Chinese Edition）
- [《算法（第4版）》 - 人民邮电出版社](https://www.ituring.com.cn/book/875)
- [豆瓣读书](https://book.douban.com/subject/19952400/)

### 在线资源（Online Resources）
- [官方配套网站 algs4.cs.princeton.edu](https://algs4.cs.princeton.edu/home/)
- [Coursera: Algorithms, Part I](https://www.coursera.org/learn/algorithms-part1)
- [Coursera: Algorithms, Part II](https://www.coursera.org/learn/algorithms-part2)
- [GitHub: algs4 代码库](https://github.com/kevin-wayne/algs4)

---

## 📚 相关推荐

- [《算法导论》CLRS](./introduction-to-algorithms.md) — 需要更严格的数学分析和更全面的主题覆盖时，这是标准参考
- [《算法图解》](./grokking-algorithms.md) — 如果觉得这本书起点太高，先用图解版建立直觉
- [《算法设计手册》](./algorithm-design-manual.md) — 更偏工程实战，Part II 的问题目录是解决实际问题的利器
