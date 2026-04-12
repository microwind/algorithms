/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 栈数据结构 - TypeScript实现
 */

// 定义栈的元素类型
type Item = number;

// Stack 类定义
class Stack {
  private top: number;
  private size: number;
  private data: Item[];

  constructor(size: number) {
    this.top = 0;
    this.size = size;
    this.data = new Array(size);
  }

  // 打印栈中的所有元素
  printStack(): void {
    if (this.isEmpty()) {
      console.log("栈为空");
      return;
    }

    let output = "";
    for (let i = 0; i < this.top; i++) {
      output += this.data[i] + " ";
    }
    console.log(output.trim());
  }

  // 判断栈是否已满
  isFull(): boolean {
    return this.top === this.size;
  }

  // 判断栈是否为空
  isEmpty(): boolean {
    return this.top === 0;
  }

  // 入栈操作
  push(value: Item): boolean {
    if (this.isFull()) {
      return false;
    }

    this.data[this.top] = value;
    this.top++;
    return true;
  }

  // 出栈操作
  pop(): Item {
    if (this.isEmpty()) {
      return 0;
    }

    this.top--;
    return this.data[this.top];
  }

  // 清空栈
  makeEmpty(): void {
    this.top = 0;
  }

  // 获取栈中元素的个数
  length(): number {
    return this.top;
  }
}

// 测试栈功能
function testStack(): void {
  const s = new Stack(5);
  console.log("执行入栈操作");
  console.log("入栈 1:", s.push(1));
  s.printStack();
  console.log("入栈 2:", s.push(2));
  s.printStack();

  console.log("执行出栈操作");
  console.log("出栈:", s.pop());
  s.printStack();
  console.log("出栈:", s.pop());
  s.printStack();

  console.log("清空栈");
  s.makeEmpty();
  s.printStack();

  console.log("测试结束");
}

testStack();

/*
 * 输出结果：
 * 执行入栈操作
 * 入栈 1: true
 * 1
 * 入栈 2: true
 * 1 2
 * 执行出栈操作
 * 出栈: 2
 * 1
 * 出栈: 1
 * 栈为空
 * 清空栈
 * 栈为空
 * 测试结束
 */
