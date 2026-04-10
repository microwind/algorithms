# 字符串基础操作（String Basic）

> 字符串的基本操作，包括反转、拼接、子串、替换等常用功能。

## 导航

| [功能说明](#功能说明) | [复杂度分析](#复杂度分析) | [实现列表](#实现列表) |

---

## 功能说明

### 常用操作

| 操作 | 说明 | 示例 |
|------|------|------|
| 反转 | 字符顺序颠倒 | "abc" → "cba" |
| 拼接 | 字符串连接 | "a" + "b" = "ab" |
| 子串 | 提取部分字符串 | "abc"[1:3] = "bc" |
| 查找 | 子串位置 | indexOf("abc", "b") = 1 |
| 替换 | 替换子串 | replace("a,b,c", ",", "-") = "a-b-c" |
| 分割 | 按分隔符分割 | split("a,b,c", ",") = ["a","b","c"] |
| 去空白 | 移除首尾空格 | trim("  abc  ") = "abc" |
| 大小写 | 转换大小写 | toUpper("abc") = "ABC" |

---

## 复杂度分析

| 操作 | 时间复杂度 | 空间复杂度 |
|------|-----------|-----------|
| 反转 | O(n) | O(n)或O(1) |
| 拼接 | O(n+m) | O(n+m) |
| 子串 | O(k) | O(k) |
| 查找 | O(n×m)朴素/O(n+m)KMP | O(1)或O(m) |
| 分割 | O(n) | O(n) |

---

## 适用场景

- **文本处理**：格式化、清洗
- **数据解析**：CSV、日志处理
- **输入验证**：格式检查
- **代码生成**：模板处理

---

## 实现列表

| 语言 | 文件名 | 说明 |
|------|--------|------|
| C | [string_basic.c](./string_basic.c) | 字符数组操作 |
| Java | [StringBasic.java](./StringBasic.java) | String类方法 |
| Go | [string_basic.go](./string_basic.go) | strings包 |
| Python | [string_basic.py](./string_basic.py) | 内置方法 |
| JavaScript | [string_basic.js](./string_basic.js) | 字符串方法 |
| TypeScript | [StringBasic.ts](./StringBasic.ts) | 类型安全 |
| Rust | [string_basic.rs](./string_basic.rs) | String/str |

---

## 使用示例

### Python 版本
```python
# 基础操作
s = "hello world"
reversed_s = s[::-1]  # "dlrow olleh"
upper = s.upper()     # "HELLO WORLD"
sub = s[0:5]          # "hello"
words = s.split()     # ["hello", "world"]
joined = "-".join(words)  # "hello-world"
```

---

## 扩展阅读

- 字符串编码（UTF-8, UTF-16）
- 不可变字符串的优势
- 字符串池与驻留
