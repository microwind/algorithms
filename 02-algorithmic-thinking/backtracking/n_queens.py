"""
N-Queens Problem using Backtracking

Algorithm Explanation:
- Place n queens on an n×n chessboard
- No two queens can attack each other (same row, column, or diagonal)
- Use backtracking to explore all possible placements
- For each row, try placing a queen in each column
- Check if placement is safe (not attacked by previously placed queens)
- If safe, place queen and move to next row
- If we place all n queens, we found a solution
- Backtrack and try next column if no solution found

Attack detection:
- Same column: Check column array
- Diagonal (top-left to bottom-right): Check if row - col is same
- Diagonal (top-right to bottom-left): Check if row + col is same

Time Complexity: O(n!) - exponential, many branches pruned
Space Complexity: O(n) - recursion depth + column/diagonal tracking

Example:
    solveNQueens(4) returns 2 solutions (there are 2 ways to place 4 queens)
"""

def solve_n_queens(n):
    """
    Solve the N-Queens problem using backtracking.

    Args:
        n: Size of the chessboard (n queens on n×n board)

    Returns:
        List of solutions, each solution is a list of board configurations
        Each board is represented as a list of strings with 'Q' and '.'
    """
    result = []
    board = [['.'] * n for _ in range(n)]
    cols = set()  # Track columns with queens
    diag1 = set()  # Track diagonals (top-left to bottom-right)
    diag2 = set()  # Track diagonals (top-right to bottom-left)

    def backtrack(row):
        """
        Recursively place queens row by row.

        Args:
            row: Current row to place a queen in
        """
        # Base case: all queens placed
        if row == n:
            # Convert board to string format
            result.append([''.join(row) for row in board])
            return

        # Try placing a queen in each column of this row
        for col in range(n):
            # Check if this column, and both diagonals are safe
            diag1_id = row - col  # Unique for each diagonal
            diag2_id = row + col  # Unique for each diagonal

            if col in cols or diag1_id in diag1 or diag2_id in diag2:
                # Column or diagonal already has a queen, skip
                continue

            # Place queen
            board[row][col] = 'Q'
            cols.add(col)
            diag1.add(diag1_id)
            diag2.add(diag2_id)

            # Explore: try to place queens in remaining rows
            backtrack(row + 1)

            # Backtrack: remove queen
            board[row][col] = '.'
            cols.remove(col)
            diag1.remove(diag1_id)
            diag2.remove(diag2_id)

    backtrack(0)
    return result


def count_n_queens(n):
    """
    Count the number of solutions to the N-Queens problem.
    More efficient than storing all solutions.

    Time Complexity: O(n!)
    Space Complexity: O(n)
    """
    count = 0
    cols = set()
    diag1 = set()
    diag2 = set()

    def backtrack(row):
        nonlocal count

        if row == n:
            count += 1
            return

        for col in range(n):
            diag1_id = row - col
            diag2_id = row + col

            if col in cols or diag1_id in diag1 or diag2_id in diag2:
                continue

            cols.add(col)
            diag1.add(diag1_id)
            diag2.add(diag2_id)

            backtrack(row + 1)

            cols.remove(col)
            diag1.remove(diag1_id)
            diag2.remove(diag2_id)

    backtrack(0)
    return count


# Test Cases
if __name__ == "__main__":
    print("=== N-Queens Problem using Backtracking ===\n")

    # Test Case 1: 4-Queens (classic problem with 2 solutions)
    print("Test 1: solveNQueens(4)")
    result1 = solve_n_queens(4)
    print(f"Found {len(result1)} solutions:\n")
    for idx, solution in enumerate(result1, 1):
        print(f"Solution {idx}:")
        for row in solution:
            print(f"  {row}")
        print()

    # Test Case 2: 1-Queen (trivial case)
    print("Test 2: solveNQueens(1)")
    result2 = solve_n_queens(1)
    print(f"Found {len(result2)} solution(s):\n")
    for idx, solution in enumerate(result2, 1):
        print(f"Solution {idx}:")
        for row in solution:
            print(f"  {row}")
        print()

    # Test Case 3: 8-Queens (classic problem with 92 solutions)
    print("Test 3: countNQueens(8)")
    count3 = count_n_queens(8)
    print(f"Found {count3} solutions for 8-Queens\n")

    # Test Case 4: Various sizes
    print("Test 4: Solution counts for various N:")
    for n in range(1, 9):
        count = count_n_queens(n)
        print(f"  N={n}: {count} solutions")
    print()

    # Test Case 5: 5-Queens
    print("Test 5: solveNQueens(5)")
    result5 = solve_n_queens(5)
    print(f"Found {len(result5)} solutions for 5-Queens")
    print("First solution:")
    for row in result5[0]:
        print(f"  {row}")
