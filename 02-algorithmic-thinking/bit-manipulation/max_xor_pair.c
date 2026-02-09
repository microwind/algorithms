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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * 暴力法：比较所有对
 *
 * @param nums 输入数组
 * @param n 数组大小
 * @return 最大XOR值
 */
int maxXorPairBruteForce(int *nums, int n) {
    int maxXor = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int xorVal = nums[i] ^ nums[j];
            if (xorVal > maxXor) {
                maxXor = xorVal;
            }
        }
    }
    return maxXor;
}

/**
 * Trie树节点
 */
typedef struct TrieNode {
    struct TrieNode *children[2];  // 0和1两个分支
} TrieNode;

/**
 * 创建新的Trie节点
 */
TrieNode *createTrieNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->children[0] = NULL;
    node->children[1] = NULL;
    return node;
}

/**
 * 释放Trie树内存
 */
void freeTrieNode(TrieNode *root) {
    if (root == NULL) return;
    freeTrieNode(root->children[0]);
    freeTrieNode(root->children[1]);
    free(root);
}

/**
 * 将数字的二进制表示插入Trie树
 */
void insertTrie(TrieNode *root, int num) {
    TrieNode *node = root;
    // 从最高位到最低位遍历
    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (node->children[bit] == NULL) {
            node->children[bit] = createTrieNode();
        }
        node = node->children[bit];
    }
}

/**
 * 找与给定数字最大XOR的数
 *
 * 贪心策略：对于每一位，尽可能走不同的路径以最大化XOR
 */
int findMaxXor(TrieNode *root, int num) {
    TrieNode *node = root;
    int maxXor = 0;
    // 从最高位到最低位遍历
    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        // 优先走相反的路径（这样XOR结果该位为1）
        int toggleBit = 1 - bit;

        if (node->children[toggleBit] != NULL) {
            maxXor |= (1 << i);
            node = node->children[toggleBit];
        } else if (node->children[bit] != NULL) {
            node = node->children[bit];
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
 * @param nums 输入数组
 * @param n 数组大小
 * @return 最大XOR值
 */
int maxXorPairTrie(int *nums, int n) {
    if (n < 2) return 0;

    TrieNode *root = createTrieNode();

    // 构建Trie树
    for (int i = 0; i < n; i++) {
        insertTrie(root, nums[i]);
    }

    int maxXor = 0;
    // 对每个数字，找与它最大XOR的数
    for (int i = 0; i < n; i++) {
        int xorVal = findMaxXor(root, nums[i]);
        if (xorVal > maxXor) {
            maxXor = xorVal;
        }
    }

    freeTrieNode(root);
    return maxXor;
}

/**
 * 贪心法（不用Trie）：逐位构建答案
 *
 * @param nums 输入数组
 * @param n 数组大小
 * @return 最大XOR值
 */
int maxXorPairGreedy(int *nums, int n) {
    if (n < 2) return 0;

    int maxXor = 0;
    int prefixMask = 0;

    // 从最高位到最低位
    for (int i = 31; i >= 0; i--) {
        prefixMask |= (1 << i);

        // 收集所有数的前缀
        int *prefixes = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            prefixes[j] = nums[j] & prefixMask;
        }

        // 尝试在当前位设为1
        int temp = maxXor | (1 << i);

        // 检查是否存在两个数的前缀异或为temp
        int found = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if ((prefixes[j] ^ prefixes[k]) == temp) {
                    maxXor = temp;
                    found = 1;
                    break;
                }
            }
            if (found) break;
        }

        free(prefixes);
    }

    return maxXor;
}

/**
 * 打印数组
 */
void printArray(int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]");
}

/**
 * 测试函数
 */
int main() {
    printf("=== 最大XOR对 ===\n\n");

    // 测试用例1：基本用例
    printf("1. 基本用例:\n");
    int testArrays[][12] = {
        {1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0},
        {8, 10, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int testSizes[] = {5, 3};

    for (int t = 0; t < 2; t++) {
        int *nums = testArrays[t];
        int n = testSizes[t];

        printf("  数组: ");
        printArray(nums, n);
        printf("\n");

        int brute = maxXorPairBruteForce(nums, n);
        int trie = maxXorPairTrie(nums, n);

        printf("  最大XOR (暴力): %d\n", brute);
        printf("  最大XOR (Trie): %d\n", trie);
        printf("  所有方法一致: %s\n\n",
               brute == trie ? "是" : "否");
    }

    // 测试用例2：XOR对的详细信息
    printf("2. XOR对的详细信息:\n");
    int nums2[] = {1, 2, 3, 4, 5};
    int n2 = 5;
    printf("  数组: ");
    printArray(nums2, n2);
    printf("\n");

    int maxXor = 0;
    int bestI = -1, bestJ = -1;
    for (int i = 0; i < n2; i++) {
        for (int j = i + 1; j < n2; j++) {
            int xorVal = nums2[i] ^ nums2[j];
            if (xorVal > maxXor) {
                maxXor = xorVal;
                bestI = i;
                bestJ = j;
            }
            if (xorVal >= 4) {  // 只显示较大的XOR值
                printf("    %d ^ %d = %d\n", nums2[i], nums2[j], xorVal);
            }
        }
    }
    printf("  最大XOR对: %d ^ %d = %d\n\n",
           nums2[bestI], nums2[bestJ], maxXor);

    // 测试用例3：边界情况
    printf("3. 边界情况:\n");
    struct {
        int arr[5];
        int size;
    } boundaryTests[] = {
        {{5, 0, 0, 0, 0}, 1},
        {{5, 3, 0, 0, 0}, 2},
        {{1, 0, 0, 0, 0}, 1},
        {{7, 7, 0, 0, 0}, 2},
    };

    for (int i = 0; i < 4; i++) {
        int *arr = boundaryTests[i].arr;
        int size = boundaryTests[i].size;
        printf("  数组: ");
        printArray(arr, size);
        printf(" -> 最大XOR: %d\n", maxXorPairTrie(arr, size));
    }
    printf("\n");

    // 测试用例4：较大数组
    printf("4. 较大数组测试:\n");
    int largeSize = 100;
    int *largeNums = (int *)malloc(largeSize * sizeof(int));
    for (int i = 0; i < largeSize; i++) {
        largeNums[i] = i + 1;
    }

    clock_t start = clock();
    int resultGreedy = maxXorPairGreedy(largeNums, largeSize);
    clock_t greedyTime = clock() - start;

    start = clock();
    int resultTrie = maxXorPairTrie(largeNums, largeSize);
    clock_t trieTime = clock() - start;

    printf("  数组大小: %d\n", largeSize);
    printf("  贪心法结果: %d, 耗时: %ld ms\n", resultGreedy, greedyTime);
    printf("  Trie法结果: %d, 耗时: %ld ms\n", resultTrie, trieTime);

    free(largeNums);

    return 0;
}
