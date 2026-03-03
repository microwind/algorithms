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
*/

class Activity {
  constructor(id, start, end) {
    this.id = id;
    this.start = start;
    this.end = end;
  }

  toString() {
    return `Activity(${this.id}: [${this.start}, ${this.end}])`;
  }
}

/*
*
 * Select the maximum number of non-overlapping activities
 * @param {Activity[]} activities - Array of activities
 * @returns {Activity[]} Selected activities
*/
function selectActivities(activities) {
  if (activities.length === 0) {
    return [];
  }

  // Sort by end time
  const sorted = [...activities].sort((a, b) => a.end - b.end);

  const selected = [sorted[0]];
  let lastEndTime = sorted[0].end;

  // Greedily select remaining activities
  for (let i = 1; i < sorted.length; i++) {
    if (sorted[i].start >= lastEndTime) {
      selected.push(sorted[i]);
      lastEndTime = sorted[i].end;
    }
  }

  return selected;
}

function testBasicExample() {
  console.log("\n[Test 1] Basic example with overlapping activities");

  const activities = [
    new Activity(1, 1, 3),
    new Activity(2, 2, 5),
    new Activity(3, 4, 6),
    new Activity(4, 6, 7),
    new Activity(5, 5, 8),
    new Activity(6, 8, 9),
  ];

  const selected = selectActivities(activities);

  console.log(`Input activities: [${activities.map(String).join(", ")}]`);
  console.log(`Selected activities: [${selected.map(String).join(", ")}]`);
  console.log(`Count: ${selected.length}`);
}

function testAllCompatible() {
  console.log("\n[Test 2] All activities compatible (non-overlapping)");

  const activities = [
    new Activity(1, 1, 2),
    new Activity(2, 2, 3),
    new Activity(3, 3, 4),
    new Activity(4, 4, 5),
  ];

  const selected = selectActivities(activities);

  console.log(`Selected activities: [${selected.map(String).join(", ")}]`);
  console.log(`Count: ${selected.length}`);
}

function testAllOverlapping() {
  console.log("\n[Test 3] All activities overlapping");

  const activities = [
    new Activity(1, 1, 10),
    new Activity(2, 2, 9),
    new Activity(3, 3, 8),
    new Activity(4, 4, 7),
  ];

  const selected = selectActivities(activities);

  console.log(`Selected activities: [${selected.map(String).join(", ")}]`);
  console.log(`Count: ${selected.length}`);
}

function testSingleActivity() {
  console.log("\n[Test 4] Single activity");

  const activities = [new Activity(1, 5, 10)];
  const selected = selectActivities(activities);

  console.log(`Selected activities: [${selected.map(String).join(", ")}]`);
  console.log(`Count: ${selected.length}`);
}

function testEmpty() {
  console.log("\n[Test 5] Empty input");

  const activities = [];
  const selected = selectActivities(activities);

  console.log(`Selected activities: [${selected.map(String).join(", ")}]`);
  console.log(`Count: ${selected.length}`);
}

function testComplexScheduling() {
  console.log("\n[Test 6] Complex scheduling scenario");

  const activities = [
    new Activity(1, 0, 6),
    new Activity(2, 1, 4),
    new Activity(3, 3, 5),
    new Activity(4, 5, 7),
    new Activity(5, 8, 9),
    new Activity(6, 5, 9),
  ];

  const selected = selectActivities(activities);

  console.log(`Selected activities: [${selected.map(String).join(", ")}]`);
  console.log(`Count: ${selected.length}`);
}

if (require.main === module) {
  console.log("==================================================");
  console.log("ACTIVITY SELECTION - Greedy Algorithm (JavaScript)");
  console.log("==================================================");

  testBasicExample();
  testAllCompatible();
  testAllOverlapping();
  testSingleActivity();
  testEmpty();
  testComplexScheduling();
}

module.exports = { Activity, selectActivities };
