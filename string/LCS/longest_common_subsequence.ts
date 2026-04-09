/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  string algorithms - longest common subsequence (LCS)
 * dynamic programming solution for finding longest common subsequence
 * time complexity: O(n*m) where n and m are lengths of input strings
 */

/**
 * LCS class with multiple implementation methods
 */
class LongestCommonSubsequence {
    private text1: string;
    private text2: string;
    private dp: number[][];

    constructor(text1: string, text2: string) {
        this.text1 = text1;
        this.text2 = text2;
        this.dp = [];
    }

    /**
     * dynamic programming method to find LCS length
     * time complexity: O(n*m)
     * space complexity: O(n*m)
     */
    public lcsLength(): number {
        const n = this.text1.length;
        const m = this.text2.length;
        
        // initialize DP table
        this.dp = Array(n + 1).fill(null).map(() => Array(m + 1).fill(0));
        
        // fill DP table
        for (let i = 1; i <= n; i++) {
            for (let j = 1; j <= m; j++) {
                if (this.text1[i - 1] === this.text2[j - 1]) {
                    this.dp[i][j] = this.dp[i - 1][j - 1] + 1;
                } else {
                    this.dp[i][j] = Math.max(this.dp[i - 1][j], this.dp[i][j - 1]);
                }
            }
        }
        
        return this.dp[n][m];
    }

    /**
     * reconstruct LCS string from DP table
     * time complexity: O(n+m)
     * space complexity: O(n+m) for the result
     */
    public getLCS(): string {
        this.lcsLength(); // ensure DP table is filled
        
        let i = this.text1.length;
        let j = this.text2.length;
        const lcs: string[] = [];
        
        while (i > 0 && j > 0) {
            if (this.text1[i - 1] === this.text2[j - 1]) {
                lcs.push(this.text1[i - 1]);
                i--;
                j--;
            } else if (this.dp[i - 1][j] > this.dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        
        return lcs.reverse().join('');
    }

    /**
     * space-optimized DP method
     * time complexity: O(n*m)
     * space complexity: O(min(n,m))
     */
    public lcsLengthOptimized(): number {
        const text1 = this.text1;
        const text2 = this.text2;
        
        // ensure text2 is the shorter string for space optimization
        if (text1.length < text2.length) {
            return this.lcsLengthOptimizedHelper(text2, text1);
        }
        return this.lcsLengthOptimizedHelper(text1, text2);
    }

    private lcsLengthOptimizedHelper(longer: string, shorter: string): number {
        const n = longer.length;
        const m = shorter.length;
        let prev = Array(m + 1).fill(0);
        let curr = Array(m + 1).fill(0);
        
        for (let i = 1; i <= n; i++) {
            for (let j = 1; j <= m; j++) {
                if (longer[i - 1] === shorter[j - 1]) {
                    curr[j] = prev[j - 1] + 1;
                } else {
                    curr[j] = Math.max(prev[j], curr[j - 1]);
                }
            }
            [prev, curr] = [curr, prev];
        }
        
        return prev[m];
    }

    /**
     * recursive method with memoization
     * time complexity: O(n*m)
     * space complexity: O(n*m) for memoization
     */
    public lcsLengthRecursive(): number {
        const memo: Map<string, number> = new Map();
        return this.lcsLengthRecursiveHelper(this.text1.length, this.text2.length, memo);
    }

    private lcsLengthRecursiveHelper(i: number, j: number, memo: Map<string, number>): number {
        const key = `${i},${j}`;
        
        if (memo.has(key)) {
            return memo.get(key)!;
        }
        
        if (i === 0 || j === 0) {
            return 0;
        }
        
        let result: number;
        if (this.text1[i - 1] === this.text2[j - 1]) {
            result = 1 + this.lcsLengthRecursiveHelper(i - 1, j - 1, memo);
        } else {
            result = Math.max(
                this.lcsLengthRecursiveHelper(i - 1, j, memo),
                this.lcsLengthRecursiveHelper(i, j - 1, memo)
            );
        }
        
        memo.set(key, result);
        return result;
    }

    /**
     * get all possible LCS strings
     * time complexity: O(n*m) for DP + exponential for reconstruction
     */
    public getAllLCS(): string[] {
        this.lcsLength(); // ensure DP table is filled
        const result: Set<string> = new Set();
        this.getAllLCSHelper(this.text1.length, this.text2.length, '', result);
        return Array.from(result);
    }

    private getAllLCSHelper(i: number, j: number, current: string, result: Set<string>): void {
        if (i === 0 || j === 0) {
            result.add(current);
            return;
        }
        
        if (this.text1[i - 1] === this.text2[j - 1]) {
            this.getAllLCSHelper(i - 1, j - 1, this.text1[i - 1] + current, result);
        } else {
            if (this.dp[i - 1][j] >= this.dp[i][j - 1]) {
                this.getAllLCSHelper(i - 1, j, current, result);
            }
            if (this.dp[i][j - 1] >= this.dp[i - 1][j]) {
                this.getAllLCSHelper(i, j - 1, current, result);
            }
        }
    }

    /**
     * print DP table for debugging
     */
    public printDPTable(): void {
        this.lcsLength(); // ensure DP table is filled
        
        console.log("DP Table:");
        let header = "    " + this.text2.split('').join(' ');
        console.log(header);
        
        for (let i = 0; i <= this.text1.length; i++) {
            let row = "";
            if (i === 0) {
                row += "  ";
            } else {
                row += this.text1[i - 1] + " ";
            }
            
            for (let j = 0; j <= this.text2.length; j++) {
                row += this.dp[i][j].toString() + " ";
            }
            console.log(row);
        }
    }

    /**
     * get similarity ratio
     */
    public getSimilarityRatio(): number {
        const lcsLength = this.lcsLength();
        const maxLength = Math.max(this.text1.length, this.text2.length);
        return maxLength === 0 ? 1.0 : lcsLength / maxLength;
    }
}

/**
 * convenience functions
 */
function lcsLength(text1: string, text2: string): number {
    const lcs = new LongestCommonSubsequence(text1, text2);
    return lcs.lcsLength();
}

function getLCS(text1: string, text2: string): string {
    const lcs = new LongestCommonSubsequence(text1, text2);
    return lcs.getLCS();
}

function lcsSimilarity(text1: string, text2: string): number {
    const lcs = new LongestCommonSubsequence(text1, text2);
    return lcs.getSimilarityRatio();
}

/**
 * main function - test LCS algorithm
 */
function testLCS(): void {
    console.log("=".repeat(70));
    console.log("Longest Common Subsequence - TypeScript Implementation");
    console.log("=".repeat(70));
    
    const testCases = [
        { text1: "AGGTAB", text2: "GXTXAYB", expected: "GTAB" },
        { text1: "ABCBDAB", text2: "BDCAB", expected: "BCAB" },
        { text1: "XMJYAUZ", text2: "MZJAWXU", expected: "MJAU" },
        { text1: "HELLO", text2: "WORLD", expected: "LO" },
        { text1: "", text2: "ABC", expected: "" },
        { text1: "ABC", text2: "", expected: "" },
        { text1: "SAME", text2: "SAME", expected: "SAME" },
    ];
    
    console.log("\n=== Test Results ===");
    for (const testCase of testCases) {
        const lcs = new LongestCommonSubsequence(testCase.text1, testCase.text2);
        const lcsString = lcs.getLCS();
        const lcsLength = lcs.lcsLength();
        const similarity = lcs.getSimilarityRatio();
        
        console.log(`Text1: "${testCase.text1}"`);
        console.log(`Text2: "${testCase.text2}"`);
        console.log(`LCS: "${lcsString}" (Length: ${lcsLength})`);
        console.log(`Similarity: ${(similarity * 100).toFixed(2)}%`);
        console.log(`Expected: "${testCase.expected}"`);
        console.log(`Match: ${lcsString === testCase.expected ? "YES" : "NO"}`);
        console.log();
    }
    
    console.log("=== Algorithm Comparison ===");
    const text1 = "ABCDGH";
    const text2 = "AEDFHR";
    const lcs = new LongestCommonSubsequence(text1, text2);
    
    console.log(`Text1: "${text1}", Text2: "${text2}"`);
    console.log(`DP Method: ${lcs.lcsLength()}`);
    console.log(`Optimized DP: ${lcs.lcsLengthOptimized()}`);
    console.log(`Recursive: ${lcs.lcsLengthRecursive()}`);
    console.log(`LCS String: "${lcs.getLCS()}"`);
    
    console.log("\n=== All Possible LCS ===");
    const complexCase = new LongestCommonSubsequence("ABCBDAB", "BDCAB");
    const allLCS = complexCase.getAllLCS();
    console.log(`All LCS for "ABCBDAB" and "BDCAB":`);
    allLCS.forEach((lcs, index) => {
        console.log(`  ${index + 1}. "${lcs}"`);
    });
    
    console.log("\n=== DP Table Example ===");
    const example = new LongestCommonSubsequence("ABC", "ABC");
    example.printDPTable();
    
    console.log("\n=== Algorithm Characteristics ===");
    console.log("Dynamic Programming Approach:");
    console.log("  - Time Complexity: O(n*m)");
    console.log("  - Space Complexity: O(n*m) or O(min(n,m)) optimized");
    console.log("  - Guarantees optimal solution");
    console.log("  - Suitable for moderate string lengths");
    
    console.log("\nRecursive with Memoization:");
    console.log("  - Time Complexity: O(n*m)");
    console.log("  - Space Complexity: O(n*m) for memoization");
    console.log("  - More intuitive but may hit recursion limits");
    console.log("  - Good for understanding the problem structure");
    
    console.log("\n=== Common Applications ===");
    console.log("LCS is used in:");
    console.log("  - DNA sequence analysis and comparison");
    console.log("  - File comparison tools (diff)");
    console.log("  - Plagiarism detection");
    console.log("  - Version control systems");
    console.log("  - Bioinformatics and computational biology");
    console.log("  - Data compression algorithms");
    console.log("  - Spell checking and auto-correction");
    
    console.log("\n=== Variations and Extensions ===");
    console.log("Related problems:");
    console.log("  - Longest Common Substring (continuous)");
    console.log("  - Shortest Common Supersequence");
    console.log("  - Edit Distance (Levenshtein distance)");
    console.log("  - Longest Palindromic Subsequence");
    console.log("  - Sequence alignment in bioinformatics");
    
    console.log("\n=== Performance Tips ===");
    console.log("Optimization strategies:");
    console.log("  - Use space-optimized DP for large strings");
    console.log("  - Consider early termination for exact matches");
    console.log("  - Use rolling hash for specific patterns");
    console.log("  - Parallel processing for multiple comparisons");
}

// auto-run test in Node.js environment
if (typeof window === 'undefined') {
    testLCS();
}
