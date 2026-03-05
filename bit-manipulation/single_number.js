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
 * @param {number[]} nums 输入数组
 * @returns {number} 单个数字
*/
function singleNumberXor(nums) {
    let result = 0;
    for (let num of nums) {
        result ^= num;
    }
    return result;
}

/*
*
 * 使用哈希表统计频数（备选方案）
 *
 * @param {number[]} nums 输入数组
 * @returns {number} 单个数字
*/
function singleNumberHash(nums) {
    const count = {};
    for (let num of nums) {
        count[num] = (count[num] || 0) + 1;
    }

    for (let num in count) {
        if (count[num] === 1) {
            return parseInt(num);
        }
    }

    return -1;
}

/*
*
 * 排序后相邻比较（备选方案）
 *
 * @param {number[]} nums 输入数组
 * @returns {number} 单个数字
*/
function singleNumberSort(nums) {
    nums.sort((a, b) => a - b);

    for (let i = 0; i < nums.length - 1; i += 2) {
        if (nums[i] !== nums[i + 1]) {
            return nums[i];
        }
    }

    return nums[nums.length - 1];
}

// 测试函数
console.log("=== 单数问题 ===\n");

// 测试用例1：基本用例
console.log("1. 基本用例:");
const nums1 = [2, 2, 1];
console.log(`  数组: [${nums1}]`);
console.log(`  单数: ${singleNumberXor(nums1)}\n`);

// 测试用例2：较大数组
console.log("2. 较大数组:");
const nums2 = [4, 1, 2, 1, 2];
console.log(`  数组: [${nums2}]`);
console.log(`  单数: ${singleNumberXor(nums2)}\n`);

// 测试用例3：负数
console.log("3. 包含负数:");
const nums3 = [-1, -1, 5, 5, 3];
console.log(`  数组: [${nums3}]`);
console.log(`  单数: ${singleNumberXor(nums3)}\n`);

// 测试用例4：单个元素
console.log("4. 单个元素:");
const nums4 = [42];
console.log(`  数组: [${nums4}]`);
console.log(`  单数: ${singleNumberXor(nums4)}\n`);

// 性能对比
console.log("5. 不同方法的结果比较:");
const nums5 = [7, 7, 8, 8, 9];
console.log(`  数组: [${nums5}]`);
console.log(`  XOR方法: ${singleNumberXor(nums5)}`);
console.log(`  哈希方法: ${singleNumberHash(nums5)}`);
console.log(`  排序方法: ${singleNumberSort([...nums5])}`);
