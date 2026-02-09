/*
N-Queens Problem using Backtracking (JavaScript Implementation)

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
- Same column: Check column set
- Diagonal (top-left to bottom-right): Check if row - col is same
- Diagonal (top-right to bottom-left): Check if row + col is same

Time Complexity: O(n!)
Space Complexity: O(n)

Example:
    solveNQueens(4) returns 2 solutions
*/

/**
 * Solve the N-Queens problem using backtracking.
 *
 * @param {number} n - Size of the chessboard (n queens on n×n board)
 * @returns {string[][]} - List of solutions, each solution is a list of board strings
 */
function solveNQueens(n) {
    const result = [];
    const colPlacement = new Array(n);
    const cols = new Set();
    const diag1 = new Set();  // row - col
    const diag2 = new Set();  // row + col

    backtrack(result, n, 0, colPlacement, cols, diag1, diag2);
    return result;
}

/**
 * Recursively place queens row by row.
 *
 * @param {string[][]} result - List to store all solutions
 * @param {number} n - Size of board
 * @param {number} row - Current row to place a queen in
 * @param {number[]} colPlacement - Array tracking queen column positions
 * @param {Set} cols - Set of columns with queens
 * @param {Set} diag1 - Set of diagonals (top-left to bottom-right)
 * @param {Set} diag2 - Set of diagonals (top-right to bottom-left)
 */
function backtrack(result, n, row, colPlacement, cols, diag1, diag2) {
    // Base case: all queens placed
    if (row === n) {
        result.push(buildBoard(n, colPlacement));
        return;
    }

    // Try placing a queen in each column of this row
    for (let col = 0; col < n; col++) {
        const diag1Id = row - col;
        const diag2Id = row + col;

        // Check if column or diagonals have a queen
        if (cols.has(col) || diag1.has(diag1Id) || diag2.has(diag2Id)) {
            continue;
        }

        // Place queen
        colPlacement[row] = col;
        cols.add(col);
        diag1.add(diag1Id);
        diag2.add(diag2Id);

        // Explore: try to place queens in remaining rows
        backtrack(result, n, row + 1, colPlacement, cols, diag1, diag2);

        // Backtrack: remove queen
        cols.delete(col);
        diag1.delete(diag1Id);
        diag2.delete(diag2Id);
    }
}

/**
 * Build the board representation from column placements.
 *
 * @param {number} n - Size of board
 * @param {number[]} colPlacement - Column placement for each row
 * @returns {string[]} - Board representation
 */
function buildBoard(n, colPlacement) {
    const board = [];
    for (let row = 0; row < n; row++) {
        let line = '';
        for (let col = 0; col < n; col++) {
            line += col === colPlacement[row] ? 'Q' : '.';
        }
        board.push(line);
    }
    return board;
}

/**
 * Count the number of solutions to the N-Queens problem.
 * More efficient than storing all solutions.
 *
 * @param {number} n - Size of board
 * @returns {number} - Number of solutions
 */
function countNQueens(n) {
    let count = 0;
    const cols = new Set();
    const diag1 = new Set();
    const diag2 = new Set();

    function countBacktrack(row) {
        if (row === n) {
            count++;
            return;
        }

        for (let col = 0; col < n; col++) {
            const diag1Id = row - col;
            const diag2Id = row + col;

            if (cols.has(col) || diag1.has(diag1Id) || diag2.has(diag2Id)) {
                continue;
            }

            cols.add(col);
            diag1.add(diag1Id);
            diag2.add(diag2Id);

            countBacktrack(row + 1);

            cols.delete(col);
            diag1.delete(diag1Id);
            diag2.delete(diag2Id);
        }
    }

    countBacktrack(0);
    return count;
}

// Test Cases
console.log("=== N-Queens Problem using Backtracking ===\n");

// Test Case 1: 4-Queens
console.log("Test 1: solveNQueens(4)");
const result1 = solveNQueens(4);
console.log(`Found ${result1.length} solutions:\n`);
result1.forEach((solution, idx) => {
    console.log(`Solution ${idx + 1}:`);
    solution.forEach(row => console.log(`  ${row}`));
    console.log();
});

// Test Case 2: 1-Queen
console.log("Test 2: solveNQueens(1)");
const result2 = solveNQueens(1);
console.log(`Found ${result2.length} solution(s):\n`);
result2.forEach((solution, idx) => {
    console.log(`Solution ${idx + 1}:`);
    solution.forEach(row => console.log(`  ${row}`));
    console.log();
});

// Test Case 3: Solution counts for various sizes
console.log("Test 3: Solution counts for various N:");
for (let n = 1; n <= 8; n++) {
    const count = countNQueens(n);
    console.log(`  N=${n}: ${count} solutions`);
}
console.log();

// Test Case 4: 5-Queens
console.log("Test 4: solveNQueens(5)");
const result4 = solveNQueens(5);
console.log(`Found ${result4.length} solutions for 5-Queens`);
console.log("First solution:");
result4[0].forEach(row => console.log(`  ${row}`));
