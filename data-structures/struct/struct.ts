/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 结构体数据结构 - TypeScript实现
 */

// Person 类：姓名、年龄、地址
class Person {
  name: string;
  age: number;
  address: string;

  constructor(name: string, age: number, address: string) {
    this.name = name;
    this.age = age;
    this.address = address;
  }

  introduce(): void {
    console.log(`Hi, I am ${this.name}, ${this.age} years old, from ${this.address}.`);
  }
}

// Employee 类：继承 Person，增加职位
class Employee extends Person {
  position: string;

  constructor(name: string, age: number, address: string, position: string) {
    super(name, age, address);
    this.position = position;
  }

  introduce(): void {
    console.log(`I am ${this.name}, a ${this.position} at the company, living in ${this.address}.`);
  }
}

const p1 = new Person("Alice", 30, "123 Main St");
p1.introduce();

const e1 = new Employee("Bob", 28, "456 Elm St", "Software Developer");
e1.introduce();

/*
 * 输出结果：
 * Hi, I am Alice, 30 years old, from 123 Main St.
 * I am Bob, a Software Developer at the company, living in 456 Elm St.
 */
