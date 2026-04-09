// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

/// 图的邻接表表示实现
/// 使用链表存储图的邻接关系

const V: usize = 5;

#[derive(Debug)]
struct Node {
    dest: usize,
    next: Option<Box<Node>>,
}

struct Graph {
    adj_list: [Option<Box<Node>>; V],
}

impl Graph {
    fn new() -> Self {
        Graph { adj_list: [None, None, None, None, None] }
    }
    
    fn add_edge(&mut self, src: usize, dest: usize) {
        let new_node = Box::new(Node {
            dest,
            next: self.adj_list[src].take(),
        });
        self.adj_list[src] = Some(new_node);
    }
    
    fn print_graph(&self) {
        for i in 0..V {
            print!("Adjacency list of vertex {}: ", i);
            let mut temp = &self.adj_list[i];
            while let Some(node) = temp {
                print!(" -> {}", node.dest);
                temp = &node.next;
            }
            println!();
        }
    }
}

fn main() {
    let mut graph = Graph::new();
    graph.add_edge(0, 1);
    graph.add_edge(0, 3);
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);
    graph.add_edge(1, 4);
    graph.add_edge(2, 4);
    graph.add_edge(3, 4);
    
    graph.print_graph();
}
