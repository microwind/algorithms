public class ArrayExample {
  public static void main(String[] args) {
      // 定义一个包含5个整数的数组
      int[] arr = {1, 2, 3, 4, 5};

      // 访问数组元素
      System.out.println("Element at index 2: " + arr[2]);

      // 修改数组元素
      arr[2] = 10;
      System.out.println("Modified element at index 2: " + arr[2]);

      // 遍历数组
      for (int i : arr) {
          System.out.print(i + " ");
      }
      System.out.println();
  }
}
