/**
 * 回溯算法 - 全排列 (Permutations)
 * 使用递归生成数组的所有排列
 */

/**
 * 生成数组的所有排列
 * @param {number[]} nums 输入数组
 * @returns {number[][]} 所有排列的数组
 */
function permutations(nums) {
    const result = [];
    
    /**
     * 回溯生成排列
     * @param {number[]} current 当前排列
     * @param {number[]} remaining 剩余元素
     */
    function backtrack(current, remaining) {
        // 基础情况：没有剩余元素，找到一个排列
        if (remaining.length === 0) {
            result.push([...current]);
            return;
        }
        
        // 递归情况：尝试每个剩余元素
        for (let i = 0; i < remaining.length; i++) {
            // 选择元素
            current.push(remaining[i]);
            
            // 递归：处理剩余元素（排除已选择的）
            const newRemaining = remaining.filter((_, index) => index !== i);
            backtrack(current, newRemaining);
            
            // 回溯：撤销选择
            current.pop();
        }
    }
    
    backtrack([], nums);
    return result;
}

// 示例
const nums = [1, 2, 3];
const result = permutations(nums);

console.log(`数组 [${nums.join(', ')}] 的所有排列:`);

result.forEach((perm, index) => {
    console.log(`  ${index + 1}. [${perm.join(', ')}]`);
});

console.log(`\n共 ${result.length} 种排列`);
