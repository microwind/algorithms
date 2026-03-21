# 《算法设计手册》The Algorithm Design Manual
> "Most professional programmers are not well prepared to tackle algorithm design problems. This is a pity, because the techniques of algorithm design form one of the core practical technologies of computer science." — Steven S. Skiena

## 📖 基本信息

| 项目 | 内容 |
|------|------|
| 书名 | The Algorithm Design Manual, 3rd Edition |
| 作者 | Steven S. Skiena |
| 版本 | 第 3 版（2020 年） |
| 出版社 | Springer / 中文版：清华大学出版社 |
| 页数 | ~800 页 |
| ISBN | 978-3030542559 |
| 难度 | 中级（Intermediate） |

---

## 一、内容概要（Content Summary）

这本书的独特之处在于它的双重结构。Part I "Practical Algorithm Design" 是一本系统性的算法设计教程，覆盖从基础分析到高级设计范式的完整链条。Part II "The Hitchhiker's Guide to Algorithms" 是一份按问题类型分类的算法目录（Catalog），收录了 75 个经典算法问题及其解法。这种"教程 + 参考手册"的组合在算法书中独一无二。

Skiena 是 Stony Brook 大学的计算机科学教授，长期从事算法教学和组合搜索（Combinatorial Search）方面的研究。他的工程背景使这本书有一种其他算法教材少见的务实气质。全书最出名的特色是穿插其中的"War Stories"（战争故事）——这些来自真实项目的工程案例展示了算法选择如何影响系统性能，一个错误的数据结构选择可能让程序慢 1000 倍，而一个巧妙的归约（Reduction）可能把不可能变成可能。

Part I 的组织方式与多数算法教材不同。它不是按数据结构或算法类型来分章，而是围绕"设计技术"展开：先讲算法分析（Algorithm Analysis），再讲数据结构作为工具（Data Structures），然后依次介绍排序（Sorting）、图遍历（Graph Traversal）、加权图算法（Weighted Graph Algorithms）、组合搜索与回溯（Combinatorial Search and Backtracking）、动态规划（Dynamic Programming），最后讨论不可解问题（Intractable Problems）和算法设计的一般方法论。这种编排强调的是"面对问题时如何选择和设计算法"，而非"这个算法是什么"。

Part II 的问题目录是这本书最有实用价值的部分。每个问题条目包含：问题的形式化定义、相关讨论、推荐的实现方案和代码库指引。当你在工作中遇到一个算法问题但不确定用什么方法时，翻 Part II 往往比搜索引擎更高效。第 3 版对这部分做了较大更新，反映了近年来算法工程领域的进展。

---

## 二、内容点评（Review）

### 这本书的亮点

**"War Stories" 是全书最有价值的内容。** 每章的 War Story 都来自 Skiena 亲身经历或密切相关的工程项目。比如在讲图算法时，他描述了如何用图遍历解决电路板布线问题；在讲动态规划时，他分享了基因序列比对的实际案例。这些故事把抽象的算法概念拉回到真实世界，让读者理解为什么要学这些东西、什么时候会用到。对于缺乏实际项目经验的学生和初级工程师来说，这些故事的教育价值不可替代。

**Part II 的问题目录是独一无二的实用参考。** 75 个算法问题按类型分为数据结构（Data Structures）、数值问题（Numerical Problems）、组合问题（Combinatorial Problems）、图问题（Graph Problems）、集合与字符串问题（Set and String Problems）和计算几何（Computational Geometry）六大类。每个问题有标准化的描述格式：输入/输出定义、讨论、推荐实现。在工程实践中遇到问题时，先在目录里定位问题类型，再看推荐方案，这个工作流程极其高效。

**对算法设计方法论的强调。** 最后一章 "How to Design Algorithms" 总结了全书的方法论：面对一个新问题，如何分类、如何选择设计范式、如何从已知问题进行归约。这种"元层面"的思考在其他教材中很少见，但对于实际工作中的算法设计至关重要。

**第 3 版的更新有实质内容。** 相比第 2 版，新版增加了随机算法（Randomized Algorithms）的内容，更新了多个 War Story，Part II 的参考实现也做了现代化处理。对于已有第 2 版的读者，第 3 版仍值得升级。

### 不足之处

**Part I 的理论深度不够均匀。** 某些章节（如图遍历、动态规划）讲解到位，但另一些章节（如排序）的覆盖相对表面化。如果只读 Part I 作为唯一的算法教材，知识体系会有缺口。Skiena 自己也承认这本书适合作为"第二本算法书"而非入门教材。

**代码实现不够系统。** 与 Sedgewick 的书相比，这本书的代码更多是片段式的，没有统一的代码库和编程语言。读者想要可运行的完整实现，需要自己去找或者参考 algorist.com 上的资源。

**Part II 的问题描述有时过于简略。** 虽然目录的覆盖面很广，但某些问题条目的讨论只有几段话，对于不熟悉该领域的读者来说可能不够用。它更像是一个索引和起点，而非完整的解题指南。

**排版和图示质量一般。** Springer 出版的技术书在排版上往往不如 Addison-Wesley 精致，这本书的图示也比较朴素。不影响阅读，但与同价位的教材相比，视觉体验稍逊。

### 适合什么人看（Target Audience）

| 读者类型 | 推荐指数 | 说明 |
|---------|---------|------|
| 有一定基础的软件工程师 | ★★★★★ | War Stories 和问题目录对工程实践直接有用 |
| 已学过一门算法课的学生 | ★★★★★ | 作为"第二本算法书"补充设计思维和实战视角 |
| 准备技术面试的候选人 | ★★★★☆ | 对问题分类和解题思路的训练很有帮助 |
| 算法零基础的入门者 | ★★☆☆☆ | 起点偏高，建议先读入门教材再来 |
| 追求数学严谨性的学者 | ★★☆☆☆ | 理论证明不是这本书的重点，选 CLRS 更合适 |
| 需要算法参考手册的团队 | ★★★★★ | Part II 可以当工具书放在手边随时查阅 |

### 解决什么问题（Problems Solved）

- **"我遇到了一个算法问题，不知道该用什么方法"**：Part II 的分类目录就是为此设计的，按问题类型检索，快速定位解法
- **"学了算法但不知道实际中怎么用"**：War Stories 用真实案例展示算法在工程中的应用，弥补理论与实践的鸿沟
- **"知道很多算法，但面对新问题不会选择"**：全书强调设计方法论，教你如何分析问题特征、选择合适的算法范式
- **"看 CLRS 太难，看入门书太浅"**：这本书的 Part I 在深度上恰好处于中间位置，配合实战故事降低理解难度
- **"需要一本算法领域的案头参考书"**：Part II 的 75 个问题条目覆盖了工程中最常见的算法需求

---

## 三、主要章节简介（Chapter Overview）

### Part I: Practical Algorithm Design

| 章节 | 标题 | 主要内容 |
|------|------|---------|
| Chapter 1 | Introduction to Algorithm Design | 算法设计的基本概念，通过 Robot Tour Optimization 和 Movie Scheduling 等实例引入正确性证明和建模思想 |
| Chapter 2 | Algorithm Analysis | 渐进分析（Asymptotic Notation）、Big-O/Omega/Theta、增长阶数（Growth Rates）、对数的重要性、算法效率的实验验证 |
| Chapter 3 | Data Structures | 连续与链式数据结构（Contiguous vs. Linked）、Stack/Queue、Dictionary、Binary Search Tree、Priority Queue、哈希表（Hashing） |
| Chapter 4 | Sorting | 排序的应用场景、Heapsort、Mergesort、Quicksort、分布排序（Distribution Sort）、排序下界（Lower Bound）、外部排序（External Sorting） |
| Chapter 5 | Graph Traversal | 图的表示（Adjacency List / Matrix）、BFS、DFS、连通分量（Connected Components）、拓扑排序（Topological Sorting） |
| Chapter 6 | Weighted Graph Algorithms | 最小生成树（Prim / Kruskal）、最短路径（Dijkstra / Floyd-Warshall）、网络流（Network Flow）、二部图匹配（Bipartite Matching） |
| Chapter 7 | Combinatorial Search and Heuristic Methods | 回溯法（Backtracking）、剪枝（Pruning）、随机方法（Randomized Algorithms）、模拟退火（Simulated Annealing）、遗传算法（Genetic Algorithms） |
| Chapter 8 | Dynamic Programming | DP 的核心思想与递推关系（Recurrence Relations）、编辑距离（Edit Distance）、最长递增子序列（LIS）、背包问题（Knapsack）、划分问题（Partition） |
| Chapter 9 | Intractable Problems and Approximation Algorithms | P vs NP、NP-Completeness、归约（Reduction）、经典 NP 完全问题、近似算法（Approximation Algorithms） |
| Chapter 10 | How to Design Algorithms | 算法设计的一般方法论：问题分类、设计范式选择、从特殊到一般的思路 |

### Part II: The Hitchhiker's Guide to Algorithms

| 章节 | 标题 | 问题类型 |
|------|------|---------|
| Chapter 12 | Data Structures | Dictionary、Priority Queue、Suffix Tree/Array、Graph、Set、Kd-Tree 等 |
| Chapter 13 | Numerical Problems | 线性方程组求解（Solving Linear Equations）、矩阵乘法（Matrix Multiplication）、随机数生成（Random Number Generation）、因式分解（Factoring/Primality Testing） |
| Chapter 14 | Combinatorial Problems | 排列与组合生成（Generating Permutations/Combinations）、子集枚举（Subset Enumeration）、日历计算（Calendrical Calculations）、调度问题（Job Scheduling） |
| Chapter 15 | Graph Problems | 连通性（Connectivity）、图的同构（Graph Isomorphism）、平面性检测（Planarity）、最短路径（Shortest Path）、网络流（Network Flow）、图着色（Graph Coloring） |
| Chapter 16 | Set and String Problems | 集合覆盖（Set Cover）、字符串匹配（String Matching）、最长公共子串（Longest Common Substring）、文本压缩（Text Compression） |
| Chapter 17 | Computational Geometry | 凸包（Convex Hull）、最近点对（Closest Pair）、Voronoi 图（Voronoi Diagrams）、三角剖分（Triangulation）、范围搜索（Range Search） |

---

## 四、图书链接（Book Links）

### 英文版（English Edition）
- [Amazon - The Algorithm Design Manual, 3rd Edition](https://www.amazon.com/Algorithm-Design-Manual-Steven-Skiena/dp/3030542556)
- [Springer 官方页面](https://link.springer.com/book/10.1007/978-3-030-54256-6)

### 中文版（Chinese Edition）
- [《算法设计手册（第2版）》 - 清华大学出版社](https://www.tup.tsinghua.edu.cn/)
- [豆瓣读书](https://book.douban.com/subject/4048566/)

### 在线资源（Online Resources）
- [algorist.com - 作者官方网站](https://www.algorist.com/)
- [Skiena 的算法课程讲座视频](https://www3.cs.stonybrook.edu/~skiena/373/videos/)
- [算法问题目录在线版](https://www.algorist.com/algorist.html)

---

## 📚 相关推荐

- [《算法导论》CLRS](./introduction-to-algorithms.md) — 需要更严格的理论分析时的标准参考，与本书互补
- [《编程珠玑》](./programming-pearls.md) — 同样强调算法思维和问题分析能力，篇幅更短、风格更紧凑
- [《算法设计》Kleinberg & Tardos](./algorithm-design.md) — 在算法设计范式（贪心、分治、DP、网络流）上讲得更深入
