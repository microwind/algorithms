
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

class MaximumSubarray {

  // 方式1、暴力求解法，逐个计算，一一对比
  public static int violenceMethod(int[] arr) {
    int maxSum = Integer.MIN_VALUE;
    for (int i = 0; i < arr.length; i++) {
      int currentSum = arr[i];
      if (currentSum > maxSum) {
        maxSum = currentSum;
      }
      System.out.println("第" + (i + 1) + "位组合：");
      System.out.println(arr[i]);

      String output = "" + arr[i];
      for (int j = i + 1; j < arr.length; j++) {
        currentSum += arr[j];
        output += " + " + arr[j];
        if (currentSum > maxSum) {
          maxSum = currentSum;
        }
        System.out.println(output + " = " + currentSum);
      }
    }
    System.out.println("violenceMethod->maxSum:" + maxSum);
    return maxSum;
  }

  // 方式2、动态规划方法，建立记录表存储每个位置的最大子数组和，比较找出最大值
  public static int dpMethod(int[] arr) {
    // 动态规划数组
    int[] dp = new int[arr.length];
    dp[0] = arr[0];

    // 计算每个位置的最大子数组和
    for (int i = 1; i < arr.length; i++) {
      dp[i] = Math.max(dp[i - 1] + arr[i], arr[i]);
    }

    // 找到最大值
    int maxSum = Integer.MIN_VALUE;
    for (int i = 0; i < dp.length; i++) {
      if (dp[i] > maxSum) {
        maxSum = dp[i];
      }
    }

    System.out.println("dpMethod->maxSum:" + maxSum);
    return maxSum;
  }

  // 方式3、Kadane算法，动态规划的升级，最简单直接
  public static int kadaneMethod(int[] arr) {
    int maxSum = arr[0];
    int currentSum = arr[0];
    for (int i = 1; i < arr.length; i++) {
      currentSum = Math.max(arr[i], currentSum + arr[i]);
      maxSum = Math.max(currentSum, maxSum);
    }
    System.out.println("kadaneMethod->maxSum:" + maxSum);
    return maxSum;
  }

  public static void main(String args[]) {
    long startTime;
    // test
    System.out.println("start:");
    startTime = System.currentTimeMillis();
    int[] arr = new int[] { -11, 10, -3, 1, -6, 13, -4 };
    MaximumSubarray.violenceMethod(arr);
    MaximumSubarray.dpMethod(arr);
    MaximumSubarray.kadaneMethod(arr);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

  }

}

/**
 * jarry@jarrys-MacBook-Pro factor % java --version
 * java 14.0.1
 * Java(TM) SE Runtime Environment (build 14.0.1+7)
 * Java HotSpot(TM) 64-Bit Server VM (build 14.0.1+7, mixed mode, sharing)
 * jarry@jarrys-MacBook-Pro array % javac MaximumSubarray.java
 * jarry@jarrys-MacBook-Pro array % java MaximumSubarray
 * start:
 * 第0位组合：
 * -11 + 10 = -1
 * -11 + 10 + -3 = -4
 * -11 + 10 + -3 + 1 = -3
 * -11 + 10 + -3 + 1 + -6 = -9
 * -11 + 10 + -3 + 1 + -6 + 13 = 4
 * -11 + 10 + -3 + 1 + -6 + 13 + -4 = 0
 * 第1位组合：
 * 10 + -3 = 7
 * 10 + -3 + 1 = 8
 * 10 + -3 + 1 + -6 = 2
 * 10 + -3 + 1 + -6 + 13 = 15
 * 10 + -3 + 1 + -6 + 13 + -4 = 11
 * 第2位组合：
 * -3 + 1 = -2
 * -3 + 1 + -6 = -8
 * -3 + 1 + -6 + 13 = 5
 * -3 + 1 + -6 + 13 + -4 = 1
 * 第3位组合：
 * 1 + -6 = -5
 * 1 + -6 + 13 = 8
 * 1 + -6 + 13 + -4 = 4
 * 第4位组合：
 * -6 + 13 = 7
 * -6 + 13 + -4 = 3
 * 第5位组合：
 * 13 + -4 = 9
 * 第6位组合：
 * violenceMethod->maxSum:15
 * dpMethod->maxSum:15
 * kadaneMethod->maxSum:15
 * 
 * time:0 ms.
 */