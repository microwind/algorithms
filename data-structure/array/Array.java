public class Array {
  public static void main(String[] args) {
    // 定义一个包含5个整数的数组
    int[] arr = { 1, 2, 3, 4, 5 };

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

/*
 * jarry@MacBook-Pro array % java -version
 * openjdk version "23" 2024-09-17
 * OpenJDK Runtime Environment (build 23+37-2369)
 * OpenJDK 64-Bit Server VM (build 23+37-2369, mixed mode, sharing)
 * jarry@MacBook-Pro array % javac Array.java
 * jarry@MacBook-Pro array % java Array
 * Element at index 2: 3
 * Modified element at index 2: 10
 * 1 2 10 4 5
 */