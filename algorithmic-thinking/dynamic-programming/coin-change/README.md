## 【零钱兑换算法详解】C/Java/Go/Python/JS/Rust不同语言实现

## 说明

零钱兑换问题是动态规划的经典问题：给定不同面额的硬币和一个总金额，计算可以凑成总金额的最少硬币数。

> **生活类比**：用 1元、5元、10元、20元纸币凑出 43 元，求最少需要几张。

## 实现过程

1. 定义 dp[i] 为凑出金额 i 的最少硬币数
2. 初始化 dp[0] = 0，其他为无穷大
3. 对于每个金额 i，遍历所有硬币面额
4. dp[i] = min(dp[i], dp[i-coin] + 1)
5. 返回 dp[amount]

## 算法流程

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 20, 'rankSpacing': 20, 'padding': 15}}}%%
graph LR
    S(["开始"]) --> INIT["初始化dp数组"]
    INIT --> LOOP1["i从1到amount"]
    LOOP1 --> LOOP2["遍历每个硬币"]
    LOOP2 --> CHECK{"i >= coin ?"}
    CHECK -->|"是"| UPDATE["dp[i] = min(dp[i], dp[i-coin]+1)"]
    CHECK -->|"否"| NEXTC["下一个硬币"]
    UPDATE --> NEXTC
    NEXTC --> LOOP2
    LOOP2 -->|"完成"| NEXTI["i++"]
    NEXTI --> LOOP1
    LOOP1 -->|"完成"| RETURN["返回dp[amount]"]

    classDef start fill:#0b8457,color:#fff,stroke:#065535
    classDef end1 fill:#e74c3c,color:#fff,stroke:#c0392b
    classDef decision fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647

    class S start
    class RETURN end1
    class CHECK decision
    class INIT,LOOP1,LOOP2,UPDATE,NEXTC,NEXTI process
```

## 示意图

```
coins = [1, 2, 5], amount = 11

dp[0] = 0
dp[1] = 1 (1)
dp[2] = 1 (2)
dp[3] = 2 (1+2)
dp[4] = 2 (2+2)
dp[5] = 1 (5)
dp[6] = 2 (5+1)
dp[7] = 2 (5+2)
dp[8] = 3 (5+2+1)
dp[9] = 3 (5+2+2)
dp[10] = 2 (5+5)
dp[11] = 3 (5+5+1)
```

## 复杂度分析

| 复杂度 | 说明 |
|--------|------|
| 时间复杂度 | O(amount × coins) |
| 空间复杂度 | O(amount) |

## 实际应用举例

### 1. 自动售货机找零
**场景**：计算找零的最少硬币/纸币数量。

**具体例子**：
- 输入：硬币 [1, 5, 10, 25]，金额 67
- 输出：6 (25+25+10+5+1+1)
- 应用：自动售货机、收银系统

```mermaid
graph TB
    ROOT(("找零计算"))
    ROOT --> INPUT["输入: 硬币面额, 金额67"]
    INPUT --> DP["动态规划计算"]
    DP --> OUTPUT["输出: 最少6枚硬币"]
    OUTPUT --> DISPENSE["自动找零"]
    
    classDef root fill:#1a1a2e,color:#fff,stroke:#16213e
    classDef process fill:#0f3460,color:#fff,stroke:#0a2647
    classDef output fill:#2ecc71,color:#fff,stroke:#27ae60
    
    class ROOT root
    class INPUT,DP,DISPENSE process
    class OUTPUT output
```

### 2. 最少邮票数
**场景**：用不同面值的邮票凑出指定邮资。

**具体例子**：
- 输入：邮票 [1, 3, 5]，邮资 8
- 输出：2 (5+3)
- 应用：邮政系统、资源分配

### 3. 购物优惠组合
**场景**：用不同面值的优惠券凑出指定折扣金额。

**具体例子**：
- 输入：优惠券 [5, 10, 20]，折扣 35
- 输出：2 (20+15 或 10+10+10+5)
- 应用：电商平台、促销活动

## 实现列表

| 语言 | 文件名 |
|------|--------|
| C | [coin_change.c](./coin_change.c) |
| Java | [CoinChange.java](./CoinChange.java) |
| Go | [coin_change.go](./coin_change.go) |
| Python | [coin_change.py](./coin_change.py) |
| JavaScript | [coin_change.js](./coin_change.js) |
| Rust | [coin_change.rs](./coin_change.rs) |
