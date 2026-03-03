#include <stdio.h>

/**
 * 反转数组的函数
 * 
 * @param arr 待反转的整型数组
 * @param n 数组的元素个数
 * @return 无返回值，直接修改原数组
 */
void reverseArray(int arr[], int n)
{
  int temp;  // 临时变量，用于交换数组元素
  
  // 交换数组的前后元素，只需要遍历数组的前一半
  // i 从数组开头开始，同时与数组末尾的元素进行交换
  for (int i = 0; i < n / 2; i++)
  {
    // 三步交换法：先保存前半部分元素，再将后半部分元素放到前半部分
    // 最后将保存的前半部分元素放到后半部分
    temp = arr[i];               // 保存当前位置的元素
    arr[i] = arr[n - i - 1];     // 将末尾对应位置的元素移到当前位置
    arr[n - i - 1] = temp;       // 将保存的元素放到末尾对应位置
  }
}

/**
 * 主函数
 * 
 * @return 程序执行状态，0表示成功
 */
int main()
{
  int arr[] = {1, 2, 3, 4, 5};          // 初始化一个整型数组，包含5个元素
  int n = sizeof(arr) / sizeof(arr[0]); // 计算数组的元素个数

  // 输出反转前的数组
  printf("反转前的数组: ");
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");

  reverseArray(arr, n); // 调用反转函数，修改原数组

  // 输出反转后的数组
  printf("反转后的数组: ");
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  
  return 0; // 程序正常结束
}