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

// 选择最多数量的不重叠活动
fn select_activities(mut activities: Vec<Activity>) -> Vec<Activity> {
    if activities.is_empty() {
        return vec![];
    }

    // 按结束时间排序
    activities.sort_by_key(|a| a.end);

    let mut selected = vec![activities[0].clone()];
    let mut last_end_time = activities[0].end;

    // 贪心选择剩余的活动
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
