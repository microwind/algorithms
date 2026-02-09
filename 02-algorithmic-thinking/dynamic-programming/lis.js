/**
 * 最长递增子序列 (LIS) - 动态规划应用
 *
 * 问题描述：
 * 给定一个无序整数数组，找出其中最长递增子序列的长度
 *
 * 动态规划方程：
 * dp[i] = 1 + max(dp[j]) for all j < i and arr[j] < arr[i]
 *
 * 时间复杂度: O(n²) 基础DP
 * 空间复杂度: O(n)
 */

/**
 * 最长递增子序列 - 基础DP方案
 */
function longestIncreasingSubsequence(arr) {
    if (arr.length === 0) return 0;

    const n = arr.length;

    // dp[i] 表示以 arr[i] 结尾的最长递增子序列长度
    const dp = Array(n).fill(1);

    // 构建 DP 表
    for (let i = 1; i < n; i++) {
        for (let j = 0; j < i; j++) {
            // 如果 arr[j] < arr[i]，可以扩展以 arr[j] 结尾的 LIS
            if (arr[j] < arr[i]) {
                dp[i] = Math.max(dp[i], dp[j] + 1);
            }
        }
    }

    // 找到最大值
    return Math.max(...dp);
}

/**
 * 最长递增子序列 - 优化方案 (O(n log n))
 * 使用二分查找和 tails 数组
 */
function longestIncreasingSubsequenceOptimized(arr) {
    if (arr.length === 0) return 0;

    // tails[i] 是长度为 i+1 的递增子序列的最小末尾元素
    const tails = [];

    for (const num of arr) {
        // 使用二分查找找到应该替换的位置
        let left = 0, right = tails.length;
        while (left < right) {
            const mid = Math.floor((left + right) / 2);
            if (tails[mid] < num) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        if (left === tails.length) {
            // 找到了更长的递增子序列
            tails.push(num);
        } else {
            // 替换较大的元素，保持 tails 的最小性
            tails[left] = num;
        }
    }

    return tails.length;
}

/**
 * 最长递增子序列 - 返回子序列本身
 */
function longestIncreasingSubsequenceWithSequence(arr) {
    if (arr.length === 0) return [0, []];

    const n = arr.length;

    // dp[i] 表示以 arr[i] 结尾的最长递增子序列长度
    const dp = Array(n).fill(1);
    // parent[i] 表示以 arr[i] 结尾的 LIS 中，前一个元素的索引
    const parent = Array(n).fill(-1);

    // 构建 DP 表
    for (let i = 1; i < n; i++) {
        for (let j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }

    // 找到最长序列的结尾位置
    let maxLength = 0;
    let maxIndex = 0;
    for (let i = 0; i < n; i++) {
        if (dp[i] > maxLength) {
            maxLength = dp[i];
            maxIndex = i;
        }
    }

    // 反向追踪构建最长子序列
    const lis = [];
    let idx = maxIndex;
    while (idx !== -1) {
        lis.unshift(arr[idx]);
        idx = parent[idx];
    }

    return [maxLength, lis];
}

// 测试函数
console.log("=== 最长递增子序列 ===\n");

// 测试用例1：基本数组
console.log("1. 基本数组");
const arr1 = [10, 9, 2, 5, 3, 7, 101, 18];
console.log("数组:", arr1);
console.log("LIS 长度（DP）:", longestIncreasingSubsequence(arr1));
console.log("LIS 长度（优化）:", longestIncreasingSubsequenceOptimized(arr1));
console.log();

// 测试用例2：已排序数组
console.log("2. 已排序数组");
const arr2 = [1, 3, 6, 7, 9, 4, 10, 5, 8];
console.log("数组:", arr2);
const [length, lis] = longestIncreasingSubsequenceWithSequence(arr2);
console.log("LIS 长度:", length);
console.log("一个 LIS:", lis);
console.log();

// 测试用例3：包含重复元素
console.log("3. 包含重复元素");
const arr3 = [1, 3, 3, 4, 5];
console.log("数组:", arr3);
console.log("LIS 长度:", longestIncreasingSubsequence(arr3));
console.log();

// 测试用例4：单调递减
console.log("4. 单调递减");
const arr4 = [5, 4, 3, 2, 1];
console.log("数组:", arr4);
console.log("LIS 长度:", longestIncreasingSubsequence(arr4));
