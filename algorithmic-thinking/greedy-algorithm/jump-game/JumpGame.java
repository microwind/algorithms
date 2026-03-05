import java.util.*;

/*
 *
 * 跳跃游戏 - 使用贪心判断能否到达最后一个下标
 *
 * 算法：
 * - 给定一个数组，每个元素表示从当前位置最多能跳的步数
 * - 判断是否可以从起点到达最后一个下标
 * - 贪心策略：维护当前能到达的最远位置 maxReach
 * - 一旦当前位置超过 maxReach，则说明不可达
 *
 * 时间复杂度：O(n)（单次遍历数组）
 * 空间复杂度：O(1)（仅使用常数个变量）
 *
 * 关键思想：
 * 在下标 i 处，最多可以到达 i + nums[i]。
 * 始终更新我们能到达的最远下标 maxReach。
 * 若出现某个下标无法到达，则整体不可达。
 */

class JumpGameAnalysis {
    boolean canReach;
    int minJumps;
    List<Integer> path;

    JumpGameAnalysis(boolean canReach, int minJumps, List<Integer> path) {
        this.canReach = canReach;
        this.minJumps = minJumps;
        this.path = path;
    }

    @Override
    public String toString() {
        return "Can reach: " + canReach + ", Min jumps: " + minJumps + ", Path: " + path;
    }
}

public class JumpGame {
    /*
     * 判断是否能到达数组的最后一个下标
     *
     * @param nums 每个元素为当前位置最大可跳跃步数的数组
     * @return 若能到达最后一个下标则为 true，否则为 false
     */
    static boolean canJump(int[] nums) {
        if (nums == null || nums.length <= 1) {
            return true;
        }

        int maxReach = 0;

        for (int i = 0; i < nums.length; i++) {
            // 如果当前位置超过了最远可达位置，则无法继续前进，返回 false
            if (i > maxReach) {
                return false;
            }

            // 更新当前能到达的最远位置
            maxReach = Math.max(maxReach, i + nums[i]);

            // 提前结束：一旦可以到达末尾，立刻返回 true
            if (maxReach >= nums.length - 1) {
                return true;
            }
        }

        return maxReach >= nums.length - 1;
    }

    /*
     * 计算到达最后一个下标所需的最少跳跃次数
     *
     * @param nums 每个元素为当前位置最大可跳跃步数的数组
     * @return 最少跳跃次数，若不可达则返回 -1
     */
    static int minJumps(int[] nums) {
        if (nums == null || nums.length <= 1) {
            return 0;
        }

        // 先检查是否可以到达终点
        int maxReach = 0;
        for (int i = 0; i < nums.length - 1; i++) {
            if (i > maxReach) {
                return -1;
            }
            maxReach = Math.max(maxReach, i + nums[i]);
        }
        // 如果当前能到达的最远位置小于数组长度减1，则返回-1
        if (maxReach < nums.length - 1) {
            return -1;
        }

        // 使用贪心策略计算最少跳跃次数
        int jumps = 0;
        int currentEnd = 0;
        int farthest = 0;
        // 遍历数组，计算最少跳跃次数
        for (int i = 0; i < nums.length - 1; i++) {
            // 更新当前能到达的最远位置
            farthest = Math.max(farthest, i + nums[i]);
            // 如果当前位置等于当前结束位置，则跳跃次数加1，并更新当前结束位置
            if (i == currentEnd) {
                jumps++;
                currentEnd = farthest;
            }
        }

        return jumps;
    }

    /*
     * 构造从起点到终点的一条跳跃路径
     *
     * @param nums 每个元素为当前位置最大可跳跃步数的数组
     * @return 路径下标序列，不可达则返回空列表
     */
    static List<Integer> jumpPath(int[] nums) {
        List<Integer> path = new ArrayList<>();

        if (nums == null || nums.length == 0) {
            return path;
        }

        if (nums.length == 1) {
            path.add(0);
            return path;
        }

        // 先检查是否可以到达终点
        int maxReach = 0;
        for (int i = 0; i < nums.length; i++) {
            if (i > maxReach) {
                return new ArrayList<>();
            }
            maxReach = Math.max(maxReach, i + nums[i]);
            if (maxReach >= nums.length - 1) {
                break;
            }
        }

        if (maxReach < nums.length - 1) {
            return new ArrayList<>();
        }

        // 贪心构造路径
        path.add(0);
        int currentPos = 0;
        // 遍历数组，构造跳跃路径
        while (currentPos < nums.length - 1) {
            // 初始化下一个位置为当前位置
            int nextPos = currentPos;
            // 初始化下一个位置能到达的最远位置为当前位置能到达的最远位置
            int maxNextReach = currentPos + nums[currentPos];
            // 遍历当前位置能到达的范围内，找到能到达的最远位置
            for (int i = currentPos + 1; i <= currentPos + nums[currentPos] && i < nums.length; i++) {
                // 如果当前位置能到达的最远位置小于当前位置能到达的最远位置，则更新当前位置能到达的最远位置
                if (i + nums[i] > maxNextReach) {
                    maxNextReach = i + nums[i];
                    nextPos = i;
                }
            }

            if (nextPos == currentPos) {
                return new ArrayList<>();
            }

            path.add(nextPos);
            currentPos = nextPos;
        }

        return path;
    }

    /*
     * 综合分析跳跃游戏问题
     *
     * @param nums 每个元素为当前位置最大可跳跃步数的数组
     * @return 包含完整分析结果的 JumpGameAnalysis 对象
     */
    static JumpGameAnalysis analyzeJumpGame(int[] nums) {
        boolean canReach = canJump(nums);
        int minJumpsCount = minJumps(nums);
        List<Integer> path = jumpPath(nums);

        return new JumpGameAnalysis(canReach, minJumpsCount, path);
    }

    static void testBasicReachable() {
        System.out.println("\n[Test 1] Reachable - should return true");

        int[] nums = {2, 3, 1, 1, 4};
        JumpGameAnalysis analysis = analyzeJumpGame(nums);

        System.out.println("Input: " + Arrays.toString(nums));
        System.out.println("Analysis: " + analysis);
    }

    static void testNotReachable() {
        System.out.println("\n[Test 2] Not reachable - should return false");

        int[] nums = {3, 2, 1, 0, 4};
        boolean result = canJump(nums);

        System.out.println("Input: " + Arrays.toString(nums));
        System.out.println("Can reach end: " + result);
    }

    static void testSingleElement() {
        System.out.println("\n[Test 3] Single element");

        int[] nums = {0};
        boolean result = canJump(nums);

        System.out.println("Input: " + Arrays.toString(nums));
        System.out.println("Can reach end: " + result);
    }

    static void testZeroJump() {
        System.out.println("\n[Test 4] All zeros except last");

        int[] nums = {0, 1};
        boolean result = canJump(nums);

        System.out.println("Input: " + Arrays.toString(nums));
        System.out.println("Can reach end: " + result);
    }

    static void testLargeJumps() {
        System.out.println("\n[Test 5] Large jumps available");

        int[] nums = {10, 0, 0, 0, 0};
        JumpGameAnalysis analysis = analyzeJumpGame(nums);

        System.out.println("Input: " + Arrays.toString(nums));
        System.out.println("Analysis: " + analysis);
    }

    static void testMultipleJumps() {
        System.out.println("\n[Test 6] Requires multiple jumps");

        int[] nums = {2, 3, 1, 1, 1};
        JumpGameAnalysis analysis = analyzeJumpGame(nums);

        System.out.println("Input: " + Arrays.toString(nums));
        System.out.println("Analysis: " + analysis);
    }

    static void testBlocked() {
        System.out.println("\n[Test 7] Blocked at second-to-last");

        int[] nums = {1, 0, 1, 0};
        boolean result = canJump(nums);

        System.out.println("Input: " + Arrays.toString(nums));
        System.out.println("Can reach end: " + result);
    }

    static void testTwoElement() {
        System.out.println("\n[Test 8] Two element array");

        int[] nums = {2, 3};
        JumpGameAnalysis analysis = analyzeJumpGame(nums);

        System.out.println("Input: " + Arrays.toString(nums));
        System.out.println("Analysis: " + analysis);
    }

    static void testDecreasing() {
        System.out.println("\n[Test 9] Large array with decreasing values");

        int[] nums = {5, 4, 3, 2, 1, 0};
        JumpGameAnalysis analysis = analyzeJumpGame(nums);

        System.out.println("Input: " + Arrays.toString(nums));
        System.out.println("Analysis: " + analysis);
    }

    static void testComplex() {
        System.out.println("\n[Test 10] Complex reachable scenario");

        int[] nums = {2, 5, 0, 0};
        JumpGameAnalysis analysis = analyzeJumpGame(nums);

        System.out.println("Input: " + Arrays.toString(nums));
        System.out.println("Analysis: " + analysis);
    }

    public static void main(String[] args) {
        System.out.println("==================================================");
        System.out.println("JUMP GAME - Greedy Approach (Java)");
        System.out.println("==================================================");

        testBasicReachable();
        testNotReachable();
        testSingleElement();
        testZeroJump();
        testLargeJumps();
        testMultipleJumps();
        testBlocked();
        testTwoElement();
        testDecreasing();
        testComplex();
    }
}
