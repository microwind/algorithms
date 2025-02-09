public class Stack {

  private int top; // 栈顶指针
  private int size; // 栈的最大容量
  private int[] dataArray; // 存储栈元素的数组

  // 构造函数，动态创建栈并设置栈的最大容量
  public Stack(int size) {
    this.size = size;
    this.dataArray = new int[size]; // 为栈分配存储空间
    this.top = 0; // 初始化栈顶指针为 0
  }

  // 打印栈中的所有元素
  public void printStack() {
    if (isEmpty()) {
      System.out.println("栈为空");
      return;
    }

    for (int i = 0; i < top; i++) {
      System.out.print(dataArray[i] + " "); // 打印栈中的每个元素
    }

    System.out.println();
  }

  // 判断栈是否已满
  public boolean isFull() {
    return top == size; // 如果栈顶指针等于栈的最大容量，表示栈已满
  }

  // 判断栈是否为空
  public boolean isEmpty() {
    return top == 0; // 如果栈顶指针为 0，表示栈为空
  }

  // 入栈操作，将元素压入栈顶
  public boolean push(int data) {
    if (isFull()) { // 如果栈已满，返回 false
      return false;
    }

    dataArray[top++] = data; // 将数据压入栈顶，栈顶指针加 1
    return true;
  }

  // 出栈操作，返回栈顶元素并移除它
  public int pop() {
    if (isEmpty()) { // 如果栈为空，返回 0（假定 0 为无效值）
      return 0;
    }

    return dataArray[--top]; // 将栈顶指针减 1，返回栈顶元素
  }

  // 清空栈，将栈顶指针设置为 0
  public void makeEmpty() {
    top = 0; // 清空栈中的所有元素
  }

  // 获取栈的当前元素个数
  public int len() {
    return top; // 栈顶指针即为栈中元素的数量
  }

  // 测试栈的功能
  public static void testStack() {
    Stack s = new Stack(5); // 创建一个容量为 5 的栈
    System.out.println("执行入栈操作");

    // 测试入栈
    System.out.println("入栈 1: " + (s.push(1) ? "成功" : "失败"));
    s.printStack();

    System.out.println("入栈 2: " + (s.push(2) ? "成功" : "失败"));
    s.printStack();

    // 测试出栈
    System.out.println("执行出栈操作");
    System.out.println("出栈: " + s.pop());
    s.printStack();

    System.out.println("出栈: " + s.pop());
    s.printStack();

    // 测试栈为空的情况
    System.out.println("出栈: " + s.pop());
    s.printStack();

    // 测试清空栈
    System.out.println("清空栈");
    s.makeEmpty();
    s.printStack();

    System.out.println("测试结束。");
  }

  // 主函数
  public static void main(String[] args) {
    testStack(); // 调用测试栈的函数
  }
}

/*
 * jarry@MacBook-Pro stack % javac Stack.java
 * jarry@MacBook-Pro stack % java Stack
 * 执行入栈操作
 * 入栈 1: 成功
 * 1
 * 入栈 2: 成功
 * 1 2
 * 执行出栈操作
 * 出栈: 2
 * 1
 * 出栈: 1
 * 栈为空
 * 出栈: 0
 * 栈为空
 * 清空栈
 * 栈为空
 * 测试结束。
 */