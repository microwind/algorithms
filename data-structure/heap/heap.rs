const MAX_SIZE: usize = 100;

/*
大顶堆：根节点始终为堆中的最大值。
         6
       /   \
      5     4
     / \   /
    3   2 1
*/
// 调整堆的结构，确保父节点大于或等于其子节点，符合大顶堆的性质
fn heapify_max(arr: &mut Vec<i32>, n: usize, i: usize) {
    let mut largest = i;           // 假设当前节点 i 为最大节点
    let left = 2 * i + 1;          // 左子节点的索引
    let right = 2 * i + 2;         // 右子节点的索引

    // 如果左子节点存在且大于当前最大值
    if left < n && arr[left] > arr[largest] {
        largest = left; // 更新最大值索引
    }

    // 如果右子节点存在且大于当前最大值
    if right < n && arr[right] > arr[largest] {
        largest = right; // 更新最大值索引
    }

    // 如果最大值不再是原节点 i，交换节点 i 和最大值节点
    if largest != i {
        arr.swap(i, largest);

        // 递归调整交换后的子树，确保其也符合大顶堆性质
        heapify_max(arr, n, largest);
    }
}

/*
小顶堆：根节点始终为堆中的最小值。
         1
       /   \
      2     4
     / \   /
    5   3 6
*/
// 调整堆的结构，确保父节点小于或等于其子节点，符合小顶堆的性质
fn heapify_min(arr: &mut Vec<i32>, n: usize, i: usize) {
    let mut smallest = i;           // 假设当前节点 i 为最小节点
    let left = 2 * i + 1;           // 左子节点的索引
    let right = 2 * i + 2;          // 右子节点的索引

    // 如果左子节点存在且小于当前最小值
    if left < n && arr[left] < arr[smallest] {
        smallest = left; // 更新最小值索引
    }

    // 如果右子节点存在且小于当前最小值
    if right < n && arr[right] < arr[smallest] {
        smallest = right; // 更新最小值索引
    }

    // 如果最小值不再是原节点 i，交换节点 i 和最小值节点
    if smallest != i {
        arr.swap(i, smallest);

        // 递归调整交换后的子树，确保其也符合小顶堆性质
        heapify_min(arr, n, smallest);
    }
}

// 构建大顶堆
fn build_max_heap(arr: &mut Vec<i32>, n: usize) {
    for i in (0..n / 2).rev() {
        heapify_max(arr, n, i);
    }
}

// 构建小顶堆
fn build_min_heap(arr: &mut Vec<i32>, n: usize) {
    for i in (0..n / 2).rev() {
        heapify_min(arr, n, i);
    }
}

// 打印堆
fn print_heap(arr: &Vec<i32>, n: usize) {
    for i in 0..n {
        print!("{} ", arr[i]);
    }
    println!();
}

fn main() {
  let mut max_heap = vec![3, 1, 6, 5, 2, 4];
  let mut min_heap = vec![3, 1, 6, 5, 2, 4];

  let max_n = max_heap.len();
  let min_n = min_heap.len();

  // 使用 MAX_SIZE 来做限制（例如限制堆的最大大小）
  if max_n > MAX_SIZE {
      println!("Max heap exceeds maximum size!");
      return;
  }

  // 构建大顶堆
  build_max_heap(&mut max_heap, max_n);
  println!("Max heap:");
  print_heap(&max_heap, max_n);

  // 构建小顶堆
  build_min_heap(&mut min_heap, min_n);
  println!("Min heap:");
  print_heap(&min_heap, min_n);
}

/*
jarry@MacBook-Pro heap % rustc heap.rs
jarry@MacBook-Pro heap % ./heap 
Max heap:
6 5 4 1 2 3 
Min heap:
1 2 4 5 3 6
*/