
/**
 * 冒泡排序升序，将最大的冒泡到最后
 */
fn bubble_sort1<T: Ord>(arr: &mut [T]) -> &mut [T] {
  let len = arr.len();
  println!("array size is {:?}", arr.len());

  for i in 0..len {
    println!("i:{}", i);
    for j in 0..len - i - 1 {
      println!("i=:{}, j=:{}", i, j);
      if arr[j] > arr[j + 1] {
        // 可以直接使用swap
        arr.swap(j, j + 1);
      }
    }
  }
  // println!("array is sorted {:?}", arr);
  return arr;
}

/**
 * 冒泡排序降序，将最小的冒泡到最后。
 * 且增加是否交换的标志，针对已排序做优化。
 */
fn bubble_sort2<T: Ord>(arr: &mut [T]) -> &mut [T] {
  let len = arr.len();
  let mut flag = true;
  let mut i = 0;
  while i < len && flag == true {
    flag = false;
    println!("i:{}", i);
    for j in 0..len - i - 1 {
      // 当前项跟后一项进行比较，如果需要交换
      // 当没有任何一项需要交换时则终止循环
      println!("i=:{}, j=:{}", i, j);
      if arr[j] < arr[j + 1] {
        flag = true;
        arr.swap(j, j + 1);
      }
    }
    i = i + 1;
  }
  return arr;
}

fn main() {
  println!("bubbleSort:");
  let mut data1 = [2, -1, 10, 5, 8, 11];
  println!("sort1 before: {:?}", data1);
  bubble_sort1(&mut data1);
  println!("sort1 after: {:?}", data1);

  let mut data2 = [2, -1, 10, 5, 8, 11];
  println!("sort2 before: {:?}", data2);
  bubble_sort2(&mut data2);
  println!("sort2 after: {:?}", data2);

}

/*
jarry@jarrys-MacBook-Pro rust % rustc -V  
rustc 1.51.0 (2fd73fabe)
jarry@jarrys-MacBook-Pro bubblesort % rustc ./bubble_sort.rs
jarry@jarrys-MacBook-Pro bubblesort % ./bubble_sort
bubbleSort:
sort1 before: [2, -1, 10, 5, 8, 11]
array size is 6
i:0
i=:0, j=:0
i=:0, j=:1
i=:0, j=:2
i=:0, j=:3
i=:0, j=:4
i:1
i=:1, j=:0
i=:1, j=:1
i=:1, j=:2
i=:1, j=:3
i:2
i=:2, j=:0
i=:2, j=:1
i=:2, j=:2
i:3
i=:3, j=:0
i=:3, j=:1
i:4
i=:4, j=:0
i:5
sort1 after: [-1, 2, 5, 8, 10, 11]
sort2 before: [2, -1, 10, 5, 8, 11]
i:0
i=:0, j=:0
i=:0, j=:1
i=:0, j=:2
i=:0, j=:3
i=:0, j=:4
i:1
i=:1, j=:0
i=:1, j=:1
i=:1, j=:2
i=:1, j=:3
i:2
i=:2, j=:0
i=:2, j=:1
i=:2, j=:2
i:3
i=:3, j=:0
i=:3, j=:1
i:4
i=:4, j=:0
i:5
sort2 after: [11, 10, 8, 5, 2, -1]
*/