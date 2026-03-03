import java.util.Arrays;

/*
*
 * 快速排序 - 分治法的高效应用
 *
 * 分治法三个步骤：
 * 1. 分解：选择一个基准元素，将数组分为三部分
 * 2. 求解：递归对左右两部分进行快速排序
 * 3. 合并：基准元素已经在最终位置，无需额外合并
 *
 * 时间复杂度: O(n log n) 平均，O(n²) 最坏
 * 空间复杂度: O(log n)
*/
public class QuickSort {
    /*
*
     * 分割函数：使用 Hoare 分割方案
*/
    private static int partition(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                // 交换 arr[i] 和 arr[j]
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        // 交换 arr[i+1] 和 arr[high]
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        return i + 1;
    }

    /*
*
     * 递归进行快速排序
*/
    private static void quickSortHelper(int[] arr, int low, int high) {
        if (low < high) {
            // 分割
            int pi = partition(arr, low, high);

            // 递归排序左右两部分
            quickSortHelper(arr, low, pi - 1);
            quickSortHelper(arr, pi + 1, high);
        }
    }

    /*
*
     * 快速排序入口函数
*/
    public static void quickSort(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return;
        }
        quickSortHelper(arr, 0, arr.length - 1);
    }

    /*
*
     * 测试函数
*/
    public static void main(String[] args) {
        System.out.println("=== 快速排序 ===\n");

        // 测试用例1：随机数组
        int[] arr1 = {64, 34, 25, 12, 22, 11, 90};
        System.out.print("原数组: ");
        System.out.println(Arrays.toString(arr1));
        quickSort(arr1);
        System.out.print("排序后: ");
        System.out.println(Arrays.toString(arr1));
        System.out.println();

        // 测试用例2：已排序数组
        int[] arr2 = {1, 2, 3, 4, 5};
        System.out.print("已排序数组: ");
        System.out.println(Arrays.toString(arr2));
        quickSort(arr2);
        System.out.print("排序后: ");
        System.out.println(Arrays.toString(arr2));
        System.out.println();

        // 测试用例3：反序数组
        int[] arr3 = {5, 4, 3, 2, 1};
        System.out.print("反序数组: ");
        System.out.println(Arrays.toString(arr3));
        quickSort(arr3);
        System.out.print("排序后: ");
        System.out.println(Arrays.toString(arr3));
        System.out.println();

        // 测试用例4：包含重复元素
        int[] arr4 = {3, 1, 4, 1, 5, 9, 2, 6};
        System.out.print("包含重复: ");
        System.out.println(Arrays.toString(arr4));
        quickSort(arr4);
        System.out.print("排序后: ");
        System.out.println(Arrays.toString(arr4));
    }
}
