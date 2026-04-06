/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 分治算法示例 - 递归分解数组
 * 
 * 算法思想：将数组不断二分，直到每个子数组只有一个元素
 * 
 * 学习重点：理解分治策略的递归实现
 */
import java.util.Arrays;

public class Divide {
    private static int step = 0;

    /**
     * 递归分解数组函数
     * 时间复杂度: O(n log n)，空间复杂度: O(log n)
     * @param arr 待分解的数组
     * @return 分解后的数组
     */
    public static int[] divide(int[] arr) {
        System.out.println("start: " + Arrays.toString(arr));
        
        // 基本情况：数组长度小于2时直接返回
        if (arr.length < 2) {
            return arr;
        }

        // 计算中间索引，将数组一分为二
        int mid = arr.length / 2;
        
        // 分别复制左半部分和右半部分的数组
        int[] left = Arrays.copyOfRange(arr, 0, mid);
        int[] right = Arrays.copyOfRange(arr, mid, arr.length);

        // 递归分解左半部分和右半部分的数组
        left = divide(left);
        right = divide(right);

        // 合并结果数组
        step += 1;
        System.out.println("after: " + step + " -> " + Arrays.toString(arr) + " " + Arrays.toString(left) + " "
                + Arrays.toString(right));

        int[] result = new int[arr.length];
        System.arraycopy(left, 0, result, 0, left.length);
        System.arraycopy(right, 0, result, left.length, right.length);
        return result;
    }

    /**
     * 主函数 - 测试分治算法
     */
    public static void main(String[] args) {
        int[] arr = { 3, 1, 2, 5, 6, 4 };
        divide(arr);
    }
}

/*打印结果
jarry@MacBook-Pro recursion % javac Divide.java
jarry@MacBook-Pro recursion % java Divide
* start: [3, 1, 2, 5, 6, 4]
* start: [3, 1, 2]
* start: [3]
* start: [1, 2]
* start: [1]
* start: [2]
* start: [5, 6, 4]
* start: [5]
* start: [6, 4]
* start: [6]
* start: [4]
* after: 3 -> [3, 1, 2] [3] [1, 2]
* after: 2 -> [3, 1, 2] [3] [1, 2]
* after: 1 -> [1]
* after: 5 -> [3, 1, 2, 5, 6, 4] [3, 1, 2] [5, 6, 4]
* after: 6 -> [5, 6, 4] [5] [6, 4]
* after: 4 -> [5, 6, 4] [5] [6, 4]
*/
