/*
使用回溯生成排列 (JavaScript Implementation)

算法说明:
- Generate all permutations of an array using backtracking
- At each step, choose an unused element to add to the current permutation
- When we've used all elements, we have a complete permutation
- Backtrack by removing the last element and trying the next option

Time Complexity: O(n! * n) - n! permutations, each taking O(n) to copy
Space Complexity: O(n) - recursion depth (not counting output)

示例:
    permute([1, 2, 3]) returns [
        [1, 2, 3], [1, 3, 2], [2, 1, 3],
        [2, 3, 1], [3, 1, 2], [3, 2, 1]
    ]
*/

/*
*
 * Generate all permutations of an array using backtracking.
 *
 * @param {number[]} nums - Array of elements to permute
 * @returns {number[][]} - List of all permutations
*/
function permute(nums) {
    const result = [];

    /*
*
     * Recursively build permutations.
     *
     * @param {number[]} current - Current partial permutation
     * @param {number[]} remaining - Unused elements
*/
    function backtrack(current, remaining) {
        // Base case: all elements used, add to result
        if (remaining.length === 0) {
            result.push([...current]);
            return;
        }

        // Try each remaining element as the next element
        for (let i = 0; i < remaining.length; i++) {
            // Choose: add remaining[i] to current permutation
            current.push(remaining[i]);

            // Explore: recursively build rest of permutation
            const newRemaining = [
                ...remaining.slice(0, i),
                ...remaining.slice(i + 1)
            ];
            backtrack(current, newRemaining);

            // Unchoose: remove the element for backtracking
            current.pop();
        }
    }

    backtrack([], nums);
    return result;
}

/*
*
 * Optimized permutation using in-place swapping.
 * More space-efficient by modifying the input array.
 *
 * Time Complexity: O(n! * n)
 * Space Complexity: O(n)
 *
 * @param {number[]} nums - Array of elements to permute
 * @returns {number[][]} - List of all permutations
*/
function permuteOptimized(nums) {
    const result = [];

    /*
*
     * Swap elements in-place.
*/
    function swap(arr, i, j) {
        [arr[i], arr[j]] = [arr[j], arr[i]];
    }

    /*
*
     * Swap elements in-place instead of creating new arrays.
     *
     * @param {number} index - Current position to permute from
*/
    function backtrack(index) {
        // Base case: reached end of array
        if (index === nums.length) {
            result.push([...nums]);
            return;
        }

        // Try each element from index onwards as the next element
        for (let i = index; i < nums.length; i++) {
            // Choose: swap elements
            swap(nums, index, i);

            // Explore: permute the rest
            backtrack(index + 1);

            // Unchoose: swap back
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
console.log("Last 3 permutations:");
for (let i = result4.length - 3; i < result4.length; i++) {
    console.log(`  [${result4[i].join(', ')}]`);
}
console.log();

// 测试用例 5: [10, 20, 30]
console.log("Test 5: permuteOptimized([10, 20, 30])");
const result5 = permuteOptimized([10, 20, 30]);
console.log(`Result (count=${result5.length}):`);
result5.forEach(perm => console.log(`  [${perm.join(', ')}]`));
