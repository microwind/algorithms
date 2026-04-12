/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 结构体数据结构 - Rust实现
 */

// Person 结构体：姓名、年龄、地址
struct Person {
  name: String,
  age: u32,
  address: String,
}

impl Person {
  fn new(name: &str, age: u32, address: &str) -> Person {
      Person {
          name: name.to_string(),
          age,
          address: address.to_string(),
      }
  }

  fn introduce(&self) {
      println!("Hi, I am {}, {} years old, from {}.", self.name, self.age, self.address);
  }
}

// Employee 结构体：组合 Person，加职位
struct Employee {
  person: Person,
  position: String,
}

impl Employee {
  fn new(name: &str, age: u32, address: &str, position: &str) -> Employee {
      Employee {
          person: Person::new(name, age, address),
          position: position.to_string(),
      }
  }

  fn introduce(&self) {
      println!("I am {}, a {} at the company, living in {}.", self.person.name, self.position, self.person.address);
  }
}

fn main() {
  let p1 = Person::new("Alice", 30, "123 Main St");
  p1.introduce();

  let e1 = Employee::new("Bob", 28, "456 Elm St", "Software Developer");
  e1.introduce();
}

/*
jarry@MacBook-Pro struct % rustc struct.rs 
jarry@MacBook-Pro struct % ./struct 
Hi, I am Alice, 30 years old, from 123 Main St.
I am Bob, a Software Developer at the company, living in 456 Elm St.
*/