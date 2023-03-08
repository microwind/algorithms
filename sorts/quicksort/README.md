## 【快速排序算法详解】Java/Go/Python/JS/C不同语言实现

## 说明

快速排序（QuickSort），又称分区交换排序（partition-exchange sort），简称快排。快排是一种通过基准划分区块，再不断交换左右项的排序方式，其采用了分治法，减少了交换的次数。它的基本思想是：通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都比另外一部分的所有数据都要小，然后再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归或迭代进行，以此让整个数列变成有序序列。

## 实现过程

1. 在待排序区间找到一个基准点(pivot)，便于理解一般是位于数组中间的那一项。
2. 逐个循环数组将小于基准的项放左侧，将大于基准的项放在右侧。一般通过交换的方式来实现。
3. 将基准点左侧全部项和基点右侧全部项分别通过递归(或迭代)方式重复第1项，直到所有数组都交换完成。

## 示意图

![快速排序](../../images/sort/quick1.png)
![快速排序](../../images/sort/quick2.gif)

## 性能分析
平均时间复杂度：O(NlogN)
最佳时间复杂度：O(NlogN)
最差时间复杂度：O(N^2)
空间复杂度：根据实现方式的不同而不同，可以查看不同版本的源码

# 代码

## Java

```java
  /* 方式1,标准递归版本。需要左右不断交换，无需新建数组。 */
  static int[] quickSort1(int arr[], int low, int high) {
    int i = low > 0 ? low : 0;
    int j = high;
    int midIndex = (i + j) / 2;
    int pivot = arr[midIndex];

    System.out.println(
        " i=" + i + ", j=" + j + ", midIndex=" + midIndex + ", pivot=" + pivot + "  arr[]=" + Arrays.toString(arr));

    // 当左侧小于等于右侧则表示还有值没有对比，需要继续
    while (i <= j) {
      // 当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
      while (arr[i] < pivot) {
        System.out.println("arr[i] < pivot: i=" + i + ", j=" + j + ", pivot=" + pivot);
        i++;
      }
      // 当前右侧大于基准时左移，直到找出比基准值小的位置来
      while (arr[j] > pivot) {
        System.out.println("arr[i] > pivot: i=" + i + ", j=" + j + ", pivot=" + pivot);
        j--;
      }

      System.out.println("low=" + low + ", high=" + high + ", i=" + i + ", j=" + j + ", pivot=" + pivot);

      // 当左侧位置小于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
      if (i <= j) {
        int tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
        // 缩小搜查范围，直到左侧都小于基数，右侧都大于基数
        i++;
        j--;
      }
    }
    // 左侧小于基数位置，不断递归左边部分
    if (low < j) {
      System.out.println("  low < j:recursion: low=" + low + ", high=" + high + ", i=" + i + ", j=" + j + ", midIndex="
          + midIndex + ", pivot=" + pivot);
      quickSort1(arr, low, j);
    }
    // 基数位置小于右侧，不断递归右侧部分
    if (i < high) {
      System.out.println("  i < high:recursion: low=" + low + ", high=" + high + ", i=" + i + ", j=" + j + ", midIndex="
          + midIndex + ", pivot=" + pivot);
      quickSort1(arr, i, high);
    }

    return arr;
  }
```

## Python

```py
# 标准递归版本。需要左右不断交换，无需新建数组。
def quick_sort2(arr, left=None, right=None):

    i = left = left if left is not None else 0
    j = right = right if right is not None else len(arr) - 1
    mid_index = (i + j) / 2
    pivot = arr[mid_index]

    # 当左侧小于等于右侧则表示还有值没有对比，需要继续
    while (i <= j):
        # 当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
        while (arr[i] < pivot):
            print('arr[i] < pivot:',
                  ' i=' + str(i) + ' j=' + str(j) + ' pivot=' + str(pivot))
            i = i + 1

        # 当前右侧大于基准时左移，直到找出比基准值小的位置来
        while (arr[j] > pivot):
            print('arr[j] > pivot:',
                  ' i=' + str(i) + ' j=' + str(j) + ' pivot=' + str(pivot))
            j -= 1

        print(
            '  left=' + str(left) + ' right=' + str(right) + ' i=' + str(i) +
            ' j=' + str(j) + ' mid_index=' + str(mid_index) + ' pivot=' +
            str(pivot) + ' arr[]=', arr)

        # 当左侧位置小于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
        if (i <= j):
            [arr[i], arr[j]] = [arr[j], arr[i]]
            # 缩小搜查范围，直到左侧都小于基数，右侧都大于基数
            i += 1
            j -= 1

    # 左侧小于基数位置，不断递归左边部分
    if (left < j):
        print(
            'left < j:recursion:  left=' + str(left) + ' right=' + str(right) +
            ' i=' + str(i) + ' j=' + str(j) + 'arr[]', arr)
        quick_sort2(arr, left, j)

    # 基数位置小于右侧，不断递归右侧部分
    if (i < right):
        print(
            'i < right:recursion:  left=' + str(left) + ' right=' +
            str(right) + ' i=' + str(i) + ' j=' + str(j) + 'arr[]', arr)
        quick_sort2(arr, i, right)

    return arr
```

## Go

```go
// 把数组分按照基准值分为左右两部分，再返回新的中间位置作为排序的pivot
func partition(arr []int, left int, right int) int {
  // pivot基准可以任意挑选，这里取右侧
  var pivotIndex = right
  var pivot = arr[pivotIndex]
  var partitionIndex = left - 1
  for i := left; i < right; i++ {
    // 如果小于基准则进行交换
    if arr[i] < pivot {
      partitionIndex++
      arr[partitionIndex], arr[i] = arr[i], arr[partitionIndex]
    }
  }
  partitionIndex++
  arr[partitionIndex], arr[pivotIndex] = arr[pivotIndex], arr[partitionIndex]
  fmt.Println("partition:", arr, partitionIndex, arr[partitionIndex], arr[left:partitionIndex], arr[partitionIndex:right])
  return partitionIndex
}

// 方式2, 标准递归版本。左右不断分区交换，无需新建数组。
func quickSort2(arr []int, left int, right int) []int {
  if left < right {
    var pivot = partition(arr, left, right)
    quickSort2(arr, left, pivot-1)
    quickSort2(arr, pivot+1, right)
  }
  return arr
}
```

## JS

```js
// 方式4, 非递归版本。需要交换，无需新建数组，利用stack或queue遍历。
function quickSort4(arr, left, right) {
  left = left !== undefined ? left : 0
  right = right !== undefined ? right : arr.length - 1

  var stack = []
  var i, j, midIndex, pivot, tmp
  // 与标准递归版相同，只是将递归改为遍历栈的方式
  // 先将左右各取一个入栈
  stack.push(left)
  stack.push(right)

  while (stack.length) {
    // 如果栈内还有数据，则一并马上取出，其他逻辑与标准递归版同
    j = right = stack.pop()
    i = left = stack.pop()
    midIndex = Math.floor((i + j) / 2)
    pivot = arr[midIndex]
    while (i <= j) {
      while (arr[i] < pivot) {
        console.log('arr[i] < pivot:', ' i=' + i + ' j=' + j + ' pivot=' + pivot + 'arr[]=' + arr)
        i++
      }
      while (arr[j] > pivot) {
        console.log('arr[j] > pivot:', ' i=' + i + ' j=' + j + ' pivot=' + pivot + 'arr[]=' + arr)
        j--
      }

      if (i <= j) {
        tmp = arr[j]
        arr[j] = arr[i]
        arr[i] = tmp
        i++
        j--
      }
    }
    if (left < j) {
      // 与递归版不同，这里添加到栈中，以便继续循环
      console.log('left < j:recursion:  left=' + left + ' right=' + right + ' i=' + i + ' j=' + j + 'arr[]=' + arr)
      stack.push(left)
      stack.push(j)
    }
    if (i < right) {
      console.log('i < right:recursion:  left=' + left + ' right=' + right + ' i=' + i + ' j=' + j + 'arr[]=' + arr)
      stack.push(i)
      stack.push(right)
    }
  }
  return arr
}
```

## TS

```ts
  // 1. 方式1, 递归新建数组版本。无需交换，每个分区都是新数组，数量庞大
  quickSort1(arr: Array<number>) {
    // 数组长度为1就不再分级
    if (arr.length <= 1) {
      return arr
    }
    console.log('split array:', arr)

    var pivot: number
    const left = Array<number>()
    const right = Array<number>()
    // 设置中间数
    var midIndex = Math.floor(arr.length / 2)
    pivot = arr[midIndex]

    for (var i = 0, l = arr.length; i < l; i++) {
      console.log(
        'i=' + i + ' midIndex=' + midIndex + ' pivot=' + pivot + ' arr[]=' + arr
      )
      // 当中间基数等于i时，跳过当前。中间数递归完成时合并
      if (midIndex === i) {
        continue
      }
      // 当前数组端里面的项小于基数则添加到左侧
      if (arr[i] < pivot) {
        left.push(arr[i])
        // 大于等于则添加到右侧
      } else {
        right.push(arr[i])
      }
    }

    arr = this.quickSort1(left).concat(pivot, this.quickSort1(right))
    // 递归调用遍历左侧和右侧，再将中间值连接起来
    return arr
  }
```

## C

```c
/** 方式1,标准递归版本。需要左右不断交换，无需新建数组。*/
void *quickSort1(int arr[], int low, int high)
{
  int i = low > 0 ? low : 0;
  int j = high;
  int midIndex = (i + j) / 2;
  int pivot = arr[midIndex];

  // 当左侧小于等于右侧则表示还有值没有对比，需要继续
  while (i <= j)
  {
    // 当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
    while (arr[i] < pivot)
    {
      printf("\r\narr[i] < pivot: i=%d, j=%d, pivot=%d", i, j, pivot);
      i++;
    }
    // 当前右侧大于基准时左移，直到找出比基准值小的位置来
    while (arr[j] > pivot)
    {
      printf("\r\narr[i] > pivot: i=%d, j=%d, pivot=%d", i, j, pivot);
      j--;
    }

    printf("\r\n  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);

    // 当左侧位置小于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
    if (i <= j)
    {
      swap(&arr[i], &arr[j]);
      // 缩小搜查范围，直到左侧都小于基数，右侧都大于基数
      i++;
      j--;
    }
  }
  // 左侧小于基数位置，不断递归左边部分
  if (low < j)
  {
    printf("\r\n  low < j:recursion:  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);
    quickSort1(arr, low, j);
  }
  // 基数位置小于右侧，不断递归右侧部分
  if (i < high)
  {
    printf("\r\n  i < high:recursion:  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);
    quickSort1(arr, i, high);
  }

  return arr;
}
```

# C++
```c++
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
void printArray(int *arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    std::cout << arr[i] << " ";
  }
  std::cout << std::right;
}

// 把数组分按照基准值分为左右两部分，再返回新的中间位置作为排序的pivot
int partition(int *arr, int left, int right)
{
  // 这里的pivot以右侧为准
  int pivotIndex = right;
  int pivot = arr[pivotIndex];
  // 记录交换的位置
  int partitionIndex = left - 1;
  for (int i = left; i < right; i++)
  {
    // 如果小于基准则进行交换
    // 把小于基数的逐个往左侧放，大于基数的往右侧放
    if (arr[i] < pivot)
    {
      partitionIndex++;
      swap(&arr[partitionIndex], &arr[i]);
    }
  }
  partitionIndex++;
  // 最后把原基数调换到分区线的位置，并返回分区线位置
  swap(&arr[partitionIndex], &arr[pivotIndex]);
  return partitionIndex;
}

void quickSort(int *arr, int left, int right)
{
  if (left < right)
  {
    int pivot = partition(arr, left, right);
    quickSort(arr, left, pivot - 1);
    quickSort(arr, pivot + 1, right);
  }
}
```
# 链接

快速排序算法源码：[https://github.com/microwind/algorithms/tree/master/sorts/quicksort](https://github.com/microwind/algorithms/tree/master/sorts/quicksort)

其他排序算法源码：[https://github.com/microwind/algorithms](https://github.com/microwind/algorithms)
