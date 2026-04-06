/**
 * 回溯算法 - 全排列 (Permutations)
 * 使用递归生成数组的所有排列
 */

/**
 * 生成数组的所有排列
 * @param nums 输入数组
 * @returns 所有排列的数组
 */
function permutations(nums: number[]): number[][] {
    const result: number[][] = [];
    
    /**
     * 回溯生成排列
     * @param current 当前排列
     * @param remaining 剩余元素
     */
    function backtrack(current: number[], remaining: number[]): void {
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
            const newRemaining: number[] = remaining.filter((_, index) => index !== i);
            backtrack(current, newRemaining);
            
            // 回溯：撤销选择
            current.pop();
        }
    }
    
    backtrack([], nums);
    return result;
}

// 示例
const inputNums: number[] = [1, 2, 3];
const permutationsResult: number[][] = permutations(inputNums);

console.log(`数组 [${inputNums.join(', ')}] 的所有排列:`);

permutationsResult.forEach((perm: number[], index: number) => {
    console.log(`  ${index + 1}. [${perm.join(', ')}]`);
});

console.log(`\n共 ${permutationsResult.length} 种排列`);
