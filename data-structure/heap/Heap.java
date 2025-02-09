public class Heap {

  static final int MAX_SIZE = 100;

  /*
   * 大顶堆：根节点始终为堆中的最大值。
   * 6
   * / \
   * 5 4
   * / \ /
   * 3 2 1
   */
  // 调整堆的结构，确保父节点大于或等于其子节点，符合大顶堆的性质
  public static void heapifyMax(int[] arr, int n, int i) {
    int largest = i; // 假设当前节点 i 为最大节点
    int left = 2 * i + 1; // 左子节点的索引
    int right = 2 * i + 2; // 右子节点的索引

    // 如果左子节点存在且大于当前最大值
    if (left < n && arr[left] > arr[largest]) {
      largest = left; // 更新最大值索引
    }

    // 如果右子节点存在且大于当前最大值
    if (right < n && arr[right] > arr[largest]) {
      largest = right; // 更新最大值索引
    }

    // 如果最大值不再是原节点 i，交换节点 i 和最大值节点
    if (largest != i) {
      int temp = arr[i];
      arr[i] = arr[largest];
      arr[largest] = temp;

      // 递归调整交换后的子树，确保其也符合大顶堆性质
      heapifyMax(arr, n, largest);
    }
  }

  /*
   * 小顶堆：根节点始终为堆中的最小值。
   * 1
   * / \
   * 2 4
   * / \ /
   * 5 3 6
   */
  // 调整堆的结构，确保父节点小于或等于其子节点，符合小顶堆的性质
  public static void heapifyMin(int[] arr, int n, int i) {
    int smallest = i; // 假设当前节点 i 为最小节点
    int left = 2 * i + 1; // 左子节点的索引
    int right = 2 * i + 2; // 右子节点的索引

    // 如果左子节点存在且小于当前最小值
    if (left < n && arr[left] < arr[smallest]) {
      smallest = left; // 更新最小值索引
    }

    // 如果右子节点存在且小于当前最小值
    if (right < n && arr[right] < arr[smallest]) {
      smallest = right; // 更新最小值索引
    }

    // 如果最小值不再是原节点 i，交换节点 i 和最小值节点
    if (smallest != i) {
      int temp = arr[i];
      arr[i] = arr[smallest];
      arr[smallest] = temp;

      // 递归调整交换后的子树，确保其也符合小顶堆性质
      heapifyMin(arr, n, smallest);
    }
  }

  // 构建大顶堆
  public static void buildMaxHeap(int[] arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
      heapifyMax(arr, n, i);
    }
  }

  // 构建小顶堆
  public static void buildMinHeap(int[] arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
      heapifyMin(arr, n, i);
    }
  }

  // 打印堆
  public static void printHeap(int[] arr, int n) {
    for (int i = 0; i < n; i++) {
      System.out.print(arr[i] + " ");
    }
    System.out.println();
  }

  public static void main(String[] args) {
    int[] maxHeap = { 3, 1, 6, 5, 2, 4 };
    int[] minHeap = { 3, 1, 6, 5, 2, 4 };

    int maxN = maxHeap.length;
    int minN = minHeap.length;

    // 构建大顶堆
    buildMaxHeap(maxHeap, maxN);
    System.out.print("Max heap: ");
    printHeap(maxHeap, maxN);

    // 构建小顶堆
    buildMinHeap(minHeap, minN);
    System.out.print("Min heap: ");
    printHeap(minHeap, minN);
  }
}

/*
 * jarry@MacBook-Pro heap % javac Heap.java
 * jarry@MacBook-Pro heap % java Heap
 * Max heap: 6 5 4 1 2 3
 * Min heap: 1 2 4 5 3 6
 */