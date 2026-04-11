/*
*
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

/*
*
 * 暴力法：比较所有对
 *
 * @param nums 输入数组
 * @return 最大XOR值
*/
function maxXorPairBruteForce(nums: number[]): number {
    let maxXor = 0;
    for (let i = 0; i < nums.length; i++) {
        for (let j = i + 1; j < nums.length; j++) {
            const xorVal = nums[i] ^ nums[j];
            if (xorVal > maxXor) {
                maxXor = xorVal;
            }
        }
    }
    return maxXor;
}

/*
*
 * Trie树节点
*/
class TrieNode {
    children: [TrieNode | null, TrieNode | null] = [null, null];
}

/*
*
 * 创建新的Trie节点
*/
function createTrieNode(): TrieNode {
    return new TrieNode();
}

/*
*
 * 将数字的二进制表示插入Trie树
*/
function insertTrie(root: TrieNode, num: number): void {
    let node = root;
    // 从最高位到最低位遍历
    for (let i = 31; i >= 0; i--) {
        const bit = (num >> i) & 1;
        if (node.children[bit] === null) {
            node.children[bit] = createTrieNode();
        }
        node = node.children[bit]!;
    }
}

/*
*
 * 找与给定数字最大XOR的数
 *
 * 贪心策略：对于每一位，尽可能走不同的路径以最大化XOR
*/
function findMaxXor(root: TrieNode, num: number): number {
    let node = root;
    let maxXor = 0;
    // 从最高位到最低位遍历
    for (let i = 31; i >= 0; i--) {
        const bit = (num >> i) & 1;
        // 优先走相反的路径（这样XOR结果该位为1）
        const toggleBit = 1 - bit;

        if (node.children[toggleBit] !== null) {
            maxXor |= (1 << i);
            node = node.children[toggleBit]!;
        } else if (node.children[bit] !== null) {
            node = node.children[bit]!;
        } else {
            // 不应该出现这种情况
            break;
        }
    }
    return maxXor;
}

/*
*
 * 使用Trie树找最大XOR对
 *
 * @param nums 输入数组
 * @return 最大XOR值
*/
function maxXorPairTrie(nums: number[]): number {
    if (nums.length < 2) return 0;

    const root = createTrieNode();

    // 构建Trie树
    for (const num of nums) {
        insertTrie(root, num);
    }

    let maxXor = 0;
    // 对每个数字，找与它最大XOR的数
    for (const num of nums) {
        const xorVal = findMaxXor(root, num);
        if (xorVal > maxXor) {
            maxXor = xorVal;
        }
    }

    return maxXor;
}

/*
*
 * 贪心法（不用Trie）：逐位构建答案
 *
 * @param nums 输入数组
 * @return 最大XOR值
*/
function maxXorPairGreedy(nums: number[]): number {
    if (nums.length < 2) return 0;

    let maxXor = 0;
    let prefixMask = 0;

    // 从最高位到最低位
    for (let i = 31; i >= 0; i--) {
        prefixMask |= (1 << i);

        // 收集所有数的前缀
        const prefixes: Set<number> = new Set();
        for (const num of nums) {
            prefixes.add(num & prefixMask);
        }

        // 尝试在当前位设为1
        const temp = maxXor | (1 << i);

        // 检查是否存在两个数的前缀异或为temp
        let found = false;
        for (const p1 of prefixes) {
            for (const p2 of prefixes) {
                if ((p1 ^ p2) === temp) {
                    maxXor = temp;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
    }

    return maxXor;
}

/*
*
 * 打印数组
*/
function printArray(arr: number[]): void {
    console.log(`[${arr.join(', ')}]`);
}

/*
*
 * 测试函数
*/
function main(): void {
    console.log("=== 最大XOR对 ===\n");

    // 测试用例1：基本用例
    console.log("1. 基本用例:");
    const testArrays: number[][] = [
        [1, 2, 3, 4, 5],
        [8, 10, 2],
    ];

    for (const nums of testArrays) {
        console.log(`  数组: `);
        printArray(nums);

        const brute = maxXorPairBruteForce(nums);
        const trie = maxXorPairTrie(nums);

        console.log(`  最大XOR (暴力): ${brute}`);
        console.log(`  最大XOR (Trie): ${trie}`);
        console.log(`  所有方法一致: ${brute === trie ? '是' : '否'}\n`);
    }

    // 测试用例2：XOR对的详细信息
    console.log("2. XOR对的详细信息:");
    const nums2 = [1, 2, 3, 4, 5];
    console.log(`  数组: `);
    printArray(nums2);

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
    const boundaryTests: { arr: number[], size: number }[] = [
        { arr: [5], size: 1 },
        { arr: [5, 3], size: 2 },
        { arr: [1], size: 1 },
        { arr: [7, 7], size: 2 },
    ];

    for (const test of boundaryTests) {
        const arr = test.arr.slice(0, test.size);
        console.log(`  数组: `);
        printArray(arr);
        console.log(` -> 最大XOR: ${maxXorPairTrie(arr)}`);
    }
    console.log();

    // 测试用例4：较大数组
    console.log("4. 较大数组测试:");
    const largeSize = 100;
    const largeNums: number[] = [];
    for (let i = 0; i < largeSize; i++) {
        largeNums.push(i + 1);
    }

    const start1 = Date.now();
    const resultGreedy = maxXorPairGreedy(largeNums);
    const greedyTime = Date.now() - start1;

    const start2 = Date.now();
    const resultTrie = maxXorPairTrie(largeNums);
    const trieTime = Date.now() - start2;

    console.log(`  数组大小: ${largeSize}`);
    console.log(`  贪心法结果: ${resultGreedy}, 耗时: ${greedyTime} ms`);
    console.log(`  Trie法结果: ${resultTrie}, 耗时: ${trieTime} ms`);
}

// 运行测试
main();
