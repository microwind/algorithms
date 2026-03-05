/*
 *
 * 跳跃游戏 - 使用贪心判断能否到达最后一个下标
 *
 * 算法：
 * - 给定一个数组，每个元素表示当前位置最大可跳跃步数
 * - 判断是否可以到达最后一个下标
 * - 贪心策略：始终维护当前能到达的最远位置
 *
 * 时间复杂度：O(n)（单次遍历）
 * 空间复杂度：O(1)（不计输出）
 */

/*
 *
 * 判断是否能到达数组的最后一个下标
 * @param {number[]} nums - 数组，每个元素是当前位置最大可跳跃步数
 * @returns {boolean} 若能到达最后一个下标则为 true
 */
function canJump(nums) {
  if (!nums || nums.length <= 1) {
    return true;
  }

  let maxReach = 0;

  for (let i = 0; i < nums.length; i++) {
    // 如果当前位置超过了最远可达位置，则无法继续前进，返回 false
    if (i > maxReach) {
      return false;
    }

    // 更新当前能到达的最远位置
    maxReach = Math.max(maxReach, i + nums[i]);

    // 提前结束：一旦可以到达末尾，立刻返回 true
    if (maxReach >= nums.length - 1) {
      return true;
    }
  }

  return maxReach >= nums.length - 1;
}

/*
 *
 * 计算到达最后一个下标所需的最少跳跃次数
 * @param {number[]} nums - 数组，每个元素是当前位置最大可跳跃步数
 * @returns {number} 最少跳跃次数，若不可达则为 -1
 */
function minJumps(nums) {
  if (!nums || nums.length <= 1) {
    return 0;
  }

  // 先检查是否可以到达终点
  let maxReach = 0;
  for (let i = 0; i < nums.length - 1; i++) {
    if (i > maxReach) {
      return -1;
    }
    maxReach = Math.max(maxReach, i + nums[i]);
  }

  if (maxReach < nums.length - 1) {
    return -1;
  }

  // 使用贪心策略计算最少跳跃次数
  let jumps = 0;
  let currentEnd = 0;
  let farthest = 0;

  for (let i = 0; i < nums.length - 1; i++) {
    farthest = Math.max(farthest, i + nums[i]);

    if (i === currentEnd) {
      jumps++;
      currentEnd = farthest;
    }
  }

  return jumps;
}

/*
 *
 * 构造从起点到终点的一条跳跃路径
 * @param {number[]} nums - 数组，每个元素是当前位置最大可跳跃步数
 * @returns {number[]} 路径下标序列，不可达则返回空数组
 */
function jumpPath(nums) {
  if (!nums || nums.length === 0) {
    return [];
  }

  if (nums.length === 1) {
    return [0];
  }

  // 先检查是否可以到达终点
  let maxReach = 0;
  for (let i = 0; i < nums.length; i++) {
    if (i > maxReach) {
      return [];
    }
    maxReach = Math.max(maxReach, i + nums[i]);
    if (maxReach >= nums.length - 1) {
      break;
    }
  }

  if (maxReach < nums.length - 1) {
    return [];
  }

  // 贪心构造路径
  const path = [0];
  let currentPos = 0;

  // 遍历数组，构造跳跃路径
  while (currentPos < nums.length - 1) {
    // 初始化下一个位置为当前位置
    let nextPos = currentPos;
    // 初始化下一个位置能到达的最远位置为当前位置能到达的最远位置
    let maxNextReach = currentPos + nums[currentPos];

    // 遍历当前位置能到达的范围内，找到能到达的最远位置
    for (let i = currentPos + 1; i <= currentPos + nums[currentPos] && i < nums.length; i++) {
      // 如果当前位置能到达的最远位置小于当前位置能到达的最远位置，则更新当前位置能到达的最远位置
      if (i + nums[i] > maxNextReach) {
        maxNextReach = i + nums[i];
        nextPos = i;
      }
    }

    if (nextPos === currentPos) {
      return [];
    }

    path.push(nextPos);
    currentPos = nextPos;
  }

  return path;
}

/*
 *
 * 综合分析跳跃游戏问题
 * @param {number[]} nums - 数组，每个元素是当前位置最大可跳跃步数
 * @returns {Object} 分析结果对象，包含 canReach、minJumps 和 path
 */
function analyzeJumpGame(nums) {
  return {
    canReach: canJump(nums),
    minJumps: minJumps(nums),
    path: jumpPath(nums),
  };
}

function testBasicReachable() {
  console.log("\n[Test 1] Reachable - should return true");

  const nums = [2, 3, 1, 1, 4];
  const analysis = analyzeJumpGame(nums);

  console.log(`Input: [${nums.join(", ")}]`);
  console.log(`Can reach end: ${analysis.canReach}`);
  console.log(`Min jumps: ${analysis.minJumps}`);
  console.log(`Path: [${analysis.path.join(", ")}]`);
}

function testNotReachable() {
  console.log("\n[Test 2] Not reachable - should return false");

  const nums = [3, 2, 1, 0, 4];
  const result = canJump(nums);

  console.log(`Input: [${nums.join(", ")}]`);
  console.log(`Can reach end: ${result}`);
}

function testSingleElement() {
  console.log("\n[Test 3] Single element");

  const nums = [0];
  const result = canJump(nums);

  console.log(`Input: [${nums.join(", ")}]`);
  console.log(`Can reach end: ${result}`);
}

function testZeroJump() {
  console.log("\n[Test 4] All zeros except last");

  const nums = [0, 1];
  const result = canJump(nums);

  console.log(`Input: [${nums.join(", ")}]`);
  console.log(`Can reach end: ${result}`);
}

function testLargeJumps() {
  console.log("\n[Test 5] Large jumps available");

  const nums = [10, 0, 0, 0, 0];
  const analysis = analyzeJumpGame(nums);

  console.log(`Input: [${nums.join(", ")}]`);
  console.log(`Can reach end: ${analysis.canReach}`);
  console.log(`Min jumps: ${analysis.minJumps}`);
  console.log(`Path: [${analysis.path.join(", ")}]`);
}

function testMultipleJumps() {
  console.log("\n[Test 6] Requires multiple jumps");

  const nums = [2, 3, 1, 1, 1];
  const analysis = analyzeJumpGame(nums);

  console.log(`Input: [${nums.join(", ")}]`);
  console.log(`Can reach end: ${analysis.canReach}`);
  console.log(`Min jumps: ${analysis.minJumps}`);
  console.log(`Path: [${analysis.path.join(", ")}]`);
}

function testBlocked() {
  console.log("\n[Test 7] Blocked at second-to-last");

  const nums = [1, 0, 1, 0];
  const result = canJump(nums);

  console.log(`Input: [${nums.join(", ")}]`);
  console.log(`Can reach end: ${result}`);
}

function testTwoElement() {
  console.log("\n[Test 8] Two element array");

  const nums = [2, 3];
  const analysis = analyzeJumpGame(nums);

  console.log(`Input: [${nums.join(", ")}]`);
  console.log(`Can reach end: ${analysis.canReach}`);
  console.log(`Min jumps: ${analysis.minJumps}`);
  console.log(`Path: [${analysis.path.join(", ")}]`);
}

function testDecreasing() {
  console.log("\n[Test 9] Large array with decreasing values");

  const nums = [5, 4, 3, 2, 1, 0];
  const analysis = analyzeJumpGame(nums);

  console.log(`Input: [${nums.join(", ")}]`);
  console.log(`Can reach end: ${analysis.canReach}`);
  console.log(`Min jumps: ${analysis.minJumps}`);
  console.log(`Path: [${analysis.path.join(", ")}]`);
}

function testComplex() {
  console.log("\n[Test 10] Complex reachable scenario");

  const nums = [2, 5, 0, 0];
  const analysis = analyzeJumpGame(nums);

  console.log(`Input: [${nums.join(", ")}]`);
  console.log(`Can reach end: ${analysis.canReach}`);
  console.log(`Min jumps: ${analysis.minJumps}`);
  console.log(`Path: [${analysis.path.join(", ")}]`);
}

if (require.main === module) {
  console.log("==================================================");
  console.log("JUMP GAME - Greedy Approach (JavaScript)");
  console.log("==================================================");

  testBasicReachable();
  testNotReachable();
  testSingleElement();
  testZeroJump();
  testLargeJumps();
  testMultipleJumps();
  testBlocked();
  testTwoElement();
  testDecreasing();
  testComplex();
}

module.exports = { canJump, minJumps, jumpPath, analyzeJumpGame };
