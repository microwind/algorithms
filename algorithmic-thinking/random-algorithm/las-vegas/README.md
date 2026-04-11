# 拉斯维加斯算法（Las Vegas Algorithm）

> 一种随机化算法，总是给出正确答案，但运行时间是随机的。适用于需要保证正确性但可以接受不确定运行时间的场景。

---

## 概述

拉斯维加斯算法是一种随机化算法，其特点是：
- **总是给出正确答案**
- **运行时间是随机的**
- 不会返回错误答案，但可能需要多次尝试

## 与蒙特卡洛算法的对比

| 特性 | 拉斯维加斯 | 蒙特卡洛 |
|------|----------|---------|
| 正确性 | 总是正确 | 概率正确 |
| 时间 | 随机 | 固定 |
| 例子 | 随机快速排序 | π估算 |

## 经典应用

### 1. 随机快速排序（Randomized QuickSort）
- 随机选择枢轴避免最坏情况
- 期望时间复杂度 O(n log n)
- 总是返回正确排序结果

### 2. 随机选择算法（Randomized Select）
- 平均 O(n) 时间找到第 k 小元素
- 基于随机分区的选择算法

### 3. 拉斯维加斯字符串匹配
- 随机化模式匹配

### 流程图

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 5}}}%%
graph TD
    S(["开始"]) --> INIT["初始化"]
    INIT --> LOOP{"达到最大尝试次数?"}
    LOOP -->|"是"| FAIL["失败"]
    LOOP -->|"否"| RANDOM["生成随机选择"]
    RANDOM --> COMPUTE["执行计算"]
    COMPUTE --> VALID{"结果正确?"}
    VALID -->|"是"| SUCCESS["返回结果"]
    VALID -->|"否"| RETRY["重试"]
    RETRY --> LOOP
    SUCCESS --> END(["结束"])
    FAIL --> END

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef decision fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647

    class S,END start
    class LOOP,VALID decision
    class INIT,RANDOM,COMPUTE,SUCCESS,FAIL,RETRY process
```

## 复杂度分析

| 指标 | 复杂度 | 说明 |
|------|--------|------|
| **期望时间** | 依问题而定 | 随机变量的期望 |
| **最坏时间** | 无界 | 理论上可能无限 |
| **正确性** | 总是返回正确结果，但运行时间不确定的随机算法。 |

## 实现列表

| 语言 | 文件名 | 说明 |
|------|--------|------|
| C | [las_vegas.c](./las_vegas.c) | 拉斯维加斯实现 |
| Java | [LasVegas.java](./LasVegas.java) | 拉斯维加斯类 |
| Python | [las_vegas.py](./las_vegas.py) | 简洁实现 |
| Go | [las_vegas.go](./las_vegas.go) | 并发优化 |


## 扩展阅读

- 随机快速排序的期望分析
- 随机选择算法
- 与蒙特卡洛算法的相互转换- 保证找到所有匹配位置

## 实现语言

本目录包含以下语言的实现：
- C
- Go
- Java
- JavaScript
- Python
- Rust
