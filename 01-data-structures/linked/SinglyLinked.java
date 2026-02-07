class SinglyLinked {
  static class Node {
      int data;
      Node next;

      Node(int data) {
          this.data = data;
          this.next = null;
      }
  }

  private Node head;

  public SinglyLinked() {
      this.head = null;
  }

  public void append(int data) {
      Node newNode = new Node(data);
      if (head == null) {
          head = newNode;
          return;
      }
      Node last = head;
      while (last.next != null) {
          last = last.next;
      }
      last.next = newNode;
  }

  public void printList() {
      Node current = head;
      while (current != null) {
          System.out.print(current.data + " -> ");
          current = current.next;
      }
      System.out.println("NULL");
  }

  public static void main(String[] args) {
      SinglyLinked list = new SinglyLinked();
      list.append(1);
      list.append(2);
      list.append(3);
      list.printList();  // 输出：1 -> 2 -> 3 -> NULL
  }
}

/*
jarry@MacBook-Pro linked % javac SinglyLinked.java
jarry@MacBook-Pro linked % java SinglyLinked      
1 -> 2 -> 3 -> NULL
*/