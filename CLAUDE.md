# CLAUDE.md

本文件为 Claude Code (claude.ai/code) 在本仓库中工作时提供指引。

## 仓库定位

本仓库是一个**教学参考型代码库**，使用多种编程语言（C、C++、Java、Kotlin、Python、JavaScript、TypeScript、Go、Rust、Swift、Dart、C#、Objective-C）并行实现常见数据结构与算法。它**不是**一个库或应用程序——没有项目级的构建系统、包管理器或测试运行器。每个源文件都是独立可运行的演示程序，面向学习者。

主要受众使用中文阅读：`README.md`（中文）是核心说明，`README_en.md` 是其英文镜像。代码注释也使用中文。

## 架构

### 一种语言一个文件，每个算法平铺存放

每个算法/数据结构都有自己的目录。各语言实现作为同级文件**直接放在该目录下**（而非嵌套在 `implementations/<lang>/` 之下）。例如，`sorting/bubblesort/` 中包含 `bubble_sort.c`、`bubble_sort.py`、`BubbleSort.java`、`bubble_sort.go`、`bubble_sort.rs` 等，连同一个 `README.md` 平铺在一起。

> 注意：`STRUCTURE.md` 描述的是一种"理想化"的嵌套结构（`implementations/c/`、`implementations/java/` 等），但仓库**并未**采用该结构。新增文件时请遵循现有的扁平约定，否则会破坏 README 中的链接表。

### 每个文件都是完整可运行的演示

每个实现文件都：
- 包含署名为 `jarryli@gmail.com` 的版权头
- 定义算法本体并提供 `main` 函数（或 `if __name__ == "__main__":` 等入口）
- 内嵌测试数据（排序类通常使用 `[7, 11, 9, 10, 12, 13, 8]`）并打印结果
- 通常在同一文件中包含同一算法的**多个变体**（例如 `bubbleSort1`/`2`/`3`/`4`，或 quicksort 的 7 种变体），用以对比优化策略与各语言惯用写法
- 在文件末尾以多行注释形式给出**预期 stdout 输出**——这就是测试基准。修改算法行为时，必须同步更新该末尾注释。

仓库中没有独立于实现的单元测试文件。验证方式是运行文件，将其输出与文件末尾的预期输出注释进行对比。

### 每个目录的 README 即为规范

每个算法目录下的 `README.md` 是该算法的"权威说明"：包含算法解释、mermaid 图、复杂度分析以及指向各语言文件的链接表。新增某种语言的实现时，**务必更新该目录的 README.md**，使链接/表格保持完整。仓库根目录的 `README.md` 与 `README_en.md` 同样直接链接到具体语言文件——尽量保持文件名稳定。

### 顶层目录组织（按教学路径，而非工程模块）

```
start-here/              入门指南与学习路线（仅 Markdown）
data-structures/         array、linked、stack、queue、tree、heap、graph、hash、map、set、list、struct
algorithmic-thinking/    greedy、divide-and-conquer、dynamic-programming、backtracking、
                         branch-and-bound、random-algorithm、search-algorithms
sorting/  searching/  string/  tree/  graph/        经典算法分类
array/  recursion/  bit-manipulation/  math/  date-time/   专题算法集合
compression/  cryptography/  network-flow/         专项算法
practice-projects/       实战项目（bloom-filter、cache-system、rate-limiter、
                         consistent-hashing 等）——这些项目**确实**采用了
                         src/<lang>/ + tests/ + docs/ + requirements.txt 的常规布局
problem-sets/            LeetCode 风格题库，按 easy/medium/hard/interview 分级
docs/  resources/        辅助文档、书籍、图片资源
```

`practice-projects/real-world/*` 是仓库中**唯一**采用常规项目结构（`src/python/`、`tests/`、`requirements.txt`）的位置。请不要将这种结构应用到 `practice-projects/` 以外。

## 命名与代码规范

以下约定通过 README 链接表隐式地强约束——一旦破坏，文档链接会静默失效。

| 语言        | 文件名风格                            | 函数/方法风格           |
|-------------|--------------------------------------|------------------------|
| C / C++     | `algorithm_name.c` / `.cpp`          | `snake_case`           |
| Java        | `AlgorithmName.java`                 | `camelCase`            |
| Kotlin      | `AlgorithmName.kt`                   | `camelCase`            |
| Python      | `algorithm_name.py`                  | `snake_case`           |
| JavaScript  | `algorithm_name.js`                  | `camelCase`            |
| TypeScript  | `AlgorithmName.ts`                   | `camelCase`            |
| Go          | `algorithm_name.go`                  | `PascalCase`（导出）    |
| Rust        | `algorithm_name.rs`                  | `snake_case`           |
| Swift       | `algorithm_name.swift`（部分为 `PascalCase.swift`） | `camelCase` |
| Dart        | `algorithm_name.dart`                | `camelCase`            |
| C#          | `AlgorithmName.cs`                   | `PascalCase`           |

来自 `CONTRIBUTING.md` 的补充约定：
- 新文件须添加标准版权头（`@author: jarryli@gmail.com`）。
- 注释使用中文，且偏教学化——多解释*为什么*，并在已有代码已经这样写的地方加入生活化类比和复杂度说明。
- 新增变体时，沿用其他文件中的编号变体模式（`bubbleSort1`、`bubbleSort2`……）。

## 运行代码

仓库内没有 `make`、`npm test` 之类的统一入口。请单文件逐个运行：

```bash
# C / C++
gcc sorting/bubblesort/bubble_sort.c -o /tmp/bs && /tmp/bs
g++ sorting/bubblesort/bubble_sort.cpp -o /tmp/bs && /tmp/bs

# Python
python sorting/bubblesort/bubble_sort.py

# Go（每个文件都使用 package main 并自带 main()——直接 run，不构建为模块）
go run sorting/bubblesort/bubble_sort.go

# Rust（单文件；用 rustc 编译，仓库根目录没有 Cargo 项目）
rustc sorting/bubblesort/bubble_sort.rs -o /tmp/bs && /tmp/bs

# Java（默认包；类名须与文件名一致）
javac sorting/bubblesort/BubbleSort.java && java -cp sorting/bubblesort BubbleSort

# JavaScript / TypeScript
node sorting/bubblesort/bubble_sort.js
npx ts-node sorting/bubblesort/BubbleSort.ts        # 或：tsc && node ...

# Swift / Kotlin / Dart / C#
swift sorting/bubblesort/bubble_sort.swift
kotlinc sorting/bubblesort/BubbleSort.kt -include-runtime -d /tmp/bs.jar && java -jar /tmp/bs.jar
dart run sorting/bubblesort/bubble_sort.dart
dotnet script sorting/bubblesort/BubbleSort.cs
```

"测试"一个实现的方式：运行它，将 stdout 与文件末尾的预期输出注释进行 diff 比对。`.gitignore` 已忽略编译产物（`*.class`、`*.o`、`a.out`、`*.pyc`、`target/`），请勿提交它们。

一个特别注意点：`*/**/ts/**/*.js` 在 .gitignore 中被忽略，意味着任何 `ts/` 子目录下由 TypeScript 编译生成的 .js 文件都不会被提交，这是有意为之。

## 修改或新增代码时

- **为已有算法新增一种语言**：在算法目录下平铺新增文件，使用上方命名表所列风格；从同目录的其他语言实现中复制结构（多个编号变体 + 一个 main 演示）；内嵌相同的测试输入；并在该目录的 `README.md` *以及* 顶层 `README.md` / `README_en.md` 对应行中追加链接。
- **新增一个算法**：在合适的顶层分类下新建目录，先写 `README.md`（解释 + 复杂度 + mermaid 图），再按 `CONTRIBUTING.md` 要求至少补齐 3 种语言的实现。
- **修改算法行为**：在你改动过的每一种语言文件中，同步更新文件末尾的预期输出注释。仓库没有 CI 校验该一致性——必须人工维护。
- **跨语言一致性**：修复 bug 或优化算法时，请将相同的变更同步应用到该算法的所有语言实现。本仓库的教学价值正来自于各语言实现可以直接对照阅读。
