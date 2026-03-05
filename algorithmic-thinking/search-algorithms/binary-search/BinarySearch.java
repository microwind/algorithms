package search.binary;

/**
 * 二分搜索（Binary Search）- Java 版本
 *
 * 要求数组有序（升序），通过不断折半缩小搜索区间。
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1) 迭代；O(log n) 递归
 */
public class BinarySearch {

    // 迭代版二分搜索
    public static int binarySearchIterative(int[] arr, int target) {
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

    // 递归版二分搜索
    public static int binarySearchRecursive(int[] arr, int target, int left, int right) {
        if (left > right) return -1;
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) return binarySearchRecursive(arr, target, mid + 1, right);
        return binarySearchRecursive(arr, target, left, mid - 1);
    }

    // 查找第一个出现的位置（左边界）
    public static int findFirstOccurrence(int[] arr, int target) {
        int left = 0, right = arr.length - 1, result = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                result = mid;
                right = mid - 1;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return result;
    }

    // 查找最后一个出现的位置（右边界）
    public static int findLastOccurrence(int[] arr, int target) {
        int left = 0, right = arr.length - 1, result = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                result = mid;
                left = mid + 1;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return result;
    }

    // 查找插入位置（lower bound）
    public static int findInsertPosition(int[] arr, int target) {
        int left = 0, right = arr.length;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

    public static void main(String[] args) {
        System.out.println("========== Binary Search (Java) ==========");

        int[] arr = {1, 3, 5, 7, 9, 11, 13};
        System.out.println("数组: " + java.util.Arrays.toString(arr));
        System.out.println("迭代查找 7 -> " + binarySearchIterative(arr, 7));
        System.out.println("递归查找 7 -> " + binarySearchRecursive(arr, 7, 0, arr.length - 1));

        int[] arr2 = {1, 3, 5, 5, 5, 7, 9};
        System.out.println("\n数组2: " + java.util.Arrays.toString(arr2));
        System.out.println("第一个 5 的位置 -> " + findFirstOccurrence(arr2, 5));
        System.out.println("最后一个 5 的位置 -> " + findLastOccurrence(arr2, 5));
        System.out.println("插入 6 的位置 -> " + findInsertPosition(arr2, 6));
    }
}

