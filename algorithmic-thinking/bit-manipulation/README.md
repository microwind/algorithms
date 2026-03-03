# 位操作算法描述 bit-manipulation algorithms

#### 算法 1：single_number（找出单独数字）
- **描述**：在数组中找到只出现一次的数字，其他数字都出现两次
- **方法**：XOR 技巧 (a ^ a = 0, a ^ 0 = a)
- **复杂度**：O(n) 时间，O(1) 空间
- **文件**：
  - `single_number.py`
  - `single_number.c`
  - `SingleNumber.java`
  - `single_number.go`
  - `single_number.js`
  - `single_number.rs`

#### 算法 2：power_of_two（2的幂检测）
- **描述**：检查数字是否为 2 的幂，计算指数，找下一个 2 的幂
- **方法**：位运算 (n & (n-1) == 0)
- **复杂度**：O(1) 时间和空间
- **文件**：
  - `power_of_two.py`
  - `power_of_two.c`
  - `PowerOfTwo.java`
  - `power_of_two.go`
  - `power_of_two.js`
  - `power_of_two.rs`

#### 算法 3：count_bits（计数 1 位）
- **描述**：计算二进制表示中的 1 位数（哈明权重）
- **方法**：循环、Kernighan、查表、并行计数
- **复杂度**：O(log n) 到 O(1)，取决于方法
- **文件**：
  - `count_bits.py`
  - `count_bits.c`
  - `CountBits.java`
  - `count_bits.go`
  - `count_bits.js`
  - `count_bits.rs`

#### 算法 4：reverse_bits（位反转）
- **描述**：反转 32 位整数中的位
- **方法**：迭代、手动操作、逐字节、查表
- **复杂度**：O(32) = O(1) 时间，O(1) 到 O(256) 空间
- **文件**：
  - `reverse_bits.py`
  - `reverse_bits.c`
  - `ReverseBits.java`
  - `reverse_bits.go`
  - `reverse_bits.js`
  - `reverse_bits.rs`

#### 算法 5：max_xor_pair（最大 XOR 对）
- **描述**：从数组中的任何对找到最大 XOR 值
- **方法**：蛮力 O(n²)、Trie树 O(n)、贪心 O(n)
- **复杂度**：O(n²) 到 O(n log n)，取决于方法
- **文件**：
  - `max_xor_pair.py`
  - `max_xor_pair.c`
  - `MaxXorPair.java`
  - `max_xor_pair.go`
  - `max_xor_pair.js`
  - `max_xor_pair.rs`

## 代码质量特性

每个实现都包括：

### 结构
- 完整的模块/文件头部，包含算法描述
- 问题陈述和核心概念
- 时间和空间复杂度分析
- 多种实现方法
- 综合测试用例

### 文档
- 详细的函数/方法注释
- 逐行算法解释
- 教育性内联注释
- 清晰的输出格式
- 强调语言特定习语

### 测试覆盖
- 每个文件 4-5 个最少测试用例
- 边界情况（边界值、空数组）
- 特殊模式（全 0、全 1、稀疏位）
- 大值和最大整数
- 对称性验证（如适用）
- 负数处理

### 语言特定优化
- **Python**：全面的文档字符串，多种实现
- **C**：手动内存管理，二进制打印工具
- **Java**：静态方法，内置位操作
- **Go**：惯用的 Go 风格函数，高效操作
- **JavaScript**：现代 ES6+ 语法，正确的 32 位处理
- **Rust**：安全的类型处理，标准库方法

## 关键算法概念覆盖

### 位运算
- XOR (^)、AND (&)、OR (|)、NOT (~)
- 左移 (<<)、右移 (>>)、无符号右移 (>>>)
- 位操作技巧
- 位提取和设置

### 数据结构
- 二进制前缀表示的 Trie 树
- 哈希映射/字典
- 数组和向量

### 算法
- 蛮力方法
- 贪心位构建
- 基于树的优化
- 查表缓存
- 并行处理