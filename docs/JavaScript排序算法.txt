/**
 * 
 * @file:   javascript_sort.js
 * @desc:   javascript sort algorithm
 * @author: jarryli
*/
 
 // https://en.wikipedia.org/wiki/Sorting_algorithm
// http://damonare.github.io/2016/09/16/%E5%8D%81%E5%A4%A7%E7%BB%8F%E5%85%B8%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95%E6%80%BB%E7%BB%93%EF%BC%88javascript%E6%8F%8F%E8%BF%B0%EF%BC%89/
// http://wuchong.me/blog/2014/02/09/algorithm-sort-summary/
// http://www.programcreek.com/2012/11/top-10-algorithms-for-coding-interview/
//http://www.jianshu.com/p/1b4068ccd505

/* ##################### */
/* 1: 冒泡 
/* a与b交换>b与c交换->c与d交换
/* 外层与内层各遍历1次
/* 逐个比较交换
/* ##################### */

/** ## 冒泡1，自左往右遍历，当前项跟左侧的全部项逐个进行对比交换 ## **/
testcase:32615
loop 0-4:
  loop 0-3:
共:1+2+3+4=10次循环
1) 1:0=>23615 

2) 2:0=>23615
3) 2:1=>23615

4) 3:0=>13625
5) 3:1=>12635
6) 3:2=>12365

7) 4:0=>12365
8) 4:1=>12365
9) 4:2=>12365
10) 4:3=>12356

复杂度：O(n*n)
var arr = [3, 2, 6, 1, 5];

    [2, 1]  [3]   [6, 5]
  [2, 1]
 [1], [2], [3], [5], [6]

交换
 2 3 6 1 5
 1 3 6 2 5
   3 6 2 5
   2 6 3 5
  

2 3 6 1 5
2 6 3 1 5
2 6 1 3 5

2 6 1 3 5

1 2 3 

6 1 2 3 5


function bubbleSort(arr) {
    var no = 0, tmp, l = arr.length;
    for(var i = 0; i < l; i++) {
        for(var j = 0; j < i; j++) {
            no++;
            tmp = arr[i];
            if (arr[i] < arr[j]) {
                arr[i] = arr[j];
                arr[j] = tmp;
            }
            console.log(no, i, j, arr);
        }
    }
    return arr;
}
bubbleSort(arr);


/** ## 冒泡2，从左至右遍历，逐个跟右侧全部进行对比交换 ## **/
testcase:32615
loop 0-4:
  loop 0-3:
共:4+3+2+1=10次循环

1) 0:1=>23615 
2) 1:2=>23615
3) 2:3=>13625
4) 3:4=>13625

5) 0:1=>12635
6) 1:2=>12365
7) 2:3=>12365

8) 0:1=>12365
9) 1:2=>12365

10) 4:3=>12356
复杂度：O(n*n)
var arr = [3,2,6,1,5];
function bubbleSort(arr) {
    var no = 0, tmp, l = arr.length;
    for(var i = 0; i < l; i++) {
        for(var j = 0; j < l - i - 1; j++) {
            no++;
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
            console.log(no, j, j + 1, arr);
        }
    }
    return arr;
}
bubbleSort(arr);

冒泡改进，寻找上次遍历的地方
记录上一个循环里交换的坐标，后续的就不用再遍历

冒泡改进，内部两个循环，同时寻找最大与最小值，分别往前和后面放

2 选择排序
从当前要排序的数组中选取最小(大)的一个放到最前面作为排好顺序的数组中，
再从剩下未排序的数组中找出最小(大)的一个放到拍好顺序的数组末尾。要将之前找到的最小(大)的索引下标保存。
继续重复上一个步骤，直到完成。

内部两个循环

8 4 5 2 3 => 选择 2 放到最前面 变为 2 4 5 8 3 => 
选择 3 放到2后面  变为 2 3 5 8 4


3 插入排序
从要排序的项中先找出第一个作为排好序的项，遍历这个排好序的项，根据大小比较将第一个插入到拍好序项目的正确位置。
再重复第一步，直至遍历完全部未排号序的项

改进插入排序： 查找插入位置时使用二分查找的方式

// 二分查找，从有序列表中以找到某个值，先把需要排序的一分为2，
// 如果大于左边就继续找，否则从右侧开始找。如此反复即可实现。

如arr = [1,2,3,4,5],找5
mid=3，left=0, right=4 mid = (0+4)/2取整 = 2
如果arr[2] 等于 5 则直接返回，如果arr[2] > 5，说明在左侧，比如找的2，那right就需要往mid的左边移动一位
否则从右侧开始找，left往右边移动一位

int binSearch(const int *Array,int start,int end,int key)
{
    int left,right;
    int mid;
    left=start;
    right=end;
    //注释中为递归算法，执行效率低，不推荐
    /*
    if(key<Array[mid])
    {
        return(binSearch(Array,left,mid,key));
    }
    else if(key>Array[mid])
    {
        return(binSearch(Array,mid+1,right,key));
    }
    else
    return mid;
    */
 
    while(left<=right) {
        mid=(left+right)/2;
        if(key==Array[mid])  return mid;
        else if(key<Array[mid]) right=mid-1;
        else if(key>Array[mid]) left=mid+1;
    }
    return -1;
    //找不到就返回-1
}

   int BinSearch(SeqList R，KeyType K)
      { //在有序表R[1..n]中进行二分查找，成功时返回结点的位置，失败时返回零
        int low=1，high=n，mid； //置当前查找区间上、下界的初值
        while(low<=high){ //当前查找区间R[low..high]非空
          mid=(low+high)/2；
          if(R[mid].key==K) return mid； //查找成功返回
          if(R[mid].key>K)
             high=mid-1; //继续在R[low..mid-1]中查找
          else
             low=mid+1； //继续在R[mid+1..high]中查找
         }
        return 0； //当low>high时表示查找区间为空，查找失败
       } //BinSeareh


选择与插入很类似，选择是从未排序的选一个最小放到已经排好顺序的项的后面。
插入则从未排序的找到第一个，遍历(从后往前)已经排好序的项，插入到比自己小的后面。



4 希尔排序
第一个突破O(n^2)的排序算法；是简单插入排序的改进版；
它与插入排序的不同之处在于，它会优先比较距离较远的元素。希尔排序又叫缩小增量排序


5.归并排序
和选择排序一样，归并排序的性能不受输入数据的影响，但表现比选择排序好的多，因为始终都是O(n log n）的时间复杂度。代价是需要额外的内存空间。

归并排序是建立在归并操作上的一种有效的排序算法。该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。归并排序是一种稳定的排序方法。将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。若将两个有序表合并成一个有序表，称为2-路归并。

先分两组，然后比较第1组的第一个和第2组的第1个，根据大小往不同数组添加，最后递归合并数组

6. 快速排序（Quick Sort）
又是一种分而治之思想在排序算法上的典型应用。本质上来看，快速排序应该算是在冒泡排序基础上的递归分治法。
快速排序的最坏运行情况是O(n²)，比如说顺序数列的快排。但它的平摊期望时间是O(n log n) ，且O(n log n)记号中隐含的常数因子很小，比复杂度稳定等于O(n log n)的归并排序要小很多。所以，对绝大多数顺序性较弱的随机数列而言，快速排序总是优于归并排序。

7、堆排序 HeapSort
堆排序在 top K 问题中使用比较频繁。堆排序是采用二叉堆的数据结构来实现的，虽然实质上还是一维数组。二叉堆是一个近似完全二叉树 。

8、计数排序（Counting Sort）
计数排序的核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。
作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。

9、桶排序（Bucket Sort）
桶排序是计数排序的升级版。它利用了函数的映射关系，高效与否的关键就在于这个映射函数的确定。

10、基数排序（Radix Sort）

// http://hanchaohan.blog.51cto.com/2996417/1308498

11、二分查找递归与非递归

function BinarySearch(srcArray, des) {
       var low = 0; 
　　var high = srcArray.length-1; 
　　while(low <= high) { 
　　    var middle = (low + high)/2; 
　　    if(des == srcArray[middle]) { 
　　        return middle; 
　　    }else if(des <srcArray[middle]) { 
　　        high = middle - 1; 
　　    }else { 
　　        low = middle + 1; 
　　    } 
　　} 
　　return -1;

}

/**
 * [binarySearch 二分查找]
 * @param  {[type]} value      [查找元素]
 * @param  {[type]} arr        [数组]
 * @param  {[type]} startIndex [开始索引]
 * @param  {[type]} endIndex   [结束索引]
 * @return {[type]}            [返回查找元素的索引]
 */
function binarySearch(value,arr,startIndex,endIndex) {
	if(!value|| !(arr instanceof Array)) return;

	var len        = arr.length,
		startIndex = typeof startIndex === "number" ? startIndex : 0,
		endIndex   = typeof endIndex   === "number" ? endIndex   : len-1,
		midIndex   = Math.floor((startIndex + endIndex) / 2),
		midval     = arr[midIndex];

	if(startIndex > endIndex) return ;

	if(midval === value){
		return midIndex;
	}else if (midval > value) {
		return binarySearch(value, arr, startIndex, midIndex - 1);
	}else {
		return binarySearch(value, arr, midIndex + 1, endIndex);
	}
}
console.log(binarySearch(3,[1,2,3,4,5,6,7]));//2


// 二叉树深度优先遍历、广度优先排序
http://blog.csdn.net/alex8046/article/details/51910018
http://xdimh.github.io/2014/09/14/Data-Structure-BST-with-javascript/
http://stackoverflow.com/questions/19330731/tree-implementation-in-java-root-parents-and-children
https://code.tutsplus.com/articles/data-structures-with-javascript-tree--cms-23393


