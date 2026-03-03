/*
*
 * 编辑距离 (Edit Distance / Levenshtein Distance) - 动态规划应用
 *
 * 问题描述：
 * 给定两个字符串，计算从一个字符串转换到另一个字符串所需的最少编辑操作数
 *
 * 动态规划方程：
 * if s1[i-1] == s2[j-1]:
 *     dp[i][j] = dp[i-1][j-1]
 * else:
 *     dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
 *
 * 时间复杂度: O(m * n)
 * 空间复杂度: O(m * n)
*/

/*
*
 * 编辑距离 - 求最少操作数
*/
function editDistance(s1, s2) {
    const m = s1.length;
    const n = s2.length;

    // dp[i][j] 表示将 s1[0:i] 转换到 s2[0:j] 的最少操作数
    const dp = Array(m + 1).fill(null).map(() => Array(n + 1).fill(0));

    // 初始化
    for (let j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    for (let i = 0; i <= m; i++) {
        dp[i][0] = i;
    }

    // 填充 DP 表
    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            if (s1[i - 1] === s2[j - 1]) {
                // 字符相同，不需要操作
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // 字符不同，选择最少操作数的方案
                dp[i][j] = 1 + Math.min(
                    dp[i - 1][j],      // 删除
                    dp[i][j - 1],      // 插入
                    dp[i - 1][j - 1]   // 替换
                );
            }
        }
    }

    return dp[m][n];
}

/*
*
 * 编辑距离 - 空间优化版本
*/
function editDistanceOptimized(s1, s2) {
    let m = s1.length;
    let n = s2.length;

    // 确保 s1 是较短的字符串
    if (m > n) {
        [s1, s2] = [s2, s1];
        [m, n] = [n, m];
    }

    // 使用两行数组来计算
    let prev = Array(n + 1).fill(0);
    let curr = Array(n + 1).fill(0);

    // 初始化 prev 行
    for (let j = 0; j <= n; j++) {
        prev[j] = j;
    }

    for (let i = 1; i <= m; i++) {
        curr[0] = i;

        for (let j = 1; j <= n; j++) {
            if (s1[i - 1] === s2[j - 1]) {
                curr[j] = prev[j - 1];
            } else {
                curr[j] = 1 + Math.min(
                    prev[j],           // 删除
                    curr[j - 1],       // 插入
                    prev[j - 1]        // 替换
                );
            }
        }

        // 交换行
        [prev, curr] = [curr, prev];
    }

    return prev[n];
}

// 测试函数
console.log("=== 编辑距离问题 ===\n");

// 测试用例1：基本编辑距离
console.log("1. 基本编辑距离");
const s1_1 = "horse";
const s2_1 = "ros";
console.log("字符串1:", s1_1);
console.log("字符串2:", s2_1);
console.log("编辑距离:", editDistance(s1_1, s2_1));
console.log();

// 测试用例2：相同字符串
console.log("2. 相同字符串");
const s1_2 = "hello";
const s2_2 = "hello";
console.log("字符串1:", s1_2);
console.log("字符串2:", s2_2);
console.log("编辑距离:", editDistance(s1_2, s2_2));
console.log();

// 测试用例3：空字符串
console.log("3. 空字符串");
const s1_3 = "abc";
const s2_3 = "";
console.log("字符串1:", s1_3);
console.log("字符串2:", s2_3);
console.log("编辑距离:", editDistance(s1_3, s2_3));
console.log();

// 测试用例4：不同长度的字符串
console.log("4. 不同长度的字符串");
const s1_4 = "intention";
const s2_4 = "execution";
console.log("字符串1:", s1_4);
console.log("字符串2:", s2_4);
console.log("编辑距离:", editDistance(s1_4, s2_4));
console.log("编辑距离（优化）:", editDistanceOptimized(s1_4, s2_4));
