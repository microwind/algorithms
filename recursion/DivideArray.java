import java.util.Arrays;

public class DivideArray {
    private static int step = 0;

    // 递归分解数组，最小粒度为2个
    public static int[] divide(int[] arr) {
        System.out.println("start: " + Arrays.toString(arr));
        if (arr.length < 2) {
            return arr;
        }

        int mid = arr.length / 2;
        int[] left = Arrays.copyOfRange(arr, 0, mid);
        int[] right = Arrays.copyOfRange(arr, mid, arr.length);

        left = divide(left);
        right = divide(right);

        step += 1;
        System.out.println("after: " + step + " -> " + Arrays.toString(arr) + " " + Arrays.toString(left) + " "
                + Arrays.toString(right));

        int[] result = new int[arr.length];
        System.arraycopy(left, 0, result, 0, left.length);
        System.arraycopy(right, 0, result, left.length, right.length);

        return result;
    }

    public static void main(String[] args) {
        int[] arr = { 3, 1, 2, 5, 6, 4 };
        divide(arr);
    }
}
/*
 * jarry@MacBook-Pro recursion % javac DivideArray.java
 * jarry@MacBook-Pro recursion % java DivideArray
 * start: [3, 1, 2, 5, 6, 4]
 * start: [3, 1, 2]
 * start: [3]
 * start: [1, 2]
 * start: [1]
 * start: [2]
 * after: 1 -> [1, 2] [1] [2]
 * after: 2 -> [3, 1, 2] [3] [1, 2]
 * start: [5, 6, 4]
 * start: [5]
 * start: [6, 4]
 * start: [6]
 * start: [4]
 * after: 3 -> [6, 4] [6] [4]
 * after: 4 -> [5, 6, 4] [5] [6, 4]
 * after: 5 -> [3, 1, 2, 5, 6, 4] [3, 1, 2] [5, 6, 4]
 */