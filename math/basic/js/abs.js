/**
 * 数学基础 - 绝对值计算 (Absolute Value)
 * 计算数值的绝对值
 * 时间复杂度: O(1)
 */

/**
 * 计算整数的绝对值
 * 
 * 算法原理：
 * - 正数：绝对值就是其本身
 * - 负数：绝对值是其相反数
 * - 零：绝对值是零
 * 
 * 参数:
 *     n: 要求绝对值的数
 * 返回:
 *     n的绝对值
 * 
 * 时间复杂度: O(1) - 常数时间
 * 空间复杂度: O(1) - 常数空间
 */
function absoluteValue(n) {
    return n < 0 ? -n : n;
}

/**
 * Math.abs标准实现
 */
function absoluteValueStandard(n) {
    return Math.abs(n);
}

/**
 * 不使用条件运算符的绝对值
 * 利用位运算（不适用于JavaScript，因为JS使用浮点数）
 * 这里用数学公式: √(n²)
 */
function absoluteValueMath(n) {
    return Math.sqrt(n * n);
}

/**
 * 测试函数
 */
function testAbsoluteValue() {
    console.log("========================================");
    console.log("    绝对值计算演示 (Absolute Value)");
    console.log("========================================\n");
    
    // 测试用例
    const testCases = [-42, 0, 100, -3.14, 2.718, -0];
    
    console.log("测试数据及结果:");
    console.log("----------------------------------------");
    testCases.forEach(num => {
        const result = absoluteValue(num);
        const stdResult = absoluteValueStandard(num);
        console.log(`输入: ${num.toString().padStart(10)} | 自定义: ${result.toString().padStart(10)} | 标准库: ${stdResult.toString().padStart(10)}`);
    });
    
    // 数学性质
    console.log("\n========================================");
    console.log("数学性质:");
    console.log("========================================");
    console.log("• 非负性: |x| ≥ 0");
    console.log("• 正定性: |x| = 0 当且仅当 x = 0");
    console.log("• 对称性: |-x| = |x|");
    console.log("• 三角不等式: |x + y| ≤ |x| + |y|");
    console.log("• 乘法性质: |x × y| = |x| × |y|");
    
    // 应用场景
    console.log("\n========================================");
    console.log("应用场景:");
    console.log("========================================");
    console.log("• 距离计算: 曼哈顿距离、欧几里得距离");
    console.log("• 误差分析: 绝对误差、相对误差");
    console.log("• 数值比较: 比较浮点数精度");
    console.log("• 向量运算: 向量的模（长度）");
    
    // 代码示例
    console.log("\n========================================");
    console.log("JavaScript代码示例:");
    console.log("========================================");
    console.log(`
// 计算两点间距离
function distance(x1, y1, x2, y2) {
    const dx = Math.abs(x2 - x1);
    const dy = Math.abs(y2 - y1);
    return Math.sqrt(dx*dx + dy*dy);
}

// 误差比较
function roughlyEqual(a, b, epsilon = 0.001) {
    return Math.abs(a - b) < epsilon;
}
`);
}

// 如果直接运行此文件，执行测试
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { absoluteValue, absoluteValueStandard, absoluteValueMath };
    
    if (require.main === module) {
        testAbsoluteValue();
    }
} else {
    // 浏览器环境
    window.absModule = { absoluteValue, absoluteValueStandard, absoluteValueMath, testAbsoluteValue };
}

/* 示例输出:
========================================
    绝对值计算演示 (Absolute Value)
========================================

测试数据及结果:
----------------------------------------
输入:        -42 | 自定义:         42 | 标准库:         42
输入:          0 | 自定义:          0 | 标准库:          0
输入:        100 | 自定义:        100 | 标准库:        100
输入:      -3.14 | 自定义:       3.14 | 标准库:       3.14
输入:      2.718 | 自定义:      2.718 | 标准库:      2.718
输入:         -0 | 自定义:          0 | 标准库:          0
*/
