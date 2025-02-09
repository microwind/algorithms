class Person {
  String name;
  int age;
  String address;

  // 构造函数
  public Person(String name, int age, String address) {
    this.name = name;
    this.age = age;
    this.address = address;
  }

  // 方法
  public void introduce() {
    System.out.println("Hi, I am " + name + ", " + age + " years old, from " + address + ".");
  }
}

// 继承示例
class Employee extends Person {
  String position;

  // 构造函数
  public Employee(String name, int age, String address, String position) {
    super(name, age, address);
    this.position = position;
  }

  // 方法覆盖
  @Override
  public void introduce() {
    System.out.println("I am " + name + ", a " + position + " at the company, living in " + address + ".");
  }
}

public class Struct {
  public static void main(String[] args) {
    Person p1 = new Person("Alice", 30, "123 Main St");
    p1.introduce();

    Employee e1 = new Employee("Bob", 28, "456 Elm St", "Software Developer");
    e1.introduce(); // 覆盖了Person的introduce方法
  }
}

/*
 * jarry@MacBook-Pro struct % javac Struct.java
 * jarry@MacBook-Pro struct % java Struct
 * Hi, I am Alice, 30 years old, from 123 Main St.
 * I am Bob, a Software Developer at the company, living in 456 Elm St.
 */