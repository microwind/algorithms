/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 数组旋转算法 (Array Rotation)
 * 
 * 算法原理：
 * - 将数组的前d个元素移动到数组末尾
 * - 剩余元素左移填充前面位置
 * - 使用临时数组存储前d个元素
 * 
 * 旋转类型：
 * - 左旋转：元素向左移动，前面的移到后面
 * - 右旋转：元素向右移动，后面的移到前面
 * 
 * 本实现为左旋转（将前d个元素移到末尾）
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(d) - 需要临时存储d个元素
 * 
 * 优化：使用三次反转法可将空间复杂度降至O(1)
 * 
 * 应用场景：
 * - 循环移位
 * - 数据重排
 * - 图像处理中的像素移动
 */

#include <stdio.h>

/**
 * 数组左旋转函数
 * 将数组前d个元素移到数组末尾
 * 
 * @param arr 待旋转的数组
 * @param d   旋转位置数（前d个元素移到末尾）
 * @param n   数组长度
 * 
 * 算法步骤：
 * 1. 创建临时数组存储前d个元素
 * 2. 将剩余n-d个元素左移d位
 * 3. 将临时数组的元素放到数组末尾
 */
void rotateArray(int arr[], int d, int n)
{
  // 步骤1：保存前d个元素到临时数组
  int temp[d];
  for (int i = 0; i < d; i++)
  {
    temp[i] = arr[i];
  }
  
  // 步骤2：将剩余元素左移（向前移动d位）
  for (int i = 0; i < n - d; i++)
  {
    arr[i] = arr[i + d];
  }
  
  // 步骤3：将临时数组元素放到数组末尾
  for (int i = 0; i < d; i++)
  {
    arr[n - d + i] = temp[i];
  }
}

/**
 * 主函数：测试数组旋转
 * 
 * 测试用例：
 * 原数组: {1, 2, 3, 4, 5, 6, 7}
 * 旋转d=3位
 * 结果:   {4, 5, 6, 7, 1, 2, 3}
 */
int main()
{
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  int n = sizeof(arr) / sizeof(arr[0]);
  int d = 3;  // 旋转3位
  
  printf("Original array: ");
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  
  rotateArray(arr, d, n);
  
  printf("Rotated array (d=%d): ", d);
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}

/**
jarry@jarrys-MacBook-Pro rotate % gcc rotate_array.c
jarry@jarrys-MacBook-Pro rotate % ./a.out           
Rotated array: 4 5 6 7 1 2 3 %    
 */