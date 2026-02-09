"""
Permutation Generator using Backtracking

Algorithm Explanation:
- Generate all permutations of a list using backtracking
- At each step, choose an unused element to add to the current permutation
- When we've used all elements, we have a complete permutation
- Backtrack by removing the last element and trying the next option

Time Complexity: O(n! * n) - n! permutations, each taking O(n) to copy
Space Complexity: O(n) - recursion depth (not counting output)

Example:
    permute([1, 2, 3]) returns [
        [1, 2, 3], [1, 3, 2], [2, 1, 3],
        [2, 3, 1], [3, 1, 2], [3, 2, 1]
    ]
"""

def permute(nums):
    """
    Generate all permutations of nums using backtracking.

    Args:
        nums: List of elements to permute

    Returns:
        List of lists, each containing a permutation
    """
    result = []

    def backtrack(current_permutation, remaining):
        """
        Recursively build permutations.

        Args:
            current_permutation: Current partial permutation being built
            remaining: List of unused elements
        """
        # Base case: all elements used, add to result
        if not remaining:
            result.append(current_permutation[:])
            return

        # Try each remaining element as the next element
        for i in range(len(remaining)):
            # Choose: add remaining[i] to current permutation
            current_permutation.append(remaining[i])

            # Explore: recursively build rest of permutation
            new_remaining = remaining[:i] + remaining[i+1:]
            backtrack(current_permutation, new_remaining)

            # Unchoose: remove the element for backtracking
            current_permutation.pop()

    backtrack([], nums)
    return result


def permute_optimized(nums):
    """
    Optimized permutation using in-place swapping.
    More space-efficient by modifying the input array.

    Time Complexity: O(n! * n)
    Space Complexity: O(n)
    """
    result = []

    def backtrack(index):
        """
        Swap elements in-place instead of creating new lists.

        Args:
            index: Current position to permute from
        """
        # Base case: reached end of array
        if index == len(nums):
            result.append(nums[:])  # Add copy of current permutation
            return

        # Try each element from index onwards as the next element
        for i in range(index, len(nums)):
            # Choose: swap elements
            nums[index], nums[i] = nums[i], nums[index]

            # Explore: permute the rest
            backtrack(index + 1)

            # Unchoose: swap back
            nums[index], nums[i] = nums[i], nums[index]

    backtrack(0)
    return result


# Test Cases
if __name__ == "__main__":
    print("=== Permutation Backtracking Test Cases ===\n")

    # Test Case 1: Small list
    print("Test 1: permute([1, 2, 3])")
    result1 = permute([1, 2, 3])
    print(f"Result (count={len(result1)}):")
    for perm in result1:
        print(f"  {perm}")
    print()

    # Test Case 2: Two elements
    print("Test 2: permute([1, 2])")
    result2 = permute([1, 2])
    print(f"Result (count={len(result2)}):")
    for perm in result2:
        print(f"  {perm}")
    print()

    # Test Case 3: Single element
    print("Test 3: permute([1])")
    result3 = permute([1])
    print(f"Result (count={len(result3)}):")
    for perm in result3:
        print(f"  {perm}")
    print()

    # Test Case 4: Optimized version with 4 elements
    print("Test 4: permute_optimized([1, 2, 3, 4])")
    test_input = [1, 2, 3, 4]
    result4 = permute_optimized(test_input)
    print(f"Result (count={len(result4)}):")
    print(f"First 3 permutations: {result4[:3]}")
    print(f"Last 3 permutations: {result4[-3:]}")
    print()

    # Test Case 5: String characters
    print("Test 5: permute(['A', 'B', 'C'])")
    result5 = permute(['A', 'B', 'C'])
    print(f"Result (count={len(result5)}):")
    for perm in result5:
        print(f"  {''.join(perm)}")
