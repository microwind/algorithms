#include <stdio.h>

// 反转数组的函数
void reverseArray(int arr[], int n)
{
  int temp;
  // 交换数组的前后元素
  for (int i = 0; i < n / 2; i++)
  {
    temp = arr[i];
    arr[i] = arr[n - i - 1];
    arr[n - i - 1] = temp;
  }
}

int main()
{
  int arr[] = {1, 2, 3, 4, 5};          // 初始化数组
  int n = sizeof(arr) / sizeof(arr[0]); // 计算数组的元素个数

  reverseArray(arr, n); // 调用反转函数

  // 输出反转后的数组
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  return 0;
}