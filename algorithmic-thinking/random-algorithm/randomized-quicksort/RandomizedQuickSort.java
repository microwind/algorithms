package randomalgorithm.randomizedquicksort;

import java.util.Arrays;
import java.util.Random;

/**
 * 随机快速排序（Randomized QuickSort）- Java 版本
 *
 * 通过在每次分区时随机选择枢轴，避免恶意输入导致的最坏 O(n^2) 情况。
 *
 * 平均时间复杂度：O(n log n)
 * 最坏时间复杂度：O(n^2)
 * 空间复杂度：O(log n)（递归栈）
 */
public class RandomizedQuickSort {

    private static final Random RANDOM = new Random();

    /**
     * 原地分区：随机选择枢轴，将数组划分为 <= pivot 与 > pivot 两部分
     *
     * @param arr   待分区数组
     * @param left  左边界（含）
     * @param right 右边界（含）
     * @return 枢轴最终所在下标
     */
    private static int randomizedPartition(int[] arr, int left, int right) {
        int randomIdx = left + RANDOM.nextInt(right - left + 1);
        // 将随机枢轴交换到右端
        int tmp = arr[randomIdx];
        arr[randomIdx] = arr[right];
        arr[right] = tmp;

        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (arr[j] <= pivot) {
                i++;
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }

        int t = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = t;
        return i + 1;
    }

    /**
     * 随机快速排序 - 原地排序
     */
    public static void randomizedQuickSort(int[] arr, int left, int right) {
        if (left < right) {
            int pivotIdx = randomizedPartition(arr, left, right);
            randomizedQuickSort(arr, left, pivotIdx - 1);
            randomizedQuickSort(arr, pivotIdx + 1, right);
        }
    }

    /**
     * 随机选择（QuickSelect）- 平均 O(n) 找到第 k 小元素
     */
    public static int randomizedSelect(int[] arr, int left, int right, int k) {
        if (left == right) {
            return arr[left];
        }
        int pivotIdx = randomizedPartition(arr, left, right);
        if (k == pivotIdx) {
            return arr[k];
        } else if (k < pivotIdx) {
            return randomizedSelect(arr, left, pivotIdx - 1, k);
        } else {
            return randomizedSelect(arr, pivotIdx + 1, right, k);
        }
    }

    public static void main(String[] args) {
        System.out.println("========== Randomized QuickSort (Java) ==========");

        int[] arr = {5, 2, 8, 1, 9, 3, 7, 4, 6};
        System.out.println("原数组: " + Arrays.toString(arr));
        int[] copy = Arrays.copyOf(arr, arr.length);
        randomizedQuickSort(copy, 0, copy.length - 1);
        System.out.println("排序后: " + Arrays.toString(copy));

        int[] arr2 = Arrays.copyOf(arr, arr.length);
        int k = 3;
        int kth = randomizedSelect(arr2, 0, arr2.length - 1, k);
        System.out.println("第 " + k + " 小元素: " + kth);
    }
}

