/*
使用回溯生成排列 (JavaScript Implementation)

算法说明:
- 使用回溯生成整数数组的所有排列
- 在每一步，为当前排列中回溯选择一个未使用的元素
- 当整太元素都了了时，我们就有了一个不完整的排列
- 通过移除上一个元素并尝试下一个选项来回溯

时间复杂度：O(n! * n) - n! 个排列，每个需要 O(n) 时间复制
空间复杂度：O(n) - 递归深度（不计算输出）

示例:
    permute([1, 2, 3]) 返回 [
        [1, 2, 3], [1, 3, 2], [2, 1, 3],
        [2, 3, 1], [3, 1, 2], [3, 2, 1]
    ]
*/

/*
 * 使用回溯生成整数数组的所有排列。
 *
 * @param {number[]} nums - 待排列的元素数组
 * @returns {number[][]} - 列表，每个元素是一个排列
*/
function permute(nums) {
    const result = [];

    /*
     * 递归构成排列。
     *
     * @param {number[]} current - 正基成的子排列
     * @param {number[]} remaining - 未使用的元素
    */
    function backtrack(current, remaining) {
        // 基础情况：所有元素都已使用，添加到结果中
        if (remaining.length === 0) {
            result.push([...current]);
            return;
        }

        // 尝试每个剩余元素作为下一个元素
        for (let i = 0; i < remaining.length; i++) {
            // 选择：将 remaining[i] 添加到当前排列
            current.push(remaining[i]);

            // 探索：递归构成排列的余下部分
            const newRemaining = [
                ...remaining.slice(0, i),
                ...remaining.slice(i + 1)
            ];
            backtrack(current, newRemaining);

            // 撤销：移除元素以回溯
            current.pop();
        }
    }

    backtrack([], nums);
    return result;
}

/*
 * 使用原位置交换优化排列。
 * 会修改源数组以节省存储空间。
 *
 * 时间复杂度：O(n! * n)
 * 空间复杂度：O(n)
 *
 * @param {number[]} nums - 整整数组不待排列
 * @returns {number[][]} - 列表，每个元素是一个排列
*/
function permuteOptimized(nums) {
    const result = [];

    /*
     * 原位置交换元素。
    */
    function swap(arr, i, j) {
        [arr[i], arr[j]] = [arr[j], arr[i]];
    }

    /*
     * 原位置交换元素而不是创建新数组。
     *
     * @param {number} index - 开始排列的当前位置
    */
    function backtrack(index) {
        // 基础情况：到达整整数组末尾
        if (index === nums.length) {
            result.push([...nums]);
            return;
        }

        // 尝试从 index 下来的每个元素作为下一个元素
        for (let i = index; i < nums.length; i++) {
            // 选择：交换元素
            swap(nums, index, i);

            // 探索：排列剩余部分
            backtrack(index + 1);

            // 撤销：交换回去
            swap(nums, index, i);
        }
    }

    backtrack(0);
    return result;
}

// 测试用例
console.log("=== Permutation Backtracking Test Cases ===\n");

// 测试用例 1: [1, 2, 3]
console.log("Test 1: permute([1, 2, 3])");
const result1 = permute([1, 2, 3]);
console.log(`Result (count=${result1.length}):`);
result1.forEach(perm => console.log(`  [${perm.join(', ')}]`));
console.log();

// 测试用例 2: [1, 2]
console.log("Test 2: permute([1, 2])");
const result2 = permute([1, 2]);
console.log(`Result (count=${result2.length}):`);
result2.forEach(perm => console.log(`  [${perm.join(', ')}]`));
console.log();

// 测试用例 3: [1]
console.log("Test 3: permute([1])");
const result3 = permute([1]);
console.log(`Result (count=${result3.length}):`);
result3.forEach(perm => console.log(`  [${perm.join(', ')}]`));
console.log();

// 测试用例 4: Optimized version with [1, 2, 3, 4]
console.log("Test 4: permuteOptimized([1, 2, 3, 4])");
const result4 = permuteOptimized([1, 2, 3, 4]);
console.log(`Result (count=${result4.length}):`);
console.log("First 3 permutations:");
for (let i = 0; i < 3; i++) {
    console.log(`  [${result4[i].join(', ')}]`);
}
console.log("后 3 个排列:");
for (let i = result4.length - 3; i < result4.length; i++) {
    console.log(`  [${result4[i].join(', ')}]`);
}
console.log();

// 测试用例 5: [10, 20, 30]
console.log("测试 5: permuteOptimized([10, 20, 30])");
const result5 = permuteOptimized([10, 20, 30]);
console.log(`结果（共 ${result5.length} 个）:`);
result5.forEach(perm => console.log(`  [${perm.join(', ')}]`));
