"""
Jump Game - Can reach the last index with greedy jumps

Algorithm:
- Given an array where each element is the maximum jump length from that position
- Determine if you can reach the last index
- Greedy approach: track the maximum index we can reach so far
- If at any point current index exceeds max reachable, return False

Time Complexity: O(n) - single pass through array
Space Complexity: O(1) - only using a single variable

Key Insight:
At each position i, we can reach up to position i + nums[i].
We maintain the maximum position we can reach (max_reach).
If we encounter a position we can't reach, it's impossible.

Greedy Choice: We don't need to decide which jump to take from each position.
We only need to know if the maximum reachable position allows us to progress.

Example:
- nums = [2, 3, 1, 1, 4]
  Position 0: can reach 0+2=2
  Position 1: can reach 1+3=4 (updates max_reach)
  We can reach position 4 (last index) → True

- nums = [3, 2, 1, 0, 4]
  Position 0: can reach 0+3=3
  Position 1: can reach 1+2=3 (no update)
  Position 2: can reach 2+1=3 (no update)
  Position 3: can reach 3+0=3 (no update)
  We cannot reach position 4 → False
"""

from typing import List


def can_jump(nums: List[int]) -> bool:
    """
    Determine if we can reach the last index of the array.

    Args:
        nums: List where each element is max jump length from that position

    Returns:
        True if we can reach the last index, False otherwise

    Example:
        >>> can_jump([2, 3, 1, 1, 4])
        True
        >>> can_jump([3, 2, 1, 0, 4])
        False
    """
    if not nums or len(nums) <= 1:
        return True

    max_reach = 0

    for i in range(len(nums)):
        # If current position is beyond what we can reach, return False
        if i > max_reach:
            return False

        # Update the maximum position we can reach
        max_reach = max(max_reach, i + nums[i])

        # Early termination: if we can reach the end, return True
        if max_reach >= len(nums) - 1:
            return True

    return max_reach >= len(nums) - 1


def jump_game_steps(nums: List[int]) -> tuple:
    """
    Return whether we can reach the end and the minimum jumps needed.

    Args:
        nums: List where each element is max jump length from that position

    Returns:
        Tuple of (can_reach, min_jumps)
    """
    if not nums or len(nums) <= 1:
        return (True, 0)

    # Check if we can reach the end
    max_reach = 0
    for i in range(len(nums)):
        if i > max_reach:
            return (False, -1)
        max_reach = max(max_reach, i + nums[i])
        if max_reach >= len(nums) - 1:
            break

    can_reach = max_reach >= len(nums) - 1

    if not can_reach:
        return (False, -1)

    # Find minimum jumps needed (greedy)
    jumps = 0
    current_end = 0
    farthest = 0

    for i in range(len(nums) - 1):
        farthest = max(farthest, i + nums[i])

        if i == current_end:
            jumps += 1
            current_end = farthest

    return (True, jumps)


def jump_game_path(nums: List[int]) -> List[int]:
    """
    Return a path (sequence of indices) to reach the last index.

    Args:
        nums: List where each element is max jump length from that position

    Returns:
        List of indices representing a valid path, or empty list if impossible
    """
    if not nums:
        return []

    if len(nums) == 1:
        return [0]

    # First check if we can reach the end
    max_reach = 0
    for i in range(len(nums)):
        if i > max_reach:
            return []
        max_reach = max(max_reach, i + nums[i])
        if max_reach >= len(nums) - 1:
            break

    # Greedy path construction: always jump as far as possible
    path = [0]
    current_pos = 0

    while current_pos < len(nums) - 1:
        max_next_pos = current_pos
        for next_pos in range(current_pos + 1, min(current_pos + nums[current_pos] + 1, len(nums))):
            # Greedy: choose the position that can reach farthest
            if next_pos + nums[next_pos] > max_next_pos + nums[max_next_pos]:
                max_next_pos = next_pos

        if max_next_pos == current_pos:
            # Can't make progress (shouldn't happen if can_jump returned True)
            return []

        path.append(max_next_pos)
        current_pos = max_next_pos

    return path


def analyze_jump_game(nums: List[int]) -> dict:
    """
    Analyze a jump game problem comprehensively.

    Args:
        nums: List where each element is max jump length from that position

    Returns:
        Dictionary with analysis results
    """
    can_reach, min_jumps = jump_game_steps(nums)
    path = jump_game_path(nums) if can_reach else []

    return {
        'can_reach': can_reach,
        'min_jumps': min_jumps,
        'path': path,
        'length': len(path) - 1 if path else -1
    }


if __name__ == "__main__":
    print("=" * 60)
    print("JUMP GAME - Greedy Approach")
    print("=" * 60)

    # Test Case 1: Basic reachable
    print("\n[Test 1] Reachable - should return True")
    nums1 = [2, 3, 1, 1, 4]
    result1 = can_jump(nums1)
    print(f"Input: {nums1}")
    print(f"Can reach end: {result1}")
    analysis1 = analyze_jump_game(nums1)
    print(f"Min jumps: {analysis1['min_jumps']}, Path: {analysis1['path']}")

    # Test Case 2: Not reachable
    print("\n[Test 2] Not reachable - should return False")
    nums2 = [3, 2, 1, 0, 4]
    result2 = can_jump(nums2)
    print(f"Input: {nums2}")
    print(f"Can reach end: {result2}")

    # Test Case 3: Single element
    print("\n[Test 3] Single element")
    nums3 = [0]
    result3 = can_jump(nums3)
    print(f"Input: {nums3}")
    print(f"Can reach end: {result3}")

    # Test Case 4: All zeros except last
    print("\n[Test 4] All zeros except last")
    nums4 = [0, 1]
    result4 = can_jump(nums4)
    print(f"Input: {nums4}")
    print(f"Can reach end: {result4}")

    # Test Case 5: Large jumps
    print("\n[Test 5] Large jumps available")
    nums5 = [10, 0, 0, 0, 0]
    result5 = can_jump(nums5)
    print(f"Input: {nums5}")
    print(f"Can reach end: {result5}")
    analysis5 = analyze_jump_game(nums5)
    print(f"Min jumps: {analysis5['min_jumps']}, Path: {analysis5['path']}")

    # Test Case 6: Minimum jumps needed
    print("\n[Test 6] Requires multiple jumps")
    nums6 = [2, 3, 1, 1, 1]
    result6 = can_jump(nums6)
    print(f"Input: {nums6}")
    print(f"Can reach end: {result6}")
    analysis6 = analyze_jump_game(nums6)
    print(f"Min jumps: {analysis6['min_jumps']}, Path: {analysis6['path']}")

    # Test Case 7: Blocked at last jump point
    print("\n[Test 7] Blocked at second-to-last")
    nums7 = [1, 0, 1, 0]
    result7 = can_jump(nums7)
    print(f"Input: {nums7}")
    print(f"Can reach end: {result7}")

    # Test Case 8: Two element array
    print("\n[Test 8] Two element array")
    nums8 = [2, 3]
    result8 = can_jump(nums8)
    print(f"Input: {nums8}")
    print(f"Can reach end: {result8}")
    analysis8 = analyze_jump_game(nums8)
    print(f"Min jumps: {analysis8['min_jumps']}, Path: {analysis8['path']}")

    # Test Case 9: Large array all reachable
    print("\n[Test 9] Large array with decreasing values")
    nums9 = [5, 4, 3, 2, 1, 0]
    result9 = can_jump(nums9)
    print(f"Input: {nums9}")
    print(f"Can reach end: {result9}")
    analysis9 = analyze_jump_game(nums9)
    print(f"Min jumps: {analysis9['min_jumps']}, Path: {analysis9['path']}")

    # Test Case 10: Complex reachable
    print("\n[Test 10] Complex reachable scenario")
    nums10 = [2, 5, 0, 0]
    result10 = can_jump(nums10)
    print(f"Input: {nums10}")
    print(f"Can reach end: {result10}")
    analysis10 = analyze_jump_game(nums10)
    print(f"Min jumps: {analysis10['min_jumps']}, Path: {analysis10['path']}")
