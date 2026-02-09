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
 */

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd)]
struct Activity {
    id: usize,
    start: usize,
    end: usize,
}

impl Activity {
    fn new(id: usize, start: usize, end: usize) -> Self {
        Activity { id, start, end }
    }
}

/// Select the maximum number of non-overlapping activities
fn select_activities(mut activities: Vec<Activity>) -> Vec<Activity> {
    if activities.is_empty() {
        return vec![];
    }

    // Sort by end time
    activities.sort_by_key(|a| a.end);

    let mut selected = vec![activities[0].clone()];
    let mut last_end_time = activities[0].end;

    // Greedily select remaining activities
    for activity in &activities[1..] {
        if activity.start >= last_end_time {
            selected.push(activity.clone());
            last_end_time = activity.end;
        }
    }

    selected
}

fn test_basic_example() {
    println!("\n[Test 1] Basic example with overlapping activities");

    let activities = vec![
        Activity::new(1, 1, 3),
        Activity::new(2, 2, 5),
        Activity::new(3, 4, 6),
        Activity::new(4, 6, 7),
        Activity::new(5, 5, 8),
        Activity::new(6, 8, 9),
    ];

    let selected = select_activities(activities.clone());

    println!("Input activities: {:?}", activities);
    println!("Selected activities: {:?}", selected);
    println!("Count: {}", selected.len());
}

fn test_all_compatible() {
    println!("\n[Test 2] All activities compatible (non-overlapping)");

    let activities = vec![
        Activity::new(1, 1, 2),
        Activity::new(2, 2, 3),
        Activity::new(3, 3, 4),
        Activity::new(4, 4, 5),
    ];

    let selected = select_activities(activities);

    println!("Selected activities: {:?}", selected);
    println!("Count: {}", selected.len());
}

fn test_all_overlapping() {
    println!("\n[Test 3] All activities overlapping");

    let activities = vec![
        Activity::new(1, 1, 10),
        Activity::new(2, 2, 9),
        Activity::new(3, 3, 8),
        Activity::new(4, 4, 7),
    ];

    let selected = select_activities(activities);

    println!("Selected activities: {:?}", selected);
    println!("Count: {}", selected.len());
}

fn test_single_activity() {
    println!("\n[Test 4] Single activity");

    let activities = vec![Activity::new(1, 5, 10)];
    let selected = select_activities(activities);

    println!("Selected activities: {:?}", selected);
    println!("Count: {}", selected.len());
}

fn test_empty() {
    println!("\n[Test 5] Empty input");

    let activities: Vec<Activity> = vec![];
    let selected = select_activities(activities);

    println!("Selected activities: {:?}", selected);
    println!("Count: {}", selected.len());
}

fn test_complex_scheduling() {
    println!("\n[Test 6] Complex scheduling scenario");

    let activities = vec![
        Activity::new(1, 0, 6),
        Activity::new(2, 1, 4),
        Activity::new(3, 3, 5),
        Activity::new(4, 5, 7),
        Activity::new(5, 8, 9),
        Activity::new(6, 5, 9),
    ];

    let selected = select_activities(activities);

    println!("Selected activities: {:?}", selected);
    println!("Count: {}", selected.len());
}

fn main() {
    println!("==================================================");
    println!("ACTIVITY SELECTION - Greedy Algorithm (Rust)");
    println!("==================================================");

    test_basic_example();
    test_all_compatible();
    test_all_overlapping();
    test_single_activity();
    test_empty();
    test_complex_scheduling();
}
