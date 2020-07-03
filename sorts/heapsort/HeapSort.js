class HeapSort {
    constructor(arr) {
        this.arr = arr;
        this.heapSort();
    }
    getParent(i) {
        return Math.floor((i - 1) / 2);
    }
    getLeft(i) {
        return 2 * i + 1;
    }
    getRight(i) {
        return 2 * i + 2;
    }
    maxHeapify(idx, size) {
        let max = idx;
        const arr = this.arr;
        const left = this.getLeft(idx);
        const right = this.getRight(idx);
        if (left < size && arr[left] > arr[max]) {
            max = left;
        }
        if (right < size && arr[right] > arr[max]) {
            max = right;
        }
        console.log('idx=', idx, 'left=', left, 'right=', right, 'max=', max, 'size:', size);
        if (max !== idx) {
            [arr[idx], arr[max]] = [arr[max], arr[idx]];
            this.maxHeapify(max, size);
        }
    }
    heapSort() {
        const arr = this.arr;
        const len = arr.length;
        // 最底层的父节点
        let parent = this.getParent(len) - 1;
        // 最底层的子节点
        let child = len - 1;
        // 从最后的父节点开始遍历，把最大的那个父节点冒出到堆顶
        while (parent >= 0) {
            this.maxHeapify(parent, len);
            console.warn('parent sort:', parent, arr);
            parent--;
        }
        console.warn('child start:', 'parent=' + parent, ' child=' + child);
        // 从子节点往上开始交换和保持大顶堆
        while (child > 0) {
            // 将顶端的父节点与当前子节点互换
            [arr[0], arr[child]] = [arr[child], arr[0]];
            // 自最底层往上遍历排序
            this.maxHeapify(0, child);
            console.warn('child sort:', child, arr);
            child--;
        }
        return arr;
    }
}
(function () {
    const arr = [7, 11, 9, 10, 12, 13, 8];
    console.log('start sort:', arr);
    console.time('heapSort');
    new HeapSort(arr);
    console.timeEnd('heapSort');
    console.log('sorted:', arr);
})();
/**
jarrys-MacBook-Pro:heapsort jarry$ tsc HeapSort.ts -t es2020
jarrys-MacBook-Pro:heapsort jarry$ node HeapSort.js
start sort: [ 7, 11, 9, 10, 12, 13, 8 ]
idx= 2 left= 5 right= 6 max= 5 size: 7
idx= 5 left= 11 right= 12 max= 5 size: 7
parent sort: 2 [ 7, 11, 13, 10, 12, 9, 8 ]
idx= 1 left= 3 right= 4 max= 4 size: 7
idx= 4 left= 9 right= 10 max= 4 size: 7
parent sort: 1 [ 7, 12, 13, 10, 11, 9, 8 ]
idx= 0 left= 1 right= 2 max= 2 size: 7
idx= 2 left= 5 right= 6 max= 5 size: 7
idx= 5 left= 11 right= 12 max= 5 size: 7
parent sort: 0 [ 13, 12, 9, 10, 11, 7, 8 ]
child start: parent=-1  child=6
idx= 0 left= 1 right= 2 max= 1 size: 6
idx= 1 left= 3 right= 4 max= 4 size: 6
idx= 4 left= 9 right= 10 max= 4 size: 6
child sort: 6 [ 12, 11, 9, 10, 8, 7, 13 ]
idx= 0 left= 1 right= 2 max= 1 size: 5
idx= 1 left= 3 right= 4 max= 3 size: 5
idx= 3 left= 7 right= 8 max= 3 size: 5
child sort: 5 [ 11, 10, 9, 7, 8, 12, 13 ]
idx= 0 left= 1 right= 2 max= 1 size: 4
idx= 1 left= 3 right= 4 max= 1 size: 4
child sort: 4 [ 10, 8, 9, 7, 11, 12, 13 ]
idx= 0 left= 1 right= 2 max= 2 size: 3
idx= 2 left= 5 right= 6 max= 2 size: 3
child sort: 3 [ 9, 8, 7, 10, 11, 12, 13 ]
idx= 0 left= 1 right= 2 max= 1 size: 2
idx= 1 left= 3 right= 4 max= 1 size: 2
child sort: 2 [ 8, 7, 9, 10, 11, 12, 13 ]
idx= 0 left= 1 right= 2 max= 0 size: 1
child sort: 1 [ 7, 8, 9, 10, 11, 12, 13 ]
heapSort: 4.307ms
sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
 */ 
