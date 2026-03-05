#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 随机采样（Reservoir Sampling）- C 版本
 *
 * 从一个数据流（或数组）中随机选择 k 个元素，
 * 保证每个元素被选中的概率都为 k/n。
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(k)
 */

// 对数组 data（长度 n）执行水库采样，结果存入 reservoir（长度至少为 k）
void reservoir_sampling(const int *data, int n, int k, int *reservoir) {
    if (k <= 0 || n <= 0) return;

    int i;
    // 前 k 个元素直接进入水库
    for (i = 0; i < n && i < k; i++) {
        reservoir[i] = data[i];
    }

    // 从第 k 个元素开始，按概率替换
    for (; i < n; i++) {
        // 生成 [0, i] 的随机整数
        int j = rand() % (i + 1);
        if (j < k) {
            reservoir[j] = data[i];
        }
    }
}

// 打印整数数组
void print_array(const int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

int main(void) {
    srand((unsigned int)time(NULL));

    printf("========== Random Sampling (C) ==========\n");

    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = (int)(sizeof(data) / sizeof(data[0]));
    int k = 3;
    int reservoir[3];

    printf("数据: ");
    print_array(data, n);

    for (int t = 1; t <= 3; t++) {
        reservoir_sampling(data, n, k, reservoir);
        printf("第 %d 次采样: ", t);
        print_array(reservoir, k);
    }

    return 0;
}

