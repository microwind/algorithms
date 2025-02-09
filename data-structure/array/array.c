#include <stdio.h>

int main()
{
    // 定义一个包含5个整数的数组
    int arr[5] = {1, 2, 3, 4, 5};

    // 访问数组元素
    printf("Element at index 2: %d\n", arr[2]);

    // 修改数组元素
    arr[2] = 10;
    printf("Modified element at index 2: %d\n", arr[2]);

    // 遍历数组
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

/*
jarry@MacBook-Pro array % gcc -v
Apple clang version 16.0.0 (clang-1600.0.26.6)
Target: arm64-apple-darwin24.1.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
jarry@MacBook-Pro array % gcc array.c
jarry@MacBook-Pro array % ./a.out
Element at index 2: 3
Modified element at index 2: 10
1 2 10 4 5
*/