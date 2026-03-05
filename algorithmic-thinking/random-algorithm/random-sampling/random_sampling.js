/*
 * 随机采样（Random Sampling）- JavaScript 版本
 *
 * 实现核心算法：水库采样（Reservoir Sampling）
 * - 适用于数据流（stream），无需预先知道数据总量 n
 * - 从 n 个元素中等概率抽取 k 个样本（无放回）
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(k)
 */

/**
 * 基础水库采样：从可迭代数据中随机选择 k 个元素
 * @param {Iterable<any>} iterable - 任意可迭代对象（数组、生成器等）
 * @param {number} k - 采样数量
 * @returns {any[]} 含有 k 个样本的数组（如果数据量 < k，则返回全部）
 */
function reservoirSampling(iterable, k) {
  const reservoir = [];
  let i = 0;

  for (const item of iterable) {
    if (i < k) {
      // 前 k 个元素直接放入水池
      reservoir.push(item);
    } else {
      // 对于第 i 个元素，以 k/(i+1) 的概率替换已有元素
      const j = Math.floor(Math.random() * (i + 1)); // [0, i]
      if (j < k) {
        reservoir[j] = item;
      }
    }
    i++;
  }

  return reservoir;
}

/**
 * 无放回随机采样（小数据集时可直接使用）
 * @param {any[]} array - 总体数组
 * @param {number} k - 采样数量
 */
function sampleWithoutReplacement(array, k) {
  if (k >= array.length) {
    return [...array];
  }
  // 对小数组可以直接洗牌再截取前 k 个
  const copy = [...array];
  for (let i = copy.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [copy[i], copy[j]] = [copy[j], copy[i]];
  }
  return copy.slice(0, k);
}

// 简单演示
if (require.main === module) {
  console.log("========== Random Sampling (JavaScript) ==========");

  const data = Array.from({ length: 10 }, (_, i) => i + 1);
  console.log("数据:", data);

  console.log("\n1. 基础水库采样（k = 3）");
  for (let t = 1; t <= 3; t++) {
    console.log(`  第 ${t} 次采样:`, reservoirSampling(data, 3));
  }

  console.log("\n2. 无放回采样（小数据集）");
  console.log("  样本:", sampleWithoutReplacement(data, 4));
}

module.exports = { reservoirSampling, sampleWithoutReplacement };

