// 基本结构体模拟
/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 结构体数据结构 - JavaScript实现
 */
// Person 类：姓名、年龄、地址
class Person {
  // 构造函数：初始化姓名、年龄、地址
  constructor(name, age, address) {
    this.name = name;
    this.age = age;
    this.address = address;
  }

  // 自我介绍
  introduce() {
    console.log(`Hi, I am ${this.name}, ${this.age} years old, from ${this.address}.`);
  }
}

// Employee 类：继承 Person，增加职位
class Employee extends Person {
  // 构造函数：调用父类构造函数，并设置职位
  constructor(name, age, address, position) {
    super(name, age, address);  // 调用 Person 构造函数
    this.position = position;
  }

  // 重写自我介绍方法
  introduce() {
    console.log(`I am ${this.name}, a ${this.position} at the company, living in ${this.address}.`);
  }
}

// 使用示例
const p1 = new Person("Alice", 30, "123 Main St");
p1.introduce();

const e1 = new Employee("Bob", 28, "456 Elm St", "Software Developer");
e1.introduce();

/*
jarry@MacBook-Pro struct % node struct.js 
Hi, I am Alice, 30 years old, from 123 Main St.
I am Bob, a Software Developer at the company, living in 456 Elm St.
*/