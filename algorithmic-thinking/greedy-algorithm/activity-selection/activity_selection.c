#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 活动选择问题 - 选择最多数量的相容活动
 *
 * 算法：
 * - 给定一组带有开始时间和结束时间的活动
 * - 选择数量最多的互不重叠活动
 * - 策略：按结束时间排序，然后贪心地选择活动
 *
 * 时间复杂度：O(n log n)（排序）
 * 空间复杂度：O(n)（存储结果）
 *
 * 关键思想：
 * 总是优先选择结束时间最早的活动，可以为后续活动留下最多空间，
 * 这一贪心选择可以得到最优解。
 */

typedef struct {
    int start;
    int end;
    int id;
} Activity;

/*
 * 按结束时间排序的比较函数
 */
int compare_by_end_time(const void *a, const void *b) {
    Activity *act_a = (Activity *)a;
    Activity *act_b = (Activity *)b;
    return act_a->end - act_b->end;
}

/*
 * 选择最多数量的不重叠活动
 *
 * 参数：
 *   activities: 活动数组
 *   n: 活动数量
 *   selected: 用于存放被选中活动的数组
 *
 * 返回：
 *   选中活动的数量
 */
int activity_selection(Activity *activities, int n, Activity *selected) {
    if (n == 0) {
        return 0;
    }

    /*
     * 按结束时间对活动进行排序
     */
    qsort(activities, n, sizeof(Activity), compare_by_end_time);

    /*
     * 总是先选择结束时间最早的第一个活动
     */
    int count = 1;
    selected[0] = activities[0];
    int last_end_time = activities[0].end;

    /*
     * 贪心选择剩余的活动
     */
    for (int i = 1; i < n; i++) {
        /*
         * 如果当前活动的开始时间不早于上一个已选活动的结束时间，
         * 则视为相容，可以选择该活动
         */
        if (activities[i].start >= last_end_time) {
            selected[count] = activities[i];
            last_end_time = activities[i].end;
            count++;
        }
    }

    return count;
}

void test_basic_example() {
    printf("\n[Test 1] Basic example with overlapping activities\n");

    Activity activities[] = {
        {1, 3, 1}, {2, 5, 2}, {4, 6, 3},
        {6, 7, 4}, {5, 8, 5}, {8, 9, 6}
    };
    int n = 6;

    Activity selected[n];
    int count = activity_selection(activities, n, selected);

    printf("Input activities:\n");
    for (int i = 0; i < n; i++) {
        printf("  Activity %d: [%d, %d]\n", activities[i].id, activities[i].start, activities[i].end);
    }

    printf("Selected activities: %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("  Activity %d: [%d, %d]\n", selected[i].id, selected[i].start, selected[i].end);
    }
}

void test_all_compatible() {
    printf("\n[Test 2] All activities compatible (non-overlapping)\n");

    Activity activities[] = {
        {1, 2, 1}, {2, 3, 2}, {3, 4, 3}, {4, 5, 4}
    };
    int n = 4;

    Activity selected[n];
    int count = activity_selection(activities, n, selected);

    printf("Selected activities: %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("  Activity %d: [%d, %d]\n", selected[i].id, selected[i].start, selected[i].end);
    }
}

void test_all_overlapping() {
    printf("\n[Test 3] All activities overlapping\n");

    Activity activities[] = {
        {1, 10, 1}, {2, 9, 2}, {3, 8, 3}, {4, 7, 4}
    };
    int n = 4;

    Activity selected[n];
    int count = activity_selection(activities, n, selected);

    printf("Selected activities: %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("  Activity %d: [%d, %d]\n", selected[i].id, selected[i].start, selected[i].end);
    }
}

void test_single_activity() {
    printf("\n[Test 4] Single activity\n");

    Activity activities[] = {{5, 10, 1}};
    int n = 1;

    Activity selected[n];
    int count = activity_selection(activities, n, selected);

    printf("Selected activities: %d\n", count);
}

void test_empty() {
    printf("\n[Test 5] Empty input\n");

    Activity *activities = NULL;
    int n = 0;
    Activity selected[1];

    int count = activity_selection(activities, n, selected);
    printf("Selected activities: %d\n", count);
}

void test_complex_scheduling() {
    printf("\n[Test 6] Complex scheduling scenario\n");

    Activity activities[] = {
        {0, 6, 1}, {1, 4, 2}, {3, 5, 3},
        {5, 7, 4}, {8, 9, 5}, {5, 9, 6}
    };
    int n = 6;

    Activity selected[n];
    int count = activity_selection(activities, n, selected);

    printf("Selected activities: %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("  Activity %d: [%d, %d]\n", selected[i].id, selected[i].start, selected[i].end);
    }
}

int main() {
    printf("==================================================\n");
    printf("ACTIVITY SELECTION - Greedy Algorithm (C)\n");
    printf("==================================================\n");

    test_basic_example();
    test_all_compatible();
    test_all_overlapping();
    test_single_activity();
    test_empty();
    test_complex_scheduling();

    return 0;
}
