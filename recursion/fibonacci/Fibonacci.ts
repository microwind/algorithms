/**
 * 斐波那契数列多实现方式教学示例
 * 
 * 包含四种实现：
 * - 纯递归：O(2^n) 时间复杂度
 * - 记忆化递归：O(n) 时间复杂度
 * - 动态规划：O(n) 时间复杂度
 * - 优化DP：O(n) 时间复杂度，O(1) 空间复杂度
 * 
 * 核心公式：F(n) = F(n-1) + F(n-2), F(0) = 0, F(1) = 1
 * 
 * 学习重点：掌握不同优化策略的性能差异
 */

// 记忆化缓存
const memo = new Map<number, number>();

/**
 * 纯递归实现 - 最慢版本
 * 时间复杂度: O(2^n)，空间复杂度: O(n)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
function fibNaive(n: number): number {
    // 基本情况
    if (n <= 1) return n;
    
    // 递归调用
    return fibNaive(n - 1) + fibNaive(n - 2);
}

/**
 * 记忆化递归实现 - 推荐版本
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
function fibMemo(n: number): number {
    // 检查缓存
    if (memo.has(n)) return memo.get(n)!;
    
    // 基本情况
    if (n <= 1) {
        memo.set(n, n);
        return n;
    }
    
    // 计算并缓存结果
    const result = fibMemo(n - 1) + fibMemo(n - 2);
    memo.set(n, result);
    return result;
}

/**
 * 动态规划实现
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
function fibDp(n: number): number {
    // 基本情况
    if (n <= 1) return n;
    
    // DP数组
    const dp = new Array(n + 1).fill(0);
    dp[0] = 0;
    dp[1] = 1;
    
    // 填充DP数组
    for (let i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

/**
 * 优化动态规划实现 - 空间优化
 * 时间复杂度: O(n)，空间复杂度: O(1)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
function fibOptimized(n: number): number {
    // 基本情况
    if (n <= 1) return n;
    
    // 前两个数
    let prev = 0, curr = 1;
    
    // 迭代计算
    for (let i = 2; i <= n; i++) {
        const next = prev + curr;
        prev = curr;
        curr = next;
    }
    
    return curr;
}

/**
 * 主函数 - 性能对比测试
 */
function main(): void {
    const n = 30;
    console.log(`计算第 ${n} 个斐波那契数`);
    
    // 测试记忆化递归
    console.log(`记忆化递归: ${fibMemo(n)}`);
    
    // 测试动态规划
    console.log(`动态规划: ${fibDp(n)}`);
    
    // 测试优化DP
    console.log(`优化DP: ${fibOptimized(n)}`);
}

// 运行主函数
main();
