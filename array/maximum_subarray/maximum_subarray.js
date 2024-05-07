/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 求最大连续子数组之和 - 暴力求解法
function maxSubarraySum1(arr) {
    // let maxSum = -Infinity;
    let maxSum

    for (let i = 0; i < arr.length; i++) {
        let currentSum = arr[i];
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }

        console.log(`第${i + 1}位`, '子数组:')
        console.log(arr[i])

        for (let j = i + 1; j < arr.length; j++) {
            currentSum += arr[j];
            if (currentSum > maxSum) {
                maxSum = currentSum;
            }

            let subarray = arr.slice(i, j + 1).join(" + ");
            console.log(`${subarray} = ${currentSum}`);
        }
    }

    console.log('maxSubarraySum1->maxSum:', maxSum);
    return maxSum;
}

// 求最大连续子数组之和 - 动态规划算法
function maxSubarraySum2(arr) {
    if (arr.length === 0) {
        return 0;
    }

    let dp = Array(arr.length).fill(0);
    dp[0] = arr[0];

    for (let i = 1; i < arr.length; i++) {
        dp[i] = Math.max(dp[i - 1] + arr[i], arr[i]);
    }

    const maxSum = Math.max(...dp);

    console.log('maxSubarraySum2->maxSum:', maxSum);
    return maxSum;
}

// 求最大连续子数组之和 - Kadane算法
function maxSubarraySum3(arr) {
    if (arr.length === 0) {
        return 0; // 处理空数组
    }

    let maxSum = arr[0];
    let currentSum = arr[0];

    for (let i = 1; i < arr.length; i++) {
        currentSum = Math.max(arr[i], currentSum + arr[i]);
        maxSum = Math.max(maxSum, currentSum);

        console.log(`current_sum: ${currentSum}, max_sum: ${maxSum}`);
    }

    console.log('maxSubarraySum3->maxSum:', maxSum);
    return maxSum;
}


// 计算分割点最大子数组和
function maxCrossingSum(arr, left, mid, right) {
    let leftSum = -Infinity;
    let tempSum = 0;

    for (let i = mid; i >= left; i--) {
        tempSum += arr[i];
        if (tempSum > leftSum) {
            leftSum = tempSum;
        }
    }

    let rightSum = -Infinity;
    tempSum = 0;

    for (let i = mid + 1; i <= right; i++) {
        tempSum += arr[i];
        if (tempSum > rightSum) {
            rightSum = tempSum;
        }
    }

    return leftSum + rightSum;
}

// 求最大连续子数组之和 - 分治法
function maxSubarraySum(arr, left, right) {
    if (left === right) {
        return arr[left];
    }

    const mid = Math.floor((left + right) / 2);

    const leftMax = maxSubarraySum(arr, left, mid);
    const rightMax = maxSubarraySum(arr, mid + 1, right);
    const crossMax = maxCrossingSum(arr, left, mid, right);

    return Math.max(leftMax, rightMax, crossMax);
}

function maxSubarraySum4(arr) {
    if (arr.length === 0) {
        return 0;
    }

    const maxSum = maxSubarraySum(arr, 0, arr.length - 1);
    console.log('maxSubarraySum4->maxSum:', maxSum);
    return maxSum;
}

// 执行测试用例，打印是否正确
(function () {
    console.time("time");
    const arr = [-11, 10, -3, 1, -6, 13, -4] // 最大为15
    maxSubarraySum1(arr)
    maxSubarraySum2(arr)
    maxSubarraySum3(arr)
    maxSubarraySum4(arr)
    console.timeEnd("time");
})();

/**
jarry@jarrys-MacBook-Pro array % node maximum_subarray.js
第1位组合:
-11 + 10 = -1
-11 + 10 + -3 = -4
-11 + 10 + -3 + 1 = -3
-11 + 10 + -3 + 1 + -6 = -9
-11 + 10 + -3 + 1 + -6 + 13 = 4
-11 + 10 + -3 + 1 + -6 + 13 + -4 = 0
第2位组合:
10 + -3 = 7
10 + -3 + 1 = 8
10 + -3 + 1 + -6 = 2
10 + -3 + 1 + -6 + 13 = 15
10 + -3 + 1 + -6 + 13 + -4 = 11
第3位组合:
-3 + 1 = -2
-3 + 1 + -6 = -8
-3 + 1 + -6 + 13 = 5
-3 + 1 + -6 + 13 + -4 = 1
第4位组合:
1 + -6 = -5
1 + -6 + 13 = 8
1 + -6 + 13 + -4 = 4
第5位组合:
-6 + 13 = 7
-6 + 13 + -4 = 3
第6位组合:
13 + -4 = 9
第7位组合:
maxSubarraySum1->maxSum: 15
maxSubarraySum2->maxSum: 15
current_sum: 10, max_sum: 10
current_sum: 7, max_sum: 10
current_sum: 8, max_sum: 10
current_sum: 2, max_sum: 10
current_sum: 15, max_sum: 15
current_sum: 11, max_sum: 15
maxSubarraySum3->maxSum: 15
maxSubarraySum4->maxSum: 15
time: 7.53ms
 */