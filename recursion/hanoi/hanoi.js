/**
 * 汉诺塔问题完整教学示例
 * 
 * 问题描述：将 n 个盘子从 A 柱移动到 C 柱，借助 B 柱
 * 移动规则：
 * - 每次只能移动一个盘子
 * - 大盘子不能放在小盘子上面
 * 
 * 递归过程：
 * 1. 将 n-1 个盘子从 A 移到 B（借助 C）
 * 2. 将第 n 个盘子从 A 移到 C
 * 3. 将 n-1 个盘子从 B 移到 C（借助 A）
 * 
 * 学习重点：理解递归分解和回溯过程
 */

let moveCount = 0;

/**
 * 汉诺塔递归函数
 * 时间复杂度: O(2^n)，空间复杂度: O(n)
 * @param {number} n 盘子数量
 * @param {string} source 起始柱子
 * @param {string} auxiliary 辅助柱子
 * @param {string} target 目标柱子
 */
function hanoi(n, source, auxiliary, target) {
    // 基本情况：只有一个盘子时直接移动
    if (n === 1) {
        console.log(`Move disk 1 from ${source} to ${target}`);
        moveCount++;
        return;
    }
    
    // 递归步骤：
    // 1. 将 n-1 个盘子从 source 移到 auxiliary，借助 target
    hanoi(n - 1, source, auxiliary, target); // Step 1
    
    // 2. 将第 n 个盘子从 source 移到 target
    console.log(`Move disk ${n} from ${source} to ${target}`); // Step 2
    moveCount++;
    
    // 3. 将 n-1 个盘子从 auxiliary 移到 target，借助 source
    hanoi(n - 1, auxiliary, target, source); // Step 3
}

/**
 * 主函数 - 测试汉诺塔问题
 */
function main() {
    console.log("=== 汉诺塔问题 ===");
    
    // 测试不同数量的盘子
    for (let n = 2; n <= 4; n++) {
        console.log(`n = ${n}:`);
        moveCount = 0;
        
        // 调用递归函数
        hanoi(n, 'A', 'B', 'C');
        
        // 输出移动次数验证
        console.log(`总移动次数: ${moveCount} (应为 ${Math.pow(2, n) - 1})`);
        console.log();
    }
}

// 运行主函数
main();
