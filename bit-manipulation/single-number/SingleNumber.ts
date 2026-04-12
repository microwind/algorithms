/*
*
 * 单数问题 - 使用XOR技巧找到单个数字
 *
 * 问题：给定一个整数数组，其中除了一个元素出现一次外，
 * 其他元素都出现两次。找到只出现一次的那个元素。
 *
 * 核心思想：
 * - XOR 的性质：a ^ a = 0, a ^ 0 = a
 * - 对所有元素进行XOR操作，两个相同的数会相消，留下单个数字
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
*/

/*
*
 * 使用XOR技巧找到单个数字
 *
 * 原理：
 * - 0 ^ x = x
 * - x ^ x = 0
 * - XOR满足交换律和结合律
 * - 对所有数字XOR，重复数字相消，留下单个数字
 *
 * @param nums 输入数组
 * @return 单个数字
*/
function singleNumberXor(nums: number[]): number {
    let result = 0;
    for (const num of nums) {
        result ^= num;
    }
    return result;
}

/*
*
 * 使用排序方法（备选方案）
 *
 * @param nums 输入数组
 * @return 单个数字
*/
function singleNumberSort(nums: number[]): number {
    const sorted = [...nums].sort((a, b) => a - b);

    // 查找单个数字
    for (let i = 0; i < sorted.length - 1; i += 2) {
        if (sorted[i] !== sorted[i + 1]) {
            return sorted[i];
        }
    }

    return sorted[sorted.length - 1];
}

/*
*
 * 使用哈希表统计频数（备选方案）
 *
 * @param nums 输入数组
 * @return 单个数字
*/
function singleNumberHash(nums: number[]): number {
    const countMap = new Map<number, number>();

    // 统计频数
    for (const num of nums) {
        countMap.set(num, (countMap.get(num) || 0) + 1);
    }

    // 找到频数为1的数字
    for (const [num, count] of countMap) {
        if (count === 1) {
            return num;
        }
    }

    return -1;  // 未找到
}

/*
*
 * 打印数组
*/
function printArray(arr: number[]): void {
    console.log(`[${arr.join(', ')}]`);
}

/*
*
 * 测试函数
*/
function main(): void {
    console.log("=== 单数问题 ===\n");

    // 测试用例1：基本用例
    console.log("1. 基本用例:");
    const nums1 = [2, 2, 1];
    console.log("  数组: ");
    printArray(nums1);
    console.log(`  单数: ${singleNumberXor(nums1)}\n`);

    // 测试用例2：较大数组
    console.log("2. 较大数组:");
    const nums2 = [4, 1, 2, 1, 2];
    console.log("  数组: ");
    printArray(nums2);
    console.log(`  单数: ${singleNumberXor(nums2)}\n`);

    // 测试用例3：负数
    console.log("3. 包含负数:");
    const nums3 = [-1, -1, 5, 5, 3];
    console.log("  数组: ");
    printArray(nums3);
    console.log(`  单数: ${singleNumberXor(nums3)}\n`);

    // 测试用例4：单个元素
    console.log("4. 单个元素:");
    const nums4 = [42];
    console.log("  数组: ");
    printArray(nums4);
    console.log(`  单数: ${singleNumberXor(nums4)}\n`);

    // 测试用例5：较大数值
    console.log("5. 较大数值:");
    const nums5 = [7, 7, 8, 8, 9];
    console.log("  数组: ");
    printArray(nums5);
    console.log(`  单数: ${singleNumberXor(nums5)}\n`);

    // 性能对比
    console.log("6. 不同方法的结果比较:");
    const nums6 = [100, 100, 200, 200, 300];
    console.log("  数组: ");
    printArray(nums6);
    console.log();
    console.log(`  XOR方法: ${singleNumberXor(nums6)}`);
    console.log(`  排序方法: ${singleNumberSort(nums6)}`);
    console.log(`  哈希方法: ${singleNumberHash(nums6)}`);
}

// 运行测试
main();
