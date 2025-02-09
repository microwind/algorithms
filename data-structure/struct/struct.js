// 基本结构体模拟
class Person {
  constructor(name, age, address) {
    this.name = name;
    this.age = age;
    this.address = address;
  }

  // 方法：显示个人信息
  introduce() {
    console.log(`Hi, I am ${this.name}, ${this.age} years old, from ${this.address}.`);
  }
}

// 继承示例
class Employee extends Person {
  constructor(name, age, address, position) {
    super(name, age, address); // 调用父类构造函数
    this.position = position;
  }

  // 方法覆盖：显示员工信息
  introduce() {
    console.log(`I am ${this.name}, a ${this.position} at the company, living in ${this.address}.`);
  }
}

// 使用示例
const p1 = new Person("Alice", 30, "123 Main St");
p1.introduce();

const e1 = new Employee("Bob", 28, "456 Elm St", "Software Developer");
e1.introduce(); // 覆盖了Person的introduce方法

/*
jarry@MacBook-Pro struct % node struct.js 
Hi, I am Alice, 30 years old, from 123 Main St.
I am Bob, a Software Developer at the company, living in 456 Elm St.
*/