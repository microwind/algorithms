# 排序（Sorting）算法概述

> 排序算法是将一组数据按照特定顺序（升序或降序）重新排列的算法。排序是计算机科学中最基础、最重要的算法之一，也是许多复杂算法的基础操作。本目录涵盖经典十大排序算法的原理、流程与多语言实现。

## 导航总览

| 排序算法 | 类型 | 时间复杂度（平均） | 稳定性 | 目录 |
|---------|------|------------------|--------|------|
| [冒泡排序 Bubble Sort](#31-冒泡排序bubble-sort) | 比较 / 交换 | O(n²) | 稳定 | [`bubblesort/`](./bubblesort/) |
| [选择排序 Selection Sort](#32-选择排序selection-sort) | 比较 / 选择 | O(n²) | 不稳定 | [`selectionsort/`](./selectionsort/) |
| [插入排序 Insertion Sort](#33-插入排序insertion-sort) | 比较 / 插入 | O(n²) | 稳定 | [`insertsort/`](./insertsort/) |
| [希尔排序 Shell Sort](#34-希尔排序shell-sort) | 比较 / 插入 | O(n^1.3) | 不稳定 | [`shellsort/`](./shellsort/) |
| [快速排序 Quick Sort](#35-快速排序quick-sort) | 比较 / 交换 | O(n log n) | 不稳定 | [`quicksort/`](./quicksort/) |
| [归并排序 Merge Sort](#36-归并排序merge-sort) | 比较 / 归并 | O(n log n) | 稳定 | [`mergesort/`](./mergesort/) |
| [堆排序 Heap Sort](#37-堆排序heap-sort) | 比较 / 选择 | O(n log n) | 不稳定 | [`heapsort/`](./heapsort/) |
| [计数排序 Counting Sort](#38-计数排序counting-sort) | 非比较 | O(n + k) | 稳定 | [`countingsort/`](./countingsort/) |
| [基数排序 Radix Sort](#39-基数排序radix-sort) | 非比较 | O(n × d) | 稳定 | [`radixsort/`](./radixsort/) |
| [桶排序 Bucket Sort](#310-桶排序bucket-sort) | 非比较 | O(n + k) | 稳定 | [`bucketsort/`](./bucketsort/) |

---

## 1. 排序算法分类

### 1.1 常见排序算法分类
```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 10}}}%%
graph TD
    ROOT(["排序算法分类"])
    ROOT --> CMP("比较排序")
    ROOT --> NCMP("非比较排序")

    CMP --> SWAP["交换排序"]
    CMP --> SEL["选择排序"]
    CMP --> INS["插入排序"]
    CMP --> MRG["归并排序"]
    
    SWAP --> BUB["冒泡排序"]
    SWAP --> QCK["快速排序"]
    SEL --> SSEL["简单选择排序"]
    SEL --> HEAP["堆排序"]
    INS --> DINS["直接插入排序"]
    INS --> SHELL["希尔排序"]
    
    NCMP --> CNT["计数排序"]
    NCMP --> RDX["基数排序"]
    NCMP --> BKT["桶排序"]
    
    classDef root fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef cat fill:#0f3460,color:#fff,stroke:#0a2647
    classDef sub fill:#533483,color:#fff,stroke:#2c1654
    classDef leaf fill:#e94560,color:#fff,stroke:#c81e45
    
    class ROOT root
    class CMP,NCMP cat
    class SWAP,SEL,INS,MRG sub
    class BUB,QCK,SSEL,HEAP,DINS,SHELL,CNT,RDX,BKT leaf
```

### 1.2 排序算法时间复杂度、空间复杂度以及稳定性
```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 5}}}%%
graph LR
    Root([排序算法]):::root

    Root --> A([插入排序]):::cat
    Root --> B([选择排序]):::cat
    Root --> C([交换排序]):::cat
    Root --> D([归并排序]):::cat
    Root --> E([线性排序]):::cat

    A --> A1["<b>简单插入排序</b> O(n²) · O(1) · 稳定"]:::leaf
    A --> A2["<b>希尔排序</b> O(n log n) · O(1) · 不稳定"]:::leaf

    B --> B1["<b>简单选择排序</b> O(n²) · O(1) · 不稳定"]:::leaf
    B --> B2["<b>堆排序</b> O(n log n) · O(1) · 不稳定"]:::leaf

    C --> C1["<b>冒泡排序</b> O(n²) · O(1) · 稳定"]:::leaf
    C --> C2["<b>快速排序</b> O(n log n) · O(log n) · 不稳定"]:::leaf

    D --> D1["<b>归并排序</b> O(n log n) · O(n) · 稳定"]:::leaf

    E --> E1["<b>计数排序</b> O(n+k) · O(n+k) · 稳定"]:::leaf
    E --> E2["<b>桶排序</b> O(n+k) · O(n+k) · 稳定"]:::leaf
    E --> E3["<b>基数排序</b> O(nd) · O(n+k) · 稳定"]:::leaf

    classDef root fill:#6436ED,stroke:#7c3aed,color:#fff,font-weight:bold
    classDef cat  fill:#5eead4,stroke:#0d9488,color:#134e4a,font-weight:bold
    classDef leaf fill:#fef9c3,stroke:#ca8a04,color:#713f12
```

---

## 2. 排序算法的基本特性

### 2.1 排序算法的评估维度

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 20, 'rankSpacing': 25, 'padding': 5}}}%%
graph TD
    DIM["评估维度"]
    DIM --> T["时间复杂度<br/>最好 / 平均 / 最坏"]
    DIM --> S["空间复杂度<br/>原地 O(1) vs 非原地"]
    DIM --> ST["稳定性<br/>相等元素是否保序"]
    DIM --> IO["内部/外部排序<br/>内存 vs 磁盘辅助"]

    classDef root fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef dim fill:#0f3460,color:#fff,stroke:#0a2647

    class DIM root
    class T,S,ST,IO dim
```

### 2.2 排序算法的稳定性示例

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 20, 'rankSpacing': 25, 'padding': 5}}}%%
graph TD
    subgraph ORIG["原始数据"]
        direction LR
        O1["张三 85"] ~~~ O2["李四 90"] ~~~ O3["王五 85"]
    end

    subgraph STABLE["稳定排序结果 ✓"]
        direction LR
        S1["张三 85"] ~~~ S2["王五 85"] ~~~ S3["李四 90"]
    end

    subgraph UNSTABLE["不稳定排序可能结果 ✗"]
        direction LR
        U1["王五 85"] ~~~ U2["张三 85"] ~~~ U3["李四 90"]
    end

    ORIG -->|"稳定排序"| STABLE
    ORIG -->|"不稳定排序"| UNSTABLE

    classDef orig fill:#0f3460,color:#fff,stroke:#0a2647
    classDef ok fill:#0b8457,color:#fff,stroke:#065535
    classDef bad fill:#e94560,color:#fff,stroke:#c81e45

    class ORIG,O1,O2,O3 orig
    class STABLE,S1,S2,S3 ok
    class UNSTABLE,U1,U2,U3 bad
```

> **稳定性的意义**：多关键字排序时（如先按分数排序，再按班级稳定排序），稳定性保证已有的排序结果不被破坏。

### 2.3 排序算法的优缺点
**优点**：
- **基础且重要**：几乎所有应用都需要排序
- **算法多样**：不同场景有最优算法选择
- **优化空间大**：可根据数据特性选择或定制

**缺点**：
- **时间成本**：大数据量排序耗时
- **空间成本**：某些算法需要额外空间
- **复杂性**：最优算法（如快速排序）实现较复杂

---

## 3. 十大经典排序算法

### 3.1 冒泡排序（Bubble Sort）

**简介**：最简单的排序算法之一。重复遍历数组，相邻元素两两比较，逆序则交换，每轮将当前未排序部分的最大值"冒泡"到末尾。可设置标志位，若某轮无交换则提前终止。

| 最好 | 平均 | 最坏 | 空间 | 稳定性 |
|------|------|------|------|--------|
| O(n) | O(n²) | O(n²) | O(1) | 稳定 |

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 5}}}%%
graph LR
    S(["开始"]) --> INIT["i = 0"]
    INIT --> OUTER{"i < n - 1 ?"}
    OUTER -->|"否"| END(["排序完成"])
    OUTER -->|"是"| JSTART["j = 0, swapped = false"]
    JSTART --> INNER{"j < n - 1 - i ?"}
    INNER -->|"否"| CHKSW{"swapped ?"}
    CHKSW -->|"否 (无交换)"| END
    CHKSW -->|"是"| INC["i++"]
    INC --> OUTER
    INNER -->|"是"| CMP{"arr[j] > arr[j+1] ?"}
    CMP -->|"否"| JINC["j++"]
    CMP -->|"是"| SWAP["交换 arr[j], arr[j+1]<br/>swapped = true"]
    SWAP --> JINC
    JINC --> INNER

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef decision fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647

    class S,END start
    class OUTER,INNER,CMP,CHKSW decision
    class INIT,JSTART,INC,JINC,SWAP process
```

**适用场景**：教学演示、小规模数据、数据接近有序时。

**实现目录**：[`bubblesort/`](./bubblesort/)

---

### 3.2 选择排序（Selection Sort）

**简介**：每轮从未排序区间中选出最小（或最大）元素，将其放到已排序区间的末尾。无论数据是否有序，比较次数始终为 O(n²)，但交换次数最多 O(n)，因此在交换代价高的场景有一定优势。

| 最好 | 平均 | 最坏 | 空间 | 稳定性 |
|------|------|------|------|--------|
| O(n²) | O(n²) | O(n²) | O(1) | 不稳定 |

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 20, 'padding': 5}}}%%
graph LR
    S(["开始"]) --> INIT["i = 0"]
    INIT --> OUTER{"i < n - 1 ?"}
    OUTER -->|"否"| END(["排序完成"])
    OUTER -->|"是"| MIN["minIdx = i, j = i + 1"]
    MIN --> INNER{"j < n ?"}
    INNER -->|"否"| DOSWAP{"minIdx ≠ i ?"}
    DOSWAP -->|"是"| SWAP["交换 arr[i], arr[minIdx]"]
    DOSWAP -->|"否"| INC["i++"]
    SWAP --> INC
    INC --> OUTER
    INNER -->|"是"| CMP{"arr[j] < arr[minIdx] ?"}
    CMP -->|"是"| UPD["minIdx = j"]
    CMP -->|"否"| JINC["j++"]
    UPD --> JINC
    JINC --> INNER

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef decision fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647

    class S,END start
    class OUTER,INNER,CMP,DOSWAP decision
    class INIT,MIN,INC,JINC,UPD,SWAP process
```

**适用场景**：数据量小且交换代价高的场景。

**实现目录**：[`selectionsort/`](./selectionsort/)

---

### 3.3 插入排序（Insertion Sort）

**简介**：类似整理扑克牌，将每个新元素插入到已排序部分的正确位置。对于基本有序的数据接近 O(n)，是小规模数据的最佳选择，也被用作快速排序和 Timsort 的子过程。

| 最好 | 平均 | 最坏 | 空间 | 稳定性 |
|------|------|------|------|--------|
| O(n) | O(n²) | O(n²) | O(1) | 稳定 |

```mermaid

graph LR
    S(["开始"]) --> INIT["i = 1"]
    INIT --> OUTER{"i < n ?"}
    OUTER -->|"否"| END(["排序完成"])
    OUTER -->|"是"| KEY["key = arr[i]<br/>j = i - 1"]
    KEY --> INNER{"j ≥ 0 且<br/>arr[j] > key ?"}
    INNER -->|"是"| SHIFT["arr[j+1] = arr[j]<br/>j--"]
    SHIFT --> INNER
    INNER -->|"否"| PLACE["arr[j+1] = key"]
    PLACE --> INC["i++"]
    INC --> OUTER

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef decision fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647

    class S,END start
    class OUTER,INNER decision
    class INIT,KEY,SHIFT,PLACE,INC process
```

**适用场景**：小规模数据、数据基本有序、作为混合排序的子过程（如 Timsort）。

**实现目录**：[`insertsort/`](./insertsort/)

---

### 3.4 希尔排序（Shell Sort）

**简介**：插入排序的改进版，也称"缩小增量排序"。先按较大步长（gap）分组进行插入排序，逐步缩小 gap 直至 1，最终完成排序。通过大步长的预处理使数据趋于有序，大幅减少最终插入排序的移动次数。时间复杂度取决于 gap 序列的选取。

| 最好 | 平均 | 最坏 | 空间 | 稳定性 |
|------|------|------|------|--------|
| O(n log n) | O(n^1.3) | O(n²) | O(1) | 不稳定 |

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 5}}}%%
graph LR
    S(["开始"]) --> GAP["gap = n / 2"]
    GAP --> GCHK{"gap > 0 ?"}
    GCHK -->|"否"| END(["排序完成"])
    GCHK -->|"是"| IINIT["i = gap"]
    IINIT --> ICHK{"i < n ?"}
    ICHK -->|"否"| GSHR["gap = gap / 2"]
    GSHR --> GCHK
    ICHK -->|"是"| KEY["key = arr[i]<br/>j = i - gap"]
    KEY --> INNER{"j ≥ 0 且<br/>arr[j] > key ?"}
    INNER -->|"是"| SHIFT["arr[j+gap] = arr[j]<br/>j -= gap"]
    SHIFT --> INNER
    INNER -->|"否"| PLACE["arr[j+gap] = key"]
    PLACE --> INC["i++"]
    INC --> ICHK

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef decision fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647

    class S,END start
    class GCHK,ICHK,INNER decision
    class GAP,IINIT,KEY,SHIFT,PLACE,INC,GSHR process
```

**适用场景**：中等规模数据、嵌入式系统等内存受限环境。

**实现目录**：[`shellsort/`](./shellsort/)

---

### 3.5 快速排序（Quick Sort）

**简介**：分治思想的经典应用。选取一个基准元素（pivot），通过分区操作将数组划分为"小于 pivot"和"大于 pivot"两部分，递归排序左右子数组。平均性能优异且缓存友好，是实际应用中最常用的通用排序算法。pivot 选择策略（三数取中、随机化）和小数组切换插入排序可有效避免最坏情况。

| 最好 | 平均 | 最坏 | 空间 | 稳定性 |
|------|------|------|------|--------|
| O(n log n) | O(n log n) | O(n²) | O(log n) | 不稳定 |

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 5}}}%%
graph LR
    S(["开始"]) --> CHK{"low < high ?"}
    CHK -->|"否"| END(["返回"])
    CHK -->|"是"| PIVOT["选择 pivot"]
    PIVOT --> PART["分区：小于 pivot 在左<br/>大于 pivot 在右<br/>返回 pivot 位置 p"]
    PART --> LEFT["递归排序左半部分<br/>quickSort(low, p-1)"]
    LEFT --> RIGHT["递归排序右半部分<br/>quickSort(p+1, high)"]
    RIGHT --> END

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef decision fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647

    class S,END start
    class CHK decision
    class PIVOT,PART,LEFT,RIGHT process
```

**适用场景**：通用大规模排序、C 标准库 `qsort()`、Java `Arrays.sort()`（基本类型）。

**实现目录**：[`quicksort/`](./quicksort/)

---

### 3.6 归并排序（Merge Sort）

**简介**：稳定的分治排序算法。将数组递归二分直到单个元素，然后自底向上两两合并有序子数组。时间复杂度始终为 O(n log n)，不受输入数据分布影响，但需要 O(n) 额外空间。链表排序时可做到 O(1) 额外空间，也是外部排序（海量数据无法一次装入内存）的基础算法。

| 最好 | 平均 | 最坏 | 空间 | 稳定性 |
|------|------|------|------|--------|
| O(n log n) | O(n log n) | O(n log n) | O(n) | 稳定 |

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 20, 'padding': 15}}}%%
graph LR
    S(["开始"]) --> CHK{"数组长度 > 1 ?"}
    CHK -->|"否"| END(["返回"])
    CHK -->|"是"| SPLIT["从中间二分为<br/>左半部分 + 右半部分"]
    SPLIT --> LSORT["递归排序左半部分"]
    LSORT --> RSORT["递归排序右半部分"]
    RSORT --> MERGE["合并两个有序子数组"]
    MERGE --> END

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef decision fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647

    class S,END start
    class CHK decision
    class SPLIT,LSORT,RSORT,MERGE process
```

**适用场景**：需要稳定排序、链表排序、外部排序（大数据无法一次装入内存）。

**实现目录**：[`mergesort/`](./mergesort/)

---

### 3.7 堆排序（Heap Sort）

**简介**：利用堆（完全二叉树）数据结构的选择排序。先将数组构建为大顶堆（父节点 ≥ 子节点），然后反复取出堆顶最大元素放到数组末尾，再对剩余元素重新堆化。原地排序，空间复杂度 O(1)，时间复杂度稳定 O(n log n)，但缓存不友好导致实际性能通常逊于快速排序。

| 最好 | 平均 | 最坏 | 空间 | 稳定性 |
|------|------|------|------|--------|
| O(n log n) | O(n log n) | O(n log n) | O(1) | 不稳定 |

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 20}}}%%
graph LR
    S(["开始"]) --> BUILD["构建大顶堆<br/>（从最后一个非叶节点<br/>到根逐个下沉）"]
    BUILD --> LOOP{"未排序部分<br/>长度 > 1 ?"}
    LOOP -->|"否"| END(["排序完成"])
    LOOP -->|"是"| SWAP["交换堆顶与<br/>未排序部分末尾"]
    SWAP --> SHRINK["未排序范围 - 1"]
    SHRINK --> HEAPIFY["对堆顶执行下沉<br/>（sift down）"]
    HEAPIFY --> LOOP

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef decision fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647

    class S,END start
    class LOOP decision
    class BUILD,SWAP,SHRINK,HEAPIFY process
```

**适用场景**：内存受限的原地排序、优先队列实现、Top K 问题。

**实现目录**：[`heapsort/`](./heapsort/)

---

### 3.8 计数排序（Counting Sort）

**简介**：非比较排序算法。统计每个元素出现的次数，然后计算前缀和确定每个元素在输出数组中的位置，最后反向填充。要求数据为整数且取值范围 k 不能过大。时间复杂度 O(n + k)，当 k = O(n) 时为线性排序。也常作为基数排序的子过程。

| 最好 | 平均 | 最坏 | 空间 | 稳定性 |
|------|------|------|------|--------|
| O(n + k) | O(n + k) | O(n + k) | O(n + k) | 稳定 |

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 20}}}%%
graph LR
    S(["开始"]) --> RANGE["找到数据最大值 max<br/>创建计数数组 count[0..max]"]
    RANGE --> COUNT["遍历数组<br/>统计每个元素出现次数"]
    COUNT --> PREFIX["对 count 数组<br/>做前缀和累加"]
    PREFIX --> FILL["反向遍历原数组<br/>根据 count 确定位置<br/>放入输出数组"]
    FILL --> END(["排序完成"])

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647

    class S,END start
    class RANGE,COUNT,PREFIX,FILL process
```

**适用场景**：整数排序且范围不大（如年龄 0-150、分数 0-100）、基数排序的子过程。

**实现目录**：[`countingsort/`](./countingsort/)

---

### 3.9 基数排序（Radix Sort）

**简介**：非比较排序算法，按"位"（个位、十位、百位……）从低位到高位（LSD）或从高位到低位（MSD）逐位进行稳定排序（通常用计数排序作为子过程）。不直接比较元素大小，而是利用整数的位信息。适用于整数或定长字符串排序，时间复杂度 O(n × d)，其中 d 为最大位数。

| 最好 | 平均 | 最坏 | 空间 | 稳定性 |
|------|------|------|------|--------|
| O(n × d) | O(n × d) | O(n × d) | O(n + k) | 稳定 |

> d = 最大位数，k = 基数（如十进制 k=10）

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 20, 'rankSpacing': 25, 'padding': 20}}}%%
graph LR
    S(["开始"]) --> MAXD["计算最大位数 d"]
    MAXD --> DINIT["digit = 1（从最低位开始）"]
    DINIT --> DCHK{"digit ≤ d ?"}
    DCHK -->|"否"| END(["排序完成"])
    DCHK -->|"是"| STABLE["按当前位进行<br/>稳定排序（计数排序）"]
    STABLE --> NEXT["digit++"]
    NEXT --> DCHK

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef decision fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647

    class S,END start
    class DCHK decision
    class MAXD,DINIT,STABLE,NEXT process
```

**适用场景**：多位数整数排序、手机号 / 身份证号等定长数字串排序。

**实现目录**：[`radixsort/`](./radixsort/)

---

### 3.10 桶排序（Bucket Sort）

**简介**：非比较排序算法，也称"箱排序"。将数据按值域均匀分配到有限数量的桶中，每个桶内部使用其他排序算法（通常插入排序）进行排序，最后按桶顺序依次拼接。当数据分布均匀时可达到 O(n) 线性时间复杂度；极端情况下（所有数据落入同一个桶）退化为桶内排序算法的复杂度。

| 最好 | 平均 | 最坏 | 空间 | 稳定性 |
|------|------|------|------|--------|
| O(n + k) | O(n + k) | O(n²) | O(n + k) | 稳定 |

> k = 桶的数量。最坏情况发生在所有元素落入同一个桶时。

```mermaid
graph LR
    S(["开始"]) --> INIT["创建 k 个空桶<br/>确定值域范围"]
    INIT --> DIST["遍历数组<br/>将每个元素分配到<br/>对应的桶中"]
    DIST --> SORT["对每个非空桶<br/>内部进行排序"]
    SORT --> CONCAT["按桶顺序<br/>依次拼接所有元素"]
    CONCAT --> END(["排序完成"])

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647

    class S,END start
    class INIT,DIST,SORT,CONCAT process
```

**适用场景**：数据分布均匀的浮点数排序、值域已知的大规模数据。

**实现目录**：[`bucketsort/`](./bucketsort/)

---

## 4. 算法复杂度对比

| 算法 | 最好 | 平均 | 最坏 | 空间 | 稳定 |
|------|------|------|------|------|------|
| 冒泡排序 | O(n) | O(n²) | O(n²) | O(1) | 稳定 |
| 选择排序 | O(n²) | O(n²) | O(n²) | O(1) | 不稳定 |
| 插入排序 | O(n) | O(n²) | O(n²) | O(1) | 稳定 |
| 希尔排序 | O(n log n) | O(n^1.3) | O(n²) | O(1) | 不稳定 |
| 快速排序 | O(n log n) | O(n log n) | O(n²) | O(log n) | 不稳定 |
| 归并排序 | O(n log n) | O(n log n) | O(n log n) | O(n) | 稳定 |
| 堆排序 | O(n log n) | O(n log n) | O(n log n) | O(1) | 不稳定 |
| 计数排序 | O(n + k) | O(n + k) | O(n + k) | O(n + k) | 稳定 |
| 基数排序 | O(n × d) | O(n × d) | O(n × d) | O(n + k) | 稳定 |
| 桶排序 | O(n + k) | O(n + k) | O(n²) | O(n + k) | 稳定 |

### 稳定性分类

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 40, 'rankSpacing': 20, 'padding': 15}}}%%
graph TD
    STABLE["稳定排序"] --> SB["冒泡"] & SI["插入"] & SM["归并"] & SC["计数"] & SR["基数"] & SBK["桶"]
    UNSTABLE["不稳定排序"] --> US["选择"] & UQ["快速"] & UH["堆"] & USH["希尔"]

    classDef stab fill:#0b8457,color:#fff,stroke:#065535
    classDef unstab fill:#e94560,color:#fff,stroke:#c81e45
    classDef item fill:#0f3460,color:#fff,stroke:#0a2647

    class STABLE stab
    class UNSTABLE unstab
    class SB,SI,SM,SC,SR,SBK,US,UQ,UH,USH item
```

---

## 5. 典型应用场景

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 15}}}%%
graph TD
    SCENE["场景选择"]
    SCENE --> SMALL["小规模 n < 50<br/>→ 插入排序"]
    SCENE --> LARGE["大规模随机数据<br/>→ 快速排序"]
    SCENE --> ORDERED["基本有序<br/>→ 插入排序"]
    SCENE --> NEED_STABLE["需要稳定排序<br/>→ 归并排序"]
    SCENE --> MEM["内存受限<br/>→ 堆排序"]
    SCENE --> INT["整数且范围小<br/>→ 计数排序"]
    SCENE --> UNIFORM["分布均匀<br/>→ 桶排序"]
    SCENE --> DIGIT["多位数整数<br/>→ 基数排序"]

    classDef root fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef scene fill:#533483,color:#fff,stroke:#2c1654

    class SCENE root
    class SMALL,LARGE,ORDERED,NEED_STABLE,MEM,INT,UNIFORM,DIGIT scene
```

### 系统级应用
- **数据库**：ORDER BY 实现，索引排序
- **文件系统**：目录列表排序
- **编译器**：符号表排序，优化决策

### 算法基础
- **搜索算法**：二分搜索需要有序数据
- **贪心算法**：通常需要排序作为预处理
- **图算法**：Kruskal 算法需要排序边

---

## 6. 实际性能考虑

### 6.1 混合排序策略

> **Timsort**（Python `sorted()` / Java `Collections.sort()` 实际使用的算法）：小数组（n < 32）用插入排序，大数组用归并排序变体，并利用数据中已有的有序段（run），最坏 O(n log n)，最好 O(n)。

> **优化快速排序**：随机选择 pivot 或三数取中避免最坏情况；小数组切换插入排序；三路划分处理大量重复元素。

### 6.2 影响实际性能的因素
- **常数因子**：同为 O(n log n) 的算法间实际速度差异大
- **缓存友好性**：快速排序缓存友好，堆排序不友好
- **数据移动代价**：链表适合归并排序，数组适合快速排序

---

## 7. 编程语言标准库排序实现

| 语言 | 函数 | 算法 |
|------|------|------|
| C | `qsort()` | 通常为快速排序 |
| Java | `Arrays.sort()` | 基本类型 Dual-Pivot QuickSort；对象 Timsort |
| Python | `sorted()` / `list.sort()` | Timsort |
| Go | `sort.Sort()` | 模式自适应排序（pdqsort） |
| JavaScript | `Array.prototype.sort()` | 各引擎不同（V8 使用 Timsort） |
| Rust | `slice.sort()` | 自适应归并排序（Timsort 变体） |

---

## 8. 学习建议

### 学习路径

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 45, 'padding': 20}}}%%
graph LR
    L1["1. 基础排序<br/>冒泡 / 选择 / 插入"] --> L2["2. 进阶排序<br/>快速排序（重点）"]
    L2 --> L3["3. 稳定排序<br/>归并排序"]
    L3 --> L4["4. 原地排序<br/>堆排序 / 希尔排序"]
    L4 --> L5["5. 线性排序<br/>计数 / 基数 / 桶"]

    classDef step fill:#0f3460,color:#fff,stroke:#0a2647

    class L1,L2,L3,L4,L5 step
```

### 实践要点
- 能手写快速排序和归并排序（面试重点）
- 理解分治思想在排序中的应用
- 掌握稳定性概念和应用场景
- 学会根据场景选择合适的排序算法
- 了解实际库函数使用的排序算法

---

## 9. 十大排序算法多语言实现

| 排序算法 | C | Java | Go | Python | JavaScript | TypeScript | Rust | Dart |
|---------|---|------|----|--------|------------|------------|------|------|
| **冒泡排序** | [C](./bubblesort/bubble_sort.c) | [Java](./bubblesort/BubbleSort.java) | [Go](./bubblesort/bubble_sort.go) | [PY](./bubblesort/bubble_sort.py) | [JS](./bubblesort/bubble_sort.js) | [TS](./bubblesort/BubbleSort.ts) | [Rust](./bubblesort/bubble_sort.rs) | [Dart](./bubblesort/bubble_sort.dart) |
| **选择排序** | [C](./selectionsort/selection_sort.c) | [Java](./selectionsort/SelectionSort.java) | [Go](./selectionsort/selection_sort.go) | [PY](./selectionsort/selection_sort.py) | [JS](./selectionsort/selection_sort.js) | [TS](./selectionsort/SelectionSort.ts) | [Rust](./selectionsort/selection_sort.rs) | - |
| **插入排序** | [C](./insertsort/insert_sort.c) | [Java](./insertsort/InsertSort.java) | [Go](./insertsort/insert_sort.go) | [PY](./insertsort/insert_sort.py) | [JS](./insertsort/insert_sort.js) | [TS](./insertsort/InsertSort.ts) | [Rust](./insertsort/insert_sort.rs) | - |
| **希尔排序** | [C](./shellsort/shell_sort.c) | [Java](./shellsort/ShellSort.java) | [Go](./shellsort/shell_sort.go) | [PY](./shellsort/shell_sort.py) | [JS](./shellsort/shell_sort.js) | [TS](./shellsort/ShellSort.ts) | [Rust](./shellsort/shell_sort.rs) | - |
| **快速排序** | [C](./quicksort/quick_sort.c) | [Java](./quicksort/QuickSort.java) | [Go](./quicksort/quick_sort.go) | [PY](./quicksort/quick_sort.py) | [JS](./quicksort/quick_sort.js) | [TS](./quicksort/QuickSort.ts) | [Rust](./quicksort/quick_sort.rs) | - |
| **归并排序** | [C](./mergesort/merge_sort.c) | [Java](./mergesort/MergeSort.java) | [Go](./mergesort/merge_sort.go) | [PY](./mergesort/merge_sort.py) | [JS](./mergesort/merge_sort.js) | [TS](./mergesort/MergeSort.ts) | [Rust](./mergesort/merge_sort.rs) | - |
| **堆排序** | [C](./heapsort/heap_sort.c) | [Java](./heapsort/HeapSort.java) | [Go](./heapsort/heap_sort.go) | [PY](./heapsort/heap_sort.py) | [JS](./heapsort/heap_sort.js) | [TS](./heapsort/HeapSort.ts) | [Rust](./heapsort/heap_sort.rs) | - |
| **计数排序** | [C](./countingsort/counting_sort.c) | [Java](./countingsort/CountingSort.java) | [Go](./countingsort/counting_sort.go) | [PY](./countingsort/counting_sort.py) | [JS](./countingsort/counting_sort.js) | [TS](./countingsort/CountingSort.ts) | [Rust](./countingsort/counting_sort.rs) | - |
| **基数排序** | [C](./radixsort/radix_sort.c) | [Java](./radixsort/RadixSort.java) | [Go](./radixsort/radix_sort.go) | [PY](./radixsort/radix_sort.py) | [JS](./radixsort/radix_sort.js) | [TS](./radixsort/RadixSort.ts) | [Rust](./radixsort/radix_sort.rs) | - |
| **桶排序** | [C](./bucketsort/bucket_sort.c) | [Java](./bucketsort/BucketSort.java) | [Go](./bucketsort/bucket_sort.go) | [PY](./bucketsort/bucket_sort.py) | [JS](./bucketsort/bucket_sort.js) | [TS](./bucketsort/BucketSort.ts) | [Rust](./bucketsort/bucket_sort.rs) | - |
