#include <iostream>
#include <string>

// 基本的结构体
struct Person
{
  std::string name;
  int age;
  std::string address;

  // 构造函数
  Person(std::string n, int a, std::string addr) : name(n), age(a), address(addr) {}

  // 方法
  void introduce()
  {
    std::cout << "Hi, I am " << name << ", " << age << " years old, from " << address << "." << std::endl;
  }
};

// 继承示例
struct Employee : public Person
{
  std::string position;

  // 构造函数
  Employee(std::string n, int a, std::string addr, std::string pos)
      : Person(n, a, addr), position(pos) {}

  // 方法覆盖
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
  e1.introduce(); // 覆盖了Person的introduce方法

  return 0;
}

/*
jarry@MacBook-Pro struct % g++ struct.cpp 
jarry@MacBook-Pro struct % ./a.out 
Hi, I am Alice, 30 years old, from 123 Main St.
I am Bob, a Software Developer at the company, living in 456 Elm St.
*/