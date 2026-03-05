/*
 * 洗牌算法（Shuffle）- JavaScript 版本
 *
 * 实现 Fisher–Yates 洗牌算法，保证每一种排列出现的概率相等。
 * 这里提供两种形式：
 * 1. 原地洗牌（in-place）：直接修改原数组
 * 2. 生成新数组的洗牌：返回一个被打乱的新数组，原数组不变
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(1) 原地版本；O(n) 新数组版本
 */

/**
 * 原地洗牌：直接修改传入的数组
 * @param {any[]} arr - 待打乱的数组
 * @returns {any[]} 同一个数组（已经被打乱）
 */
function shuffleInPlace(arr) {
  // 从数组末尾开始，逐个与前面某个随机位置交换
  for (let i = arr.length - 1; i > 0; i--) {
    // 在 [0, i] 范围内生成一个随机整数 j
    const j = Math.floor(Math.random() * (i + 1));
    // 交换 arr[i] 与 arr[j]
    [arr[i], arr[j]] = [arr[j], arr[i]];
  }
  return arr;
}

/**
 * 非原地洗牌：返回一个新数组，原数组不变
 * @param {any[]} arr - 待打乱的数组
 * @returns {any[]} 新数组（打乱后的结果）
 */
function shuffleNewArray(arr) {
  // 先复制一份数组，再在副本上做原地洗牌
  const copy = arr.slice();
  return shuffleInPlace(copy);
}

// 简单演示
if (require.main === module) {
  console.log("========== Shuffle (JavaScript) ==========");
  const original = [1, 2, 3, 4, 5, 6, 7, 8, 9];
  console.log("原数组:", original);
  console.log("原地洗牌结果:", shuffleInPlace([...original]));
  console.log("新数组洗牌结果:", shuffleNewArray(original));
  console.log("原数组保持不变:", original);
}

module.exports = { shuffleInPlace, shuffleNewArray };

