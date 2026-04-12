/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 结构体数据结构 - JavaScript实现（扩展版）
 */

// Person 类：姓名、年龄、地址
class Person {
  constructor(name, age, address) {
    this.name = name;
    this.age = age;
    this.address = address;
  }

  introduce() {
    console.log(`Hi, I am ${this.name}, ${this.age} years old, from ${this.address}.`);
  }

  getAge() {
    return this.age;
  }

  birthday() {
    this.age++;
    console.log(`${this.name} had a birthday! Now ${this.age} years old.`);
  }
}

// Employee 类：继承 Person，增加职位和薪水
class Employee extends Person {
  constructor(name, age, address, position, salary = 0) {
    super(name, age, address);
    this.position = position;
    this.salary = salary;
  }

  introduce() {
    console.log(`I am ${this.name}, a ${this.position} at the company, living in ${this.address}.`);
  }

  getSalary() {
    return this.salary;
  }

  raiseSalary(amount) {
    this.salary += amount;
    console.log(`${this.name}'s salary increased by ${amount}. New salary: ${this.salary}`);
  }

  birthday() {
    super.birthday();
    this.raiseSalary(1000);
  }
}

console.log("=== Struct/Object Example ===");

console.log("\n--- Person Objects ---");
const p1 = new Person("Alice", 30, "123 Main St");
p1.introduce();

console.log("\n--- Employee Objects ---");
const e1 = new Employee("Bob", 28, "456 Elm St", "Software Developer", 50000);
e1.introduce();
console.log("Salary:", e1.getSalary());

console.log("\n--- Inheritance & Method Override ---");
e1.birthday();

/*
示例输出:
=== Struct/Object Example ===

--- Person Objects ---
Hi, I am Alice, 30 years old, from 123 Main St.

--- Employee Objects ---
I am Bob, a Software Developer at the company, living in 456 Elm St.
Salary: 50000

--- Inheritance & Method Override ---
Bob had a birthday! Now 29 years old.
Bob's salary increased by 1000. New salary: 51000
*/
