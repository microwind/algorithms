/*
 * 广度优先搜索（BFS）- JavaScript 版本
 *
 * 使用队列按「层」遍历图或树：
 * - bfsTraversal: 遍历所有可达节点
 * - bfsShortestPath: 无权图最短路径
 *
 * 时间复杂度：O(V + E)
 * 空间复杂度：O(V)
 */

/**
 * BFS 遍历：返回从起点出发的访问顺序
 * @param {Object<string, string[]>} graph - 邻接表
 * @param {string} start - 起始节点
 */
function bfsTraversal(graph, start) {
  const visited = new Set();
  const queue = [start];
  const order = [];
  visited.add(start);

  while (queue.length > 0) {
    const node = queue.shift();
    order.push(node);
    for (const neighbor of graph[node] || []) {
      if (!visited.has(neighbor)) {
        visited.add(neighbor);
        queue.push(neighbor);
      }
    }
  }
  return order;
}

/**
 * BFS 最短路径（无权图）
 * @param {Object<string, string[]>} graph
 * @param {string} start
 * @param {string} end
 * @returns {string[]|null} 最短路径（包含起点和终点），不存在返回 null
 */
function bfsShortestPath(graph, start, end) {
  if (start === end) return [start];
  const queue = [[start, [start]]];
  const visited = new Set([start]);

  while (queue.length > 0) {
    const [node, path] = queue.shift();
    for (const neighbor of graph[node] || []) {
      if (!visited.has(neighbor)) {
        if (neighbor === end) {
          return [...path, neighbor];
        }
        visited.add(neighbor);
        queue.push([neighbor, [...path, neighbor]]);
      }
    }
  }
  return null;
}

// 简单演示
if (require.main === module) {
  console.log("========== BFS (JavaScript) ==========");
  const graph = {
    A: ["B", "C"],
    B: ["A", "D", "E"],
    C: ["A", "F"],
    D: ["B"],
    E: ["B", "F"],
    F: ["C", "E"],
  };
  console.log("图:", graph);
  console.log("BFS 遍历从 A 开始 ->", bfsTraversal(graph, "A"));
  console.log("A 到 F 的最短路径 ->", bfsShortestPath(graph, "A", "F"));
}

module.exports = { bfsTraversal, bfsShortestPath };

