public class ReverseArray {
  // 反转数组的函数
  public static void reverseArray(int[] arr) {
      int n = arr.length;
      int temp;
      // 交换数组的前后元素
      for (int i = 0; i < n / 2; i++) {
          temp = arr[i];
          arr[i] = arr[n - i - 1];
          arr[n - i - 1] = temp;
      }
  }

  public static void main(String[] args) {
      int[] arr = {1, 2, 3, 4, 5}; // 初始化数组
      reverseArray(arr); // 调用反转函数
      // 输出反转后的数组
      for (int i : arr) {
          System.out.print(i + " ");
      }
  }
}