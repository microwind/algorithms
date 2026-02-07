class Stack {
  constructor(size) {
    this.top = 0;
    this.size = size;
    this.data = new Array(size);
  }

  // 打印栈中的所有元素
  printStack() {
    if (this.isEmpty()) {
      console.log("栈为空");
      return;
    }

    for (let i = 0; i < this.top; i++) {
      process.stdout.write(this.data[i] + " ");
    }
    console.log();
  }

  // 判断栈是否已满
  isFull() {
    return this.top === this.size;
  }

  // 判断栈是否为空
  isEmpty() {
    return this.top === 0;
  }

  // 入栈操作
  push(value) {
    if (this.isFull()) {
      return false;
    }

    this.data[this.top] = value;
    this.top++;
    return true;
  }

  // 出栈操作
  pop() {
    if (this.isEmpty()) {
      return 0;
    }

    this.top--;
    return this.data[this.top];
  }

  // 清空栈
  makeEmpty() {
    this.top = 0;
  }

  // 获取栈中元素的个数
  len() {
    return this.top;
  }
}

// 测试栈功能
function testStack() {
  let s = new Stack(5);
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
jarry@MacBook-Pro stack % node stack.js
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