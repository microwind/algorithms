# 基础数学运算（Basic Math）

> 基础算术运算实现，包括加减乘除、取模、绝对值等基本数学操作。

## 导航

| [功能说明](#功能说明) | [复杂度分析](#复杂度分析) | [实现列表](#实现列表) |

---

## 功能说明

### 支持的运算

| 运算 | 说明 | 示例 |
|------|------|------|
| 加法 | 两数相加 | 5 + 3 = 8 |
| 减法 | 两数相减 | 5 - 3 = 2 |
| 乘法 | 两数相乘 | 5 × 3 = 15 |
| 除法 | 带余除法 | 17 ÷ 5 = 3...2 |
| 取模 | 求余数 | 17 % 5 = 2 |
| 绝对值 | 非负值 | \| -5 \| = 5 |
| 最大/最小 | 比较运算 | max(3,5) = 5 |
| 幂运算 | 乘方 | 2³ = 8 |
| 平方根 | 开方 | √16 = 4 |

### 大数运算

- 大整数加法/乘法（超出标准类型的数值）
- 高精度浮点运算
- 科学计数法处理

---

## 复杂度分析

| 指标 | 复杂度 | 说明 |
|------|--------|------|
| **时间复杂度** | O(1) | 基础运算为常数时间 |
| **大数运算** | O(n) | n为数字位数 |
| **空间复杂度** | O(1) | 基础运算，大数运算O(n) |

---

## 适用场景

- **科学计算**：基础算术需求
- **金融计算**：精度要求高的计算
- **教学演示**：算法基础学习
- **嵌入式系统**：基础数学库
- **密码学应用**：大数运算基础

---

## 实现列表

| 语言 | 文件 | 说明 |
|------|------|------|
| C | [addition.c](./c/addition.c), [subtraction.c](./c/subtraction.c), [multiplication.c](./c/multiplication.c), [division.c](./c/division.c) | 基础运算 |
| Java | [BasicMath.java](./java/BasicMath.java) | 封装类 |
| Go | [basic/](./go) | 多文件实现 |
| Python | [basic_operations.py](./py/basic_operations.py) | 运算符重载 |
| JavaScript | [math_operations.js](./js/math_operations.js) | Math对象应用 |
| TypeScript | [BasicMath.ts](./ts/BasicMath.ts) | 类型安全版本 |
| Rust | [basic_math.rs](./rs/basic_math.rs) | 泛型实现 |

---

## 使用示例

### Python 版本
```python
# 基础运算
result = add(5, 3)  # 8
result = multiply(5, 3)  # 15
result = power(2, 10)  # 1024
result = sqrt(16)  # 4.0

# 大数运算
big = big_add("12345678901234567890", "98765432109876543210")
```

---

## 扩展阅读

- IEEE 754 浮点数标准
- 高精度计算库（GMP, MPFR）
- 快速幂算法
- Karatsuba大数乘法
