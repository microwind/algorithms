import java.util.Arrays;

class List {
  private int[] data;
  private int size;
  private int capacity;

  public List() {
    capacity = 10;
    // 这里采取数组来模拟List，与ArrayList类似
    data = new int[capacity];
    size = 0;
  }

  public void resize(int newCapacity) {
    if (newCapacity > capacity) {
      data = Arrays.copyOf(data, newCapacity);
      capacity = newCapacity;
    }
  }

  public void add(int value) {
    if (size == capacity) {
      resize(capacity * 2);
    }
    data[size++] = value;
  }

  public void remove() {
    if (size > 0) {
      size--;
    }
  }

  public int get(int index) {
    if (index < 0 || index >= size) {
      throw new IndexOutOfBoundsException("Index out of range");
    }
    return data[index];
  }

  public int size() {
    return size;
  }

  public int capacity() {
    return capacity;
  }

  public void print() {
    System.out.println("List: " + Arrays.toString(Arrays.copyOf(data, size)));
  }

  public static void main(String[] args) {
    List list = new List();
    list.add(10);
    list.add(20);
    list.add(30);
    list.print(); // List: [10, 20, 30]

    System.out.println("Element at index 1: " + list.get(1)); // 20

    list.remove();
    list.print(); // List: [10, 20]

    System.out.println("Size: " + list.size()); // 2
    System.out.println("Capacity: " + list.capacity()); // 10

    list.resize(20);
    System.out.println("New Capacity: " + list.capacity()); // 20
  }
}

/**
 * jarry@MacBook-Pro list % javac List.java
 * jarry@MacBook-Pro list % java List
 * List: [10, 20, 30]
 * Element at index 1: 20
 * List: [10, 20]
 * Size: 2
 * Capacity: 10
 * New Capacity: 20
 */