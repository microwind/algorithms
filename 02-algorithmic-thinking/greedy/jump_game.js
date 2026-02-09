/**
 * Jump Game - Can reach the last index with greedy jumps
 *
 * Algorithm:
 * - Given an array where each element is the maximum jump length from that position
 * - Determine if you can reach the last index
 * - Greedy approach: track the maximum index we can reach so far
 *
 * Time Complexity: O(n) - single pass through array
 * Space Complexity: O(1) - excluding output
 */

/**
 * Determine if we can reach the last index of the array
 * @param {number[]} nums - Array where each element is max jump length
 * @returns {boolean} True if we can reach the last index
 */
function canJump(nums) {
  if (!nums || nums.length <= 1) {
    return true;
  }

  let maxReach = 0;

  for (let i = 0; i < nums.length; i++) {
    // If current position is beyond what we can reach, return false
    if (i > maxReach) {
      return false;
    }

    // Update the maximum position we can reach
    maxReach = Math.max(maxReach, i + nums[i]);

    // Early termination: if we can reach the end, return true
    if (maxReach >= nums.length - 1) {
      return true;
    }
  }

  return maxReach >= nums.length - 1;
}

/**
 * Find the minimum number of jumps needed to reach the last index
 * @param {number[]} nums - Array where each element is max jump length
 * @returns {number} Minimum jumps needed, or -1 if unreachable
 */
function minJumps(nums) {
  if (!nums || nums.length <= 1) {
    return 0;
  }

  // Check if reachable
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

  // Find minimum jumps using greedy
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

/**
 * Find a path from start to end
 * @param {number[]} nums - Array where each element is max jump length
 * @returns {number[]} Path indices, or empty array if unreachable
 */
function jumpPath(nums) {
  if (!nums || nums.length === 0) {
    return [];
  }

  if (nums.length === 1) {
    return [0];
  }

  // Check if reachable
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

  // Greedy path construction
  const path = [0];
  let currentPos = 0;

  while (currentPos < nums.length - 1) {
    let nextPos = currentPos;
    let maxNextReach = currentPos + nums[currentPos];

    for (let i = currentPos + 1; i <= currentPos + nums[currentPos] && i < nums.length; i++) {
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

/**
 * Analyze a jump game problem comprehensively
 * @param {number[]} nums - Array where each element is max jump length
 * @returns {Object} Analysis with canReach, minJumps, and path
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
