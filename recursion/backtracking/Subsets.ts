/**
 * 回溯算法 - 子集生成 (Subsets)
 * 使用递归生成数组的所有子集
 */

/**
 * 生成数组的所有子集
 * @param nums 输入数组
 * @returns 所有子集的数组
 */
function subsets(nums: number[]): number[][] {
    const result: number[][] = [];
    
    /**
     * 回溯生成子集
     * @param start 开始位置
     * @param current 当前子集
     */
    function backtrack(start: number, current: number[]): void {
        // 每次递归都将当前子集加入结果
        result.push([...current]);
        
        // 从start开始尝试每个元素
        for (let i = start; i < nums.length; i++) {
            // 选择元素
            current.push(nums[i]);
            
            // 递归：继续处理后面的元素
            backtrack(i + 1, current);
            
            // 回溯：撤销选择
            current.pop();
        }
    }
    
    backtrack(0, []);
    return result;
}

// 示例
const inputNums: number[] = [1, 2, 3];
const subsetsResult: number[][] = subsets(inputNums);

console.log(`数组 [${inputNums.join(', ')}] 的所有子集:`);
console.log(`共 ${subsetsResult.length} 个子集\n`);

subsetsResult.forEach((subset: number[], index: number) => {
    console.log(`  ${index + 1}. [${subset.join(', ')}]`);
});

console.log('\n递归过程可视化:');
console.log('        []');
console.log('       / | \\');
console.log('     [1] [2] [3]');
console.log('    /  \\      |');
console.log('  [1,2] [1,3] [2,3]');
console.log('   /');
console.log('[1,2,3]');
