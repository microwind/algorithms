import java.util.*;

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
public class MaxXorPair {
    /*
*
     * 暴力法：比较所有对
     *
     * @param nums 输入数组
     * @return 最大XOR值
*/
    public static int maxXorPairBruteForce(int[] nums) {
        int maxXor = 0;
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                int xorVal = nums[i] ^ nums[j];
                maxXor = Math.max(maxXor, xorVal);
            }
        }
        return maxXor;
    }

    /*
*
     * Trie树节点
*/
    static class TrieNode {
        TrieNode[] children = new TrieNode[2];  // 0和1两个分支
    }

    /*
*
     * 将数字的二进制表示插入Trie树
*/
    private static void insertTrie(TrieNode root, int num) {
        TrieNode node = root;
        // 从最高位到最低位遍历
        for (int i = 31; i >= 0; i--) {
            int bit = (num >>> i) & 1;
            if (node.children[bit] == null) {
                node.children[bit] = new TrieNode();
            }
            node = node.children[bit];
        }
    }

    /*
*
     * 找与给定数字最大XOR的数
     *
     * 贪心策略：对于每一位，尽可能走不同的路径以最大化XOR
*/
    private static int findMaxXor(TrieNode root, int num) {
        TrieNode node = root;
        int maxXor = 0;
        // 从最高位到最低位遍历
        for (int i = 31; i >= 0; i--) {
            int bit = (num >>> i) & 1;
            // 优先走相反的路径（这样XOR结果该位为1）
            int toggleBit = 1 - bit;

            if (node.children[toggleBit] != null) {
                maxXor |= (1 << i);
                node = node.children[toggleBit];
            } else if (node.children[bit] != null) {
                node = node.children[bit];
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
    public static int maxXorPairTrie(int[] nums) {
        if (nums.length < 2) return 0;

        TrieNode root = new TrieNode();

        // 构建Trie树
        for (int num : nums) {
            insertTrie(root, num);
        }

        int maxXor = 0;
        // 对每个数字，找与它最大XOR的数
        for (int num : nums) {
            int xorVal = findMaxXor(root, num);
            maxXor = Math.max(maxXor, xorVal);
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
    public static int maxXorPairGreedy(int[] nums) {
        if (nums.length < 2) return 0;

        int maxXor = 0;
        int prefixMask = 0;

        // 从最高位到最低位
        for (int i = 31; i >= 0; i--) {
            prefixMask |= (1 << i);

            // 收集所有数的前缀
            Set<Integer> prefixes = new HashSet<>();
            for (int num : nums) {
                prefixes.add(num & prefixMask);
            }

            // 尝试在当前位设为1
            int temp = maxXor | (1 << i);

            // 检查是否存在两个数的前缀异或为temp
            for (int prefix : prefixes) {
                if (prefixes.contains(temp ^ prefix)) {
                    maxXor = temp;
                    break;
                }
            }
        }

        return maxXor;
    }

    /*
*
     * 测试函数
*/
    public static void main(String[] args) {
        System.out.println("=== 最大XOR对 ===\n");

        // 测试用例1：基本用例
        System.out.println("1. 基本用例:");
        int[][] testArrays = {
                {1, 2, 3, 4, 5},
                {8, 10, 2},
                {14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70},
        };

        for (int[] nums : testArrays) {
            System.out.println("  数组: " + Arrays.toString(nums));

            int brute = maxXorPairBruteForce(nums);
            int trie = maxXorPairTrie(nums);
            int greedy = maxXorPairGreedy(nums);

            System.out.println("  最大XOR (暴力): " + brute);
            System.out.println("  最大XOR (Trie): " + trie);
            System.out.println("  最大XOR (贪心): " + greedy);
            System.out.println("  所有方法一致: " +
                    (brute == trie && trie == greedy ? "是" : "否"));
            System.out.println();
        }

        // 测试用例2：XOR对的详细信息
        System.out.println("2. XOR对的详细信息:");
        int[] nums2 = {1, 2, 3, 4, 5};
        System.out.println("  数组: " + Arrays.toString(nums2));

        int maxXor = 0;
        int bestI = -1, bestJ = -1;
        for (int i = 0; i < nums2.length; i++) {
            for (int j = i + 1; j < nums2.length; j++) {
                int xorVal = nums2[i] ^ nums2[j];
                if (xorVal > maxXor) {
                    maxXor = xorVal;
                    bestI = i;
                    bestJ = j;
                }
                if (xorVal >= 4) {  // 只显示较大的XOR值
                    System.out.printf("    %d ^ %d = %d\n",
                            nums2[i], nums2[j], xorVal);
                }
            }
        }
        System.out.printf("  最大XOR对: %d ^ %d = %d\n\n",
                nums2[bestI], nums2[bestJ], maxXor);

        // 测试用例3：边界情况
        System.out.println("3. 边界情况:");
        int[][] boundaryTests = {
                {5},
                {5, 3},
                {1},
                {7, 7},
        };

        for (int[] nums : boundaryTests) {
            System.out.println("  数组: " + Arrays.toString(nums) +
                    " -> 最大XOR: " + maxXorPairTrie(nums));
        }
        System.out.println();

        // 测试用例4：较大数组
        System.out.println("4. 较大数组测试:");
        int largeSize = 100;
        int[] largeNums = new int[largeSize];
        for (int i = 0; i < largeSize; i++) {
            largeNums[i] = i + 1;
        }

        long startTime = System.currentTimeMillis();
        int resultGreedy = maxXorPairGreedy(largeNums);
        long greedyTime = System.currentTimeMillis() - startTime;

        startTime = System.currentTimeMillis();
        int resultTrie = maxXorPairTrie(largeNums);
        long trieTime = System.currentTimeMillis() - startTime;

        System.out.println("  数组大小: " + largeSize);
        System.out.printf("  贪心法结果: %d, 耗时: %d ms\n",
                resultGreedy, greedyTime);
        System.out.printf("  Trie法结果: %d, 耗时: %d ms\n",
                resultTrie, trieTime);
    }
}
