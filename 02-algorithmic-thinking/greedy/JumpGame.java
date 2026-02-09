import java.util.*;

/**
 * Jump Game - Can reach the last index with greedy jumps
 *
 * Algorithm:
 * - Given an array where each element is the maximum jump length from that position
 * - Determine if you can reach the last index
 * - Greedy approach: track the maximum index we can reach so far
 * - If at any point current index exceeds max reachable, return false
 *
 * Time Complexity: O(n) - single pass through array
 * Space Complexity: O(1) - only using variables
 *
 * Key Insight:
 * At each position i, we can reach up to position i + nums[i].
 * We maintain the maximum position we can reach (maxReach).
 * If we encounter a position we can't reach, it's impossible.
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
    /**
     * Determine if we can reach the last index of the array
     *
     * @param nums Array where each element is max jump length from that position
     * @return true if we can reach the last index, false otherwise
     */
    static boolean canJump(int[] nums) {
        if (nums == null || nums.length <= 1) {
            return true;
        }

        int maxReach = 0;

        for (int i = 0; i < nums.length; i++) {
            // If current position is beyond what we can reach, return false
            if (i > maxReach) {
                return false;
            }

            // Update the maximum position we can reach
            maxReach = Math.max(maxReach, i + nums[i]);

            // Early termination: if we can reach the end, return true
            if (maxReach >= nums.length - 1) {
                return true;
            }
        }

        return maxReach >= nums.length - 1;
    }

    /**
     * Find the minimum number of jumps needed to reach the last index
     *
     * @param nums Array where each element is max jump length from that position
     * @return Minimum jumps, or -1 if unreachable
     */
    static int minJumps(int[] nums) {
        if (nums == null || nums.length <= 1) {
            return 0;
        }

        // Check if reachable
        int maxReach = 0;
        for (int i = 0; i < nums.length - 1; i++) {
            if (i > maxReach) {
                return -1;
            }
            maxReach = Math.max(maxReach, i + nums[i]);
        }

        if (maxReach < nums.length - 1) {
            return -1;
        }

        // Find minimum jumps using greedy
        int jumps = 0;
        int currentEnd = 0;
        int farthest = 0;

        for (int i = 0; i < nums.length - 1; i++) {
            farthest = Math.max(farthest, i + nums[i]);

            if (i == currentEnd) {
                jumps++;
                currentEnd = farthest;
            }
        }

        return jumps;
    }

    /**
     * Find a path from start to end
     *
     * @param nums Array where each element is max jump length from that position
     * @return List representing the path indices, or empty if unreachable
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

        // Check if reachable
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

        // Greedy path construction
        path.add(0);
        int currentPos = 0;

        while (currentPos < nums.length - 1) {
            int nextPos = currentPos;
            int maxNextReach = currentPos + nums[currentPos];

            for (int i = currentPos + 1; i <= currentPos + nums[currentPos] && i < nums.length; i++) {
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

    /**
     * Analyze a jump game problem comprehensively
     *
     * @param nums Array where each element is max jump length from that position
     * @return JumpGameAnalysis with complete results
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
