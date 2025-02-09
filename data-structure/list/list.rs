struct List {
  data: Vec<i32>,
}

impl List {
  fn new() -> Self {
      List { data: Vec::with_capacity(10) }
  }

  fn add(&mut self, value: i32) {
      self.data.push(value);
  }

  fn remove(&mut self) {
      self.data.pop();
  }

  fn get(&self, index: usize) -> Option<i32> {
      self.data.get(index).copied()
  }

  fn print(&self) {
      println!("List: {:?}", self.data);
  }
}

fn main() {
  let mut list = List::new();
  list.add(10);
  list.add(20);
  list.add(30);
  list.print();

  list.remove(); // 调用 remove 方法
  list.print();

  if let Some(value) = list.get(1) { // 调用 get 方法
      println!("Element at index 1: {}", value);
  }
}

/*
jarry@MacBook-Pro list % rustc list.rs
jarry@MacBook-Pro list % ./list 
List: [10, 20, 30]
List: [10, 20]
Element at index 1: 20
*/
