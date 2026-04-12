/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 结构体数据结构 - Go实现
 */

package main

import "fmt"

// 基本结构体：定义Person结构体，包含姓名、年龄和地址
type Person struct {
  Name    string // 姓名
  Age     int    // 年龄
  Address string // 地址
}

// 构造函数（Go 没有正式的构造函数，但可以使用工厂函数）
// 参数name：姓名
// 参数age：年龄
// 参数address：地址
// 返回值：指向Person结构体的指针
func NewPerson(name string, age int, address string) *Person {
  return &Person{name, age, address} // 创建并返回Person结构体的指针
}

// 方法：自我介绍
// 接收者p：指向Person结构体的指针
func (p *Person) Introduce() {
  fmt.Printf("Hi, I am %s, %d years old, from %s.\n", p.Name, p.Age, p.Address)
}

// 继承示例（通过嵌套结构体）：Employee结构体嵌入Person结构体
// Go通过结构体嵌入（embedding）来实现类似继承的效果
type Employee struct {
  Person   // 嵌入Person结构体，自动获得Person的所有字段和方法
  Position string // 职位
}

// 构造函数：初始化Employee结构体
// 参数name：姓名
// 参数age：年龄
// 参数address：地址
// 参数position：职位
// 返回值：指向Employee结构体的指针
func NewEmployee(name string, age int, address string, position string) *Employee {
  return &Employee{Person: Person{name, age, address}, Position: position} // 创建并返回Employee结构体的指针
}

// 方法覆盖：重写嵌入的Person的Introduce方法
// 接收者e：指向Employee结构体的指针
func (e *Employee) Introduce() {
  fmt.Printf("I am %s, a %s at the company, living in %s.\n", e.Name, e.Position, e.Address)
}

func main() {
  // 创建Person对象并初始化
  p1 := NewPerson("Alice", 30, "123 Main St")
  p1.Introduce() // 调用Person的Introduce方法

  // 创建Employee对象并初始化（演示结构体嵌入和方法覆盖）
  e1 := NewEmployee("Bob", 28, "456 Elm St", "Software Developer")
  e1.Introduce() // 调用Employee的Introduce方法，覆盖了Person的Introduce方法
}

/*
jarry@MacBook-Pro struct % go run struct.go
Hi, I am Alice, 30 years old, from 123 Main St.
I am Bob, a Software Developer at the company, living in 456 Elm St.
*/
