package search.linear;

/**
 * 线性搜索（Linear Search）- Java 版本
 *
 * 从头到尾依次比较，最朴素的查找算法。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */
public class LinearSearch {

    /**
     * 查找第一个等于 target 的元素下标
     *
     * @param arr    待搜索数组
     * @param target 目标值
     * @return 下标，未找到返回 -1
     */
    public static int linearSearch(int[] arr, int target) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) {
                return i;
            }
        }
        return -1;
    }

    /**
     * 查找所有等于 target 的元素下标
     *
     * @param arr    数组
     * @param target 目标值
     * @return 所有匹配下标组成的数组
     */
    public static int[] linearSearchAll(int[] arr, int target) {
        java.util.List<Integer> list = new java.util.ArrayList<>();
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) {
                list.add(i);
            }
        }
        return list.stream().mapToInt(Integer::intValue).toArray();
    }

    public static void main(String[] args) {
        System.out.println("========== Linear Search (Java) ==========");
        int[] arr = {5, 2, 8, 1, 9, 3, 7};
        System.out.println("数组: " + java.util.Arrays.toString(arr));
        System.out.println("查找 8 -> " + linearSearch(arr, 8));
        System.out.println("查找 10 -> " + linearSearch(arr, 10));

        int[] arr2 = {1, 2, 3, 2, 4, 2};
        System.out.println("数组2: " + java.util.Arrays.toString(arr2));
        System.out.println("查找所有 2 -> " + java.util.Arrays.toString(linearSearchAll(arr2, 2)));
    }
}

