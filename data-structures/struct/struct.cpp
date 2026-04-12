/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 结构体数据结构 - C++实现
 */

#include <iostream>
#include <string>

// Person 结构体：姓名、年龄、地址
struct Person
{
  std::string name;
  int age;
  std::string address;

  Person(std::string n, int a, std::string addr) : name(n), age(a), address(addr) {}

  void introduce()
  {
    std::cout << "Hi, I am " << name << ", " << age << " years old, from " << address << "." << std::endl;
  }
};

// Employee 结构体：继承 Person，加职位
struct Employee : public Person
{
  std::string position;

  Employee(std::string n, int a, std::string addr, std::string pos)
      : Person(n, a, addr), position(pos) {}

  void introduce()
  {
    std::cout << "I am " << name << ", a " << position << " at the company, living in " << address << "." << std::endl;
  }
};

int main()
{
  Person p1("Alice", 30, "123 Main St");
  p1.introduce();

  Employee e1("Bob", 28, "456 Elm St", "Software Developer");
  e1.introduce();

  return 0;
}

/*
jarry@MacBook-Pro struct % g++ struct.cpp 
jarry@MacBook-Pro struct % ./a.out 
Hi, I am Alice, 30 years old, from 123 Main St.
I am Bob, a Software Developer at the company, living in 456 Elm St.
*/