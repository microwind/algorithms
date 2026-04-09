/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 绝对值计算 (Absolute Value)
 * 计算数值的绝对值
 * 时间复杂度: O(1)
 */

/**
 * 计算数字的绝对值
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
function absoluteValue(n: number): number {
    return n < 0 ? -n : n;
}

/**
 * Math.abs标准实现
 */
function absoluteValueStandard(n: number): number {
    return Math.abs(n);
}

/**
 * 泛型版本的绝对值
 * TypeScript中可以用number类型覆盖所有数值
 */
function absoluteValueTyped<T extends number>(n: T): T {
    return (n < 0 ? -n : n) as T;
}

/**
 * BigInt版本的绝对值
 */
function absoluteValueBigInt(n: bigint): bigint {
    return n < 0 ? -n : n;
}

// 类型安全的绝对值函数
function absTyped<T extends number>(n: T): T {
    return (n < 0 ? -n : n) as T;
}

// 编译时类型检查
const result1: number = absTyped(-42);        // ✓ 正确
const result2: number = absTyped(-3.14);      // ✓ 正确
// const result3: string = absTyped("hello");   // ✗ 编译错误

// 与接口结合
interface Point {
    x: number;
    y: number;
}

function manhattanDistance(p1: Point, p2: Point): number {
    return Math.abs(p2.x - p1.x) + Math.abs(p2.y - p1.y);
}

/**
 * 测试函数
 */
function testAbsoluteValue(): void {
    console.log("========================================");
    console.log("    绝对值计算演示 (Absolute Value)");
    console.log("========================================\n");
    
    // 测试用例
    const testCases: number[] = [-42, 0, 100, -3.14, 2.718, -0];
    
    console.log("测试数据及结果:");
    console.log("----------------------------------------");
    testCases.forEach((num: number) => {
        const result: number = absoluteValue(num);
        const stdResult: number = absoluteValueStandard(num);
        console.log(`输入: ${num.toString().padStart(10)} | 自定义: ${result.toString().padStart(10)} | 标准库: ${stdResult.toString().padStart(10)}`);
    });
    
    // BigInt测试
    console.log("\nBigInt测试:");
    console.log("----------------------------------------");
    const bigNum: bigint = -999999999999999999999999999999n;
    console.log(`输入: ${bigNum} | 绝对值: ${absoluteValueBigInt(bigNum)}`);
    
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
    
    // 类型安全示例
    console.log("\n========================================");
    console.log("TypeScript类型安全示例:");
    console.log("========================================");
    console.log(``);
}

// 运行测试
testAbsoluteValue();

export { absoluteValue, absoluteValueStandard, absoluteValueTyped, absoluteValueBigInt };

/*打印结果
jarry@Mac ts % ts-node abs.ts 
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
输入:          0 | 自定义:          0 | 标准库:          0

BigInt测试:
----------------------------------------
输入: -999999999999999999999999999999 | 绝对值: 999999999999999999999999999999

========================================
数学性质:
========================================
• 非负性: |x| ≥ 0
• 正定性: |x| = 0 当且仅当 x = 0
• 对称性: |-x| = |x|
• 三角不等式: |x + y| ≤ |x| + |y|
• 乘法性质: |x × y| = |x| × |y|

========================================
应用场景:
========================================
• 距离计算: 曼哈顿距离、欧几里得距离
• 误差分析: 绝对误差、相对误差
• 数值比较: 比较浮点数精度
• 向量运算: 向量的模（长度）

========================================
TypeScript类型安全示例:
========================================
*/