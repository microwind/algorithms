struct Stack {
  top: usize,
  size: usize,
  data: Vec<i32>,
}

impl Stack {
  // 创建栈
  fn new(size: usize) -> Self {
      Stack {
          top: 0,
          size,
          data: vec![0; size],
      }
  }

  // 打印栈中的所有元素
  fn print_stack(&self) {
      if self.is_empty() {
          println!("栈为空");
          return;
      }

      for i in 0..self.top {
          print!("{} ", self.data[i]);
      }
      println!();
  }

  // 判断栈是否已满
  fn is_full(&self) -> bool {
      self.top == self.size
  }

  // 判断栈是否为空
  fn is_empty(&self) -> bool {
      self.top == 0
  }

  // 入栈操作
  fn push(&mut self, value: i32) -> bool {
      if self.is_full() {
          return false;
      }

      self.data[self.top] = value;
      self.top += 1;
      true
  }

  // 出栈操作
  fn pop(&mut self) -> i32 {
      if self.is_empty() {
          return 0;
      }

      self.top -= 1;
      self.data[self.top]
  }

  // 清空栈
  fn make_empty(&mut self) {
      self.top = 0;
  }

  // 获取栈中元素的个数
  fn len(&self) -> usize {
      self.top
  }
}

// 测试栈功能
fn test_stack() {
  let mut s = Stack::new(5);
  println!("执行入栈操作");
  println!("入栈 1: {}", s.push(1));
  s.print_stack();
  println!("入栈 2: {}", s.push(2));
  s.print_stack();

  println!("栈的长度: {}", s.len());

  println!("执行出栈操作");
  println!("出栈: {}", s.pop());
  s.print_stack();
  println!("出栈: {}", s.pop());
  s.print_stack();

  println!("清空栈");
  s.make_empty();
  s.print_stack();

  println!("测试结束");
}

fn main() {
  test_stack();
}

/*
jarry@MacBook-Pro stack % rustc stack.rs
jarry@MacBook-Pro stack % ./stack 
执行入栈操作
入栈 1: true
1 
入栈 2: true
1 2 
栈的长度: 2
执行出栈操作
出栈: 2
1 
出栈: 1
栈为空
清空栈
栈为空
测试结束
*/