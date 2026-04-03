/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 堆排序算法实现
 * 提供五种不同的实现方式，适合不同场景和性能需求
 */

import java.util.Arrays;

public class HeapSort {

    /**
     * 打印数组内容的辅助函数
     */
    private static void printArray(int[] arr, String label) {
        System.out.println(label + ": " + Arrays.toString(arr));
    }

    /**
     * 打印堆的树形结构
     */
    private static void printHeapTree(int[] arr, String title) {
        if (arr.length < 7) {
            System.out.println(title + ": " + Arrays.toString(arr));
            return;
        }
        
        System.out.println(title);
        System.out.println("              " + arr[0] + "(0)");
        System.out.println("          /         \\");
        System.out.println("        " + arr[1] + "(1)        " + arr[2] + "(2)");
        System.out.println("       /    \\      /     \\");
        System.out.println("   " + arr[3] + "(3)  " + arr[4] + "(4)  " + arr[5] + "(5)  " + arr[6] + "(6)");
        System.out.println();
    }

    /**
     * 性能测试辅助函数
     */
    private static void performanceTest(SortFunction sortFunc, int[] arr, String name) {
        // 创建数组副本，避免修改原数组
        int[] testArr = Arrays.copyOf(arr, arr.length);
        printArray(testArr, name + "原始数组");
        
        // 开始计时
        long startTime = System.nanoTime();
        sortFunc.sort(testArr);
        long endTime = System.nanoTime();
        
        System.out.println(name + ": " + String.format("%.3f", (endTime - startTime) / 1_000_000.0) + "ms");
        printArray(testArr, name + "排序结果");
        System.out.println(); // 空行分隔
    }

    // ==================== 主程序：算法演示和性能测试 ====================
    
    // 测试数据：
    private static final int[] testData = {7, 11, 9, 10, 12, 13, 8};

    /**
     * 带步骤打印的堆化函数
     */
    private static void heapifyWithSteps(int[] arr, int n, int i, int parentStep) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        // 第一步：比较左子节点
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        
        // 第二步：比较右子节点
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        
        // 第三步：如果需要交换，执行交换并递归堆化
        if (largest != i) {
            // 关键点：交换父子节点
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            
            int newLeft = 2 * largest + 1;
            int newRight = 2 * largest + 2;
            int maxIdx = largest;
            
            if (newLeft < n && arr[newLeft] > arr[maxIdx]) maxIdx = newLeft;
            if (newRight < n && arr[newRight] > arr[maxIdx]) maxIdx = newRight;
            
            System.out.println(parentStep + ".1 maxHeapify: idx= " + largest + " left= " + newLeft + " right= " + newRight + " max= " + maxIdx + " size= " + n);
            printHeapTree(arr, "");
            
            heapifyWithSteps(arr, n, largest, parentStep);
        }
    }

    /**
     * 堆排序基础版本 - 最大堆
     * 
     * 算法原理：
     * 1. 构建最大堆：将无序数组构建成最大堆结构
     * 2. 交换堆顶：将堆顶元素（最大值）与堆尾元素交换
     * 3. 调整堆：对剩余元素重新堆化，保持堆结构
     * 4. 重复步骤2-3，直到整个数组有序
     * 
     * 生活类比：就像在队伍中挑选最高的人站到最后，
     * 然后在剩下的人中再挑选最高的站到倒数第二个位置，依此类推
     * 
     * 时间复杂度：O(n log n) - 构建堆O(n)，每次堆化O(log n)
     * 空间复杂度：O(1) - 原地排序，不需要额外空间
     * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
     */
    public static void heapSort1(int[] arr) {
        System.out.println("heapSort1 max-heap:");
        int n = arr.length;
        
        printHeapTree(arr, "oringal array:");
        
        // 第一步：构建最大堆
        System.out.println("父节点步骤");
        int stepCount = 1;
        // 关键点：从最后一个非叶子节点开始堆化
        for (int i = n / 2 - 1; i >= 0; i--) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int maxIdx = i;
            
            if (left < n && arr[left] > arr[maxIdx]) maxIdx = left;
            if (right < n && arr[right] > arr[maxIdx]) maxIdx = right;
            
            System.out.println(stepCount + ". maxHeapify: idx= " + i + " left= " + left + " right= " + right + " max= " + maxIdx + " size= " + n);
            stepCount++;
            
            if (maxIdx != i) {
                int temp = arr[i];
                arr[i] = arr[maxIdx];
                arr[maxIdx] = temp;
                printHeapTree(arr, "");
                
                // 递归堆化
                heapifyWithSteps(arr, n, maxIdx, stepCount - 1);
                stepCount++;
            } else {
                stepCount++;
            }
        }
        
        // 第二步：逐个取出堆顶元素并排序
        System.out.println("子节点堆排序:");
        for (int i = n - 1; i > 0; i--) {
            System.out.println(stepCount + ". swap, child = " + i + ":");
            // 将堆顶元素（最大）与末尾元素交换
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            printHeapTree(arr, "");
            
            // 第三步：重新调整堆
            heapifyWithSteps(arr, i, 0, stepCount);
            stepCount++;
        }
        
        printArray(arr, "排序后数组");
    }

    /**
     * 堆化辅助函数 - 最小堆
     */
    private static void heapifyMin(int[] arr, int n, int i) {
        int smallest = i; // 初始化最小元素为根节点
        int left = 2 * i + 1; // 左子节点
        int right = 2 * i + 2; // 右子节点
        
        // 如果左子节点小于根节点
        if (left < n && arr[left] < arr[smallest]) {
            smallest = left;
        }
        
        // 如果右子节点小于当前最小节点
        if (right < n && arr[right] < arr[smallest]) {
            smallest = right;
        }
        
        // 如果最小节点不是根节点，交换并继续堆化
        if (smallest != i) {
            int temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
            heapifyMin(arr, n, smallest);
        }
    }

    /**
     * 堆排序优化版本 - 最小堆
     * 
     * 算法思路：
     * 使用最小堆进行排序，最终结果为升序
     * 构建最小堆后，依次取出最小元素放到已排序区域
     * 
     * 优化效果：
     * - 直接得到升序结果，无需反转
     * - 某些场景下更直观
     * 
     * 时间复杂度：O(n log n)
     * 空间复杂度：O(1) - 原地排序
     * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
     */
    public static void heapSort2(int[] arr) {
        System.out.println("heapSort2 min-heap:");
        int n = arr.length;
        
        // 第一步：构建最小堆
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapifyMin(arr, n, i);
        }
        
        // 第二步：逐个取出最小元素
        for (int i = n - 1; i > 0; i--) {
            // 将堆顶元素（最小）与末尾元素交换
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            
            // 第三步：重新调整堆
            heapifyMin(arr, i, 0);
        }
        
        // 反转数组得到升序结果
        for (int i = 0; i < n / 2; i++) {
            int temp = arr[i];
            arr[i] = arr[n - 1 - i];
            arr[n - 1 - i] = temp;
        }
        
        printArray(arr, "排序后数组");
    }

    /**
     * 堆排序 - 迭代版本
     * 
     * 算法思路：
     * 使用迭代方式实现堆化，避免递归调用
     * 通过循环调整父子节点关系
     * 
     * 优化效果：
     * - 避免了递归调用的开销
     * - 更好的性能表现
     * 
     * 时间复杂度：O(n log n)
     * 空间复杂度：O(1) - 原地排序
     * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
     */
    public static void heapSort3(int[] arr) {
        System.out.println("heapSort3 iterative:");
        int n = arr.length;
        
        // 第一步：构建最大堆（迭代方式）
        for (int i = n / 2 - 1; i >= 0; i--) {
            int current = i;
            while (true) {
                int largest = current;
                int left = 2 * current + 1;
                int right = 2 * current + 2;
                
                // 比较左子节点
                if (left < n && arr[left] > arr[largest]) {
                    largest = left;
                }
                // 比较右子节点
                if (right < n && arr[right] > arr[largest]) {
                    largest = right;
                }
                
                if (largest == current) {
                    break;
                }
                
                // 交换父子节点
                int temp = arr[current];
                arr[current] = arr[largest];
                arr[largest] = temp;
                current = largest;
            }
        }
        
        // 第二步：逐个取出堆顶元素
        for (int i = n - 1; i > 0; i--) {
            // 交换堆顶与末尾元素
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            
            // 第三步：迭代堆化
            int current = 0;
            while (true) {
                int largest = current;
                int left = 2 * current + 1;
                int right = 2 * current + 2;
                
                // 比较左子节点
                if (left < i && arr[left] > arr[largest]) {
                    largest = left;
                }
                // 比较右子节点
                if (right < i && arr[right] > arr[largest]) {
                    largest = right;
                }
                
                if (largest == current) {
                    break;
                }
                
                // 交换父子节点
                int temp2 = arr[current];
                arr[current] = arr[largest];
                arr[largest] = temp2;
                current = largest;
            }
        }
        
        printArray(arr, "排序后数组");
    }

    /**
     * 堆排序 - 自底向上版本
     * 
     * 算法思路：
     * 从底部开始构建堆，逐步向上调整
     * 使用不同的堆化策略，提高构建效率
     * 
     * 优化效果：
     * - 更高效的堆构建过程
     * - 减少不必要的比较
     * 
     * 时间复杂度：O(n log n)
     * 空间复杂度：O(1) - 原地排序
     * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
     */
    public static void heapSort4(int[] arr) {
        System.out.println("heapSort4 bottom-up:");
        int n = arr.length;
        
        // 第一步：自底向上构建最大堆
        for (int i = 1; i < n; i++) {
            int child = i;
            int parent = (child - 1) / 2;
            
            // 向上调整：确保父节点大于子节点
            while (parent >= 0 && arr[parent] < arr[child]) {
                int temp = arr[parent];
                arr[parent] = arr[child];
                arr[child] = temp;
                child = parent;
                parent = (child - 1) / 2;
                if (child == 0) {
                    break;
                }
            }
        }
        
        // 第二步：逐个取出堆顶元素
        for (int i = n - 1; i > 0; i--) {
            // 交换堆顶与末尾元素
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            
            // 第三步：向下调整
            int parent = 0;
            int child = 1;
            
            while (child < i) {
                // 选择较大的子节点
                if (child + 1 < i && arr[child] < arr[child + 1]) {
                    child++;
                }
                
                if (arr[parent] >= arr[child]) {
                    break;
                }
                
                // 交换父子节点
                int temp2 = arr[parent];
                arr[parent] = arr[child];
                arr[child] = temp2;
                parent = child;
                child = 2 * parent + 1;
            }
        }
        
        printArray(arr, "排序后数组");
    }

    /**
     * 堆排序 - 非递归版本
     * 
     * 算法思路：
     * 使用非递归方式实现堆化，提供父子节点计算函数
     * 通过循环调整堆结构，避免递归调用
     * 
     * 优化效果：
     * - 避免递归调用栈开销
     * - 更直观的父子节点关系计算
     * - 详细的调试日志输出
     * 
     * 时间复杂度：O(n log n)
     * 空间复杂度：O(1) - 原地排序
     * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
     */
    public static void heapSort5(int[] arr) {
        System.out.println("heapSort5 non-recursive:");
        
        // 根据完全二叉树结构性质，父子节点与数组下标的关系
        class NodeHelper {
            int getParent(int i) { return (i - 1) / 2; }
            int getLeft(int i) { return 2 * i + 1; }
            int getRight(int i) { return 2 * i + 2; }
        }
        NodeHelper node = new NodeHelper();
        
        /**
         * 始终保持大顶堆特性, 构建大顶堆的非递归写法
         */
        java.util.function.BiConsumer<int[], Integer> maxHeapify = (array, idx) -> {
            int size = array.length;
            int current = array[idx];
            int child = node.getLeft(idx);
            // 从当前位置的左节点开始遍历
            for (; child < size;) {
                System.out.println("current= " + current + "  idx= " + idx + "  child= " + child + "  size= " + size);
                // 如果左节点小于右节点且小于总长度，则指向右节点
                if (child + 1 < size && array[child] < array[child + 1]) {
                    child++;
                }
                if (array[child] > current) {
                    // 如果子节点大于父节点，将子节点的值赋给父节点
                    array[idx] = array[child];
                    // 当前节点指向该子节点，继续循环
                    idx = child;
                } else {
                    // 子节点小于父节点则跳出循环
                    break;
                }
                // 遍历子树父节点
                child = node.getLeft(idx);
            }
            // 赋值为父节点的值
            array[idx] = current;
        };
        
        int n = arr.length;
        // 最底层的父节点
        int parent = node.getParent(n) - 1;
        // 最底层的子节点
        int child = n - 1;
        
        // 从最后的父节点开始遍历，构建大顶堆，并把最大数冒出到堆顶
        while (parent >= 0) {
            maxHeapify.accept(arr, parent);
            System.out.println("parent sort: " + parent + " " + Arrays.toString(arr));
            parent--;
        }
        
        System.out.println("child start: parent=" + parent + "  child=" + child);
        // 自下向上逐个将子节点数与最顶端的数进行交换，并保持最大堆特性
        while (child > 0) {
            // 将顶端的父节点与当前子节点互换
            int temp = arr[0];
            arr[0] = arr[child];
            arr[child] = temp;
            // 自最底层往上遍历构建大顶堆，已经排好序的不再交换
            maxHeapify.accept(arr, 0);
            System.out.println("child sort: " + child + " " + Arrays.toString(arr));
            child--;
        }
        
        printArray(arr, "排序后数组");
    }

    // ==================== 算法测试和性能对比 ====================

    public static void main(String[] args) {
        // 测试1：最大堆版本
        performanceTest(HeapSort::heapSort1, testData, "heapSort1 max-heap");

        // 测试2：最小堆版本
        performanceTest(HeapSort::heapSort2, testData, "heapSort2 min-heap");

        // 测试3：迭代版本
        performanceTest(HeapSort::heapSort3, testData, "heapSort3 iterative");

        // 测试4：自底向上版本
        performanceTest(HeapSort::heapSort4, testData, "heapSort4 bottom-up");

        // 测试5：非递归版本
        performanceTest(HeapSort::heapSort5, testData, "heapSort5 non-recursive");

        System.out.println("=== 算法对比总结 ===");
        System.out.println("1. heapSort1 max-heap：经典实现，升序排序");
        System.out.println("2. heapSort2 min-heap：反向思维，直观易懂");
        System.out.println("3. heapSort3 iterative：避免递归，性能优化");
        System.out.println("4. heapSort4 bottom-up：高效构建，减少比较");
        System.out.println("5. heapSort5 non-recursive：非递归堆化，父子节点计算函数");
    }

    @FunctionalInterface
    interface SortFunction {
        void sort(int[] arr);
    }
}
