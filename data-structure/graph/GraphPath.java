
import java.util.*;

/**
 * GraphPath类：该类用于表示图的结构，adjacencyList存储每个节点及其相邻节点的列表。
 * addEdge方法：用于向图中添加边，使用HashMap来保存每个节点及其相邻节点的信息。
 * Dijkstra算法：dijkstra()方法使用优先队列来动态更新最短路径。PriorityQueue按距离升序排列，确保每次处理最短路径节点。
 * Edge类：用于表示边，包含目标节点和边的权重（距离）。
 */

class GraphPath {
  private Map<String, List<Edge>> adjacencyList;

  // 构造函数，初始化图
  public GraphPath() {
    adjacencyList = new HashMap<>();
  }

  // 添加边 (起点, 终点, 距离)
  public void addEdge(String start, String end, int distance) {
    adjacencyList.computeIfAbsent(start, k -> new ArrayList<>()).add(new Edge(end, distance));
    adjacencyList.computeIfAbsent(end, k -> new ArrayList<>()); // 保证终点也在图中
  }

  // Dijkstra算法寻找最短路径
  public Map<String, Integer> dijkstra(String start) {
    // 存储最短路径的距离
    Map<String, Integer> distances = new HashMap<>();
    for (String vertex : adjacencyList.keySet()) {
      distances.put(vertex, Integer.MAX_VALUE); // 初始设置为无穷大
    }
    distances.put(start, 0);

    // 优先队列按距离排序
    PriorityQueue<Edge> priorityQueue = new PriorityQueue<>(Comparator.comparingInt(Edge::getDistance));
    priorityQueue.add(new Edge(start, 0));

    while (!priorityQueue.isEmpty()) {
      Edge current = priorityQueue.poll();
      String currentVertex = current.getEnd();
      int currentDistance = current.getDistance();

      // 遍历相邻节点
      for (Edge edge : adjacencyList.get(currentVertex)) {
        int newDist = currentDistance + edge.getDistance();
        if (newDist < distances.get(edge.getEnd())) {
          distances.put(edge.getEnd(), newDist);
          priorityQueue.add(new Edge(edge.getEnd(), newDist));
        }
      }
    }

    return distances;
  }

  // 输出最短路径及其距离
  public void printShortestPath(String start, String end) {
    Map<String, Integer> distances = dijkstra(start);
    System.out.println("从 " + start + " 到 " + end + " 的最短距离是: " + distances.get(end) + " 公里");
  }

  // 边类，表示图中的边（目标节点，边的权重）
  static class Edge {
    private String end;
    private int distance;

    public Edge(String end, int distance) {
      this.end = end;
      this.distance = distance;
    }

    public String getEnd() {
      return end;
    }

    public int getDistance() {
      return distance;
    }
  }

  public static void main(String[] args) {
    GraphPath cityMap = new GraphPath();

    // 添加边（地点之间的道路及其距离）
    cityMap.addEdge("A", "B", 5);
    cityMap.addEdge("A", "C", 2);
    cityMap.addEdge("B", "C", 1);
    cityMap.addEdge("B", "D", 3);
    cityMap.addEdge("C", "D", 8);
    cityMap.addEdge("C", "E", 10);
    cityMap.addEdge("D", "E", 4);
    cityMap.addEdge("D", "F", 6);
    cityMap.addEdge("E", "F", 2);

    // 输出从A到F的最短路径
    cityMap.printShortestPath("A", "F");
  }
}

/**
 * jarry@jarrys-MacBook-Pro graph % javac GraphPath.java
 * jarry@jarrys-MacBook-Pro graph % java GraphPath
 * 从 A 到 F 的最短距离是: 14 公里
 */