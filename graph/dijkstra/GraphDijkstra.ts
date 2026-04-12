/** Copyright https://github.com/microwind */
const V = 6, INF = Number.MAX_SAFE_INTEGER;
function minDistance(dist: number[], visited: boolean[]): number {
    let min = INF, minIndex = -1;
    for (let v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) { min = dist[v]; minIndex = v; }
    }
    return minIndex;
}
function dijkstra(graph: number[][], src: number): void {
    const dist: number[] = new Array(V).fill(INF);
    const visited: boolean[] = new Array(V).fill(false);
    dist[src] = 0;
    for (let count = 0; count < V - 1; count++) {
        const u = minDistance(dist, visited);
        visited[u] = true;
        for (let v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] !== 0 && dist[u] !== INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    console.log("Vertex Distance from Source");
    for (let i = 0; i < V; i++) console.log(`${i} ${dist[i]}`);
}
const graph = [[0,4,0,0,0,0],[4,0,8,0,0,0],[0,8,0,7,0,4],[0,0,7,0,9,14],[0,0,0,9,0,10],[0,0,4,14,10,0]];
dijkstra(graph, 0);
export { dijkstra, minDistance };
