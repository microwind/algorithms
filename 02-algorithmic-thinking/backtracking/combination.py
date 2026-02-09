"""
Combination Generator using Backtracking

Algorithm Explanation:
- Generate all combinations of k elements from n elements (C(n,k))
- Use backtracking to systematically explore all choices
- At each step, choose to include or exclude an element
- Only explore elements >= current position to avoid duplicates
- Backtrack when we've selected k elements or exhausted options

Time Complexity: O(C(n,k) * k) where C(n,k) is the number of combinations
Space Complexity: O(k) for recursion depth and current combination

Example:
    combine(4, 2) returns [
        [1, 2], [1, 3], [1, 4],
        [2, 3], [2, 4], [3, 4]
    ]
"""

def combine(n, k):
    """
    Generate all combinations of k elements from 1 to n.

    Args:
        n: Total number of elements (1 to n)
        k: Size of each combination

    Returns:
        List of lists, each containing a combination
    """
    result = []

    def backtrack(start, current_combination):
        """
        Recursively build combinations.

        Args:
            start: Starting number to consider (to avoid duplicates)
            current_combination: Current combination being built
        """
        # Base case: combination is complete
        if len(current_combination) == k:
            result.append(current_combination[:])
            return

        # Try each number from start to n
        for num in range(start, n + 1):
            # Choose: add num to current combination
            current_combination.append(num)

            # Explore: build rest of combination
            # Only numbers >= num+1 to avoid duplicates
            backtrack(num + 1, current_combination)

            # Unchoose: remove num for backtracking
            current_combination.pop()

    backtrack(1, [])
    return result


def combine_optimized(n, k):
    """
    Optimized combination using early termination.
    Prunes branches that can't possibly yield k elements.

    Time Complexity: O(C(n,k) * k)
    Space Complexity: O(k)
    """
    result = []

    def backtrack(start, current_combination):
        # Base case: combination is complete
        if len(current_combination) == k:
            result.append(current_combination[:])
            return

        # Optimization: early termination
        # Remaining slots needed: k - len(current_combination)
        # Elements available: n - start + 1
        # If not enough elements available, stop
        remaining = k - len(current_combination)
        available = n - start + 1
        if available < remaining:
            return

        # Try each number from start to n
        for num in range(start, n + 1):
            current_combination.append(num)
            backtrack(num + 1, current_combination)
            current_combination.pop()

    backtrack(1, [])
    return result


# Test Cases
if __name__ == "__main__":
    print("=== Combination Backtracking Test Cases ===\n")

    # Test Case 1: combine(4, 2)
    print("Test 1: combine(4, 2)")
    result1 = combine(4, 2)
    print(f"Result (count={len(result1)}):")
    for combo in result1:
        print(f"  {combo}")
    print()

    # Test Case 2: combine(3, 1)
    print("Test 2: combine(3, 1)")
    result2 = combine(3, 1)
    print(f"Result (count={len(result2)}):")
    for combo in result2:
        print(f"  {combo}")
    print()

    # Test Case 3: combine(3, 3)
    print("Test 3: combine(3, 3)")
    result3 = combine(3, 3)
    print(f"Result (count={len(result3)}):")
    for combo in result3:
        print(f"  {combo}")
    print()

    # Test Case 4: combine(5, 3)
    print("Test 4: combine(5, 3)")
    result4 = combine(5, 3)
    print(f"Result (count={len(result4)}):")
    for combo in result4:
        print(f"  {combo}")
    print()

    # Test Case 5: combine(6, 2) using optimized
    print("Test 5: combine_optimized(6, 2)")
    result5 = combine_optimized(6, 2)
    print(f"Result (count={len(result5)}):")
    for combo in result5:
        print(f"  {combo}")
    print()

    # Test Case 6: combine_optimized(5, 4)
    print("Test 6: combine_optimized(5, 4)")
    result6 = combine_optimized(5, 4)
    print(f"Result (count={len(result6)}):")
    for combo in result6:
        print(f"  {combo}")
