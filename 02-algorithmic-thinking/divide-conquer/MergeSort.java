import java.util.Arrays;

/**
 * 归并排序 - 分治法的典型应用
 *
 * 分治法三个步骤：
 * 1. 分解：将数组分成两个子数组
 * 2. 求解：递归对子数组进行归并排序
 * 3. 合并：将两个已排序的子数组合并
 *
 * 时间复杂度: O(n log n)
 * 空间复杂度: O(n)
 */
public class MergeSort {
    /**
     * 合并两个已排序的数组
     */
    private static void merge(int[] arr, int left, int mid, int right) {
        // 创建临时数组
        int[] temp = new int[right - left + 1];

        int i = left;
        int j = mid + 1;
        int k = 0;

        // 比较两个子数组的元素
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }

        // 复制左侧剩余元素
        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        // 复制右侧剩余元素
        while (j <= right) {
            temp[k++] = arr[j++];
        }

        // 将临时数组复制回原数组
        for (i = left, k = 0; i <= right; i++, k++) {
            arr[i] = temp[k];
        }
    }

    /**
     * 递归进行归并排序
     */
    private static void mergeSortHelper(int[] arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            // 递归排序左半部分
            mergeSortHelper(arr, left, mid);

            // 递归排序右半部分
            mergeSortHelper(arr, mid + 1, right);

            // 合并两个已排序的部分
            merge(arr, left, mid, right);
        }
    }

    /**
     * 归并排序入口函数
     */
    public static void mergeSort(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return;
        }
        mergeSortHelper(arr, 0, arr.length - 1);
    }

    /**
     * 测试函数
     */
    public static void main(String[] args) {
        System.out.println("=== 归并排序 ===\n");

        // 测试用例1：随机数组
        int[] arr1 = {64, 34, 25, 12, 22, 11, 90};
        System.out.print("原数组: ");
        System.out.println(Arrays.toString(arr1));
        mergeSort(arr1);
        System.out.print("排序后: ");
        System.out.println(Arrays.toString(arr1));
        System.out.println();

        // 测试用例2：已排序数组
        int[] arr2 = {1, 2, 3, 4, 5};
        System.out.print("已排序数组: ");
        System.out.println(Arrays.toString(arr2));
        mergeSort(arr2);
        System.out.print("排序后: ");
        System.out.println(Arrays.toString(arr2));
        System.out.println();

        // 测试用例3：反序数组
        int[] arr3 = {5, 4, 3, 2, 1};
        System.out.print("反序数组: ");
        System.out.println(Arrays.toString(arr3));
        mergeSort(arr3);
        System.out.print("排序后: ");
        System.out.println(Arrays.toString(arr3));
        System.out.println();

        // 测试用例4：包含重复元素
        int[] arr4 = {3, 1, 4, 1, 5, 9, 2, 6};
        System.out.print("包含重复: ");
        System.out.println(Arrays.toString(arr4));
        mergeSort(arr4);
        System.out.print("排序后: ");
        System.out.println(Arrays.toString(arr4));
    }
}
