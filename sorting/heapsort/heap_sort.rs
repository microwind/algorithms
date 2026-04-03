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

use std::time::Instant;

/**
 * 打印数组内容的辅助函数
 */
fn print_array(arr: &[i32], label: &str) {
    println!("{}: {:?}", label, arr);
}

/**
 * 打印堆的树形结构
 */
fn print_heap_tree(arr: &[i32], title: &str) {
    if arr.len() < 7 {
        println!("{}: {:?}", title, arr);
        return;
    }
    
    println!("{}", title);
    println!("              {}(0)", arr[0]);
    println!("          /         \\");
    println!("        {}(1)        {}(2)", arr[1], arr[2]);
    println!("       /    \\      /     \\");
    println!("   {}(3)  {}(4)  {}(5)  {}(6)", arr[3], arr[4], arr[5], arr[6]);
    println!();
}

/**
 * 性能测试辅助函数
 */
fn performance_test<F>(sort_func: F, arr: &[i32], name: &str) 
where 
    F: Fn(&mut Vec<i32>),
{
    // 创建数组副本，避免修改原数组
    let mut test_arr = arr.to_vec();
    print_array(&test_arr, &format!("{}原始数组", name));
    
    // 开始计时
    let start = Instant::now();
    sort_func(&mut test_arr);
    let duration = start.elapsed();
    
    println!("{}: {:.3}ms", name, duration.as_millis() as f64);
    print_array(&test_arr, &format!("{}排序结果", name));
    println!(); // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
const TEST_DATA: [i32; 7] = [7, 11, 9, 10, 12, 13, 8];

/**
 * 带步骤打印的堆化函数
 */
fn heapify_with_steps(arr: &mut Vec<i32>, n: usize, i: usize, parent_step: i32) {
    let mut largest = i;
    let left = 2 * i + 1;
    let right = 2 * i + 2;
    
    // 第一步：比较左子节点
    if left < n && arr[left] > arr[largest] {
        largest = left;
    }
    
    // 第二步：比较右子节点
    if right < n && arr[right] > arr[largest] {
        largest = right;
    }
    
    // 第三步：如果需要交换，执行交换并递归堆化
    if largest != i {
        // 关键点：交换父子节点
        arr.swap(i, largest);
        
        let new_left = 2 * largest + 1;
        let new_right = 2 * largest + 2;
        let mut max_idx = largest;
        
        if new_left < n && arr[new_left] > arr[max_idx] {
            max_idx = new_left;
        }
        if new_right < n && arr[new_right] > arr[max_idx] {
            max_idx = new_right;
        }
        
        println!("{}.1 maxHeapify: idx= {} left= {} right= {} max= {} size= {}", 
            parent_step, largest, new_left, new_right, max_idx, n);
        print_heap_tree(arr, "");
        
        heapify_with_steps(arr, n, largest, parent_step);
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
fn heap_sort1(arr: &mut Vec<i32>) {
    println!("heapSort1 max-heap:");
    let n = arr.len();
    
    print_heap_tree(arr, "oringal array:");
    
    // 第一步：构建最大堆
    println!("父节点步骤");
    let mut step_count = 1;
    // 关键点：从最后一个非叶子节点开始堆化
    for i in (0..n/2).rev() {
        let left = 2 * i + 1;
        let right = 2 * i + 2;
        let mut max_idx = i;
        
        if left < n && arr[left] > arr[max_idx] {
            max_idx = left;
        }
        if right < n && arr[right] > arr[max_idx] {
            max_idx = right;
        }
        
        println!("{}. maxHeapify: idx= {} left= {} right= {} max= {} size= {}", 
            step_count, i, left, right, max_idx, n);
        step_count += 1;
        
        if max_idx != i {
            arr.swap(i, max_idx);
            print_heap_tree(arr, "");
            
            // 递归堆化
            heapify_with_steps(arr, n, max_idx, step_count - 1);
            step_count += 1;
        } else {
            step_count += 1;
        }
    }
    
    // 第二步：逐个取出堆顶元素并排序
    println!("子节点堆排序:");
    for i in (1..n).rev() {
        println!("{}. swap, child = {}:", step_count, i);
        // 将堆顶元素（最大）与末尾元素交换
        arr.swap(0, i);
        print_heap_tree(arr, "");
        
        // 第三步：重新调整堆
        heapify_with_steps(arr, i, 0, step_count);
        step_count += 1;
    }
    
    print_array(arr, "排序后数组");
}

/**
 * 堆化辅助函数 - 最小堆
 */
fn heapify_min(arr: &mut Vec<i32>, n: usize, i: usize) {
    let mut smallest = i; // 初始化最小元素为根节点
    let left = 2 * i + 1; // 左子节点
    let right = 2 * i + 2; // 右子节点
    
    // 如果左子节点小于根节点
    if left < n && arr[left] < arr[smallest] {
        smallest = left;
    }
    
    // 如果右子节点小于当前最小节点
    if right < n && arr[right] < arr[smallest] {
        smallest = right;
    }
    
    // 如果最小节点不是根节点，交换并继续堆化
    if smallest != i {
        arr.swap(i, smallest);
        heapify_min(arr, n, smallest);
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
fn heap_sort2(arr: &mut Vec<i32>) {
    println!("heapSort2 min-heap:");
    let n = arr.len();
    
    // 第一步：构建最小堆
    for i in (0..n/2).rev() {
        heapify_min(arr, n, i);
    }
    
    // 第二步：逐个取出最小元素
    for i in (1..n).rev() {
        // 将堆顶元素（最小）与末尾元素交换
        arr.swap(0, i);
        
        // 第三步：重新调整堆
        heapify_min(arr, i, 0);
    }
    
    // 反转数组得到升序结果
    arr.reverse();
    
    print_array(arr, "排序后数组");
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
fn heap_sort3(arr: &mut Vec<i32>) {
    println!("heapSort3 iterative:");
    let n = arr.len();
    
    // 第一步：构建最大堆（迭代方式）
    for i in (0..n/2).rev() {
        let mut current = i;
        loop {
            let mut largest = current;
            let left = 2 * current + 1;
            let right = 2 * current + 2;
            
            // 比较左子节点
            if left < n && arr[left] > arr[largest] {
                largest = left;
            }
            // 比较右子节点
            if right < n && arr[right] > arr[largest] {
                largest = right;
            }
            
            if largest == current {
                break;
            }
            
            // 交换父子节点
            arr.swap(current, largest);
            current = largest;
        }
    }
    
    // 第二步：逐个取出堆顶元素
    for i in (1..n).rev() {
        // 交换堆顶与末尾元素
        arr.swap(0, i);
        
        // 第三步：迭代堆化
        let mut current = 0;
        loop {
            let mut largest = current;
            let left = 2 * current + 1;
            let right = 2 * current + 2;
            
            // 比较左子节点
            if left < i && arr[left] > arr[largest] {
                largest = left;
            }
            // 比较右子节点
            if right < i && arr[right] > arr[largest] {
                largest = right;
            }
            
            if largest == current {
                break;
            }
            
            // 交换父子节点
            arr.swap(current, largest);
            current = largest;
        }
    }
    
    print_array(arr, "排序后数组");
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
fn heap_sort4(arr: &mut Vec<i32>) {
    println!("heapSort4 bottom-up:");
    let n = arr.len();
    
    // 第一步：自底向上构建最大堆
    for i in 1..n {
        let mut child = i;
        let mut parent = (child - 1) / 2;
        
        // 向上调整：确保父节点大于子节点
        while child > 0 && arr[parent] < arr[child] {
            arr.swap(parent, child);
            child = parent;
            if child == 0 {
                break;
            }
            parent = (child - 1) / 2;
        }
    }
    
    // 第二步：逐个取出堆顶元素
    for i in (1..n).rev() {
        // 交换堆顶与末尾元素
        arr.swap(0, i);
        
        // 第三步：向下调整
        let mut parent = 0;
        let mut child = 1;
        
        while child < i {
            // 选择较大的子节点
            if child + 1 < i && arr[child] < arr[child + 1] {
                child += 1;
            }
            
            if arr[parent] >= arr[child] {
                break;
            }
            
            // 交换父子节点
            arr.swap(parent, child);
            parent = child;
            child = 2 * parent + 1;
        }
    }
    
    print_array(arr, "排序后数组");
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
fn heap_sort5(arr: &mut Vec<i32>) {
    println!("heapSort5 non-recursive:");
    
    // 根据完全二叉树结构性质，父子节点与数组下标的关系
    let get_parent = |i: usize| (i - 1) / 2;
    let get_left = |i: usize| 2 * i + 1;
    // let get_right = |i: usize| 2 * i + 2;
    
    /*
     * 始终保持大顶堆特性, 构建大顶堆的非递归写法
     */
    let max_heapify = |array: &mut Vec<i32>, idx: usize, size: usize| {
        let current = array[idx];
        let mut idx_mut = idx;
        let mut child = get_left(idx_mut);
        // 从当前位置的左节点开始遍历
        while child < size {
            println!("current= {}  idx= {}  child= {}  size= {}", current, idx_mut, child, size);
            // 如果左节点小于右节点且小于总长度，则指向右节点
            if child + 1 < size && array[child] < array[child + 1] {
                child += 1;
            }
            if array[child] > current {
                // 如果子节点大于父节点，将子节点的值赋给父节点
                array[idx_mut] = array[child];
                // 当前节点指向该子节点，继续循环
                idx_mut = child;
            } else {
                // 子节点小于父节点则跳出循环
                break;
            }
            // 遍历子树父节点
            child = get_left(idx_mut);
        }
        // 赋值为父节点的值
        array[idx_mut] = current;
    };
    
    let n = arr.len();
    // 最底层的父节点
    let mut parent = get_parent(n) as i32 - 1;
    // 最底层的子节点
    let mut child = n - 1;
    
    // 从最后的父节点开始遍历，构建大顶堆，并把最大数冒出到堆顶
    while parent >= 0 {
        max_heapify(arr, parent as usize, n);
        print!("parent sort: {} ", parent);
        print_array(arr, "");
        parent -= 1;
    }
    
    println!("child start: parent={}  child={}", parent, child);
    // 自下向上逐个将子节点数与最顶端的数进行交换，并保持最大堆特性
    while child > 0 {
        // 将顶端的父节点与当前子节点互换
        arr.swap(0, child);
        // 自最底层往上遍历构建大顶堆，已经排好序的不再交换
        max_heapify(arr, 0, child);
        print!("child sort: {} ", child);
        print_array(arr, "");
        child -= 1;
    }
    
    print_array(arr, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

fn main() {
    // 测试1：最大堆版本
    performance_test(heap_sort1, &TEST_DATA, "heapSort1 max-heap");

    // 测试2：最小堆版本
    performance_test(heap_sort2, &TEST_DATA, "heapSort2 min-heap");

    // 测试3：迭代版本
    performance_test(heap_sort3, &TEST_DATA, "heapSort3 iterative");

    // 测试4：自底向上版本
    performance_test(heap_sort4, &TEST_DATA, "heapSort4 bottom-up");

    // 测试5：非递归版本
    performance_test(heap_sort5, &TEST_DATA, "heapSort5 non-recursive");

    println!("=== 算法对比总结 ===");
    println!("1. heapSort1 max-heap：经典实现，升序排序");
    println!("2. heapSort2 min-heap：反向思维，直观易懂");
    println!("3. heapSort3 iterative：避免递归，性能优化");
    println!("4. heapSort4 bottom-up：高效构建，减少比较");
    println!("5. heapSort5 non-recursive：非递归堆化，父子节点计算函数");
}

/* 打印结果
jarry@Mac heapsort % rustc heap_sort.rs && ./heap_sort
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
heapSort1 max-heap: 0.000ms
heapSort1 max-heap排序结果: [7, 8, 9, 10, 11, 12, 13]

heapSort2 min-heap原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort2 min-heap:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
heapSort2 min-heap: 0.000ms
heapSort2 min-heap排序结果: [7, 8, 9, 10, 11, 12, 13]

heapSort3 iterative原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort3 iterative:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
heapSort3 iterative: 0.000ms
heapSort3 iterative排序结果: [7, 8, 9, 10, 11, 12, 13]

heapSort4 bottom-up原始数组: [7, 11, 9, 10, 12, 13, 8]
heapSort4 bottom-up:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
heapSort4 bottom-up: 0.000ms
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
heapSort5 non-recursive: 0.000ms
heapSort5 non-recursive排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. heapSort1 max-heap：经典实现，升序排序
2. heapSort2 min-heap：反向思维，直观易懂
3. heapSort3 iterative：避免递归，性能优化
4. heapSort4 bottom-up：高效构建，减少比较
5. heapSort5 non-recursive：非递归堆化，父子节点计算函数
*/