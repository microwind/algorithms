/*
使用回溯算法的N皇后问题 (JavaScript Implementation)

算法说明:
- 在n×n棋盘上放置n个皇后
- 任意两个皇后不能相互攻击（不在同一行、列或对角线上）
- 使用回溯探索所有可能的放置方案
- 对于每一行，尝试在每一列放置一个皇后
- 检查放置是否安全（不被之前放置的皇后攻击）
- 如果安全，则放置皇后并移到下一行
- 如果所有n个皇后都被放置，则找到一个解
- 如果没有找到解，回溯并尝试下一列

攻击检测:
- Same column: Check column set
- 对角线（左上到右下）：检查row - col是否相同
- 对角线（右上到左下）：检查row + col是否相同

Time Complexity: O(n!)
Space Complexity: O(n)

示例:
    solveNQueens(4) returns 2 solutions
*/

/*
*
 * 使用回溯算法解决N皇后问题.
 *
 * @param {number} n - 棋盘大小（n个皇后放在n×n棋盘上）
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

/*
*
 * 递归地逐行放置皇后.
 *
 * @param {string[][]} result - List to store all solutions
 * @param {number} n - Size of board
 * @param {number} row - 当前要放置皇后的行
 * @param {number[]} colPlacement - Array tracking queen column positions
 * @param {Set} cols - Set of columns with queens
 * @param {Set} diag1 - Set of diagonals (top-left to bottom-right)
 * @param {Set} diag2 - Set of diagonals (top-right to bottom-left)
*/
function backtrack(result, n, row, colPlacement, cols, diag1, diag2) {
    // 基本情况：所有皇后都已放置
    if (row === n) {
        result.push(buildBoard(n, colPlacement));
        return;
    }

    // 尝试在此行的每一列放置一个皇后
    for (let col = 0; col < n; col++) {
        const diag1Id = row - col;
        const diag2Id = row + col;

        // Check if column or diagonals have a queen
        if (cols.has(col) || diag1.has(diag1Id) || diag2.has(diag2Id)) {
            continue;
        }

        // 放置皇后
        colPlacement[row] = col;
        cols.add(col);
        diag1.add(diag1Id);
        diag2.add(diag2Id);

        // 探索：尝试在剩余行放置皇后
        backtrack(result, n, row + 1, colPlacement, cols, diag1, diag2);

        // 回溯：移除皇后
        cols.delete(col);
        diag1.delete(diag1Id);
        diag2.delete(diag2Id);
    }
}

/*
*
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

/*
*
 * 计算N皇后问题的解的数量.
 * 比存储所有解更高效.
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

// 测试用例
console.log("=== N-Queens Problem using Backtracking ===\n");

// 测试用例 1: 4-Queens
console.log("Test 1: solveNQueens(4)");
const result1 = solveNQueens(4);
console.log(`Found ${result1.length} solutions:\n`);
result1.forEach((solution, idx) => {
    console.log(`Solution ${idx + 1}:`);
    solution.forEach(row => console.log(`  ${row}`));
    console.log();
});

// 测试用例 2: 1-Queen
console.log("Test 2: solveNQueens(1)");
const result2 = solveNQueens(1);
console.log(`Found ${result2.length} solution(s):\n`);
result2.forEach((solution, idx) => {
    console.log(`Solution ${idx + 1}:`);
    solution.forEach(row => console.log(`  ${row}`));
    console.log();
});

// 测试用例 3: Solution counts for various sizes
console.log("Test 3: Solution counts for various N:");
for (let n = 1; n <= 8; n++) {
    const count = countNQueens(n);
    console.log(`  N=${n}: ${count} solutions`);
}
console.log();

// 测试用例 4: 5-Queens
console.log("Test 4: solveNQueens(5)");
const result4 = solveNQueens(5);
console.log(`Found ${result4.length} solutions for 5-Queens`);
console.log("First solution:");
result4[0].forEach(row => console.log(`  ${row}`));
