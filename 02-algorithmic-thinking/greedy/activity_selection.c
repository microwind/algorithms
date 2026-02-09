#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Activity Selection Problem - Select maximum compatible activities
 *
 * Algorithm:
 * - Given activities with start and end times
 * - Select the maximum number of non-overlapping activities
 * - Strategy: Sort by end time, then greedily select activities
 *
 * Time Complexity: O(n log n) - due to sorting
 * Space Complexity: O(n) - for storing results
 *
 * Key Insight:
 * Always picking the activity that ends earliest leaves the most room
 * for other activities. This greedy choice leads to optimal solution.
 */

typedef struct {
    int start;
    int end;
    int id;
} Activity;

/* Comparator for sorting by end time */
int compare_by_end_time(const void *a, const void *b) {
    Activity *act_a = (Activity *)a;
    Activity *act_b = (Activity *)b;
    return act_a->end - act_b->end;
}

/*
 * Select the maximum number of non-overlapping activities
 *
 * Args:
 *   activities: Array of activities
 *   n: Number of activities
 *   selected: Array to store selected activities
 *
 * Returns:
 *   Count of selected activities
 */
int activity_selection(Activity *activities, int n, Activity *selected) {
    if (n == 0) {
        return 0;
    }

    /* Sort activities by end time */
    qsort(activities, n, sizeof(Activity), compare_by_end_time);

    /* Always select the first activity (ends earliest) */
    int count = 1;
    selected[0] = activities[0];
    int last_end_time = activities[0].end;

    /* Greedily select remaining activities */
    for (int i = 1; i < n; i++) {
        /* If this activity starts after the last selected activity ends,
         * it's compatible and we select it */
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
