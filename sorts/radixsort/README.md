## 【基数排序算法详解】Java/Go/Python/JS/C不同语言实现

## 说明

基数排序（RadixSort）是一种非比较型整数排序算法，其原理是将整数按位数切割成不同的数字，然后按每个位数分别比较。由于整数也可以表达字符串（比如名字或日期）和特定格式的浮点数，所以基数排序也不是只能使用于整数。基数排序的发明可以追溯到1887年赫尔曼·何乐礼在列表机（Tabulation Machine）上的贡献。
s
基数排序的方式可以采用LSD（Least significant digital）或MSD（Most significant digital），LSD的排序方式由键值的最右边开始，而MSD则相反，由键值的最左边开始。每个数位的排序过程可使用计数排序。

## 实现过程

1. 将待排序数列（正整数）统一为同样的数位长度，数位较短的补零。
2. 每个数位单独排序，从最低位到最高位，或从最高位到最低位，由低到高比较好排。
3. 这样从最低位排序一直到最高位排序完成以后，数列就变成一个有序序列。

## 示意图

![基数排序](../../images/sort/radix1.png)
![基数排序](../../images/sort/radix2.gif)

## 性能分析
时间复杂度：O(k*N)
空间复杂度：O(k + N)
稳定性：稳定

# 代码

## Java

```java
class RadixSort {

  // 基数排序，基于计数排序的基础上，按数字的每个位置来排序
  public static int[] countingSort(int arr[], int exponent) {
    // 基数exponent按10进位，range为10
    int range = 10;
    int[] countList = new int[range];
    int[] sortedList = new int[arr.length];

    // 根据基数求得当前项目对应位置的数值，并给对应计数数组位置加1
    for (int i = 0; i < arr.length; i++) {
      int item = arr[i];
      // 根据exponent获得当前位置的数字是几，存入对应计数数组
      int idx = (item / exponent) % range;
      countList[idx] += 1;
    }

    // 根据位置计数，后面的位数为前面的累加之和
    for (int i = 1; i < range; i++) {
      countList[i] += countList[i - 1];
    }
    System.out.println("radixSort1 countingSort countList:" + Arrays.toString(countList));

    // 根据计数数组按顺序取出排序内容
    for (int i = arr.length - 1; i >= 0; i--) {
      int idx = (arr[i] / exponent) % range;
      // 根据计数位置得到顺序
      sortedList[countList[idx] - 1] = arr[i];
      countList[idx] -= 1;
    }

    // 最后赋值给原数据
    for (int i = 0; i < arr.length; i++) {
      arr[i] = sortedList[i];
    }
    System.out.println("radixSort1 -> sortedList:" + Arrays.toString(sortedList));
    return sortedList;
  }

  // 基数排序1，按数位大小，基于计数排序实现
  public static int[] radixSort1(int arr[]) {
    int max = arr[0];
    for (int i = 0; i < arr.length; i++) {
      if (arr[i] > max) {
        max = arr[i];
      }
    }
    // 根据最大值，逐个按进位(基数)来应用排序，exponent即数位。
    for (int exponent = 1; (max / exponent) > 0; exponent *= 10) {
      countingSort(arr, exponent);
    }
    return arr;
  }
}
```

## Python

```py
# 利用计数排序来实现基本排序
def counting_sort(arr, exponent):
    arr_len = len(arr)
    # 基数exponent按10进位，amount表示0-9的数字的长度，也是10个
    amount = 10
    count_list = [0] * amount
    sorted_list = [0] * arr_len

    # 根据基数求得当前项目对应位置的数值，并给对应计数数组位置加1
    for i in range(0, arr_len):
        index = arr[i] // exponent % amount
        count_list[index] += 1

    # 当前位置加上左侧位置，后面的位数为前面的累加之和
    for i in range(1, amount):
        count_list[i] += count_list[i - 1]

    # 构建输出数组，根据计数数组按顺序取得排序内容
    i = arr_len - 1
    while i >= 0:
        index = arr[i] // exponent % amount
        sorted_list[count_list[index] - 1] = arr[i]
        count_list[index] -= 1
        i -= 1

    # 复制输出数组到原始数组
    for i in range(0, arr_len):
        arr[i] = sorted_list[i]

    return arr

def radix_sort(arr):
    max_value = max(arr)
    # 根据最大值，逐个按进位(基数)来应用排序，exponent即数位。
    exponent = 1
    while max_value // exponent > 0:
        counting_sort(arr, exponent)
        exponent *= 10

    return arr
```

## Go

```go
// 基数排序2，基于计数排序实现，计数排序写在一个方法内
func radixSort2(arr []int) []int {
  var arrLen = len(arr)
  // 基数exponent按10进位，amount为10
  var amount = 10
  var sortedList = make([]int, arrLen)
  var max = arr[0]
  for i := 0; i < arrLen; i++ {
    if arr[i] > max {
      max = arr[i]
    }
  }

  // 根据基数求得当前项目对应位置的数值，并给对应计数数组位置加1
  // 按最大值补齐数位，基数exponent按10进位
  for exponent := 1; (max / exponent) > 0; exponent *= amount {

    // 计数数组，长度为10，0-9一共10个数字
    countList := make([]int, amount)
    // 根据基数得到当前位数，并给计数数组对应位置加1
    for i := 0; i < arrLen; i++ {
      var item = arr[i]
      var idx = (item / exponent) % amount
      countList[idx] += 1
    }

    // 计数排序构建，自前往后，逐个将上一项的值存入当前项
    for i := 1; i < amount; i++ {
      countList[i] += countList[i-1]
    }

    fmt.Println("radixSort2 -> countList:", countList)

    // 根据计数数组按顺序取出排序内容
    for i := arrLen - 1; i >= 0; i-- {
      var idx = (arr[i] / exponent) % amount
      sortedList[countList[idx]-1] = arr[i]
      countList[idx] -= 1
    }

    // 将新顺序赋值给原数组
    for i := 0; i < arrLen; i++ {
      arr[i] = sortedList[i]
    }
  }

  return arr
}
```

## JS

```js
// 1. 基数排序，基于计数排序的基础上，按数字的每个位置来排序
function radixSort1(arr) {

  function countingSort(arr, exponent) {
    const countList = []
    const range = 10
    countList.length = range
    countList.fill(0)
    for (let i = 0, l = arr.length; i < l; i++) {
      const item = arr[i]
      // 根据基数取得数位上的值，并给对应计数数组加1
      const idx = Math.floor((item / exponent) % range)
      countList[idx] += 1
    }
    console.log('countingSort countList:', countList)

    // 后面的位数为前面的累加之和
    for (let i = 1; i < range; i++) {
      countList[i] += countList[i - 1]
    }

    const sortedList = []
    // 补齐位数，根据计数数组按顺序取得排序内容
    for (let i = arr.length - 1; i >= 0; i--) {
      const idx = Math.floor((arr[i] / exponent) % range)
      sortedList[countList[idx] - 1] = arr[i]
      countList[idx] -= 1
    }

    // 根据新顺序重新调整原数组
    for (let i = 0; i < arr.length; i++) {
      arr[i] = sortedList[i]
    }

    return sortedList
  }

  const max = Math.max.apply(null, arr)
  // 根据最大值，逐个按进位(基数)来应用排序，exponent即基数。
  for (let exponent = 1; Math.floor(max / exponent) > 0; exponent *= 10) {
    countingSort(arr, exponent)
  }
  return arr
}
```

## TS

```ts
 class RadixSort {
  // 基数排序，基于计数排序的基础上，按数字的每个位置来排序
  countingSort(arr: Array<number>, exponent: number) {
    const countList = Array<number>()
    const range = 10;
    countList.length = range;
    countList.fill(0);
    for (let i = 0, l = arr.length; i < l; i++) {
      const item = arr[i];
      // 取得数字的最后一位，并给对应计数数组加1
      const idx = Math.floor((item / exponent) % range);
      countList[idx] += 1;
    }
    console.log("countingSort countList:", countList);

    // 根据位置计数，后面的位数为前面的累加之和
    for (let i = 1; i < range; i++) {
      countList[i] += countList[i - 1];
    }

    const sortedList = Array<number>();
    // 根据计数数组按顺序取出排序内容
    for (let i = arr.length - 1; i >= 0; i--) {
      const idx = Math.floor((arr[i] / exponent) % range);
      sortedList[countList[idx] - 1] = arr[i];
      countList[idx] -= 1;
    }

    // 最后赋值给原数据
    for (let i = 0; i < arr.length; i++) {
      arr[i] = sortedList[i];
    }
    return sortedList;
  }

  radixSort(arr: Array<number>) {
    let sortedList = Array<number>();
    const max = Math.max.apply(null, arr);
    for (let exponent = 1; Math.floor(max / exponent) > 0; exponent *= 10) {
      sortedList = this.countingSort(arr, exponent);
    }
    return sortedList;
  }
}
```

## C

```c
// 计数排序，根据基数按位进行计数
void counting_sort(int arr[], int len, int exponent)
{
  int output[len];
  int range = 10;
  int count_list[range];
  memset(count_list, 0, range * sizeof(int));
  // 根据数字所在位置进行计数
  for (int i = 0; i < len; i++)
  {
    int item = arr[i];
    int idx = (item / exponent) % range;
    count_list[idx]++;
  }

  // 构建计数排序，当前位置加上左侧位置，后面的位数为前面的累加之和
  for (int i = 1; i < range; i++)
  {
    count_list[i] += count_list[i - 1];
  }

  // 构建输出数组，根据计数数组按顺序取得排序内容
  for (int i = len - 1; i >= 0; i--)
  {
    int idx = (arr[i] / exponent) % range;
    output[count_list[idx] - 1] = arr[i];
    count_list[idx]--;
  }

  // 复制输出数组到原始数组
  for (int i = 0; i < len; i++)
  {
    arr[i] = output[i];
  }
}

// 基数排序
int *radix_sort(int arr[], int len)
{
  // 找出最大值
  int max_value = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] > max_value)
      max_value = arr[i];
  }

  // 根据最大值，逐个按进位(基数)来应用排序，exponent即数位。
  for (int exponent = 1; max_value / exponent > 0; exponent *= 10)
  {
    counting_sort(arr, len, exponent);
  }

  return arr;
}
```

# C++
```c++
// 基数排序，基于计数排序实现，计数排序写在一个方法内
int *radixSort(int *arr, int len)
{

  // 以10倍递进
  int range = 10;
  int output[len];

  int max = arr[0];
  for (int i = 0; i < len; i++)
  {
    if (arr[i] > max)
    {
      max = arr[i];
    }
  }

  // 根据最大值，逐个按进位(基数)来应用排序，exponent即基数。
  for (int exponent = 1; (max / exponent) > 0; exponent *= range)
  {

    // 计数数组，长度为10，0-9一共10个数字
    int countList[range];
    memset(countList, 0, range * sizeof(int));
    // 根据基数得到当前位数，并给计数数组对应位置加1
    for (int i = 0; i < len; i++)
    {
      int item = arr[i];
      int idx = (item / exponent) % range;
      countList[idx] += 1;
    }

    // 计数排序构建，自前往后，逐个将上一项的值存入当前项
    for (int i = 1; i < range; i++)
    {
      countList[i] += countList[i - 1];
    }

    // 根据计数数组按顺序取出排序内容
    for (int i = len - 1; i >= 0; i--)
    {
      int idx = (arr[i] / exponent) % range;
      output[countList[idx] - 1] = arr[i];
      countList[idx] -= 1;
    }

    // 复制输出数组到原始数组
    for (int i = 0; i < len; i++)
    {
      arr[i] = output[i];
    }
  }

  return arr;
}
```
# 链接

# 基数排序与计数排序、桶排序区别
    基数排序与计数排序、桶排序都使用桶的概念来排序，其差异如下：
    基数排序：根据数据的位数来分配桶，每一位对应一个桶，先将全部数据的位数按最大位数对齐，再根据位数上的值大小排列；
    计数排序：根据最大最小差值设定若干桶，每个桶对应一个数值，将数据放入桶里并把值存入下一个桶，最后按索引顺序取出对应桶里的值；
    桶排序：根据情况分为若干个桶，每个桶存储一定范围的数值，每个桶单独排序，最后按桶顺序取出数据；

基数排序算法源码：[https://github.com/microwind/algorithms/tree/master/sorts/radixsort](https://github.com/microwind/algorithms/tree/master/sorts/radixsort)

其他排序算法源码：[https://github.com/microwind/algorithms](https://github.com/microwind/algorithms)
