/*
*
 * Maximize Number - Remove k digits to get maximum value
 *
 * Algorithm:
 * - Given a digit string and k, remove k digits to maximize the resulting number
 * - Use a greedy stack-based approach
 *
 * Time Complexity: O(n) - each digit is pushed/popped at most once
 * Space Complexity: O(n) - for the stack
*/

/*
*
 * Remove k digits from the string to get maximum resulting number
 * @param {string} numStr - String of digits
 * @param {number} k - Number of digits to remove
 * @returns {string} String representing the maximum number
*/
function removeKDigits(numStr, k) {
  if (k >= numStr.length) {
    return "0";
  }

  if (k === 0) {
    return numStr;
  }

  // Stack-based greedy approach
  const stack = [];
  let toDelete = k;

  for (const digit of numStr) {
    // Remove smaller digits from stack when we encounter a larger digit
    while (toDelete > 0 && stack.length > 0 && stack[stack.length - 1] < digit) {
      stack.pop();
      toDelete--;
    }
    stack.push(digit);
  }

  // If we still have digits to delete, remove from the end
  while (toDelete > 0) {
    stack.pop();
    toDelete--;
  }

  // Build result
  let result = stack.join("");

  // Handle leading zeros
  result = result.replace(/^0+/, "");

  return result === "" ? "0" : result;
}

/*
*
 * Remove k digits with position tracking
 * @param {string} numStr - String of digits
 * @param {number} k - Number of digits to remove
 * @returns {Object} Object with result and deleted positions
*/
function removeKDigitsWithTracking(numStr, k) {
  if (k >= numStr.length) {
    return { result: "0", deletedPositions: [] };
  }

  if (k === 0) {
    return { result: numStr, deletedPositions: [] };
  }

  const stack = [];
  const deletedPositions = [];
  let toDelete = k;

  for (let i = 0; i < numStr.length; i++) {
    const digit = numStr[i];
    while (toDelete > 0 && stack.length > 0 && stack[stack.length - 1][0] < digit) {
      const [, pos] = stack.pop();
      deletedPositions.push(pos);
      toDelete--;
    }
    stack.push([digit, i]);
  }

  // Delete remaining from end if needed
  while (toDelete > 0 && stack.length > 0) {
    const [, pos] = stack.pop();
    deletedPositions.push(pos);
    toDelete--;
  }

  // Build result
  let result = stack.map(([digit]) => digit).join("");

  // Handle leading zeros
  result = result.replace(/^0+/, "");

  return {
    result: result === "" ? "0" : result,
    deletedPositions: deletedPositions.sort((a, b) => a - b),
  };
}

function testStandardExample() {
  console.log("\n[Test 1] Standard example from problem");

  const numStr = "1432219";
  const k = 3;
  const result = removeKDigits(numStr, k);

  console.log(`Input: '${numStr}', k=${k}`);
  console.log(`Output: '${result}'`);
  console.log(`Expected: '4321'`);
}

function testLeadingZeros() {
  console.log("\n[Test 2] Remove leading zeros");

  const numStr = "10200";
  const k = 1;
  const result = removeKDigits(numStr, k);

  console.log(`Input: '${numStr}', k=${k}`);
  console.log(`Output: '${result}'`);
  console.log(`Expected: '200'`);
}

function testSameDigits() {
  console.log("\n[Test 3] All same digits");

  const numStr = "1111";
  const k = 2;
  const result = removeKDigits(numStr, k);

  console.log(`Input: '${numStr}', k=${k}`);
  console.log(`Output: '${result}'`);
  console.log(`Expected: '11'`);
}

function testDescendingOrder() {
  console.log("\n[Test 4] Descending digits - remove from end");

  const numStr = "54321";
  const k = 2;
  const result = removeKDigits(numStr, k);

  console.log(`Input: '${numStr}', k=${k}`);
  console.log(`Output: '${result}'`);
  console.log(`Expected: '321'`);
}

function testAscendingOrder() {
  console.log("\n[Test 5] Ascending digits - remove from front");

  const numStr = "12345";
  const k = 2;
  const result = removeKDigits(numStr, k);

  console.log(`Input: '${numStr}', k=${k}`);
  console.log(`Output: '${result}'`);
  console.log(`Expected: '345'`);
}

function testRemoveAll() {
  console.log("\n[Test 6] Remove all digits");

  const numStr = "123";
  const k = 3;
  const result = removeKDigits(numStr, k);

  console.log(`Input: '${numStr}', k=${k}`);
  console.log(`Output: '${result}'`);
  console.log(`Expected: '0'`);
}

function testRemoveZero() {
  console.log("\n[Test 7] Remove zero digits");

  const numStr = "1234";
  const k = 0;
  const result = removeKDigits(numStr, k);

  console.log(`Input: '${numStr}', k=${k}`);
  console.log(`Output: '${result}'`);
  console.log(`Expected: '1234'`);
}

function testMultipleZeros() {
  console.log("\n[Test 8] Multiple zeros in middle");

  const numStr = "100200";
  const k = 2;
  const result = removeKDigits(numStr, k);

  console.log(`Input: '${numStr}', k=${k}`);
  console.log(`Output: '${result}'`);
}

function testMixed() {
  console.log("\n[Test 9] Mixed digits");

  const numStr = "112";
  const k = 1;
  const result = removeKDigits(numStr, k);

  console.log(`Input: '${numStr}', k=${k}`);
  console.log(`Output: '${result}'`);
  console.log(`Expected: '12'`);
}

function testLargeNumber() {
  console.log("\n[Test 10] With deletion position tracking");

  const numStr = "987654321";
  const k = 4;
  const result = removeKDigitsWithTracking(numStr, k);

  console.log(`Input: '${numStr}', k=${k}`);
  console.log(`Output: '${result.result}'`);
  console.log(`Deleted positions: [${result.deletedPositions.join(", ")}]`);
}

if (require.main === module) {
  console.log("==================================================");
  console.log("MAXIMIZE NUMBER - Remove k Digits (JavaScript)");
  console.log("==================================================");

  testStandardExample();
  testLeadingZeros();
  testSameDigits();
  testDescendingOrder();
  testAscendingOrder();
  testRemoveAll();
  testRemoveZero();
  testMultipleZeros();
  testMixed();
  testLargeNumber();
}

module.exports = { removeKDigits, removeKDigitsWithTracking };
