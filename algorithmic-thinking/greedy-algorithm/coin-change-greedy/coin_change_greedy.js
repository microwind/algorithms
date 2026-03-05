/*
 *
 * 零钱兑换问题 - 贪心算法
 *
 * 算法：
 * - 使用贪心策略：每次选择不超过剩余金额的最大面值硬币
 * - 持续用最大面值硬币去抵扣，直到金额为 0
 * - 注意：这种贪心解并不总是最优
 *
 * 重要说明：该贪心算法并不适用于所有硬币体系！
 */

class CoinChangeResult {
  constructor(count, coins) {
    this.count = count;
    this.coins = coins;
  }

  toString() {
    if (this.count === -1) {
      return "Impossible";
    }
    return `${this.count} coins: [${this.coins.join(", ")}]`;
  }
}

/*
 *
 * 使用贪心算法求最少硬币数（不一定最优）
 * @param {number[]} coins - 硬币面值数组
 * @param {number} amount - 目标金额
 * @returns {CoinChangeResult} 结果（硬币数量和具体硬币列表）
 */
function coinChangeGreedy(coins, amount) {
  if (amount === 0) {
    return new CoinChangeResult(0, []);
  }

  // 将硬币面值按降序排序
  const sorted = [...coins].sort((a, b) => b - a);

  let count = 0;
  const coinsUsed = [];
  let remaining = amount;

  for (const coin of sorted) {
    while (remaining >= coin) {
      remaining -= coin;
      coinsUsed.push(coin);
      count++;
    }
  }

  if (remaining !== 0) {
    return new CoinChangeResult(-1, []);
  }

  return new CoinChangeResult(count, coinsUsed);
}

/*
 *
 * 使用动态规划求最少硬币数（一定最优）
 * @param {number[]} coins - 硬币面值数组
 * @param {number} amount - 目标金额
 * @returns {CoinChangeResult} 结果（硬币数量和具体硬币列表）
 */
function coinChangeDP(coins, amount) {
  if (amount === 0) {
    return new CoinChangeResult(0, []);
  }

  const dp = new Array(amount + 1).fill(Infinity);
  dp[0] = 0;
  const parent = new Array(amount + 1).fill(-1);

  for (let currAmount = 1; currAmount <= amount; currAmount++) {
    for (const coin of coins) {
      if (coin <= currAmount && dp[currAmount - coin] !== Infinity) {
        if (dp[currAmount - coin] + 1 < dp[currAmount]) {
          dp[currAmount] = dp[currAmount - coin] + 1;
          parent[currAmount] = coin;
        }
      }
    }
  }

  if (dp[amount] === Infinity) {
    return new CoinChangeResult(-1, []);
  }

  // 还原一组最优解中使用的硬币
  const coinsUsed = [];
  let curr = amount;
  while (curr > 0) {
    const coin = parent[curr];
    coinsUsed.push(coin);
    curr -= coin;
  }

  return new CoinChangeResult(dp[amount], coinsUsed);
}

function compareGreedyVsDP(coins, amount) {
  const greedy = coinChangeGreedy(coins, amount);
  const dp = coinChangeDP(coins, amount);

  console.log(`Coins: [${coins.join(", ")}], Amount: ${amount}`);
  console.log(`Greedy: ${greedy}`);
  console.log(`DP:     ${dp}`);

  if (greedy.count !== -1 && dp.count !== -1) {
    if (greedy.count === dp.count) {
      console.log("✓ Greedy is optimal for this input");
    } else {
      console.log(`✗ Greedy is suboptimal (difference: ${greedy.count - dp.count})`);
    }
  }
  console.log();
}

function testStandardCoins() {
  console.log("\n[Test 1] US Coins (greedy optimal)");
  const result = coinChangeGreedy([1, 5, 10, 25], 41);
  console.log("Coins: [1, 5, 10, 25], Amount: 41");
  console.log(`Result: ${result}`);
}

function testGreedyFails1() {
  console.log("\n[Test 2] Greedy fails case");
  compareGreedyVsDP([1, 3, 4], 6);
}

function testGreedyFails2() {
  console.log("\n[Test 3] Another greedy fails case");
  compareGreedyVsDP([1, 7, 10], 11);
}

function testGreedyOptimal() {
  console.log("\n[Test 4] Greedy optimal case");
  compareGreedyVsDP([1, 5, 10, 25], 30);
}

function testImpossibleAmount() {
  console.log("\n[Test 5] Impossible amount (no 1-cent coin)");
  const result = coinChangeGreedy([5, 10, 25], 11);
  console.log("Coins: [5, 10, 25], Amount: 11");
  console.log(`Result: ${result}`);
}

function testZeroAmount() {
  console.log("\n[Test 6] Zero amount");
  const result = coinChangeGreedy([1, 5, 10], 0);
  console.log("Coins: [1, 5, 10], Amount: 0");
  console.log(`Result: ${result}`);
}

function testSingleCoinType() {
  console.log("\n[Test 7] Single coin type");
  compareGreedyVsDP([7], 21);
}

function testLargeAmount() {
  console.log("\n[Test 8] Large amount");
  const result = coinChangeGreedy([1, 5, 10, 25, 50], 158);
  console.log("Coins: [1, 5, 10, 25, 50], Amount: 158");
  console.log(`Result: ${result}`);
}

function testNonStandardCoins() {
  console.log("\n[Test 9] Non-standard coins where greedy fails");
  compareGreedyVsDP([1, 3, 4, 5], 13);
}

function testEdgeCase() {
  console.log("\n[Test 10] Larger denomination problem");
  compareGreedyVsDP([2, 5, 10], 11);
}

if (require.main === module) {
  console.log("==================================================");
  console.log("COIN CHANGE - Greedy vs DP Comparison (JavaScript)");
  console.log("==================================================");

  testStandardCoins();
  testGreedyFails1();
  testGreedyFails2();
  testGreedyOptimal();
  testImpossibleAmount();
  testZeroAmount();
  testSingleCoinType();
  testLargeAmount();
  testNonStandardCoins();
  testEdgeCase();
}

module.exports = { CoinChangeResult, coinChangeGreedy, coinChangeDP };
