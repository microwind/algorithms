/**
 * 结构体/对象示例 - 数据结构的组合
 *
 * 结构体是一种将多个不同类型的数据组合在一起的复合数据结构
 * 特点：
 * - 将相关的数据和操作封装在一起
 * - 提高代码的组织性和可维护性
 * - 支持继承和多态
 * 应用场景：
 * - 实体对象表示（如用户、产品等）
 * - 数据容器
 * - 业务逻辑封装
 */

/**
 * 基础结构体：Person（人）
 */
class Person {
  constructor(name, age, address) {
    this.name = name;
    this.age = age;
    this.address = address;
  }

  /**
   * 方法：显示个人信息
   */
  introduce() {
    console.log(`Hi, I am ${this.name}, ${this.age} years old, from ${this.address}.`);
  }

  /**
   * 方法：获取年龄
   */
  getAge() {
    return this.age;
  }

  /**
   * 方法：生日（年龄增加1）
   */
  birthday() {
    this.age++;
    console.log(`${this.name} had a birthday! Now ${this.age} years old.`);
  }
}

/**
 * 继承示例：Employee（员工）继承 Person
 */
class Employee extends Person {
  constructor(name, age, address, position, salary = 0) {
    super(name, age, address);  // 调用父类构造函数
    this.position = position;  // 职位
    this.salary = salary;  // 薪水
  }

  /**
   * 方法覆盖：显示员工信息
   */
  introduce() {
    console.log(`I am ${this.name}, a ${this.position} at the company, living in ${this.address}.`);
  }

  /**
   * 特有方法：获取工资
   */
  getSalary() {
    return this.salary;
  }

  /**
   * 特有方法：加薪
   */
  raiseSalary(amount) {
    this.salary += amount;
    console.log(`${this.name}'s salary increased by ${amount}. New salary: ${this.salary}`);
  }

  /**
   * 覆盖生日方法
   */
  birthday() {
    super.birthday();
    this.raiseSalary(1000);  // 生日加薪
  }
}

// ===== 测试代码 =====
console.log("=== Struct/Object Example ===");

console.log("\n--- Person Objects ---");
const p1 = new Person("Alice", 30, "123 Main St");
p1.introduce();

console.log("\n--- Employee Objects ---");
const e1 = new Employee("Bob", 28, "456 Elm St", "Software Developer", 50000);
e1.introduce();
console.log("Salary:", e1.getSalary());

console.log("\n--- Inheritance & Method Override ---");
e1.birthday();  // 调用子类覆盖的方法

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
