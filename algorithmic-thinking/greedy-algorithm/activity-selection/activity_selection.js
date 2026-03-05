/*
*
 * 活动选择问题 - 贪心选择最多不重叠活动
 *
 * 算法思路：
 * - 给定一组活动，每个活动有开始和结束时间
 * - 选择最多数量的互不重叠活动
 * - 策略：按结束时间排序，贪心选择结束最早的活动
 *
 * 时间复杂度：O(n log n)（排序）
 * 空间复杂度：O(n)（存储结果）
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
 * 选择最多数量的不重叠活动（贪心算法）
 * @param {Activity[]} activities - 活动数组
 * @returns {Activity[]} 选中的活动数组
*/
function selectActivities(activities) {
  if (activities.length === 0) {
    return [];
  }

  // 按结束时间排序
  const sorted = [...activities].sort((a, b) => a.end - b.end);

  const selected = [sorted[0]];
  let lastEndTime = sorted[0].end;

  // 贪心选择剩余活动
  for (let i = 1; i < sorted.length; i++) {
    if (sorted[i].start >= lastEndTime) {
      selected.push(sorted[i]);
      lastEndTime = sorted[i].end;
    }
  }

  return selected;
}

function testBasicExample() {
  console.log("\n[测试1] 基本重叠活动");

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
  console.log("\n[测试2] 全部活动不重叠");

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
  console.log("\n[测试3] 全部活动重叠");

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
  console.log("\n[测试4] 单个活动");

  const activities = [new Activity(1, 5, 10)];
  const selected = selectActivities(activities);

  console.log(`Selected activities: [${selected.map(String).join(", ")}]`);
  console.log(`Count: ${selected.length}`);
}

function testEmpty() {
  console.log("\n[测试5] 空输入");

  const activities = [];
  const selected = selectActivities(activities);

  console.log(`Selected activities: [${selected.map(String).join(", ")}]`);
  console.log(`Count: ${selected.length}`);
}

function testComplexScheduling() {
  console.log("\n[测试6] 复杂调度场景");

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
  console.log("活动选择问题 - 贪心算法 (JavaScript)");
  console.log("==================================================");

  testBasicExample();
  testAllCompatible();
  testAllOverlapping();
  testSingleActivity();
  testEmpty();
  testComplexScheduling();
}

module.exports = { Activity, selectActivities };
