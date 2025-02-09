// 定义节点结构体
#[derive(Debug)]
struct Node {
    vertex: usize,
    next: Option<Box<Node>>,
}

// 定义图结构体
struct Graph {
    num_vertices: usize,
    adj_lists: Vec<Option<Box<Node>>>,
}

impl Graph {
    // 创建图
    fn create_graph(vertices: usize) -> Self {
        let mut adj_lists = Vec::with_capacity(vertices);
        for _ in 0..vertices {
            adj_lists.push(None); // 初始化为 None
        }

        Graph {
            num_vertices: vertices,
            adj_lists,
        }
    }

    // 创建节点
    fn create_node(v: usize) -> Box<Node> {
        Box::new(Node { vertex: v, next: None })
    }

    // 添加边
    fn add_edge(&mut self, src: usize, dest: usize) {
        // 添加从 src 到 dest 的边
        let new_node = Graph::create_node(dest);
        let old_head = self.adj_lists[src].take();
        self.adj_lists[src] = Some(new_node);

        let mut temp = &mut self.adj_lists[src];
        while let Some(ref mut next_node) = temp {
            temp = &mut next_node.next;
        }
        *temp = old_head;

        // 添加从 dest 到 src 的边（无向图）
        let new_node = Graph::create_node(src);
        let old_head = self.adj_lists[dest].take();
        self.adj_lists[dest] = Some(new_node);

        let mut temp = &mut self.adj_lists[dest];
        while let Some(ref mut next_node) = temp {
            temp = &mut next_node.next;
        }
        *temp = old_head;
    }

    // 打印图
    fn print_graph(&self) {
        for v in 0..self.num_vertices {
            print!("\nVertex {}: ", v);
            let mut temp = &self.adj_lists[v];
            while let Some(ref node) = temp {
                print!("{} -> ", node.vertex);
                temp = &node.next;
            }
            println!();
        }
    }
}

fn main() {
    // 创建图并添加边
    let mut graph = Graph::create_graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    // 打印图
    graph.print_graph();
}

/*
jarry@MacBook-Pro graph % rustc graph.rs
jarry@MacBook-Pro graph % ./graph 

Vertex 0: 2 -> 1 -> 

Vertex 1: 2 -> 0 -> 

Vertex 2: 3 -> 1 -> 0 -> 

Vertex 3: 2 -> 
*/