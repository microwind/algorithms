# 字符串递归操作（String Recursion）

> 使用递归处理字符串相关问题。

## 算法原理

### 常见递归操作

| 操作 | 递归定义 | 终止条件 |
|------|----------|----------|
| 反转 | reverse(s) = reverse(s[1:]) + s[0] | 空串 |
| 回文判断 | 首字符==尾字符且中间是回文 | 长度<=1 |
| 子序列 | 包含/不包含当前字符 | 空串 |
| 排列 | 每个字符作为开头 | 空串 |

---

## 复杂度分析

| 操作 | 时间复杂度 | 空间复杂度 |
|------|-----------|-----------|
| 字符串反转 | O(n) | O(n)栈 |
| 回文判断 | O(n) | O(n)栈 |
| 全排列 | O(n!) | O(n)栈 |
| 子序列 | O(2^n) | O(n)栈 |

## 算法流程

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 20}}}%%
graph LR
    S(["开始"]) --> INPUT["输入字符串"]
    INPUT --> TYPE{"操作类型?"}
    TYPE -->|"反转"| REVERSE["递归: reverse(s[1:]) + s[0]"]
    TYPE -->|"回文判断"| PALIN["首尾字符比较"]
    TYPE -->|"子序列"| SUBSEQ["包含/不包含当前字符"]
    TYPE -->|"排列"| PERMUTE["每个字符作为开头"]
    REVERSE --> CHECK1{"字符串为空?"}
    PALIN --> CHECK2{"长度<=1?"}
    SUBSEQ --> CHECK3{"字符串为空?"}
    PERMUTE --> CHECK4{"字符串为空?"}
    CHECK1 -->|"是"| END1(["返回空串"])
    CHECK1 -->|"否"| RECURSE1["递归处理剩余部分"]
    CHECK2 -->|"是"| END2(["返回True"])
    CHECK2 -->|"否"| COMPARE{"首==尾?"}
    CHECK3 -->|"是"| END3(["返回空串"])
    CHECK3 -->|"否"| RECURSE3["递归生成子序列"]
    CHECK4 -->|"是"| END4(["返回空串"])
    CHECK4 -->|"否"| RECURSE4["递归排列剩余字符"]
    COMPARE -->|"否"| END5(["返回False"])
    COMPARE -->|"是"| RECURSE2["递归检查中间部分"]
    RECURSE1 --> END1
    RECURSE2 --> END2
    RECURSE3 --> END3
    RECURSE4 --> END4

    %% 节点样式
    classDef start fill:#ff7f50,color:#fff,stroke:#e5533c,stroke-width:2px
    classDef end1 fill:#ff7f50,color:#fff,stroke:#e5533c,stroke-width:2px
    classDef decision fill:#6a5acd,color:#fff,stroke:#483d8b,stroke-width:2px
    classDef process fill:#20b2aa,color:#fff,stroke:#008080,stroke-width:2px
    
    %% 应用样式
    class S,END1,END2,END3,END4,END5 start
    class TYPE,CHECK1,CHECK2,CHECK3,CHECK4,COMPARE decision
    class INPUT,REVERSE,PALIN,SUBSEQ,PERMUTE,RECURSE1,RECURSE2,RECURSE3,RECURSE4 process
```

---

## 适用场景

- **字符串处理**：反转、回文、子串
- **模式匹配**：递归正则表达式
- **生成问题**：排列、组合、子集
- **解析器实现**：语法树递归下降

---

## 实现列表

| 语言 | 文件名 | 说明 |
|------|--------|------|
| C | [string_recursion.c](./string_recursion.c) | 递归实现 |
| Java | [StringRecursion.java](./StringRecursion.java) | 类封装 |
| Go | [string_recursion.go](./string_recursion.go) | 递归实现 |
| Python | [string_recursion.py](./string_recursion.py) | 递归实现 |
| JavaScript | [string_recursion.js](./string_recursion.js) | 递归实现 |
| TypeScript | [StringRecursion.ts](./StringRecursion.ts) | 类型安全 |
| Rust | [string_recursion.rs](./string_recursion.rs) | 递归实现 |

---

## 使用示例

### Python 版本
```python
# 字符串反转
result = reverse_string("hello")  # "olleh"

# 回文判断
result = is_palindrome("racecar")  # True

# 所有子序列
result = all_subsequences("abc")
# ['', 'a', 'b', 'c', 'ab', 'ac', 'bc', 'abc']
```

---

## 扩展阅读

- 迭代vs递归字符串处理
- 尾递归优化
- 字符串动态规划
