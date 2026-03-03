// 基本的结构体
struct Person {
  name: String,
  age: u32,
  address: String,
}

impl Person {
  // 构造函数
  fn new(name: &str, age: u32, address: &str) -> Person {
      Person {
          name: name.to_string(),
          age,
          address: address.to_string(),
      }
  }

  // 方法
  fn introduce(&self) {
      println!("Hi, I am {}, {} years old, from {}.", self.name, self.age, self.address);
  }
}

// 继承示例：使用组合模拟继承
struct Employee {
  person: Person,
  position: String,
}

impl Employee {
  // 构造函数
  fn new(name: &str, age: u32, address: &str, position: &str) -> Employee {
      Employee {
          person: Person::new(name, age, address),
          position: position.to_string(),
      }
  }

  // 方法
  fn introduce(&self) {
      println!("I am {}, a {} at the company, living in {}.", self.person.name, self.position, self.person.address);
  }
}

fn main() {
  let p1 = Person::new("Alice", 30, "123 Main St");
  p1.introduce();

  let e1 = Employee::new("Bob", 28, "456 Elm St", "Software Developer");
  e1.introduce();  // 覆盖了Person的introduce方法
}

/*
jarry@MacBook-Pro struct % rustc struct.rs 
jarry@MacBook-Pro struct % ./struct 
Hi, I am Alice, 30 years old, from 123 Main St.
I am Bob, a Software Developer at the company, living in 456 Elm St.
*/