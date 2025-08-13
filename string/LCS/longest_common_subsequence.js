/**
 * 最长公共子序列（LCS）求解函数
 * 
 * 功能：找到两个字符串中最长的公共子序列（字符顺序一致但不必连续）
 * 
 * @param {string} firstString 第一个输入字符串
 * @param {string} secondString 第二个输入字符串
 * @returns {Array} 一个数组，第一个元素是LCS的长度，第二个元素是LCS的具体内容
 * 
 * 举例：
 * 序列A为"abcdef"，序列B为"bcef"，
 * 最长公共子序列为"bcef"，
 * 注意最长公共子序列不用保证每一个字符必须连续。
 */
/*
示例与算法对比说明
示例：
若序列 A 为 “abcdef”，序列 B 为 “bcef”，其最长公共子序列为 “bcef”（即序列 B）。需注意，最长公共子序列仅要求字符顺序一致，无需连续。
暴力解法思路：
选择一个参照序列（如 A），遍历其每个字符作为公共子序列的起始点；
将该字符与另一序列（如 B）的每个字符比较，若匹配，则在两序列中均向后移动指针继续比较，直至某一序列结束；
重复上述过程，以参照序列的每个字符为起点计算可能的公共子序列长度，最终取最大值。
暴力解法的问题：
时间复杂度为 O (n²×m)（其中 n 为序列 A 的长度，m 为序列 B 的长度），效率过低。因此，需要更优的算法 —— 动态规划。
*/
function findLCS(firstString, secondString) {
    const lengthOfFirst = firstString.length;
    const lengthOfSecond = secondString.length;
    
    // 创建DP表：dpTable[i][j]表示前i个字符与前j个字符的LCS长度
    const dpTable = Array.from({ length: lengthOfFirst + 1 }, 
        () => new Array(lengthOfSecond + 1).fill(0));
    
    // 填充DP表
    for (let i = 1; i <= lengthOfFirst; i++) {
        for (let j = 1; j <= lengthOfSecond; j++) {
            const charFromFirst = firstString[i - 1];
            const charFromSecond = secondString[j - 1];
            
            if (charFromFirst === charFromSecond) {
                // 字符相同，继承前序结果+1
                dpTable[i][j] = dpTable[i - 1][j - 1] + 1;
            } else {
                // 字符不同，取两种情况的最大值
                dpTable[i][j] = Math.max(dpTable[i - 1][j], dpTable[i][j - 1]);
            }
        }
    }
    
    // 回溯找到具体的LCS序列
    const lcsCharacters = [];
    let currentI = lengthOfFirst;
    let currentJ = lengthOfSecond;
    
    while (currentI > 0 && currentJ > 0) {
        const currentCharFirst = firstString[currentI - 1];
        const currentCharSecond = secondString[currentJ - 1];
        
        if (currentCharFirst === currentCharSecond) {
            lcsCharacters.push(currentCharFirst);
            currentI--;
            currentJ--;
        } else if (dpTable[currentI - 1][currentJ] > dpTable[currentI][currentJ - 1]) {
            currentI--;
        } else {
            currentJ--;
        }
    }
    
    // 反转得到正确顺序
    const lcsContent = lcsCharacters.reverse().join('');
    return [dpTable[lengthOfFirst][lengthOfSecond], lcsContent];
}

/** 运行LCS算法的测试用例集合 */
function runLCSTests() {
    // 测试用例数组：[字符串1, 字符串2, 预期长度, 可能的预期结果数组]
    const testCases = [
        ["ABCBDAB", "BDCAB", 4, ["BCAB", "BDAB"]],
        ["HELLO", "HELLO", 5, ["HELLO"]],
        ["ABCDEF", "ACE", 3, ["ACE"]],
        ["ABCD", "EFGH", 0, [""]],
        ["", "TEST", 0, [""]],
        ["AABBAABB", "ABAB", 4, ["AABB", "ABAB", "ABBA"]],
        ["XMJYAUZ", "MZJAWXU", 4, ["MJAU", "MZAU"]],
        ["A", "A", 1, ["A"]],
        ["A", "B", 0, [""]],
        ["123@abc", "a3@x1", 3, ["3@a", "1@a", "3a@"]]
    ];
    
    testCases.forEach((testCase, index) => {
        const [s1, s2, expectedLen, possibleResults] = testCase;
        console.log(`\n测试用例 ${index + 1}:`);
        console.log(`字符串1: ${s1}`);
        console.log(`字符串2: ${s2}`);
        
        const [actualLen, actualResult] = findLCS(s1, s2);
        
        const lenMatch = actualLen === expectedLen;
        const resultMatch = possibleResults.includes(actualResult);
        
        console.log(`预期长度: ${expectedLen}, 实际长度: ${actualLen} → ${lenMatch ? '通过' : '失败'}`);
        console.log(`预期结果之一: ${possibleResults[0]}, 实际结果: ${actualResult} → ${resultMatch ? '通过' : '失败'}`);
        console.log(`测试结果: ${lenMatch && resultMatch ? '全部通过' : '存在问题'}`);
    });
}

// 示例用法
const stringOne = "AABCBDAB";
const stringTwo = "ABDCAB";

const [lcsLength, lcsResult] = findLCS(stringOne, stringTwo);
console.log("示例计算结果：");
console.log(`第一个字符串: ${stringOne}`);
console.log(`第二个字符串: ${stringTwo}`);
console.log(`最长公共子序列的长度: ${lcsLength}`);  // 输出5
console.log(`最长公共子序列的内容: ${lcsResult}`);  // 输出"ABDAB"

// 运行测试用例
console.log("\n开始执行测试用例...");
runLCSTests();

/**
jarry@Mac LCS % node longest_common_subsequence.js
示例计算结果：
第一个字符串: AABCBDAB
第二个字符串: ABDCAB
最长公共子序列的长度: 5
最长公共子序列的内容: ABDAB

开始执行测试用例...

测试用例 1:
字符串1: ABCBDAB
字符串2: BDCAB
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: BCAB, 实际结果: BDAB → 通过
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
预期长度: 3, 实际长度: 3 → 通过
预期结果之一: ACE, 实际结果: ACE → 通过
测试结果: 全部通过

测试用例 4:
字符串1: ABCD
字符串2: EFGH
预期长度: 0, 实际长度: 0 → 通过
预期结果之一: , 实际结果:  → 通过
测试结果: 全部通过

测试用例 5:
字符串1: 
字符串2: TEST
预期长度: 0, 实际长度: 0 → 通过
预期结果之一: , 实际结果:  → 通过
测试结果: 全部通过

测试用例 6:
字符串1: AABBAABB
字符串2: ABAB
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: AABB, 实际结果: ABAB → 通过
测试结果: 全部通过

测试用例 7:
字符串1: XMJYAUZ
字符串2: MZJAWXU
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: MJAU, 实际结果: MJAU → 通过
测试结果: 全部通过

测试用例 8:
字符串1: A
字符串2: A
预期长度: 1, 实际长度: 1 → 通过
预期结果之一: A, 实际结果: A → 通过
测试结果: 全部通过

测试用例 9:
字符串1: A
字符串2: B
预期长度: 0, 实际长度: 0 → 通过
预期结果之一: , 实际结果:  → 通过
测试结果: 全部通过

测试用例 10:
字符串1: 123@abc
字符串2: a3@x1
预期长度: 3, 实际长度: 2 → 失败
预期结果之一: 3@a, 实际结果: 3@ → 失败
测试结果: 存在问题
 */