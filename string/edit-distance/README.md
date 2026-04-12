# 编辑距离（Edit Distance）

> 两个字符串之间的最小编辑操作次数，也称Levenshtein距离。

## 算法原理

### 动态规划定义

设dp[i][j]为word1[0..i-1]转换到word2[0..j-1]的最小编辑次数：

```
dp[i][j] = min(
    dp[i-1][j] + 1,      # 删除
    dp[i][j-1] + 1,      # 插入
    dp[i-1][j-1] + cost  # 替换(0或1)
)
```

### 示例

```
kitten → sitting
kitten → sitten (替换k→s)
sitten → sittin (替换e→i)
sittin → sitting (插入g)

编辑距离: 3
```

---

## 复杂度分析

| 指标 | 复杂度 | 说明 |
|------|--------|------|
| **时间复杂度** | O(m×n) | m,n为字符串长度 |
| **空间复杂度** | O(m×n)或O(min(m,n)) | DP表或滚动数组 |

## 算法流程

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 20}}}%%
graph LR
    S(["开始"]) --> INPUT["输入两个字符串"]
    INPUT --> INIT["初始化DP表"]
    INIT --> OUTER{"i < m ?"}
    OUTER -->|"否"| END(["返回 dp[m][n]"])
    OUTER -->|"是"| INNER{"j < n ?"}
    INNER -->|"否"| INCI["i++"]
    INCI --> OUTER
    INNER -->|"是"| CHECK{"字符相同?"}
    CHECK -->|"是"| COST["cost = 0"]
    CHECK -->|"否"| COST1["cost = 1"]
    COST1 --> CALC
    COST --> CALC["dp[i][j] = min<br/>dp[i-1][j]+1<br/>dp[i][j-1]+1<br/>dp[i-1][j-1]+cost"]
    CALC --> INCJ["j++"]
    INCJ --> INNER

    %% 节点样式
    classDef start fill:#ff7f50,color:#fff,stroke:#e5533c,stroke-width:2px
    classDef end1 fill:#ff7f50,color:#fff,stroke:#e5533c,stroke-width:2px
    classDef decision fill:#6a5acd,color:#fff,stroke:#483d8b,stroke-width:2px
    classDef process fill:#20b2aa,color:#fff,stroke:#008080,stroke-width:2px
    
    %% 应用样式
    class S,END start
    class OUTER,INNER,CHECK decision
    class INPUT,INIT,CALC,INCI,INCJ,COST,COST1 process
```

---

## 适用场景

- **拼写纠错**：找出最相近的正确单词
- **DNA比对**：计算序列差异
- **语音识别**：音素序列比对
- **抄袭检测**：文本相似度
- **机器翻译**：评估翻译质量

---

## 实现列表

| 语言 | 文件名 | 说明 |
|------|--------|------|
| C | [edit_distance.c](./edit_distance.c) | DP实现 |
| Java | [EditDistance.java](./EditDistance.java) | 类封装 |
| Go | [edit_distance.go](./edit_distance.go) | 简洁实现 |
| Python | [edit_distance.py](./edit_distance.py) | DP实现 |
| JavaScript | [edit_distance.js](./edit_distance.js) | 迭代实现 |
| TypeScript | [EditDistance.ts](./EditDistance.ts) | 类型安全 |
| Rust | [edit_distance.rs](./edit_distance.rs) | 高效实现 |

---

## 使用示例

### Python 版本
```python
# 计算编辑距离
distance = edit_distance("kitten", "sitting")  # 3

# 获取编辑操作序列
operations = edit_operations("kitten", "sitting")
# ["replace k→s", "replace e→i", "insert g"]
```

---

## 扩展阅读

- 汉明距离（仅替换）
- Damerau-Levenshtein距离（含交换）
- Jaro-Winkler相似度
