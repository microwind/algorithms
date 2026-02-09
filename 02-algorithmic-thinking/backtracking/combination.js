/*
Combination Generator using Backtracking (JavaScript Implementation)

Algorithm Explanation:
- Generate all combinations of k elements from 1 to n (C(n,k))
- Use backtracking to systematically explore all choices
- At each step, only consider elements >= current start position
- This prevents duplicate combinations
- When we've selected k elements, add to result

Time Complexity: O(C(n,k) * k) where C(n,k) is the number of combinations
Space Complexity: O(k) for recursion depth and current combination

Example:
    combine(4, 2) returns [
        [1,2], [1,3], [1,4], [2,3], [2,4], [3,4]
    ]
*/

/**
 * Generate all combinations of k elements from 1 to n.
 *
 * @param {number} n - Total number of elements (1 to n)
 * @param {number} k - Size of each combination
 * @returns {number[][]} - List of all combinations
 */
function combine(n, k) {
    const result = [];

    /**
     * Recursively build combinations.
     *
     * @param {number} start - Starting number to consider
     * @param {number[]} current - Current combination being built
     */
    function backtrack(start, current) {
        // Base case: combination is complete
        if (current.length === k) {
            result.push([...current]);
            return;
        }

        // Try each number from start to n
        for (let num = start; num <= n; num++) {
            // Choose: add num to current combination
            current.push(num);

            // Explore: build rest of combination
            // Only numbers >= num+1 to avoid duplicates
            backtrack(num + 1, current);

            // Unchoose: remove num for backtracking
            current.pop();
        }
    }

    backtrack(1, []);
    return result;
}

/**
 * Optimized combination with early termination.
 * Prunes branches that can't possibly yield k elements.
 *
 * Time Complexity: O(C(n,k) * k)
 * Space Complexity: O(k)
 *
 * @param {number} n - Total number of elements
 * @param {number} k - Size of each combination
 * @returns {number[][]} - List of all combinations
 */
function combineOptimized(n, k) {
    const result = [];

    function backtrack(start, current) {
        // Base case: combination is complete
        if (current.length === k) {
            result.push([...current]);
            return;
        }

        // Optimization: early termination
        // Remaining slots needed: k - current.length
        // Elements available: n - start + 1
        // If not enough elements available, stop
        const remaining = k - current.length;
        const available = n - start + 1;
        if (available < remaining) {
            return;
        }

        // Try each number from start to n
        for (let num = start; num <= n; num++) {
            current.push(num);
            backtrack(num + 1, current);
            current.pop();
        }
    }

    backtrack(1, []);
    return result;
}

// Test Cases
console.log("=== Combination Backtracking Test Cases ===\n");

// Test Case 1: combine(4, 2)
console.log("Test 1: combine(4, 2)");
const result1 = combine(4, 2);
console.log(`Result (count=${result1.length}):`);
result1.forEach(combo => console.log(`  [${combo.join(', ')}]`));
console.log();

// Test Case 2: combine(3, 1)
console.log("Test 2: combine(3, 1)");
const result2 = combine(3, 1);
console.log(`Result (count=${result2.length}):`);
result2.forEach(combo => console.log(`  [${combo.join(', ')}]`));
console.log();

// Test Case 3: combine(3, 3)
console.log("Test 3: combine(3, 3)");
const result3 = combine(3, 3);
console.log(`Result (count=${result3.length}):`);
result3.forEach(combo => console.log(`  [${combo.join(', ')}]`));
console.log();

// Test Case 4: combine(5, 3)
console.log("Test 4: combine(5, 3)");
const result4 = combine(5, 3);
console.log(`Result (count=${result4.length}):`);
result4.forEach(combo => console.log(`  [${combo.join(', ')}]`));
console.log();

// Test Case 5: combineOptimized(6, 2)
console.log("Test 5: combineOptimized(6, 2)");
const result5 = combineOptimized(6, 2);
console.log(`Result (count=${result5.length}):`);
result5.forEach(combo => console.log(`  [${combo.join(', ')}]`));
console.log();

// Test Case 6: combineOptimized(5, 4)
console.log("Test 6: combineOptimized(5, 4)");
const result6 = combineOptimized(5, 4);
console.log(`Result (count=${result6.length}):`);
result6.forEach(combo => console.log(`  [${combo.join(', ')}]`));
