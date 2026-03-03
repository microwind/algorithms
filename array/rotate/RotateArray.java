public class RotateArray {
  // 旋转数组
  public static void rotateArray(int[] arr, int d) {
      int n = arr.length;
      int[] temp = new int[d];
      for (int i = 0; i < d; i++) {
          temp[i] = arr[i];
      }
      for (int i = 0; i < n - d; i++) {
          arr[i] = arr[i + d];
      }
      for (int i = 0; i < d; i++) {
          arr[n - d + i] = temp[i];
      }
  }

  public static void main(String[] args) {
      int[] arr = {1, 2, 3, 4, 5, 6, 7};
      int d = 2;
      rotateArray(arr, d);
      System.out.println("Rotated array:");
      for (int i : arr) {
          System.out.print(i + " ");
      }
  }
}

/**
jarry@jarrys-MacBook-Pro rotate % javac RotateArray.java 
jarry@jarrys-MacBook-Pro rotate % java RotateArray 
Rotated array:
3 4 5 6 7 1 2 %  
 */