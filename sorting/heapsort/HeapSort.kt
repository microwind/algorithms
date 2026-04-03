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

/**
 * 打印数组内容的辅助函数
 */
fun printArray(arr: IntArray, label: String) {
    println("$label: ${arr.contentToString()}")
}

/**
 * 打印堆的树形结构
 */
fun printHeapTree(arr: IntArray, title: String) {
    if (arr.size < 7) {
        println("$title: ${arr.contentToString()}")
        return
    }
    
    println(title)
    println("              ${arr[0]}(0)")
    println("          /         \\")
    println("        ${arr[1]}(1)        ${arr[2]}(2)")
    println("       /    \\      /     \\")
    println("   ${arr[3]}(3)  ${arr[4]}(4)  ${arr[5]}(5)  ${arr[6]}(6)")
    println()
}

/**
 * 性能测试辅助函数
 */
fun performanceTest(sortFunc: (IntArray) -> Unit, arr: IntArray, name: String) {
    // 创建数组副本，避免修改原数组
    val testArr = arr.copyOf()
    printArray(testArr, "${name}原始数组")
    
    // 开始计时
    val startTime = System.nanoTime()
    sortFunc(testArr)
    val endTime = System.nanoTime()
    
    val duration = (endTime - startTime) / 1_000_000.0
    println(String.format("%s: %.3fms", name, duration))
    printArray(testArr, "${name}排序结果")
    println() // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
val testData = intArrayOf(7, 11, 9, 10, 12, 13, 8)

/**
 * 带步骤打印的堆化函数
 */
fun heapifyWithSteps(arr: IntArray, n: Int, i: Int, parentStep: Int) {
    var largest = i
    val left = 2 * i + 1
    val right = 2 * i + 2
    
    // 第一步：比较左子节点
    if (left < n && arr[left] > arr[largest]) {
        largest = left
    }
    
    // 第二步：比较右子节点
    if (right < n && arr[right] > arr[largest]) {
        largest = right
    }
    
    // 第三步：如果需要交换，执行交换并递归堆化
    if (largest != i) {
        // 关键点：交换父子节点
        val temp = arr[i]
        arr[i] = arr[largest]
        arr[largest] = temp
        
        val newLeft = 2 * largest + 1
        val newRight = 2 * largest + 2
        var maxIdx = largest
        
        if (newLeft < n && arr[newLeft] > arr[maxIdx]) maxIdx = newLeft
        if (newRight < n && arr[newRight] > arr[maxIdx]) maxIdx = newRight
        
        println("$parentStep.1 maxHeapify: idx= $largest left= $newLeft right= $newRight max= $maxIdx size= $n")
        printHeapTree(arr, "")
        
        heapifyWithSteps(arr, n, largest, parentStep)
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
fun heapSort1(arr: IntArray) {
    println("heapSort1 max-heap:")
    val n = arr.size
    
    printHeapTree(arr, "oringal array:")
    
    // 第一步：构建最大堆
    println("父节点步骤")
    var stepCount = 1
    // 关键点：从最后一个非叶子节点开始堆化
    for (i in n / 2 - 1 downTo 0) {
        val left = 2 * i + 1
        val right = 2 * i + 2
        var maxIdx = i
        
        if (left < n && arr[left] > arr[maxIdx]) maxIdx = left
        if (right < n && arr[right] > arr[maxIdx]) maxIdx = right
        
        println("$stepCount. maxHeapify: idx= $i left= $left right= $right max= $maxIdx size= $n")
        stepCount++
        
        if (maxIdx != i) {
            val temp = arr[i]
            arr[i] = arr[maxIdx]
            arr[maxIdx] = temp
            printHeapTree(arr, "")
            
            // 递归堆化
            heapifyWithSteps(arr, n, maxIdx, stepCount - 1)
            stepCount++
        } else {
            stepCount++
        }
    }
    
    // 第二步：逐个取出堆顶元素并排序
    println("子节点堆排序:")
    for (i in n - 1 downTo 1) {
        println("$stepCount. swap, child = $i:")
        // 将堆顶元素（最大）与末尾元素交换
        val temp = arr[0]
        arr[0] = arr[i]
        arr[i] = temp
        printHeapTree(arr, "")
        
        // 第三步：重新调整堆
        heapifyWithSteps(arr, i, 0, stepCount)
        stepCount++
    }
    
    printArray(arr, "排序后数组")
}

/**
 * 堆化辅助函数 - 最小堆
 */
fun heapifyMin(arr: IntArray, n: Int, i: Int) {
    var smallest = i // 初始化最小元素为根节点
    val left = 2 * i + 1 // 左子节点
    val right = 2 * i + 2 // 右子节点
    
    // 如果左子节点小于根节点
    if (left < n && arr[left] < arr[smallest]) {
        smallest = left
    }
    
    // 如果右子节点小于当前最小节点
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right
    }
    
    // 如果最小节点不是根节点，交换并继续堆化
    if (smallest != i) {
        val temp = arr[i]
        arr[i] = arr[smallest]
        arr[smallest] = temp
        heapifyMin(arr, n, smallest)
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
fun heapSort2(arr: IntArray) {
    println("heapSort2 min-heap:")
    val n = arr.size
    
    // 第一步：构建最小堆
    for (i in n / 2 - 1 downTo 0) {
        heapifyMin(arr, n, i)
    }
    
    // 第二步：逐个取出最小元素
    for (i in n - 1 downTo 1) {
        // 将堆顶元素（最小）与末尾元素交换
        val temp = arr[0]
        arr[0] = arr[i]
        arr[i] = temp
        
        // 第三步：重新调整堆
        heapifyMin(arr, i, 0)
    }
    
    // 反转数组得到升序结果
    arr.reverse()
    
    printArray(arr, "排序后数组")
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
fun heapSort3(arr: IntArray) {
    println("heapSort3 iterative:")
    val n = arr.size
    
    // 第一步：构建最大堆（迭代方式）
    for (i in n / 2 - 1 downTo 0) {
        var current = i
        while (true) {
            var largest = current
            val left = 2 * current + 1
            val right = 2 * current + 2
            
            // 比较左子节点
            if (left < n && arr[left] > arr[largest]) {
                largest = left
            }
            // 比较右子节点
            if (right < n && arr[right] > arr[largest]) {
                largest = right
            }
            
            if (largest == current) {
                break
            }
            
            // 交换父子节点
            val temp = arr[current]
            arr[current] = arr[largest]
            arr[largest] = temp
            current = largest
        }
    }
    
    // 第二步：逐个取出堆顶元素
    for (i in n - 1 downTo 1) {
        // 交换堆顶与末尾元素
        val temp = arr[0]
        arr[0] = arr[i]
        arr[i] = temp
        
        // 第三步：迭代堆化
        var current = 0
        while (true) {
            var largest = current
            val left = 2 * current + 1
            val right = 2 * current + 2
            
            // 比较左子节点
            if (left < i && arr[left] > arr[largest]) {
                largest = left
            }
            // 比较右子节点
            if (right < i && arr[right] > arr[largest]) {
                largest = right
            }
            
            if (largest == current) {
                break
            }
            
            // 交换父子节点
            val temp = arr[current]
            arr[current] = arr[largest]
            arr[largest] = temp
            current = largest
        }
    }
    
    printArray(arr, "排序后数组")
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
fun heapSort4(arr: IntArray) {
    println("heapSort4 bottom-up:")
    val n = arr.size
    
    // 第一步：自底向上构建最大堆
    for (i in 1 until n) {
        var child = i
        var parent = (child - 1) / 2
        
        // 向上调整：确保父节点大于子节点
        while (parent >= 0 && arr[parent] < arr[child]) {
            val temp = arr[parent]
            arr[parent] = arr[child]
            arr[child] = temp
            child = parent
            parent = (child - 1) / 2
            if (child == 0) {
                break
            }
        }
    }
    
    // 第二步：逐个取出堆顶元素
    for (i in n - 1 downTo 1) {
        // 交换堆顶与末尾元素
        val temp = arr[0]
        arr[0] = arr[i]
        arr[i] = temp
        
        // 第三步：向下调整
        var parent = 0
        var child = 1
        
        while (child < i) {
            // 选择较大的子节点
            if (child + 1 < i && arr[child] < arr[child + 1]) {
                child++
            }
            
            if (arr[parent] >= arr[child]) {
                break
            }
            
            // 交换父子节点
            val temp = arr[parent]
            arr[parent] = arr[child]
            arr[child] = temp
            parent = child
            child = 2 * parent + 1
        }
    }
    
    printArray(arr, "排序后数组")
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
fun heapSort5(arr: IntArray) {
    println("heapSort5 non-recursive:")
    
    // 根据完全二叉树结构性质，父子节点与数组下标的关系
    val getParent = { i: Int -> (i - 1) / 2 }
    val getLeft = { i: Int -> 2 * i + 1 }
    val getRight = { i: Int -> 2 * i + 2 }
    
    /**
     * 始终保持大顶堆特性, 构建大顶堆的非递归写法
     */
    fun maxHeapify(array: IntArray, idx: Int, size: Int) {
        var current = array[idx]
        var idxMut = idx
        var child = getLeft(idxMut)
        // 从当前位置的左节点开始遍历
        while (child < size) {
            println("current= $current  idx= $idxMut  child= $child  size= $size")
            // 如果左节点小于右节点且小于总长度，则指向右节点
            if (child + 1 < size && array[child] < array[child + 1]) {
                child++
            }
            if (array[child] > current) {
                // 如果子节点大于父节点，将子节点的值赋给父节点
                array[idxMut] = array[child]
                // 当前节点指向该子节点，继续循环
                idxMut = child
            } else {
                // 子节点小于父节点则跳出循环
                break
            }
            // 遍历子树父节点
            child = getLeft(idxMut)
        }
        // 赋值为父节点的值
        array[idxMut] = current
    }
    
    val n = arr.size
    // 最底层的父节点
    var parent = getParent(n) - 1
    // 最底层的子节点
    var child = n - 1
    
    // 从最后的父节点开始遍历，构建大顶堆，并把最大数冒出到堆顶
    while (parent >= 0) {
        maxHeapify(arr, parent, n)
        print("parent sort: $parent ")
        printArray(arr, "")
        parent--
    }
    
    println("child start: parent=$parent  child=$child")
    // 自下向上逐个将子节点数与最顶端的数进行交换，并保持最大堆特性
    while (child > 0) {
        // 将顶端的父节点与当前子节点互换
        val temp = arr[0]
        arr[0] = arr[child]
        arr[child] = temp
        // 自最底层往上遍历构建大顶堆，已经排好序的不再交换
        maxHeapify(arr, 0, child)
        print("child sort: $child ")
        printArray(arr, "")
        child--
    }
    
    printArray(arr, "排序后数组")
}

// ==================== 算法测试和性能对比 ====================

fun main() {
    // 测试1：最大堆版本
    performanceTest(::heapSort1, testData, "heapSort1 max-heap")

    // 测试2：最小堆版本
    performanceTest(::heapSort2, testData, "heapSort2 min-heap")

    // 测试3：迭代版本
    performanceTest(::heapSort3, testData, "heapSort3 iterative")

    // 测试4：自底向上版本
    performanceTest(::heapSort4, testData, "heapSort4 bottom-up")

    // 测试5：非递归版本
    performanceTest(::heapSort5, testData, "heapSort5 non-recursive")

    println("=== 算法对比总结 ===")
    println("1. heapSort1 max-heap：经典实现，升序排序")
    println("2. heapSort2 min-heap：反向思维，直观易懂")
    println("3. heapSort3 iterative：避免递归，性能优化")
    println("4. heapSort4 bottom-up：高效构建，减少比较")
    println("5. heapSort5 non-recursive：非递归堆化，父子节点计算函数")
}

/* 打印结果
jarry@Mac heapsort % kotlinc HeapSort.kt -include-runtime -d HeapSort.jar && java -jar HeapSort.jar            
heapSort1 max-heap原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort1 max-heap:
oringal array:
              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  12(4)  13(5)  8(6)

父节点步骤
1. maxHeapify: idx= 2 left= 5 right= 6 max= 5 size= 7

              7(0)
          /         \
        11(1)        13(2)
       /    \      /     \
   10(3)  12(4)  9(5)  8(6)

3. maxHeapify: idx= 1 left= 3 right= 4 max= 4 size= 7

              7(0)
          /         \
        12(1)        13(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

5. maxHeapify: idx= 0 left= 1 right= 2 max= 2 size= 7

              13(0)
          /         \
        12(1)        7(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

5.1 maxHeapify: idx= 5 left= 11 right= 12 max= 5 size= 7

              13(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  8(6)

子节点堆排序:
7. swap, child = 6:

              8(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

7.1 maxHeapify: idx= 1 left= 3 right= 4 max= 4 size= 6

              12(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

7.1 maxHeapify: idx= 4 left= 9 right= 10 max= 4 size= 6

              12(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  7(5)  13(6)

8. swap, child = 5:

              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

8.1 maxHeapify: idx= 1 left= 3 right= 4 max= 3 size= 5

              11(0)
          /         \
        7(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

8.1 maxHeapify: idx= 3 left= 7 right= 8 max= 3 size= 5

              11(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  8(4)  12(5)  13(6)

9. swap, child = 4:

              8(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

9.1 maxHeapify: idx= 1 left= 3 right= 4 max= 1 size= 4

              10(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

10. swap, child = 3:

              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

10.1 maxHeapify: idx= 2 left= 5 right= 6 max= 2 size= 3

              9(0)
          /         \
        8(1)        7(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

11. swap, child = 2:

              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

11.1 maxHeapify: idx= 1 left= 3 right= 4 max= 1 size= 2

              8(0)
          /         \
        7(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

12. swap, child = 1:

              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

排序后数组: [7, 8, 9, 10, 11, 12, 13]
heapSort1 max-heap: 1.534ms
heapSort1 max-heap排序结果: [7, 8, 9, 10, 11, 12, 13]

heapSort2 min-heap原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort2 min-heap:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
heapSort2 min-heap: 6.039ms
heapSort2 min-heap排序结果: [7, 8, 9, 10, 11, 12, 13]

heapSort3 iterative原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort3 iterative:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
heapSort3 iterative: 0.029ms
heapSort3 iterative排序结果: [7, 8, 9, 10, 11, 12, 13]

heapSort4 bottom-up原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort4 bottom-up:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
heapSort4 bottom-up: 0.161ms
heapSort4 bottom-up排序结果: [7, 8, 9, 10, 11, 12, 13]

heapSort5 non-recursive原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort5 non-recursive:
current= 9  idx= 2  child= 5  size= 7
parent sort: 2 : [7, 11, 13, 10, 12, 9, 8]
current= 11  idx= 1  child= 3  size= 7
parent sort: 1 : [7, 12, 13, 10, 11, 9, 8]
current= 7  idx= 0  child= 1  size= 7
current= 7  idx= 2  child= 5  size= 7
parent sort: 0 : [13, 12, 9, 10, 11, 7, 8]
child start: parent=-1  child=6
current= 8  idx= 0  child= 1  size= 6
current= 8  idx= 1  child= 3  size= 6
child sort: 6 : [12, 11, 9, 10, 8, 7, 13]
current= 7  idx= 0  child= 1  size= 5
current= 7  idx= 1  child= 3  size= 5
child sort: 5 : [11, 10, 9, 7, 8, 12, 13]
current= 8  idx= 0  child= 1  size= 4
current= 8  idx= 1  child= 3  size= 4
child sort: 4 : [10, 8, 9, 7, 11, 12, 13]
current= 7  idx= 0  child= 1  size= 3
child sort: 3 : [9, 8, 7, 10, 11, 12, 13]
current= 7  idx= 0  child= 1  size= 2
child sort: 2 : [8, 7, 9, 10, 11, 12, 13]
child sort: 1 : [7, 8, 9, 10, 11, 12, 13]
排序后数组: [7, 8, 9, 10, 11, 12, 13]
heapSort5 non-recursive: 0.839ms
heapSort5 non-recursive排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. heapSort1 max-heap：经典实现，升序排序
2. heapSort2 min-heap：反向思维，直观易懂
3. heapSort3 iterative：避免递归，性能优化
4. heapSort4 bottom-up：高效构建，减少比较
5. heapSort5 non-recursive：非递归堆化，父子节点计算函数
*/