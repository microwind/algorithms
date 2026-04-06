/**
 * 字符串递归操作示例
 * 
 * 算法特点：
 * - 演示递归在字符串处理中的应用
 * - 包含字符串反转、回文检查、元音计数
 * 
 * 学习重点：理解递归在字符串操作中的使用
 */

/**
 * 递归反转字符串
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param {string} s 要反转的字符串
 * @return {string} 反转后的字符串
 */
function reverseString(s) {
    // 基础情况：空字符串或单个字符
    if (s.length <= 1) {
        return s;
    }
    
    // 递归：剩余部分反转 + 第一个字符放到末尾
    return reverseString(s.slice(1)) + s[0];
}

/**
 * 递归检查字符串是否为回文
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param {string} s 要检查的字符串
 * @return {boolean} 是否为回文
 */
function isPalindrome(s) {
    s = s.toLowerCase(); // 忽略大小写
    
    // 基础情况：空字符串或单个字符是回文
    if (s.length <= 1) {
        return true;
    }
    
    // 如果首尾字符不同，不是回文
    if (s[0] !== s[s.length - 1]) {
        return false;
    }
    
    // 递归检查去掉首尾后的中间部分
    return isPalindrome(s.slice(1, -1));
}

/**
 * 递归计算字符串中元音字母的数量
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param {string} s 要计算的字符串
 * @return {number} 元音字母数量
 */
function countVowels(s) {
    const vowels = 'aeiouAEIOU';
    
    // 基础情况：空字符串
    if (s.length === 0) {
        return 0;
    }
    
    // 检查第一个字符是否是元音
    const firstIsVowel = vowels.includes(s[0]) ? 1 : 0;
    
    // 递归计算剩余部分
    return firstIsVowel + countVowels(s.slice(1));
}

/**
 * 主函数 - 测试字符串递归操作
 */
function main() {
    console.log("========================================");
    console.log("字符串递归操作示例");
    console.log("========================================");
    
    // 测试1：字符串反转
    const testStr1 = "Hello";
    console.log("\n1. 字符串反转:");
    console.log(`   原字符串: '${testStr1}'`);
    console.log(`   反转后:   '${reverseString(testStr1)}'`);
    
    // 测试2：回文检查
    console.log("\n2. 回文检查:");
    const testCases = ["radar", "hello", "Aba", "level"];
    for (const s of testCases) {
        const result = isPalindrome(s) ? "是回文" : "不是回文";
        console.log(`   '${s}' -> ${result}`);
    }
    
    // 测试3：元音计数
    const testStr2 = "Hello World";
    console.log("\n3. 元音计数:");
    console.log(`   字符串: '${testStr2}'`);
    console.log(`   元音数量: ${countVowels(testStr2)}`);
    
    console.log("\n========================================");
}

/*打印结果
jarry@Mac string-recursion % node string_operations.js
========================================
字符串递归操作示例
========================================

1. 字符串反转:
   原字符串: 'Hello'
   反转后:   'olleH'

2. 回文检查:
   'radar' -> 是回文
   'hello' -> 不是回文
   'Aba' -> 是回文
   'level' -> 是回文

3. 元音计数:
   字符串: 'Hello World'
   元音数量: 3

========================================
*/

// 运行主函数
main();
