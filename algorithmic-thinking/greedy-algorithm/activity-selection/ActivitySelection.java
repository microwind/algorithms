import java.util.*;

/*
*
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

class Activity implements Comparable<Activity> {
    int id;
    int start;
    int end;

    Activity(int id, int start, int end) {
        this.id = id;
        this.start = start;
        this.end = end;
    }

    @Override
    public int compareTo(Activity other) {
        return Integer.compare(this.end, other.end);
    }

    @Override
    public String toString() {
        return "Activity(" + id + ": [" + start + ", " + end + "])";
    }
}

public class ActivitySelection {
    /*
*
     * Select the maximum number of non-overlapping activities
     *
     * @param activities List of activities
     * @return List of selected activities
*/
    static List<Activity> selectActivities(List<Activity> activities) {
        if (activities.isEmpty()) {
            return new ArrayList<>();
        }

        // Sort activities by end time (greedy choice)
        Collections.sort(activities);

        List<Activity> selected = new ArrayList<>();
        selected.add(activities.get(0));
        int lastEndTime = activities.get(0).end;

        // Greedily select remaining activities
        for (int i = 1; i < activities.size(); i++) {
            Activity current = activities.get(i);
            if (current.start >= lastEndTime) {
                selected.add(current);
                lastEndTime = current.end;
            }
        }

        return selected;
    }

    static void testBasicExample() {
        System.out.println("\n[Test 1] Basic example with overlapping activities");

        List<Activity> activities = Arrays.asList(
            new Activity(1, 1, 3),
            new Activity(2, 2, 5),
            new Activity(3, 4, 6),
            new Activity(4, 6, 7),
            new Activity(5, 5, 8),
            new Activity(6, 8, 9)
        );

        List<Activity> selected = selectActivities(activities);

        System.out.println("Input activities: " + activities);
        System.out.println("Selected activities: " + selected);
        System.out.println("Count: " + selected.size());
    }

    static void testAllCompatible() {
        System.out.println("\n[Test 2] All activities compatible (non-overlapping)");

        List<Activity> activities = Arrays.asList(
            new Activity(1, 1, 2),
            new Activity(2, 2, 3),
            new Activity(3, 3, 4),
            new Activity(4, 4, 5)
        );

        List<Activity> selected = selectActivities(activities);

        System.out.println("Selected activities: " + selected);
        System.out.println("Count: " + selected.size());
    }

    static void testAllOverlapping() {
        System.out.println("\n[Test 3] All activities overlapping");

        List<Activity> activities = Arrays.asList(
            new Activity(1, 1, 10),
            new Activity(2, 2, 9),
            new Activity(3, 3, 8),
            new Activity(4, 4, 7)
        );

        List<Activity> selected = selectActivities(activities);

        System.out.println("Selected activities: " + selected);
        System.out.println("Count: " + selected.size());
    }

    static void testSingleActivity() {
        System.out.println("\n[Test 4] Single activity");

        List<Activity> activities = Collections.singletonList(
            new Activity(1, 5, 10)
        );

        List<Activity> selected = selectActivities(activities);

        System.out.println("Selected activities: " + selected);
        System.out.println("Count: " + selected.size());
    }

    static void testEmpty() {
        System.out.println("\n[Test 5] Empty input");

        List<Activity> activities = new ArrayList<>();
        List<Activity> selected = selectActivities(activities);

        System.out.println("Selected activities: " + selected);
        System.out.println("Count: " + selected.size());
    }

    static void testComplexScheduling() {
        System.out.println("\n[Test 6] Complex scheduling scenario");

        List<Activity> activities = Arrays.asList(
            new Activity(1, 0, 6),
            new Activity(2, 1, 4),
            new Activity(3, 3, 5),
            new Activity(4, 5, 7),
            new Activity(5, 8, 9),
            new Activity(6, 5, 9)
        );

        List<Activity> selected = selectActivities(activities);

        System.out.println("Selected activities: " + selected);
        System.out.println("Count: " + selected.size());
    }

    public static void main(String[] args) {
        System.out.println("==================================================");
        System.out.println("ACTIVITY SELECTION - Greedy Algorithm (Java)");
        System.out.println("==================================================");

        testBasicExample();
        testAllCompatible();
        testAllOverlapping();
        testSingleActivity();
        testEmpty();
        testComplexScheduling();
    }
}
