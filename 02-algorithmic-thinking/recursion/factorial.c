#include <stdio.h>
/*
递归：代码简洁，逻辑清晰，适合解决分治问题，但可能存在栈溢出风险。
循环：效率更高，避免了函数调用开销，适合解决简单迭代问题，但代码复杂度可能较高。
计算阶乘的递归思维：
n! = n * (n-1)!，直到 n=0 时返回 1 作为递归终止条件。
*/
// 计算阶乘的递归函数，相比循环，递归有时候可以更方便解决遍历的问题。
long long factorial(int n) {
    if (n == 0) return 1;  // 递归终止条件
    return n * factorial(n - 1);  // 递归调用
}

#include <stdio.h>

// 循环版阶乘，以结果作为乘数
long long factorial_iterative(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
/*
factorial(5) 计算过程：
factorial(5) = 5 * factorial(4)
              = 5 * (4 * factorial(3))
              = 5 * (4 * (3 * factorial(2)))
              = 5 * (4 * (3 * (2 * factorial(1))))
              = 5 * (4 * (3 * (2 * (1 * factorial(0)))))
              = 5 * 4 * 3 * 2 * 1 * 1 = 120

=======

调用过程图：
factorial(5)
   ├──> factorial(4)
   │      ├──> factorial(3)
   │      │      ├──> factorial(2)
   │      │      │      ├──> factorial(1)
   │      │      │      │      ├──> factorial(0) = 1
   │      │      │      │      ├──> 1 * 1 = 1
   │      │      │      ├──> 2 * 1 = 2
   │      │      ├──> 3 * 2 = 6
   │      ├──> 4 * 6 = 24
   ├──> 5 * 24 = 120
*/
    int num = 5;
    printf("Factorial of %d is %lld\n", num, factorial(num));

    printf("Recursive: Factorial of %d is %lld\n", num, factorial_iterative(num));
    return 0;
}

/*
jarry@MacBook-Pro recursion % gcc factorial.c 
jarry@MacBook-Pro recursion % ./a.out 
Factorial of 5 is 120
Recursive: Factorial of 5 is 120
*/