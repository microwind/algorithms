package main

import "fmt"

// 定义栈的元素类型
type item int

// Stack 结构体定义
type Stack struct {
  top  int
  size int
  data []item
}

// 创建栈
func createStack(size int) *Stack {
  return &Stack{
    top:  0,
    size: size,
    data: make([]item, size),
  }
}

// 打印栈中的所有元素
func (s *Stack) printStack() {
  if s.isEmpty() {
    fmt.Println("栈为空")
    return
  }

  for i := 0; i < s.top; i++ {
    fmt.Printf("%d ", s.data[i])
  }
  fmt.Println()
}

// 判断栈是否已满
func (s *Stack) isFull() bool {
  return s.top == s.size
}

// 判断栈是否为空
func (s *Stack) isEmpty() bool {
  return s.top == 0
}

// 入栈操作
func (s *Stack) push(value item) bool {
  if s.isFull() {
    return false
  }

  s.data[s.top] = value
  s.top++
  return true
}

// 出栈操作
func (s *Stack) pop() item {
  if s.isEmpty() {
    return 0
  }

  s.top--
  return s.data[s.top]
}

// 清空栈
func (s *Stack) makeEmpty() {
  s.top = 0
}

// 获取栈中元素的个数
func (s *Stack) len() int {
  return s.top
}

// 测试栈功能
func testStack() {
  s := createStack(5)
  fmt.Println("执行入栈操作")
  fmt.Printf("入栈 1: %v\n", s.push(1))
  s.printStack()
  fmt.Printf("入栈 2: %v\n", s.push(2))
  s.printStack()

  fmt.Println("执行出栈操作")
  fmt.Printf("出栈: %d\n", s.pop())
  s.printStack()
  fmt.Printf("出栈: %d\n", s.pop())
  s.printStack()

  fmt.Println("清空栈")
  s.makeEmpty()
  s.printStack()

  fmt.Println("测试结束")
}

func main() {
  testStack()
}

/*
jarry@MacBook-Pro stack % go run stack.go
执行入栈操作
入栈 1: true
1
入栈 2: true
1 2
执行出栈操作
出栈: 2
1
出栈: 1
栈为空
清空栈
栈为空
测试结束
*/
