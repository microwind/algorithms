import java.util.Arrays;

/**
 * 二分查找 - 分治法的查询应用
 *
 * 前置条件：数组必须已排序
 *
 * 时间复杂度: O(log n)
 * 空间复杂度: O(1) 迭代版本，O(log n) 递归版本
 */
public class BinarySearch {
    /**
     * 二分查找（迭代版本）
     */
    public static int binarySearch(int[] arr, int target) {
        int left = 0, right = arr.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }

    /**
     * 二分查找（递归版本）
     */
    public static int binarySearchRecursive(int[] arr, int left, int right, int target) {
        if (left > right) {
            return -1;
        }

        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            return binarySearchRecursive(arr, mid + 1, right, target);
        } else {
            return binarySearchRecursive(arr, left, mid - 1, target);
        }
    }

    /**
     * 查找第一个 >= target 的元素位置（左边界）
     */
    public static int binarySearchLeft(int[] arr, int target) {
        int left = 0, right = arr.length - 1;
        int result = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] >= target) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return result;
    }

    /**
     * 测试函数
     */
    public static void main(String[] args) {
        System.out.println("=== 二分查找 ===\n");

        int[] arr = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
        System.out.print("数组: ");
        System.out.println(Arrays.toString(arr));
        System.out.println();

        // 测试用例1：迭代版本
        System.out.println("1. 迭代版本:");
        System.out.println("  查找 7: " + binarySearch(arr, 7));
        System.out.println("  查找 20: " + binarySearch(arr, 20));
        System.out.println();

        // 测试用例2：递归版本
        System.out.println("2. 递归版本:");
        System.out.println("  查找 9: " + binarySearchRecursive(arr, 0, arr.length - 1, 9));
        System.out.println("  查找 2: " + binarySearchRecursive(arr, 0, arr.length - 1, 2));
        System.out.println();

        // 测试用例3：查找边界
        int[] arrDup = {1, 2, 2, 2, 3, 4, 5, 5, 5, 6};
        System.out.print("3. 查找边界 (数组: ");
        System.out.print(Arrays.toString(arrDup));
        System.out.println("):");
        System.out.println("  左边界 2: " + binarySearchLeft(arrDup, 2));
        System.out.println("  左边界 5: " + binarySearchLeft(arrDup, 5));
        System.out.println();

        // 测试用例4：查找不存在的元素
        System.out.println("4. 查找不存在的元素:");
        System.out.println("  查找 100: " + binarySearch(arr, 100));
        System.out.println("  查找 0: " + binarySearch(arr, 0));
    }
}
