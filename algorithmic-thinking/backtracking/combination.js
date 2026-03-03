/*
使用回溯生成组合 (JavaScript Implementation)

算法说明:
- 生成从1到n中选取k个元素的所有组合 (C(n,k))
- 使用回溯系统地探索所有选择
- At each step, only consider elements >= current start position
- This prevents duplicate combinations
- When we've selected k elements, add to result

时间复杂度：O(C(n,k) * k)，其中C(n,k)是组合数
空间复杂度：O(k)，用于递归深度和当前组合

示例:
    combine(4, 2) 返回 [
        [1,2], [1,3], [1,4], [2,3], [2,4], [3,4]
    ]
*/

/*
*
 * 生成从1到n中选取k个元素的所有组合.
 *
 * @param {number} n - 元素的总数（1到n）
 * @param {number} k - 每个组合的大小
 * @returns {number[][]} - List of all combinations
*/
function combine(n, k) {
    const result = [];

    /*
*
     * 递归地构建组合.
     *
     * @param {number} start - Starting number to consider
     * @param {number[]} current - 当前要构建的组合
*/
    function backtrack(start, current) {
        // 基本情况：组合已完成
        if (current.length === k) {
            result.push([...current]);
            return;
        }

        // 尝试从start到n的每个数字
        for (let num = start; num <= n; num++) {
            // 选择：将num添加到当前组合
            current.push(num);

            // 探索：构建组合的其余部分
            // 仅数字 >= num+1 以避免重复
            backtrack(num + 1, current);

            // 取消选择：移除num以进行回溯
            current.pop();
        }
    }

    backtrack(1, []);
    return result;
}

/*
*
 * Optimized combination with early termination.
 * 剪枝不可能产生k个元素的分支.
 *
 * Time Complexity: O(C(n,k) * k)
 * Space Complexity: O(k)
 *
 * @param {number} n - Total number of elements
 * @param {number} k - 每个组合的大小
 * @returns {number[][]} - List of all combinations
*/
function combineOptimized(n, k) {
    const result = [];

    function backtrack(start, current) {
        // 基本情况：组合已完成
        if (current.length === k) {
            result.push([...current]);
            return;
        }

        // 优化：提前终止
        // Remaining slots needed: k - current.length
        // 可用的元素：n - start + 1
        // 如果没有足够的可用元素，则停止
        const remaining = k - current.length;
        const available = n - start + 1;
        if (available < remaining) {
            return;
        }

        // 尝试从start到n的每个数字
        for (let num = start; num <= n; num++) {
            current.push(num);
            backtrack(num + 1, current);
            current.pop();
        }
    }

    backtrack(1, []);
    return result;
}

// 测试用例
console.log("=== Combination Backtracking Test Cases ===\n");

// 测试用例 1: combine(4, 2)
console.log("Test 1: combine(4, 2)");
const result1 = combine(4, 2);
console.log(`Result (count=${result1.length}):`);
result1.forEach(combo => console.log(`  [${combo.join(', ')}]`));
console.log();

// 测试用例 2: combine(3, 1)
console.log("Test 2: combine(3, 1)");
const result2 = combine(3, 1);
console.log(`Result (count=${result2.length}):`);
result2.forEach(combo => console.log(`  [${combo.join(', ')}]`));
console.log();

// 测试用例 3: combine(3, 3)
console.log("Test 3: combine(3, 3)");
const result3 = combine(3, 3);
console.log(`Result (count=${result3.length}):`);
result3.forEach(combo => console.log(`  [${combo.join(', ')}]`));
console.log();

// 测试用例 4: combine(5, 3)
console.log("Test 4: combine(5, 3)");
const result4 = combine(5, 3);
console.log(`Result (count=${result4.length}):`);
result4.forEach(combo => console.log(`  [${combo.join(', ')}]`));
console.log();

// 测试用例 5: combineOptimized(6, 2)
console.log("Test 5: combineOptimized(6, 2)");
const result5 = combineOptimized(6, 2);
console.log(`Result (count=${result5.length}):`);
result5.forEach(combo => console.log(`  [${combo.join(', ')}]`));
console.log();

// 测试用例 6: combineOptimized(5, 4)
console.log("Test 6: combineOptimized(5, 4)");
const result6 = combineOptimized(5, 4);
console.log(`Result (count=${result6.length}):`);
result6.forEach(combo => console.log(`  [${combo.join(', ')}]`));
