fn main() {
  // 定义一个包含5个整数的数组
  let mut arr = [1, 2, 3, 4, 5];
  
  // 访问数组元素
  println!("Element at index 2: {}", arr[2]);

  // 修改数组元素
  arr[2] = 10;
  println!("Modified element at index 2: {}", arr[2]);

  // 遍历数组
  for i in 0..arr.len() {
      print!("{} ", arr[i]);
  }
  println!();
}

/*
jarry@MacBook-Pro array % rustc -V
rustc 1.84.0 (9fc6b4312 2025-01-07)
jarry@MacBook-Pro array % rustc array.rs
jarry@MacBook-Pro array % ./array 
Element at index 2: 3
Modified element at index 2: 10
1 2 10 4 5 
*/