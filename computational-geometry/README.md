## 【计算几何算法详解】Java/Go/Python/JS/C/Rust不同语言实现

## 说明

计算几何算法是解决几何问题的计算方法，在AI时代广泛应用于计算机图形学、机器人路径规划、地理信息系统、计算机视觉等领域。

> **生活类比**：就像用尺子和圆规精确绘制几何图形，计算几何算法就是数字世界的"精密绘图工具"。

## 算法分类

### 1. 凸包算法
- **Graham扫描法** - 基于极角排序的凸包算法
- **Andrew单调链** - 高效的凸包算法
- **Jarvis步进法** - 包裹式凸包算法

### 2. 线段相交算法
- **跨立实验** - 判断线段相交
- **参数方程法** - 精确计算交点
- **扫描线算法** - 批量线段相交

### 3. 点在多边形内判断
- **射线法** - 射线与边界交点数判断
- ** winding数法** - 绕数判断
- **角度和法** - 角度累加判断

### 4. Voronoi图算法
- **Fortune算法** - 扫描线构造Voronoi图
- **增量法** - 逐点添加构造

## 算法流程

### Graham扫描法流程图

```mermaid
%%{init: {'flowchart': {'nodeSpacing': 15, 'rankSpacing': 25, 'padding': 20}}}%%
graph LR
    S(["开始"]) --> FIND["找到最下方的点"]
    FIND --> SORT["按极角排序其他点"]
    SORT --> PUSH["前三个点入栈"]
    PUSH --> LOOP{"还有未处理点？"}
    LOOP -->|"是"| CHECK["检查转向"]
    CHECK -->{"左转？"}
    CHECK -->|"是"| ADD["点入栈"]
    ADD --> LOOP
    CHECK -->|"右转"| POP["弹出栈顶"]
    POP --> CHECK
    LOOP -->|"否"| RESULT(["输出凸包"])

    %% 节点样式
    classDef start fill:#ff7f50,color:#fff,stroke:#e5533c,stroke-width:2px
    classDef end1 fill:#ff7f50,color:#fff,stroke:#e5533c,stroke-width:2px
    classDef loop fill:#1e90ff,color:#fff,stroke:#104e8b,stroke-width:2px
    classDef decision fill:#6a5acd,color:#fff,stroke:#483d8b,stroke-width:2px
    classDef process fill:#20b2aa,color:#fff,stroke:#008080,stroke-width:2px
    
    %% 应用样式
    class S,RESULT start
    class LOOP,CHECK decision
    class FIND,SORT,PUSH,ADD,POP process
```

## 时间复杂度分析

- **Graham扫描法**: O(n log n)
- **Andrew单调链**: O(n log n)
- **Jarvis步进法**: O(nh) h为凸包顶点数
- **线段相交**: O(1)
- **点在多边形内**: O(n)
- **Fortune算法**: O(n log n)

# 代码

## Java

```java
import java.util.*;

public class ComputationalGeometry {
    
    static class Point {
        double x, y;
        
        Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
        
        double distanceTo(Point other) {
            return Math.sqrt(Math.pow(x - other.x, 2) + Math.pow(y - other.y, 2));
        }
    }
    
    // Graham扫描法求凸包
    public static List<Point> grahamScan(List<Point> points) {
        if (points.size() < 3) return new ArrayList<>(points);
        
        // 找到最下方的点（y最小，若相等则x最小）
        Point start = points.get(0);
        for (Point p : points) {
            if (p.y < start.y || (p.y == start.y && p.x < start.x)) {
                start = p;
            }
        }
        
        // 按极角排序
        final Point finalStart = start;
        points.sort((a, b) -> {
            double angleA = Math.atan2(a.y - finalStart.y, a.x - finalStart.x);
            double angleB = Math.atan2(b.y - finalStart.y, b.x - finalStart.x);
            return Double.compare(angleA, angleB);
        });
        
        // Graham扫描
        Stack<Point> hull = new Stack<>();
        hull.push(start);
        
        for (int i = 1; i < points.size(); i++) {
            Point current = points.get(i);
            
            while (hull.size() >= 2) {
                Point second = hull.pop();
                Point first = hull.peek();
                
                if (crossProduct(first, second, current) > 0) {
                    hull.push(second);
                    break;
                }
            }
            
            hull.push(current);
        }
        
        return new ArrayList<>(hull);
    }
    
    // 计算叉积
    private static double crossProduct(Point a, Point b, Point c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }
    
    // 判断点是否在多边形内（射线法）
    public static boolean pointInPolygon(Point point, List<Point> polygon) {
        int intersections = 0;
        int n = polygon.size();
        
        for (int i = 0; i < n; i++) {
            Point p1 = polygon.get(i);
            Point p2 = polygon.get((i + 1) % n);
            
            if (rayIntersectsSegment(point, p1, p2)) {
                intersections++;
            }
        }
        
        return intersections % 2 == 1;
    }
    
    // 射线与线段相交判断
    private static boolean rayIntersectsSegment(Point point, Point p1, Point p2) {
        if (p1.y > point.y != p2.y > point.y) {
            double x = (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x;
            if (x > point.x) {
                return true;
            }
        }
        return false;
    }
    
    // 线段相交判断
    public static boolean segmentsIntersect(Point p1, Point p2, Point p3, Point p4) {
        double d1 = crossProduct(p3, p4, p1);
        double d2 = crossProduct(p3, p4, p2);
        double d3 = crossProduct(p1, p2, p3);
        double d4 = crossProduct(p1, p2, p4);
        
        return ((d1 * d2 < 0) && (d3 * d4 < 0)) ||
               (Math.abs(d1) < 1e-10 && onSegment(p3, p4, p1)) ||
               (Math.abs(d2) < 1e-10 && onSegment(p3, p4, p2)) ||
               (Math.abs(d3) < 1e-10 && onSegment(p1, p2, p3)) ||
               (Math.abs(d4) < 1e-10 && onSegment(p1, p2, p4));
    }
    
    private static boolean onSegment(Point p1, Point p2, Point p3) {
        return Math.min(p1.x, p2.x) <= p3.x && p3.x <= Math.max(p1.x, p2.x) &&
               Math.min(p1.y, p2.y) <= p3.y && p3.y <= Math.max(p1.y, p2.y);
    }
    
    public static void main(String[] args) {
        List<Point> points = Arrays.asList(
            new Point(0, 0), new Point(1, 1), new Point(2, 0),
            new Point(1, -1), new Point(0.5, 0.5)
        );
        
        System.out.println("原始点集:");
        points.forEach(p -> System.out.printf("(%.1f, %.1f) ", p.x, p.y));
        
        List<Point> hull = grahamScan(points);
        System.out.println("\n凸包:");
        hull.forEach(p -> System.out.printf("(%.1f, %.1f) ", p.x, p.y));
        
        Point testPoint = new Point(0.7, 0.3);
        List<Point> polygon = Arrays.asList(
            new Point(0, 0), new Point(1, 0), new Point(1, 1), new Point(0, 1)
        );
        
        boolean inside = pointInPolygon(testPoint, polygon);
        System.out.printf("\n点(%.1f, %.1f)在多边形内: %b\n", 
                         testPoint.x, testPoint.y, inside);
    }
}
```

## Python

```python
import math

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def distance_to(self, other):
        return math.sqrt((self.x - other.x)**2 + (self.y - other.y)**2)
    
    def __repr__(self):
        return f"({self.x:.1f}, {self.y:.1f})"

def cross_product(a, b, c):
    """计算叉积"""
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)

def graham_scan(points):
    """Graham扫描法求凸包"""
    if len(points) < 3:
        return points
    
    # 找到最下方的点
    start = min(points, key=lambda p: (p.y, p.x))
    
    # 按极角排序
    sorted_points = sorted(points, key=lambda p: math.atan2(p.y - start.y, p.x - start.x))
    
    # Graham扫描
    hull = [start]
    
    for current in sorted_points[1:]:
        while len(hull) >= 2:
            second = hull.pop()
            first = hull[-1]
            
            if cross_product(first, second, current) > 0:
                hull.append(second)
                break
        
        hull.append(current)
    
    return hull

def point_in_polygon(point, polygon):
    """判断点是否在多边形内（射线法）"""
    intersections = 0
    n = len(polygon)
    
    for i in range(n):
        p1 = polygon[i]
        p2 = polygon[(i + 1) % n]
        
        if ray_intersects_segment(point, p1, p2):
            intersections += 1
    
    return intersections % 2 == 1

def ray_intersects_segment(point, p1, p2):
    """射线与线段相交判断"""
    if (p1.y > point.y) != (p2.y > point.y):
        x = (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x
        if x > point.x:
            return True
    return False

def segments_intersect(p1, p2, p3, p4):
    """线段相交判断"""
    d1 = cross_product(p3, p4, p1)
    d2 = cross_product(p3, p4, p2)
    d3 = cross_product(p1, p2, p3)
    d4 = cross_product(p1, p2, p4)
    
    return ((d1 * d2 < 0) and (d3 * d4 < 0)) or \
           (abs(d1) < 1e-10 and on_segment(p3, p4, p1)) or \
           (abs(d2) < 1e-10 and on_segment(p3, p4, p2)) or \
           (abs(d3) < 1e-10 and on_segment(p1, p2, p3)) or \
           (abs(d4) < 1e-10 and on_segment(p1, p2, p4))

def on_segment(p1, p2, p3):
    """判断点是否在线段上"""
    return (min(p1.x, p2.x) <= p3.x <= max(p1.x, p2.x) and
            min(p1.y, p2.y) <= p3.y <= max(p1.y, p2.y))

def main():
    points = [
        Point(0, 0), Point(1, 1), Point(2, 0),
        Point(1, -1), Point(0.5, 0.5)
    ]
    
    print("原始点集:")
    print(" ".join(str(p) for p in points))
    
    hull = graham_scan(points)
    print("\n凸包:")
    print(" ".join(str(p) for p in hull))
    
    test_point = Point(0.7, 0.3)
    polygon = [Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)]
    
    inside = point_in_polygon(test_point, polygon)
    print(f"\n点{test_point}在多边形内: {inside}")

if __name__ == "__main__":
    main()
```

## Go

```go
package main

import (
	"fmt"
	"math"
	"sort"
)

type Point struct {
	X, Y float64
}

func (p Point) DistanceTo(other Point) float64 {
	return math.Sqrt(math.Pow(p.X-other.X, 2) + math.Pow(p.Y-other.Y, 2))
}

func crossProduct(a, b, c Point) float64 {
	return (b.X-a.X)*(c.Y-a.Y) - (b.Y-a.Y)*(c.X-a.X)
}

func grahamScan(points []Point) []Point {
	if len(points) < 3 {
		return points
	}
	
	// 找到最下方的点
	start := points[0]
	for _, p := range points {
		if p.Y < start.Y || (p.Y == start.Y && p.X < start.X) {
			start = p
		}
	}
	
	// 按极角排序
	sort.Slice(points, func(i, j int) bool {
		angleI := math.Atan2(points[i].Y-start.Y, points[i].X-start.X)
		angleJ := math.Atan2(points[j].Y-start.Y, points[j].X-start.X)
		return angleI < angleJ
	})
	
	// Graham扫描
	hull := []Point{start}
	
	for _, current := range points[1:] {
		for len(hull) >= 2 {
			second := hull[len(hull)-1]
			hull = hull[:len(hull)-1]
			first := hull[len(hull)-1]
			
			if crossProduct(first, second, current) > 0 {
				hull = append(hull, second)
				break
			}
		}
		hull = append(hull, current)
	}
	
	return hull
}

func pointInPolygon(point Point, polygon []Point) bool {
	intersections := 0
	n := len(polygon)
	
	for i := 0; i < n; i++ {
		p1 := polygon[i]
		p2 := polygon[(i+1)%n]
		
		if rayIntersectsSegment(point, p1, p2) {
			intersections++
		}
	}
	
	return intersections%2 == 1
}

func rayIntersectsSegment(point, p1, p2 Point) bool {
	if (p1.Y > point.Y) != (p2.Y > point.Y) {
		x := (p2.X-p1.X)*(point.Y-p1.Y)/(p2.Y-p1.Y) + p1.X
		if x > point.X {
			return true
		}
	}
	return false
}

func main() {
	points := []Point{
		{0, 0}, {1, 1}, {2, 0},
		{1, -1}, {0.5, 0.5},
	}
	
	fmt.Println("原始点集:")
	for _, p := range points {
		fmt.Printf("(%.1f, %.1f) ", p.X, p.Y)
	}
	
	hull := grahamScan(points)
	fmt.Println("\n凸包:")
	for _, p := range hull {
		fmt.Printf("(%.1f, %.1f) ", p.X, p.Y)
	}
	
	testPoint := Point{0.7, 0.3}
	polygon := []Point{{0, 0}, {1, 0}, {1, 1}, {0, 1}}
	
	inside := pointInPolygon(testPoint, polygon)
	fmt.Printf("\n点(%.1f, %.1f)在多边形内: %t\n", 
		testPoint.X, testPoint.Y, inside)
}
```

## JavaScript

```javascript
class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
    
    distanceTo(other) {
        return Math.sqrt(Math.pow(this.x - other.x, 2) + Math.pow(this.y - other.y, 2));
    }
    
    toString() {
        return `(${this.x.toFixed(1)}, ${this.y.toFixed(1)})`;
    }
}

function crossProduct(a, b, c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

function grahamScan(points) {
    if (points.length < 3) return points;
    
    // 找到最下方的点
    const start = points.reduce((min, p) => 
        p.y < min.y || (p.y === min.y && p.x < min.x) ? p : min
    );
    
    // 按极角排序
    const sortedPoints = [...points].sort((a, b) => {
        const angleA = Math.atan2(a.y - start.y, a.x - start.x);
        const angleB = Math.atan2(b.y - start.y, b.x - start.x);
        return angleA - angleB;
    });
    
    // Graham扫描
    const hull = [start];
    
    for (const current of sortedPoints.slice(1)) {
        while (hull.length >= 2) {
            const second = hull.pop();
            const first = hull[hull.length - 1];
            
            if (crossProduct(first, second, current) > 0) {
                hull.push(second);
                break;
            }
        }
        hull.push(current);
    }
    
    return hull;
}

function pointInPolygon(point, polygon) {
    let intersections = 0;
    const n = polygon.length;
    
    for (let i = 0; i < n; i++) {
        const p1 = polygon[i];
        const p2 = polygon[(i + 1) % n];
        
        if (rayIntersectsSegment(point, p1, p2)) {
            intersections++;
        }
    }
    
    return intersections % 2 === 1;
}

function rayIntersectsSegment(point, p1, p2) {
    if ((p1.y > point.y) !== (p2.y > point.y)) {
        const x = (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x;
        if (x > point.x) {
            return true;
        }
    }
    return false;
}

// 示例使用
const points = [
    new Point(0, 0), new Point(1, 1), new Point(2, 0),
    new Point(1, -1), new Point(0.5, 0.5)
];

console.log("原始点集:");
console.log(points.map(p => p.toString()).join(" "));

const hull = grahamScan(points);
console.log("\n凸包:");
console.log(hull.map(p => p.toString()).join(" "));

const testPoint = new Point(0.7, 0.3);
const polygon = [
    new Point(0, 0), new Point(1, 0), new Point(1, 1), new Point(0, 1)
];

const inside = pointInPolygon(testPoint, polygon);
console.log(`\n点${testPoint}在多边形内: ${inside}`);
```

## C

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

double distanceTo(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double crossProduct(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int comparePoints(const void* a, const void* b) {
    Point* pa = (Point*)a;
    Point* pb = (Point*)b;
    if (pa->y != pb->y) return pa->y < pb->y ? -1 : 1;
    return pa->x < pb->x ? -1 : 1;
}

int compareAngles(const void* a, const void* b, void* start) {
    Point* pa = (Point*)a;
    Point* pb = (Point*)b;
    Point* ps = (Point*)start;
    
    double angleA = atan2(pa->y - ps->y, pa->x - ps->x);
    double angleB = atan2(pb->y - ps->y, pb->x - ps->x);
    
    return angleA < angleB ? -1 : 1;
}

Point* grahamScan(Point* points, int n, int* hullSize) {
    if (n < 3) {
        *hullSize = n;
        return points;
    }
    
    // 找到最下方的点
    Point* start = &points[0];
    for (int i = 1; i < n; i++) {
        if (points[i].y < start->y || 
            (points[i].y == start->y && points[i].x < start->x)) {
            start = &points[i];
        }
    }
    
    // 按极角排序（简化实现）
    Point* sorted = malloc(n * sizeof(Point));
    memcpy(sorted, points, n * sizeof(Point));
    qsort_r(sorted, n, sizeof(Point), start, compareAngles);
    
    // Graham扫描
    Point* hull = malloc(n * sizeof(Point));
    int hullIndex = 0;
    
    hull[hullIndex++] = *start;
    
    for (int i = 1; i < n; i++) {
        while (hullIndex >= 2) {
            Point second = hull[--hullIndex];
            Point first = hull[hullIndex - 1];
            
            if (crossProduct(first, second, sorted[i]) > 0) {
                hull[hullIndex++] = second;
                break;
            }
        }
        hull[hullIndex++] = sorted[i];
    }
    
    *hullSize = hullIndex;
    return hull;
}

int pointInPolygon(Point point, Point* polygon, int n) {
    int intersections = 0;
    
    for (int i = 0; i < n; i++) {
        Point p1 = polygon[i];
        Point p2 = polygon[(i + 1) % n];
        
        if (rayIntersectsSegment(point, p1, p2)) {
            intersections++;
        }
    }
    
    return intersections % 2 == 1;
}

int rayIntersectsSegment(Point point, Point p1, Point p2) {
    if ((p1.y > point.y) != (p2.y > point.y)) {
        double x = (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x;
        if (x > point.x) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Point points[] = {
        {0, 0}, {1, 1}, {2, 0},
        {1, -1}, {0.5, 0.5}
    };
    int n = sizeof(points) / sizeof(points[0]);
    
    printf("原始点集:\n");
    for (int i = 0; i < n; i++) {
        printf("(%.1f, %.1f) ", points[i].x, points[i].y);
    }
    
    int hullSize;
    Point* hull = grahamScan(points, n, &hullSize);
    
    printf("\n凸包:\n");
    for (int i = 0; i < hullSize; i++) {
        printf("(%.1f, %.1f) ", hull[i].x, hull[i].y);
    }
    
    Point testPoint = {0.7, 0.3};
    Point polygon[] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    int polygonSize = 4;
    
    int inside = pointInPolygon(testPoint, polygon, polygonSize);
    printf("\n点(%.1f, %.1f)在多边形内: %d\n", 
           testPoint.x, testPoint.y, inside);
    
    free(hull);
    return 0;
}
```

## Rust

```rust
use std::f64::consts::PI;

#[derive(Debug, Clone, Copy)]
struct Point {
    x: f64,
    y: f64,
}

impl Point {
    fn new(x: f64, y: f64) -> Self {
        Point { x, y }
    }
    
    fn distance_to(&self, other: &Point) -> f64 {
        ((self.x - other.x).powi(2) + (self.y - other.y).powi(2)).sqrt()
    }
}

fn cross_product(a: &Point, b: &Point, c: &Point) -> f64 {
    (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)
}

fn graham_scan(points: &[Point]) -> Vec<Point> {
    if points.len() < 3 {
        return points.to_vec();
    }
    
    // 找到最下方的点
    let start = points.iter().min_by(|a, b| {
        a.y.partial_cmp(&b.y).unwrap()
            .then(a.x.partial_cmp(&b.x).unwrap())
    }).unwrap();
    
    // 按极角排序
    let mut sorted_points = points.to_vec();
    sorted_points.sort_by(|a, b| {
        let angle_a = (a.y - start.y).atan2(a.x - start.x);
        let angle_b = (b.y - start.y).atan2(b.x - start.x);
        angle_a.partial_cmp(&angle_b).unwrap()
    });
    
    // Graham扫描
    let mut hull = vec![*start];
    
    for &current in &sorted_points[1..] {
        while hull.len() >= 2 {
            let second = hull.pop().unwrap();
            let first = hull[hull.len() - 1];
            
            if cross_product(&first, &second, &current) > 0.0 {
                hull.push(second);
                break;
            }
        }
        hull.push(current);
    }
    
    hull
}

fn point_in_polygon(point: &Point, polygon: &[Point]) -> bool {
    let mut intersections = 0;
    let n = polygon.len();
    
    for i in 0..n {
        let p1 = &polygon[i];
        let p2 = &polygon[(i + 1) % n];
        
        if ray_intersects_segment(point, p1, p2) {
            intersections += 1;
        }
    }
    
    intersections % 2 == 1
}

fn ray_intersects_segment(point: &Point, p1: &Point, p2: &Point) -> bool {
    if (p1.y > point.y) != (p2.y > point.y) {
        let x = (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x;
        if x > point.x {
            return true;
        }
    }
    false
}

fn main() {
    let points = vec![
        Point::new(0.0, 0.0), Point::new(1.0, 1.0), Point::new(2.0, 0.0),
        Point::new(1.0, -1.0), Point::new(0.5, 0.5)
    ];
    
    println!("原始点集:");
    for p in &points {
        print!("({:.1}, {:.1}) ", p.x, p.y);
    }
    
    let hull = graham_scan(&points);
    println!("\n凸包:");
    for p in &hull {
        print!("({:.1}, {:.1}) ", p.x, p.y);
    }
    
    let test_point = Point::new(0.7, 0.3);
    let polygon = vec![
        Point::new(0.0, 0.0), Point::new(1.0, 0.0), 
        Point::new(1.0, 1.0), Point::new(0.0, 1.0)
    ];
    
    let inside = point_in_polygon(&test_point, &polygon);
    println!("\n点({:.1}, {:.1})在多边形内: {}", 
             test_point.x, test_point.y, inside);
}
```

# 链接

计算几何算法源码：[https://github.com/microwind/algorithms/tree/main/computational-geometry](https://github.com/microwind/algorithms/tree/main/computational-geometry)

其他算法源码：[https://github.com/microwind/algorithms](https://github.com/microwind/algorithms)
