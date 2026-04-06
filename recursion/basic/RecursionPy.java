import java.util.HashMap;
import java.util.Map;

/**
 * 递归算法示例集合（基于Python版本）
 * 包含阶乘、斐波那契、汉诺塔、二分查找、数组求和、字符串反转等示例
 */
public class RecursionPy {
    
    // 1. 阶乘 (Factorial)
    // 时间复杂度: O(n), 空间复杂度: O(n)（递归栈深度）
    public static int factorial(int n) {
        /* 计算 n 的阶乘 */
        if (n <= 1) {
            return 1;
        }
        return n * factorial(n - 1);
    }
    
    // 2. 斐波那契数列
    // 普通递归: 时间复杂度 O(2^n)，空间复杂度 O(n)
    public static int fibonacci(int n) {
        /* 计算斐波那契数列第 n 项（普通递归） */
        if (n <= 1) {
            return n;
        }
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
    
    // 优化版本（记忆化）
    public static int fibonacciMemo(int n, Map<Integer, Integer> memo) {
        /* 计算斐波那契数列第 n 项（带记忆化） */
        if (memo.containsKey(n)) {
            return memo.get(n);
        }
        
        if (n <= 1) {
            memo.put(n, n);
        } else {
            memo.put(n, fibonacciMemo(n - 1, memo) + fibonacciMemo(n - 2, memo));
        }
        
        return memo.get(n);
    }
    
    public static int fibonacciMemo(int n) {
        return fibonacciMemo(n, new HashMap<>());
    }
    
    // 3. 汉诺塔问题
    // 时间复杂度: O(2^n - 1)，空间复杂度: O(n)
    public static void hanoi(int n, String source, String target, String auxiliary) {
        /*
         * 解决汉诺塔问题
         * 将 n 个盘子从 source 柱移动到 target 柱
         */
        if (n == 1) {
            System.out.println("Move disk 1 from " + source + " to " + target);
            return;
        }
        
        // 将 n-1 个盘子从 source 移动到 auxiliary
        hanoi(n - 1, source, auxiliary, target);
        
        // 将最后一个盘子从 source 移动到 target
        System.out.println("Move disk " + n + " from " + source + " to " + target);
        
        // 将 n-1 个盘子从 auxiliary 移动到 target
        hanoi(n - 1, auxiliary, target, source);
    }
    
    // 4. 二分查找（递归版本）
    // 时间复杂度: O(log n)，空间复杂度: O(log n)
    public static int binarySearch(int[] arr, int target, int low, int high) {
        /* 在排序数组中递归查找目标值 */
        if (low > high) {
            return -1;
        }
        
        int mid = (low + high) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] > target) {
            return binarySearch(arr, target, low, mid - 1);
        } else {
            return binarySearch(arr, target, mid + 1, high);
        }
    }
    
    // 5. 数组求和
    // 时间复杂度: O(n)，空间复杂度: O(n)
    public static int arraySum(int[] arr, int index) {
        /* 递归计算数组元素和 */
        if (index >= arr.length) {
            return 0;
        }
        return arr[index] + arraySum(arr, index + 1);
    }
    
    public static int arraySum(int[] arr) {
        return arraySum(arr, 0);
    }
    
    // 6. 反转字符串
    // 时间复杂度: O(n)，空间复杂度: O(n)
    public static String reverseString(String s) {
        /* 递归反转字符串 */
        if (s.isEmpty()) {
            return "";
        }
        return reverseString(s.substring(1)) + s.charAt(0);
    }
    
    public static void main(String[] args) {
        System.out.println("=== 递归算法测试 ===\n");
        
        // 测试阶乘
        System.out.println("1. 阶乘");
        System.out.println("5! = " + factorial(5));
        
        // 测试斐波那契
        System.out.println("\n2. 斐波那契数列");
        System.out.println("fib(10) = " + fibonacci(10));
        System.out.println("fib(10) with memo = " + fibonacciMemo(10));
        
        // 测试汉诺塔
        System.out.println("\n3. 汉诺塔问题 (n=3)");
        hanoi(3, "A", "C", "B");
        
        // 测试二分查找
        System.out.println("\n4. 二分查找");
        int[] arr = {1, 3, 5, 7, 9, 11, 13};
        System.out.println("查找 7: 索引 = " + binarySearch(arr, 7, 0, arr.length - 1));
        
        // 测试数组求和
        System.out.println("\n5. 数组求和");
        int[] sumArr = {1, 2, 3, 4, 5};
        System.out.println("sum([1,2,3,4,5]) = " + arraySum(sumArr));
        
        // 测试字符串反转
        System.out.println("\n6. 字符串反转");
        System.out.println("reverse('hello') = " + reverseString("hello"));
    }
}
