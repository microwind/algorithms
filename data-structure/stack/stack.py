class Stack:
    def __init__(self, size):
        self.top = 0
        self.size = size
        self.data = [None] * size

    # 打印栈中的所有元素
    def print_stack(self):
        if self.is_empty():
            print("栈为空")
            return

        for i in range(self.top):
            print(self.data[i], end=" ")
        print()

    # 判断栈是否已满
    def is_full(self):
        return self.top == self.size

    # 判断栈是否为空
    def is_empty(self):
        return self.top == 0

    # 入栈操作
    def push(self, value):
        if self.is_full():
            return False

        self.data[self.top] = value
        self.top += 1
        return True

    # 出栈操作
    def pop(self):
        if self.is_empty():
            return 0

        self.top -= 1
        return self.data[self.top]

    # 清空栈
    def make_empty(self):
        self.top = 0

    # 获取栈中元素的个数
    def len(self):
        return self.top


# 测试栈功能
def test_stack():
    s = Stack(5)
    print("执行入栈操作")
    print(f"入栈 1: {s.push(1)}")
    s.print_stack()
    print(f"入栈 2: {s.push(2)}")
    s.print_stack()

    print("执行出栈操作")
    print(f"出栈: {s.pop()}")
    s.print_stack()
    print(f"出栈: {s.pop()}")
    s.print_stack()

    print("清空栈")
    s.make_empty()
    s.print_stack()

    print("测试结束")


test_stack()

"""
jarry@MacBook-Pro stack % python stack.py
执行入栈操作
入栈 1: True
1 
入栈 2: True
1 2 
执行出栈操作
出栈: 2
1 
出栈: 1
栈为空
清空栈
栈为空
测试结束
"""