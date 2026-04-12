/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 结构体数据结构 - Java实现
 */
// Person 类：表示一个人的基本信息
class Person {
    String name;
    int age;
    String address;

    // 构造函数：初始化 Person 对象的三个属性
    public Person(String name, int age, String address) {
        this.name = name;
        this.age = age;
        this.address = address;
    }

    public void introduce() {
        System.out.println("Hi, I am " + name + ", " + age + " years old, from " + address + ".");
    }
}

// Employee 类：继承 Person，增加职位信息
class Employee extends Person {
    String position;

    // 构造函数：调用父类构造函数初始化 Person 部分，再设置职位
    public Employee(String name, int age, String address, String position) {
        super(name, age, address); // 调用父类 Person 的构造函数
        this.position = position;  // 初始化职位
    }

    // 重写父类的 introduce 方法，输出员工特有的自我介绍
    @Override
    public void introduce() {
        System.out.println("I am " + name + ", a " + position + " at the company, living in " + address + ".");
    }
}

// 主类：程序的入口，演示 Person 和 Employee 的使用
public class Struct {
    public static void main(String[] args) {
        // 创建 Person 对象并调用 introduce 方法
        Person p1 = new Person("Alice", 30, "123 Main St");
        p1.introduce();

        // 创建 Employee 对象并调用重写后的 introduce 方法
        Employee e1 = new Employee("Bob", 28, "456 Elm St", "Software Developer");
        e1.introduce();
    }
}

/*
 * jarry@MacBook-Pro struct % javac Struct.java
 * jarry@MacBook-Pro struct % java Struct
 * Hi, I am Alice, 30 years old, from 123 Main St.
 * I am Bob, a Software Developer at the company, living in 456 Elm St.
 */