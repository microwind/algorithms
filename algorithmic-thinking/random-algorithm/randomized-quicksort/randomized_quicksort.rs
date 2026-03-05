use rand::Rng;

/// 随机快速排序（Randomized QuickSort）- Rust 版本
///
/// 通过随机选择枢轴，将最坏 O(n^2) 的情况「概率化」为极小，
/// 期望时间复杂度为 O(n log n)。

fn randomized_partition(arr: &mut [i32], left: isize, right: isize) -> isize {
    let mut rng = rand::thread_rng();
    let random_idx = rng.gen_range(left..=right);
    arr.swap(random_idx as usize, right as usize);

    let pivot = arr[right as usize];
    let mut i = left - 1;

    for j in left..right {
        if arr[j as usize] <= pivot {
            i += 1;
            arr.swap(i as usize, j as usize);
        }
    }
    let pivot_pos = i + 1;
    arr.swap(pivot_pos as usize, right as usize);
    pivot_pos
}

fn randomized_quicksort(arr: &mut [i32], left: isize, right: isize) {
    if left < right {
        let p = randomized_partition(arr, left, right);
        randomized_quicksort(arr, left, p - 1);
        randomized_quicksort(arr, p + 1, right);
    }
}

fn randomized_select(arr: &mut [i32], left: isize, right: isize, k: isize) -> i32 {
    if left == right {
        return arr[left as usize];
    }
    let p = randomized_partition(arr, left, right);
    if k == p {
        arr[k as usize]
    } else if k < p {
        randomized_select(arr, left, p - 1, k)
    } else {
        randomized_select(arr, p + 1, right, k)
    }
}

fn main() {
    println!("========== Randomized QuickSort (Rust) ==========");

    let mut arr = vec![5, 2, 8, 1, 9, 3, 7, 4, 6];
    println!("原向量: {:?}", arr);

    let mut sorted = arr.clone();
    let n = sorted.len() as isize;
    randomized_quicksort(&mut sorted, 0, n - 1);
    println!("排序后: {:?}", sorted);

    let mut copy = arr.clone();
    let k: isize = 3;
    let kth = randomized_select(&mut copy, 0, n - 1, k);
    println!("第 {} 小元素: {}", k, kth);
}

