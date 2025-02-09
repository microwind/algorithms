package main

import "fmt"

// 基本结构体
type Person struct {
  Name    string
  Age     int
  Address string
}

// 构造函数（Go 没有正式的构造函数，但可以使用工厂函数）
func NewPerson(name string, age int, address string) *Person {
  return &Person{name, age, address}
}

// 方法
func (p *Person) Introduce() {
  fmt.Printf("Hi, I am %s, %d years old, from %s.\n", p.Name, p.Age, p.Address)
}

// 继承示例（通过嵌套结构体）
type Employee struct {
  Person   // 嵌入Person结构体，模拟继承
  Position string
}

// 构造函数
func NewEmployee(name string, age int, address string, position string) *Employee {
  return &Employee{Person: Person{name, age, address}, Position: position}
}

// 方法覆盖
func (e *Employee) Introduce() {
  fmt.Printf("I am %s, a %s at the company, living in %s.\n", e.Name, e.Position, e.Address)
}

func main() {
  p1 := NewPerson("Alice", 30, "123 Main St")
  p1.Introduce()

  e1 := NewEmployee("Bob", 28, "456 Elm St", "Software Developer")
  e1.Introduce() // 覆盖了Person的Introduce方法
}

/*
jarry@MacBook-Pro struct % go run struct.go
Hi, I am Alice, 30 years old, from 123 Main St.
I am Bob, a Software Developer at the company, living in 456 Elm St.
*/
