/**
 * 最长公共子序列（LCS）问题有两种方式定义子序列，一种是子序列不要求连续，一种是子序列要求连续。
 * 下面介绍要求子序列必须是连续的情况下，如何用算法解决最长公共子序列问题。
 * 
 * 以两个字符串 “abcdea”和“aebcda”为例，如果子序列不要求连续，其最长公共子序列为“abcda”，
 * 如果子序列要求是连续，则其最长公共子序列应为“bcd”。在这种情况下，有可能两个字符串出现多个长度相同的
 * 公共子串，比如“askdfiryetd”和“trkdffirey”两个字符串就存在两个长度为3的公共子串，分别是“kdf”和“fir”，
 * 因此问题的性质发生了变化，需要找出两个字符串所有可能存在公共子串的情况，然后取最长的一个，如果有多个
 * 最长的公共子串，只取其中一个即可。
 */

/**
 * 最长公共子串（连续）求解函数
 * 
 * 功能：找到两个字符串中最长的连续公共子串（字符顺序一致且连续相邻）
 * 
 * 参数：
 *   str1: 第一个输入字符串
 *   str2: 第二个输入字符串
 * 
 * 返回值：
 *   一个对象，包含最长公共子串的长度（length）和内容（substring）
 */
function longestContinuousSubsequence(str1, str2) {
    const len1 = str1.length;
    const len2 = str2.length;
    
    // 特殊情况处理
    if (len1 === 0 || len2 === 0) {
        return { length: 0, substring: "" };
    }
    
    // 创建DP表：dp[i][j]表示以str1[i-1]和str2[j-1]为结尾的最长公共子串长度
    const dp = Array.from({ length: len1 + 1 }, () => new Array(len2 + 1).fill(0));
    
    let maxLength = 0;  // 记录最长公共子串的长度
    let endIndex = 0;   // 记录最长公共子串在str1中的结束索引
    
    // 填充DP表
    for (let i = 1; i <= len1; i++) {
        for (let j = 1; j <= len2; j++) {
            if (str1[i - 1] === str2[j - 1]) {
                // 当前字符相同，长度 = 前一位的长度 + 1（连续累加）
                dp[i][j] = dp[i - 1][j - 1] + 1;
                
                // 更新最长长度和结束索引
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i;  // 记录在str1中的结束位置
                }
            } else {
                // 字符不同，连续中断，长度重置为0
                dp[i][j] = 0;
            }
        }
    }
    
    // 提取最长公共子串
    let longestSubstring = "";
    if (maxLength > 0) {
        const startIndex = endIndex - maxLength;
        longestSubstring = str1.substring(startIndex, endIndex);
    }
    
    return { length: maxLength, substring: longestSubstring };
}

// 检查字符串是否在字符串数组中
function isInArray(str, array) {
    return array.includes(str);
}

// 测试用例
function testLongestContinuousSubsequence() {
    // 测试用例数组
    const testCases = [
        { s1: "ABCBDAB", s2: "BDCAB", expectedLen: 2, possibleResults: ["BC", "AB"] },
        { s1: "HELLO", s2: "HELLO", expectedLen: 5, possibleResults: ["HELLO"] },
        { s1: "ABCDEF", s2: "ACE", expectedLen: 1, possibleResults: ["A", "C", "E"] },
        { s1: "ABCDXYZ", s2: "XYZABCD", expectedLen: 4, possibleResults: ["ABCD"] },
        { s1: "12345", s2: "54321", expectedLen: 1, possibleResults: ["1", "2", "3", "4", "5"] },
        { s1: "ABABC", s2: "BABCA", expectedLen: 4, possibleResults: ["ABCA", "BABC"] }
    ];
    
    testCases.forEach((tc, index) => {
        console.log(`测试用例 ${index + 1}:`);
        console.log(`字符串1: ${tc.s1}`);
        console.log(`字符串2: ${tc.s2}`);
        
        const result = longestContinuousSubsequence(tc.s1, tc.s2);
        const lenMatch = result.length === tc.expectedLen;
        const resultMatch = isInArray(result.substring, tc.possibleResults);
        
        console.log(`预期长度: ${tc.expectedLen}, 实际长度: ${result.length} → ${lenMatch ? "通过" : "失败"}`);
        console.log(`预期结果之一: ${tc.possibleResults[0]}, 实际结果: ${result.substring} → ${resultMatch ? "通过" : "失败"}`);
        console.log(`测试结果: ${lenMatch && resultMatch ? "全部通过" : "存在问题"}\n`);
    });
}

// 示例
const s1 = "ABCBDAB";
const s2 = "BDCAB";
const exampleResult = longestContinuousSubsequence(s1, s2);

console.log("示例:");
console.log(`字符串1: ${s1}`);
console.log(`字符串2: ${s2}`);
console.log(`最长公共子串长度: ${exampleResult.length}`);
console.log(`最长公共子串: ${exampleResult.substring}\n`);

// 运行测试
testLongestContinuousSubsequence();

/**
jarry@Mac LCS % node longest_continuous_subsequence.js
示例:
字符串1: ABCBDAB
字符串2: BDCAB
最长公共子串长度: 2
最长公共子串: AB

测试用例 1:
字符串1: ABCBDAB
字符串2: BDCAB
预期长度: 2, 实际长度: 2 → 通过
预期结果之一: BC, 实际结果: AB → 通过
测试结果: 全部通过

测试用例 2:
字符串1: HELLO
字符串2: HELLO
预期长度: 5, 实际长度: 5 → 通过
预期结果之一: HELLO, 实际结果: HELLO → 通过
测试结果: 全部通过

测试用例 3:
字符串1: ABCDEF
字符串2: ACE
预期长度: 1, 实际长度: 1 → 通过
预期结果之一: A, 实际结果: A → 通过
测试结果: 全部通过

测试用例 4:
字符串1: ABCDXYZ
字符串2: XYZABCD
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: ABCD, 实际结果: ABCD → 通过
测试结果: 全部通过

测试用例 5:
字符串1: 12345
字符串2: 54321
预期长度: 1, 实际长度: 1 → 通过
预期结果之一: 1, 实际结果: 1 → 通过
测试结果: 全部通过

测试用例 6:
字符串1: ABABC
字符串2: BABCA
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: ABCA, 实际结果: BABC → 通过
测试结果: 全部通过
 */