"""
Activity Selection Problem - Select maximum compatible activities

Algorithm:
- Given activities with start and end times
- Select the maximum number of non-overlapping activities
- Strategy: Sort by end time, then greedily select activities that don't overlap

Time Complexity: O(n log n) - due to sorting
Space Complexity: O(1) - excluding output

Key Insight:
Always picking the activity that ends earliest leaves the most room for
other activities. This greedy choice leads to optimal solution.

Proof: Consider any optimal solution. If it doesn't contain the activity
with the earliest end time, we can replace the first activity with it
without affecting feasibility (since it ends earlier).
"""


def activity_selection(activities):
    """
    Select the maximum number of non-overlapping activities.

    参数:
        activities: List of tuples (start_time, end_time)

    返回:
        List of selected activities as tuples

    示例:
        >>> activities = [(1, 3), (2, 5), (4, 6), (6, 7), (5, 8), (8, 9)]
        >>> result = activity_selection(activities)
        >>> len(result)
        4
    """
    if not activities:
        return []

    # Sort activities by end time (greedy choice)
    # This ensures we select activities that end earliest
    sorted_activities = sorted(activities, key=lambda x: x[1])

    # Always select the first activity (ends earliest)
    selected = [sorted_activities[0]]
    last_end_time = sorted_activities[0][1]

    # Greedily select remaining activities
    for i in range(1, len(sorted_activities)):
        start_time, end_time = sorted_activities[i]
        # If this activity starts after the last selected activity ends,
        # it's compatible and we select it
        if start_time >= last_end_time:
            selected.append(sorted_activities[i])
            last_end_time = end_time

    return selected


def activity_count(activities):
    """
    Return the count of maximum non-overlapping activities.

    参数:
        activities: List of tuples (start_time, end_time)

    返回:
        Integer count of selected activities
    """
    return len(activity_selection(activities))


def compare_with_brute_force(activities):
    """
    Compare greedy solution with brute force for validation.

    For small inputs, we can verify greedy gives optimal solution.
    """
    from itertools import combinations

    if not activities:
        return True

    greedy_count = len(activity_selection(activities))

    # Check all possible subsets
    max_valid = 0
    for r in range(len(activities), 0, -1):
        for subset in combinations(activities, r):
            # Check if subset is valid (no overlaps)
            sorted_subset = sorted(subset, key=lambda x: x[1])
            valid = True
            for j in range(1, len(sorted_subset)):
                if sorted_subset[j][0] < sorted_subset[j-1][1]:
                    valid = False
                    break
            if valid:
                max_valid = max(max_valid, len(subset))
                if max_valid > greedy_count:
                    return False
        if max_valid >= greedy_count:
            break

    return max_valid == greedy_count


if __name__ == "__main__":
    print("=" * 60)
    print("ACTIVITY SELECTION - Greedy Algorithm")
    print("=" * 60)

    # 测试用例 1: Basic example
    print("\n[Test 1] Basic example with overlapping activities")
    activities1 = [(1, 3), (2, 5), (4, 6), (6, 7), (5, 8), (8, 9)]
    result1 = activity_selection(activities1)
    print(f"Input activities: {activities1}")
    print(f"Selected activities: {result1}")
    print(f"Count: {len(result1)}")
    print(f"Optimal: {compare_with_brute_force(activities1)}")

    # 测试用例 2: All compatible
    print("\n[Test 2] All activities compatible (non-overlapping)")
    activities2 = [(1, 2), (2, 3), (3, 4), (4, 5)]
    result2 = activity_selection(activities2)
    print(f"Input activities: {activities2}")
    print(f"Selected activities: {result2}")
    print(f"Count: {len(result2)}")

    # 测试用例 3: All overlapping
    print("\n[Test 3] All activities overlapping")
    activities3 = [(1, 10), (2, 9), (3, 8), (4, 7)]
    result3 = activity_selection(activities3)
    print(f"Input activities: {activities3}")
    print(f"Selected activities: {result3}")
    print(f"Count: {len(result3)}")

    # 测试用例 4: Single activity
    print("\n[Test 4] Single activity")
    activities4 = [(5, 10)]
    result4 = activity_selection(activities4)
    print(f"Input activities: {activities4}")
    print(f"Selected activities: {result4}")
    print(f"Count: {len(result4)}")

    # 测试用例 5: Empty input
    print("\n[Test 5] Empty input")
    activities5 = []
    result5 = activity_selection(activities5)
    print(f"Input activities: {activities5}")
    print(f"Selected activities: {result5}")
    print(f"Count: {len(result5)}")

    # 测试用例 6: Complex scheduling
    print("\n[Test 6] Complex scheduling scenario")
    activities6 = [(0, 6), (1, 4), (3, 5), (5, 7), (8, 9), (5, 9)]
    result6 = activity_selection(activities6)
    print(f"Input activities: {activities6}")
    print(f"Selected activities: {result6}")
    print(f"Count: {len(result6)}")
    print(f"Optimal: {compare_with_brute_force(activities6)}")
