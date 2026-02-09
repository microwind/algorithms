/**
 * 最大XOR对 - 找数组中最大的XOR值
 *
 * 问题：给定一个数组，找到任意两个元素的最大XOR值
 *
 * 核心思想：
 * - 暴力法：比较所有对
 * - 字典树(Trie)：高效地查找最大XOR
 *
 * 时间复杂度:
 * - 暴力法: O(n^2)
 * - Trie方法: O(n * k) 其中k是整数的位数
 *
 * 空间复杂度: O(n * k) for Trie
 */

/**
 * 暴力法：比较所有对
 *
 * @param {number[]} nums 输入数组
 * @returns {number} 最大XOR值
 */
function maxXorPairBruteForce(nums) {
    let maxXor = 0;
    for (let i = 0; i < nums.length; i++) {
        for (let j = i + 1; j < nums.length; j++) {
            const xorVal = nums[i] ^ nums[j];
            maxXor = Math.max(maxXor, xorVal);
        }
    }
    return maxXor;
}

/**
 * Trie树节点
 */
class TrieNode {
    constructor() {
        this.children = [null, null];  // 0和1两个分支
    }
}

/**
 * 将数字的二进制表示插入Trie树
 */
function insertTrie(root, num) {
    let node = root;
    // 从最高位到最低位遍历
    for (let i = 31; i >= 0; i--) {
        const bit = (num >>> i) & 1;
        if (node.children[bit] === null) {
            node.children[bit] = new TrieNode();
        }
        node = node.children[bit];
    }
}

/**
 * 找与给定数字最大XOR的数
 *
 * 贪心策略：对于每一位，尽可能走不同的路径以最大化XOR
 */
function findMaxXor(root, num) {
    let node = root;
    let maxXor = 0;
    // 从最高位到最低位遍历
    for (let i = 31; i >= 0; i--) {
        const bit = (num >>> i) & 1;
        // 优先走相反的路径（这样XOR结果该位为1）
        const toggleBit = 1 - bit;

        if (node.children[toggleBit] !== null) {
            maxXor |= (1 << i);
            node = node.children[toggleBit];
        } else if (node.children[bit] !== null) {
            node = node.children[bit];
        } else {
            // 不应该出现这种情况
            break;
        }
    }
    return maxXor;
}

/**
 * 使用Trie树找最大XOR对
 *
 * @param {number[]} nums 输入数组
 * @returns {number} 最大XOR值
 */
function maxXorPairTrie(nums) {
    if (nums.length < 2) return 0;

    const root = new TrieNode();

    // 构建Trie树
    for (let num of nums) {
        insertTrie(root, num);
    }

    let maxXor = 0;
    // 对每个数字，找与它最大XOR的数
    for (let num of nums) {
        const xorVal = findMaxXor(root, num);
        maxXor = Math.max(maxXor, xorVal);
    }

    return maxXor;
}

/**
 * 贪心法（不用Trie）：逐位构建答案
 *
 * @param {number[]} nums 输入数组
 * @returns {number} 最大XOR值
 */
function maxXorPairGreedy(nums) {
    if (nums.length < 2) return 0;

    let maxXor = 0;
    let prefixMask = 0;

    // 从最高位到最低位
    for (let i = 31; i >= 0; i--) {
        prefixMask |= (1 << i);

        // 收集所有数的前缀
        const prefixes = new Set();
        for (let num of nums) {
            prefixes.add(num & prefixMask);
        }

        // 尝试在当前位设为1
        const temp = maxXor | (1 << i);

        // 检查是否存在两个数的前缀异或为temp
        for (let prefix of prefixes) {
            if (prefixes.has(temp ^ prefix)) {
                maxXor = temp;
                break;
            }
        }
    }

    return maxXor;
}

// 测试函数
console.log("=== 最大XOR对 ===\n");

// 测试用例1：基本用例
console.log("1. 基本用例:");
const testArrays = [
    [1, 2, 3, 4, 5],
    [8, 10, 2],
    [14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70],
];

for (let nums of testArrays) {
    console.log(`  数组: [${nums}]`);

    const brute = maxXorPairBruteForce(nums);
    const trie = maxXorPairTrie(nums);
    const greedy = maxXorPairGreedy(nums);

    console.log(`  最大XOR (暴力): ${brute}`);
    console.log(`  最大XOR (Trie): ${trie}`);
    console.log(`  最大XOR (贪心): ${greedy}`);
    console.log(`  所有方法一致: ${brute === trie && trie === greedy ? "是" : "否"}`);
    console.log();
}

// 测试用例2：XOR对的详细信息
console.log("2. XOR对的详细信息:");
const nums2 = [1, 2, 3, 4, 5];
console.log(`  数组: [${nums2}]`);

let maxXor = 0;
let bestI = -1, bestJ = -1;
for (let i = 0; i < nums2.length; i++) {
    for (let j = i + 1; j < nums2.length; j++) {
        const xorVal = nums2[i] ^ nums2[j];
        if (xorVal > maxXor) {
            maxXor = xorVal;
            bestI = i;
            bestJ = j;
        }
        if (xorVal >= 4) {  // 只显示较大的XOR值
            console.log(`    ${nums2[i]} ^ ${nums2[j]} = ${xorVal}`);
        }
    }
}
console.log(`  最大XOR对: ${nums2[bestI]} ^ ${nums2[bestJ]} = ${maxXor}\n`);

// 测试用例3：边界情况
console.log("3. 边界情况:");
const boundaryTests = [
    [5],
    [5, 3],
    [1],
    [7, 7],
];

for (let nums of boundaryTests) {
    console.log(`  数组: [${nums}] -> 最大XOR: ${maxXorPairTrie(nums)}`);
}
console.log();

// 测试用例4：较大数组
console.log("4. 较大数组测试:");
const largeSize = 100;
const largeNums = [];
for (let i = 0; i < largeSize; i++) {
    largeNums.push(i + 1);
}

let start = performance.now();
const resultGreedy = maxXorPairGreedy(largeNums);
const greedyTime = performance.now() - start;

start = performance.now();
const resultTrie = maxXorPairTrie(largeNums);
const trieTime = performance.now() - start;

console.log(`  数组大小: ${largeSize}`);
console.log(`  贪心法结果: ${resultGreedy}, 耗时: ${greedyTime.toFixed(2)}ms`);
console.log(`  Trie法结果: ${resultTrie}, 耗时: ${trieTime.toFixed(2)}ms`);
