# Backtracking Algorithms Implementation Summary

Complete implementations of 3 fundamental backtracking algorithms across 6 programming languages.

## Overview

This directory contains production-ready implementations of three classic backtracking algorithms, each implemented in:
- Python
- C
- Java
- Go
- JavaScript
- Rust

### Files Created (18 Total)

```
backtracking/
├── PERMUTATION ALGORITHM (6 files)
│   ├── permutation.py      - Python implementation
│   ├── permutation.c       - C implementation
│   ├── Permutation.java    - Java implementation
│   ├── permutation.go      - Go implementation
│   ├── permutation.js      - JavaScript implementation
│   └── permutation.rs      - Rust implementation
│
├── COMBINATION ALGORITHM (6 files)
│   ├── combination.py      - Python implementation
│   ├── combination.c       - C implementation
│   ├── Combination.java    - Java implementation
│   ├── combination.go      - Go implementation
│   ├── combination.js      - JavaScript implementation
│   └── combination.rs      - Rust implementation
│
└── N-QUEENS ALGORITHM (6 files)
    ├── n_queens.py         - Python implementation
    ├── n_queens.c          - C implementation
    ├── NQueens.java        - Java implementation
    ├── n_queens.go         - Go implementation
    ├── n_queens.js         - JavaScript implementation
    └── n_queens.rs         - Rust implementation
```

---

## Algorithm 1: PERMUTATION

### Description
Generate all permutations of a list/array using backtracking.

### Key Features
- **Approach**: Choose-Explore-Unchoose pattern
- **Two implementations per language**:
  1. **Basic**: Creates new arrays/slices for each level
  2. **Optimized**: In-place swapping for better memory efficiency
- **Time Complexity**: O(n! × n)
- **Space Complexity**: O(n) recursion depth (excluding output)

### Algorithm Steps
1. For each position, try each unused element
2. Recursively permute remaining elements
3. Backtrack by removing the chosen element
4. When all elements are used, save the permutation

### Test Cases Included
- permute([1, 2, 3]) → 6 permutations
- permute([1, 2]) → 2 permutations
- permute([1]) → 1 permutation
- permute([1, 2, 3, 4]) → 24 permutations
- Character permutation examples

### Example Output
```
Test 1: permute([1, 2, 3])
Result (count=6):
  [1, 2, 3]
  [1, 3, 2]
  [2, 1, 3]
  [2, 3, 1]
  [3, 1, 2]
  [3, 2, 1]
```

---

## Algorithm 2: COMBINATION

### Description
Generate all combinations of k elements from n elements using backtracking.

### Key Features
- **Approach**: Choose-Explore-Unchoose with positional constraints
- **Two implementations per language**:
  1. **Basic**: Standard combination generation
  2. **Optimized**: Early termination pruning
- **Time Complexity**: O(C(n,k) × k)
- **Space Complexity**: O(k) recursion depth
- **Formula**: C(n,k) = n! / (k! × (n-k)!)

### Algorithm Steps
1. Start from position 1 to n
2. Only consider elements >= current position (avoids duplicates)
3. When combination size reaches k, save it
4. Backtrack and try next element
5. Early termination: Stop if not enough remaining elements

### Test Cases Included
- combine(4, 2) → 6 combinations
- combine(3, 1) → 3 combinations
- combine(3, 3) → 1 combination
- combine(5, 3) → 10 combinations
- combine(6, 2) → 15 combinations

### Example Output
```
Test 1: combine(4, 2)
Result (count=6):
  [1, 2]
  [1, 3]
  [1, 4]
  [2, 3]
  [2, 4]
  [3, 4]
```

---

## Algorithm 3: N-QUEENS

### Description
Place n queens on an n×n chessboard so no two queens attack each other using backtracking.

### Key Features
- **Approach**: Row-by-row placement with attack detection
- **Two implementations per language**:
  1. **Solve**: Returns all valid solutions
  2. **Count**: Counts solutions without storing them (memory efficient)
- **Time Complexity**: O(n!) with pruning
- **Space Complexity**: O(n) for tracking columns and diagonals

### Attack Detection
Queens attack along three directions:
1. **Same column**: Track in a set
2. **Diagonal (↘)**: Track by (row - col)
3. **Diagonal (↙)**: Track by (row + col)

### Algorithm Steps
1. Place one queen per row (column to be determined)
2. For each row, try each column
3. Check if placement is safe (no conflicts with previous queens)
4. If safe, place queen and move to next row
5. If we place all n queens, found a solution
6. Backtrack and try next column

### Known Solutions
- N=1: 1 solution
- N=2: 0 solutions
- N=3: 0 solutions
- N=4: 2 solutions
- N=5: 10 solutions
- N=6: 4 solutions
- N=7: 40 solutions
- N=8: 92 solutions

### Test Cases Included
- solveNQueens(4) → 2 solutions
- solveNQueens(1) → 1 solution
- solveNQueens(5) → 10 solutions
- countNQueens(1-8) → Counts for all sizes

### Example Output
```
Test 1: solveNQueens(4)
Found 2 solutions:

Solution 1:
  .Q..
  ...Q
  Q...
  ..Q.

Solution 2:
  ..Q.
  Q...
  ...Q
  .Q..
```

---

## Language-Specific Notes

### Python (permutation.py, combination.py, n_queens.py)
- Clean, readable syntax
- List comprehensions and slicing
- Set-based tracking for diagonals
- Includes both basic and optimized versions
- Complete test cases with clear output

### C (permutation.c, combination.c, n_queens.c)
- Manual memory management (malloc/free)
- Struct-based result containers
- In-place swapping for efficiency
- Proper cleanup and error handling
- Array-based tracking

### Java (Permutation.java, Combination.java, NQueens.java)
- ArrayList and HashSet for dynamic collections
- Class-based with static methods
- Clean object-oriented design
- Generic type support
- Comprehensive documentation

### Go (permutation.go, combination.go, n_queens.go)
- Idiomatic Go with slices and maps
- Goroutine-friendly (though sequential here)
- Efficient memory usage with clone operations
- Clean error handling patterns
- Simple, readable code

### JavaScript (permutation.js, combination.js, n_queens.js)
- Modern ES6+ syntax
- Array spread operator and Set collections
- Nested function closures
- Console-based testing
- Browser and Node.js compatible

### Rust (permutation.rs, combination.rs, n_queens.rs)
- Rust's ownership and borrowing system
- Vec and HashSet collections
- Safe memory management (no manual allocation)
- Zero-cost abstractions
- Idiomatic Rust patterns

---

## Running the Code

### Python
```bash
python3 permutation.py
python3 combination.py
python3 n_queens.py
```

### C
```bash
gcc -o permutation permutation.c && ./permutation
gcc -o combination combination.c && ./combination
gcc -o n_queens n_queens.c && ./n_queens
```

### Java
```bash
javac Permutation.java && java Permutation
javac Combination.java && java Combination
javac NQueens.java && java NQueens
```

### Go
```bash
go run permutation.go
go run combination.go
go run n_queens.go
```

### JavaScript (Node.js)
```bash
node permutation.js
node combination.js
node n_queens.js
```

### Rust
```bash
rustc permutation.rs && ./permutation
rustc combination.rs && ./combination
rustc n_queens.rs && ./n_queens
```

---

## Common Backtracking Pattern

All implementations follow the classic backtracking paradigm:

```
function backtrack(choices):
    if all choices made:
        return result

    for each valid option in current choices:
        choose option
        backtrack(remaining choices)
        unchoose option
```

### Pruning Techniques Used
1. **Permutation**: Check if element already used
2. **Combination**: Only consider elements >= current position
3. **N-Queens**: Check column and diagonal conflicts

---

## Complexity Analysis Summary

| Algorithm | Time Complexity | Space Complexity | # Solutions |
|-----------|-----------------|------------------|-------------|
| Permutation(n) | O(n! × n) | O(n) | n! |
| Combination(n,k) | O(C(n,k) × k) | O(k) | C(n,k) |
| N-Queens(n) | O(n!) | O(n) | Varies |

---

## Learning Outcomes

After studying this code, you'll understand:
1. Backtracking algorithm fundamentals
2. Choose-Explore-Unchoose pattern
3. Pruning strategies for optimization
4. Implementation across multiple languages
5. Time and space complexity analysis
6. Set/Map-based tracking for constraints
7. In-place vs. copy-based approaches

---

## Files by Location

All files located in: `/Users/jarry/github/algorithms/02-algorithmic-thinking/backtracking/`

Total: 18 files, ~82 KB of well-documented code
