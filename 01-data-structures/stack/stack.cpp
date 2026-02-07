#include <iostream>
#include <stack>
#include <list>
using namespace std;
int main()
{
  //构建 stack 容器适配器
  list<int> values = {1, 2, 3, 4, 5, 6};
  stack<int, list<int>> my_stack(values);
  //查看 my_stack 存储元素的个数
  cout << "size of my_stack: " << my_stack.size() << endl;
  cout << "my_stack.pop(): " << endl;
  // 弹出1个
  my_stack.pop();
  cout << "my_stack.top():" << my_stack.top() << endl;
  // 压栈1个
  my_stack.push(4);
  //将 my_stack 中存储的元素依次弹栈，直到其为空
  while (!my_stack.empty())
  {
    cout << "item:" << my_stack.top() << endl;
    //将栈顶元素弹栈
    my_stack.pop();
  }
  return 0;
}

/**
jarrys-MacBook-Pro:stack jarry$ g++ -std=c++11 -o stack stack.cpp
jarrys-MacBook-Pro:stack jarry$ ./stack 
size of my_stack: 3
my_stack.pop(): 
2
item:4
item:2
item:1
 */