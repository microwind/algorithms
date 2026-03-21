# 《算法设计》Algorithm Design
> "The text that bridges the gap between theoretical algorithm design and real-world problem solving." — 常见于 Cornell CS 课程评价

## 📖 基本信息

| 项目 | 内容 |
|------|------|
| 书名 | Algorithm Design |
| 作者 | Jon Kleinberg, Éva Tardos |
| 版本 | 第 1 版（2005 年） |
| 出版社 | Pearson / 中文版：清华大学出版社 |
| 页数 | ~864 页 |
| ISBN | 978-0321295354 |
| 难度 | 中级偏上（Upper Intermediate） |

> **版本说明**：本书至今只有一个版本（2005 年），未出修订版。中文版由清华大学出版社引进出版，翻译质量尚可但部分术语翻译与国内习惯有出入。英文原版的写作风格清晰流畅，推荐直接阅读英文版。注意市面上有价格较高的精装版和较便宜的国际版（International Edition），内容相同。

---

## 一、内容概要（Content Summary）

Kleinberg 和 Tardos 都是 Cornell 大学计算机科学系的教授，在组合优化（Combinatorial Optimization）和算法理论领域有深厚的学术积累。Tardos 是网络流（Network Flow）和近似算法（Approximation Algorithms）方面的权威研究者，Kleinberg 则以网络科学（Network Science）和计算社会学方面的工作闻名。这种学术背景使得本书在理论深度上有坚实的根基，同时两位作者长期承担本科算法教学，对如何向学生解释复杂概念有丰富的经验。

本书的核心组织原则是"算法设计范式"（Algorithm Design Paradigm）。与 CLRS 按数据结构和算法类型分章不同，本书围绕几种核心设计方法展开：贪心算法（Greedy Algorithms）、分治法（Divide and Conquer）、动态规划（Dynamic Programming）、网络流（Network Flow）。每种方法独占一章或多章，从动机到原理到应用层层递进。这种编排方式的优势在于，读者学完一章后获得的不只是几个具体算法的知识，而是一整套解决特定类型问题的方法论。这正是书名中"设计"（Design）一词的含义——本书教的不是算法本身，而是设计算法的方法。

本书在教学法上有一个鲜明的特点：每章都以一个具体的、有实际背景的问题作为引子。这个引导问题（Motivating Problem）不是简单的例题，而是经过精心选择的、能自然引出该章设计方法的真实场景。比如贪心算法一章从区间调度问题（Interval Scheduling）入手，分治法从归并排序和计算逆序对（Counting Inversions）开始，动态规划从加权区间调度（Weighted Interval Scheduling）和序列比对（Sequence Alignment）展开。这种"问题先行"的方式让读者在接触形式化定义之前，已经对算法的应用场景和设计直觉有了感性认识。

以动态规划一章为例，说明这种教学方法的具体效果。本章不是一上来就给出 DP 的形式化定义（"最优子结构 + 重叠子问题"这种抽象描述），而是从加权区间调度问题开始：有一组任务，每个有开始时间、结束时间和权重，目标是选择不冲突的任务使总权重最大。读者先尝试用贪心策略（上一章刚学的方法）解决，发现贪心在这里不行——因为权重不同，局部最优不等于全局最优。然后 Bentley 自然地引出"子问题"的概念和递推关系，DP 的核心思想就这样从问题本身中生长出来，而不是从天而降的抽象定义。

全书的后半部分转向计算复杂性和高级主题。NP 与计算不可解性（NP and Computational Intractability）一章系统性地介绍了 NP 完全性理论和归约技术（Reduction Techniques），被广泛认为是同类教材中最清晰的处理方式之一。之后的章节覆盖了可解性的延伸（Extending the Limits of Tractability）、近似算法（Approximation Algorithms）、随机化算法（Randomized Algorithms）和局部搜索（Local Search）等前沿设计范式，为有志于深入研究的读者提供了扎实的理论基础。

在北美高校中，这本书是仅次于 CLRS 的第二大算法教材选择。除 Cornell 外，Princeton、UC Berkeley、University of Washington 等校的算法课程也采用或参考了本书。Kevin Wayne（Princeton）基于本书制作的一套教学课件在全球范围内被广泛使用，成为了事实上的配套教学资源。本书的影响力不仅体现在课堂上——其网络流章节和 NP 完全性章节被许多研究论文和其他教材引用，已经成为这两个领域教学的标准参考。

---

## 二、内容点评（Review）

### 这本书的亮点

**"问题先行"的教学设计是同类教材中最好的。** 每章开头的引导问题不是随便选的，而是经过精心构造的：它足够简单以至于读者能理解问题的含义，同时又足够丰富以至于能自然引出整章的设计方法。比如在贪心算法一章，区间调度问题（Interval Scheduling）直观地展示了贪心策略的核心思想——做出局部最优选择并证明全局最优性。这种从具体到抽象的路径符合大多数人的认知模式，降低了理论内容的学习门槛。

值得注意的是，这种教学设计不仅降低了入门难度，还帮助读者建立了"面对新问题时应该怎么思考"的范式。在实际工作中或考试中遇到一个算法问题时，你首先要做的就是分析问题的结构——它是否具有贪心选择性质？是否有最优子结构？能否建模为流网络？本书通过反复演练这种分析过程，让读者内化了这套思维框架。

**网络流（Network Flow）一章堪称教科书级别的典范。** 从最大流最小割定理（Max-Flow Min-Cut Theorem）到 Ford-Fulkerson 算法，再到二部图匹配（Bipartite Matching）、不相交路径（Disjoint Paths）、流量网络的应用，这一章的讲解深度和清晰度在所有算法教材中可能是最好的。Tardos 本人在这个领域的研究背景使得讲解不仅准确，而且有一种对问题本质的洞察力。许多学生和教师在讲授网络流时，首选的参考资料就是本书的这一章。

本章特别出色的部分是"网络流的应用"（Applications of Network Flow）。通过一系列精心设计的例子——调查设计（Survey Design）、航班调度（Airline Scheduling）、图像分割（Image Segmentation）——作者展示了如何将看似与流量无关的问题建模为网络流问题。这种"建模能力"是算法设计中最难教但最有价值的技能之一，而本章通过具体案例把它讲活了。

**NP 完全性和归约的处理方式清晰且实用。** 这个话题在许多教材中要么过于形式化（让学生迷失在定义中），要么过于简略（只给结论不给直觉）。Kleinberg 和 Tardos 取了一条中间路线：先建立直觉（为什么有些问题"难"），再给出形式化定义（P、NP、NP-Complete 的精确定义），最后通过一系列精心编排的归约（Reductions）展示如何证明一个新问题是 NP 完全的。归约链的呈现从 Circuit-SAT 到 3-SAT，再到 Independent Set、Vertex Cover、Set Cover 等，逻辑链条完整，每一步的动机都解释得很清楚。

**习题质量高且分层合理。** 每章末尾的习题数量充足（通常 30-50 道），按难度分级标记。较简单的题目帮助巩固概念，较难的题目则是真正的算法设计挑战。不少习题后来出现在各大学的算法课程考试和编程竞赛中，说明其质量得到了广泛认可。许多习题具有实际应用背景——通信网络设计、DNA 序列分析、交通调度——这使得做习题的过程不仅仅是技术训练，也是对算法应用场景的积累。

**贪心算法正确性证明的方法论独到。** 贪心算法的难点不在于设计贪心策略，而在于证明策略的正确性。本书系统性地介绍了"交换论证"（Exchange Argument）和"贪心保持领先"（Greedy Stays Ahead）两种证明方法，并在多个问题（区间调度、Dijkstra、Huffman 编码）中反复演练。这种对证明方法论的重视在其他教材中并不常见。

**理论与应用的平衡比 CLRS 更好。** CLRS 是一本无可争议的参考手册，但它的百科全书式结构使得读者有时难以看到"全局图景"——学了红黑树之后未必理解什么时候该用它。Kleinberg-Tardos 的编排方式恰好弥补了这个缺点：以设计范式为主线，每种方法都有明确的适用场景和判断标准，读者更容易建立"面对什么类型的问题，应该尝试什么方法"的直觉。

**动态规划一章的循序渐进特别值得称道。** 从一维的加权区间调度，到二维的序列比对，再到更复杂的 RNA 二级结构预测——难度递增的节奏控制得恰到好处。每个新问题都在前一个问题的基础上增加一层复杂度，读者不会感到突然的跳跃。这种渐进式的难度设计使得 DP 这个公认的"算法课难点"变得可以消化。相比之下，许多教材直接用矩阵链乘法或最优二叉搜索树作为 DP 的入门例子，对初学者来说台阶过高。

### 不足之处

**数据结构的覆盖偏弱。** 本书聚焦于算法设计范式，对数据结构的讨论集中在第二章和第三章的基础部分。红黑树（Red-Black Tree）、B 树（B-Tree）、跳表（Skip List）、并查集（Union-Find）的高级实现等内容要么简略提及，要么完全缺席。如果你需要系统学习数据结构，需要另外找一本专门的参考书或回到 CLRS。

**只有第 1 版，内容未随时间更新。** 本书出版于 2005 年，至今未出新版。虽然核心的算法设计理论并未过时，但近二十年来在随机化算法、在线算法（Online Algorithms）、流式算法（Streaming Algorithms）等领域的进展未能体现。此外，书中没有涉及现代工程中常见的一些话题，如分布式算法、并行计算、以及机器学习中的优化算法等。不过，就算法设计的核心方法论而言——贪心、分治、DP、网络流、NP 完全性——这些内容在可预见的未来不会过时。

**代码实现几乎没有。** 本书以伪代码（Pseudocode）为主，没有提供任何特定编程语言的实现。对于喜欢通过运行代码来理解算法的学习者来说，需要自己动手实现或寻找第三方代码资源。与 Sedgewick 那种"每个算法都有完整 Java 实现"的风格形成鲜明对比。好消息是 Kevin Wayne 的配套课件中包含了部分算法的 Java 实现，可以作为补充。

**某些章节的数学要求较高。** 特别是网络流、NP 完全性和随机化算法的章节，需要较扎实的离散数学（Discrete Mathematics）和概率论（Probability Theory）基础。对于数学背景较弱的读者，这些章节的阅读难度会明显上升。建议在阅读前复习基本的图论术语、概率基础和数学归纳法。

**篇幅较长，不适合快速查阅。** 864 页的体量加上叙述性的写作风格，使得本书更适合从头到尾系统阅读，而不太适合作为案头参考书快速检索某个算法。如果你需要快速查某个算法的实现细节，CLRS 或 Sedgewick 的书更方便。

**PSPACE 章节对多数读者价值有限。** Chapter 9 关于 PSPACE 的讨论虽然在理论上完整，但对于非理论方向的学生和工程师来说，实际应用场景极少。许多使用本书的课程会跳过这一章，把时间分配给更实用的近似算法或随机化算法章节。

**第一章的稳定匹配问题选择有争议。** Gale-Shapley 算法虽然优雅，但作为全书的开篇引导问题，它与后续章节的主题关联并不紧密。一些教师认为用更贴近日常编程的问题（如排序或搜索相关的问题）来开篇会更容易让学生进入状态。

### 适合什么人看（Target Audience）

| 读者类型 | 推荐指数 | 说明 |
|---------|---------|------|
| CS 本科生上算法设计课 | ★★★★★ | 这本书就是为本科算法课设计的，Cornell 等名校的标准教材 |
| 已有基础想深入设计范式的工程师 | ★★★★★ | 贪心、分治、DP、网络流的讲解深度和清晰度在同类书中最佳 |
| 准备算法竞赛的选手 | ★★★★☆ | 设计方法论和高质量习题对竞赛有直接帮助，但缺少一些竞赛常用的高级数据结构 |
| 准备技术面试的候选人 | ★★★★☆ | DP 和贪心的部分对面试特别有用，NP 完全性在面试中较少涉及 |
| 纯自学、无教师指导的学习者 | ★★★☆☆ | 叙述风格适合自学，但部分章节的难度需要一定基础才能消化 |
| 需要快速参考手册的实践者 | ★★☆☆☆ | 本书的叙事结构不利于快速检索，选 CLRS 或《算法设计手册》更合适 |

### 解决什么问题（Problems Solved）

- **"我学了很多算法，但面对新问题不知道用哪种设计范式"**：全书以设计范式为组织主线，系统地教你判断一个问题适合用贪心、分治还是动态规划
- **"我知道动态规划，但不知道怎么设计状态转移方程"**：DP 一章从最简单的加权区间调度开始，逐步推进到序列比对、最短路径、背包问题，展示了一套设计 DP 方案的系统化方法
- **"网络流是什么？什么时候用？怎么把问题建模成流问题？"**：本书的网络流章节是这个领域最好的入门材料之一，从基础理论到多样化的应用场景都有清晰的覆盖
- **"NP 完全性的证明我看不懂"**：本书的归约链条组织得当，从直觉到形式化逐步推进，是理解 NP 完全性证明技术的最佳入口之一
- **"CLRS 太厚太像字典，我需要一本更适合通读的算法设计教材"**：本书的叙述风格和"问题先行"的结构使它比 CLRS 更适合作为教学用书和自学教材
- **"我需要理解如何把实际问题建模成算法问题"**：每章开头的引导问题展示了从实际场景到形式化问题定义的建模过程，这种能力是算法设计的第一步

---

## 附、与同类书的对比（Comparison）

本书的定位在算法教材中独特但不孤立，理解它与同类书的关系有助于选择合适的学习路径。

| 对比维度 | 《算法设计》KT | 《算法导论》CLRS | 《算法设计手册》Skiena | 《算法》Sedgewick |
|---------|-------------|----------------|---------------------|-----------------|
| 定位 | 设计范式教材 | 全面参考手册 | 实战导向教程 | 系统性教程 |
| 组织方式 | 按设计范式分章 | 按主题分章 | 教程 + 问题目录 | 按主题分章 |
| 教学法 | 问题先行 | 定义先行 | War Stories 驱动 | 可视化 + 代码 |
| 网络流 | 极为详尽 | 一章覆盖 | 简要提及 | 不涉及 |
| NP 完全性 | 系统性归约链 | 经典处理 | 面向实用 | 简要介绍 |
| 代码实现 | 伪代码为主 | 伪代码为主 | C / C++ 片段 | 完整 Java 实现 |
| 配套资源 | Princeton 课件 | MIT OCW | algorist.com | Coursera 课程 |
| 适合通读 | 适合 | 不适合 | Part I 适合 | 适合 |

> **选书建议**：如果你是第一次学算法，先读 Sedgewick 或《算法图解》打好基础。如果你已有基础，想深入理解算法设计的"为什么"（为什么贪心在这里有效？为什么这个问题需要 DP？），本书是最佳选择。如果你需要一本随时翻阅的参考手册，选 CLRS。三本书各有分工，不构成替代关系。

一个常见的学习路径是：先用 Sedgewick 或 CLRS 系统性地学习基本算法和数据结构，然后用 Kleinberg-Tardos 提升算法设计能力，特别是在贪心正确性证明、DP 状态设计和网络流建模方面。两个阶段的侧重点不同：前者强调"知道有哪些算法"，后者强调"面对新问题能设计出合适的算法"。

---

## 三、主要章节简介（Chapter Overview）

全书 13 章，前三章是基础，中间四章覆盖核心设计范式（贪心、分治、DP、网络流），后六章处理计算复杂性和高级设计方法。以下是各章的内容概述。

| 章节 | 标题 | 主要内容 |
|------|------|---------|
| Chapter 1 | Introduction: Some Representative Problems | 通过稳定匹配问题（Stable Matching / Gale-Shapley Algorithm）引入算法设计的基本思路，展示如何从问题定义到算法设计再到正确性证明的完整流程。Gale-Shapley 算法的分析过程是全书方法论的缩影：先理解问题结构，再设计算法，最后严格证明正确性和复杂度。本章还概述了五个贯穿全书的代表性问题，让读者在开始深入学习前对全书的主题有一个宏观的认识 |
| Chapter 2 | Basics of Algorithm Analysis | 计算模型（Computational Model）、渐进分析（Asymptotic Analysis）、Big-O / Omega / Theta 记号、常见增长阶数的比较、对数和指数增长的直觉建立。本章还讨论了如何分析包含多个嵌套循环和递归调用的算法复杂度 |
| Chapter 3 | Graphs | 图的基本定义与表示方法（邻接表 / 邻接矩阵）、BFS 与 DFS 的性质与应用、连通性（Connectivity）、拓扑排序（Topological Ordering）、二部图检测（Bipartiteness）、有向无环图（DAG）的性质。本章不仅教图的基础知识，更重要的是建立"把问题建模为图"的思维方式 |
| Chapter 4 | Greedy Algorithms | 区间调度问题（Interval Scheduling）、最早截止时间优先调度（Earliest Deadline First）、最短路径（Dijkstra 算法）、最小生成树（Prim / Kruskal）、Huffman 编码（Huffman Codes）。核心方法论：如何用交换论证（Exchange Argument）和"贪心保持领先"（Greedy Stays Ahead）证明贪心策略的正确性 |
| Chapter 5 | Divide and Conquer | 归并排序与逆序对计数（Counting Inversions）、最近点对问题（Closest Pair of Points）、整数乘法（Karatsuba Algorithm）、矩阵乘法（Strassen's Algorithm）。主定理（Master Theorem）及其应用，以及如何分析分治递归的时间复杂度 |
| Chapter 6 | Dynamic Programming | 加权区间调度（Weighted Interval Scheduling）、分段最小二乘法（Segmented Least Squares）、背包问题（Knapsack Problem）、RNA 二级结构（RNA Secondary Structure）、序列比对（Sequence Alignment）、最短路径（Bellman-Ford）。本章从最简单的一维 DP 开始，逐步过渡到二维和更复杂的子问题结构，系统性地教授如何识别子问题、定义递推关系、确定计算顺序。子问题图（Subproblem Graph）的概念帮助读者可视化 DP 的结构 |
| Chapter 7 | Network Flow | 最大流问题与 Ford-Fulkerson 方法、最大流最小割定理（Max-Flow Min-Cut Theorem）、容量缩放算法（Capacity Scaling）、二部图匹配（Bipartite Matching）、不相交路径（Edge / Vertex Disjoint Paths）、流量网络的建模应用（Survey Design、Airline Scheduling、Image Segmentation）。本章是全书的高光章节，展示了如何将看似无关的问题统一建模为网络流问题，Tardos 在此领域的深厚功底使讲解兼具直觉性和严谨性 |
| Chapter 8 | NP and Computational Intractability | 多项式时间归约（Polynomial-Time Reductions）、NP 完全性的定义与直觉、Circuit Satisfiability、3-SAT 的 NP 完全性、从 3-SAT 到 Independent Set / Vertex Cover / Set Cover / Hamiltonian Cycle 的归约链、证明 NP 完全性的一般策略。归约链的组织是本章最大的亮点：每个归约都有清晰的动机解释，读者能理解为什么选择这个归约方向而非另一个 |
| Chapter 9 | PSPACE: A Class of Problems beyond NP | PSPACE 的定义、量化布尔公式（Quantified Boolean Formulas / QSAT）、竞争性问题（Competitive Problems）与博弈论相关的复杂性分析、PSPACE 完全问题。这一章在大多数算法课程中是可选内容，但对理论导向的读者有价值 |
| Chapter 10 | Extending the Limits of Tractability | 处理 NP 困难问题的实用策略：在特殊图结构上寻找有效算法（Tree Decomposition）、固定参数可解性（Fixed-Parameter Tractability）、树宽（Treewidth）的概念与应用。这一章告诉你：即使问题是 NP 困难的，在特定条件下仍可能找到有效解法 |
| Chapter 11 | Approximation Algorithms | 近似比（Approximation Ratio）的定义、贪心近似（Load Balancing、Set Cover 的对数近似）、定价方法（Pricing Method / Vertex Cover）、线性规划松弛（LP Relaxation）、多项式时间近似方案（PTAS）。本章展示了面对 NP 困难问题时的务实态度：放弃精确最优，但保证解的质量有可证明的下界 |
| Chapter 12 | Local Search | 局部搜索的基本框架、Metropolis 算法与模拟退火（Simulated Annealing）、局部搜索在 Maximum Cut 和 Nash Equilibrium 中的应用、局部最优与全局最优的关系分析。虽然局部搜索缺乏严格的最优性保证，但在实践中往往能找到足够好的解 |
| Chapter 13 | Randomized Algorithms | 随机化算法的基本概念（Las Vegas vs. Monte Carlo）、随机化竞争分析（Contention Resolution）、MAX 3-SAT 的随机近似、随机最小割算法（Karger's Algorithm）、Chernoff 界（Chernoff Bounds）的应用。这一章展示了随机性作为算法设计工具的威力 |

> **阅读建议**：核心章节为 Chapter 4（Greedy）、Chapter 5（Divide and Conquer）、Chapter 6（Dynamic Programming）和 Chapter 7（Network Flow）。如果时间有限，优先读这四章可以获得算法设计范式的核心方法论。Chapter 8（NP 完全性）对于理解计算复杂性理论至关重要，建议在读完前四章后阅读。

---

## 四、图书链接（Book Links）

### 英文版（English Edition）
- [Amazon - Algorithm Design](https://www.amazon.com/Algorithm-Design-Jon-Kleinberg/dp/0321295358)
- [Pearson 出版信息](https://www.pearson.com/en-us/subject-catalog/p/algorithm-design/P200000003259)

### 中文版（Chinese Edition）
- [《算法设计》 - 清华大学出版社](https://www.tup.tsinghua.edu.cn/)
- [豆瓣读书](https://book.douban.com/subject/1475870/)

### 在线资源（Online Resources）
- [Kleinberg 在 Cornell 的算法课程页面](https://www.cs.cornell.edu/~kleinber/)
- [Tardos 在 Cornell 的个人页面](https://www.cs.cornell.edu/~eva/)
- [Kevin Wayne 的算法课件（基于本书）](https://www.cs.princeton.edu/~wayne/kleinberg-tardos/) — 被全球数百所大学采用的高质量教学课件
- [Cornell CS 4820 算法课程](https://www.cs.cornell.edu/courses/cs4820/) — 基于本书的 Cornell 本科算法课
- [习题解答讨论（非官方）](https://github.com/kayaklee/Algorithm-Design) — 社区维护的部分习题参考

### 前置知识建议（Prerequisites）

阅读本书前，建议具备以下基础：

- **离散数学**（Discrete Mathematics）：集合、关系、图论基础、组合计数、基本概率论
- **数据结构基础**：数组、链表、栈、队列、二叉树、图的基本表示和遍历
- **编程能力**：能够读懂伪代码并用至少一种编程语言实现算法
- **数学成熟度**：能够跟随简单的数学归纳法证明和渐进分析

### 延伸阅读（Further Reading）
- *Computational Complexity: A Modern Approach* by Arora & Barak — 想深入计算复杂性理论的读者的下一步
- *Combinatorial Optimization* by Korte & Vygen — 在网络流和组合优化方向的进阶参考
- *Approximation Algorithms* by Vazirani — 近似算法方向的专门教材
- *Network Flows: Theory, Algorithms, and Applications* by Ahuja, Magnanti & Orlin — 网络流方向的进阶参考

### 使用本书的知名课程（Courses Using This Book）

以下大学的算法课程采用或参考了本书作为主要教材：

| 学校 | 课程编号 | 说明 |
|------|---------|------|
| Cornell University | CS 4820 | 作者所在校，算法设计核心课程 |
| Princeton University | COS 226 / COS 521 | Kevin Wayne 基于本书制作了广泛使用的教学课件 |
| UC Berkeley | CS 170 | 部分学期采用本书作为参考 |
| University of Washington | CSE 421 | 算法设计课程的标准教材之一 |

---

## 📚 相关推荐

- [《算法导论》CLRS](./introduction-to-algorithms.md) — 需要更全面的覆盖面和更详细的数据结构内容时的标准参考
- [《算法设计手册》](./algorithm-design-manual.md) — 更偏工程实战，War Stories 和问题目录在实际工作中直接有用
- [《算法》Sedgewick](./algorithms-sedgewick.md) — 需要完整的代码实现和配套视频课程时的首选

---

## 返回

- [图书推荐首页](./README.md)
- [资源与素材](../README.md)
- [项目首页](../../README.md)
