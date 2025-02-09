package main

import "fmt"

type Map struct {
    entries  []Entry
    size     int
    capacity int
}

type Entry struct {
    key   string
    value int
}

// 重新分配容量
func (m *Map) resizeMap(newCapacity int) {
    m.capacity = newCapacity
}

// 插入键值对（如果存在则更新）
func (m *Map) put(key string, value int) {
    for i := 0; i < m.size; i++ {
        if m.entries[i].key == key {
            m.entries[i].value = value // 更新值
            return
        }
    }
    if m.size >= m.capacity {
        m.resizeMap(m.capacity * 2)
    }
    m.entries = append(m.entries, Entry{key, value})
    m.size++
}

// 查找键
func (m *Map) get(key string) int {
    for i := 0; i < m.size; i++ {
        if m.entries[i].key == key {
            return m.entries[i].value
        }
    }
    return -1 // 未找到
}

// 删除键
func (m *Map) delete(key string) {
    for i := 0; i < m.size; i++ {
        if m.entries[i].key == key {
            m.entries = append(m.entries[:i], m.entries[i+1:]...)
            m.size--
            return
        }
    }
}

func main() {
    mapObj := Map{capacity: 10}
    mapObj.put("apple", 10)
    mapObj.put("banana", 20)
    mapObj.put("orange", 30)

    fmt.Println("apple:", mapObj.get("apple"))
    fmt.Println("banana:", mapObj.get("banana"))
    fmt.Println("grape:", mapObj.get("grape"))

    mapObj.delete("banana")
    fmt.Println("banana after delete:", mapObj.get("banana"))
}

/*
jarry@MacBook-Pro map % go run map.go
apple: 10
banana: 20
grape: -1
banana after delete: -1
*/
