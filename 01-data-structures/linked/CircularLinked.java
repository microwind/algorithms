class CircularLinked {
  static class Node {
      int data;
      Node next;

      Node(int data) {
          this.data = data;
          this.next = null;
      }
  }

  private Node head;

  public CircularLinked() {
      this.head = null;
  }

  public void append(int data) {
      Node newNode = new Node(data);
      if (head == null) {
          head = newNode;
          newNode.next = head;
          return;
      }
      Node last = head;
      while (last.next != head) {
          last = last.next;
      }
      last.next = newNode;
      newNode.next = head;
  }

  public void printList() {
      if (head == null) {
          return;
      }
      Node current = head;
      do {
          System.out.print(current.data + " -> ");
          current = current.next;
      } while (current != head);
      System.out.println("(back to head)");
  }

  public static void main(String[] args) {
      CircularLinked list = new CircularLinked();
      list.append(1);
      list.append(2);
      list.append(3);
      list.printList();  // 输出：1 -> 2 -> 3 -> (back to head)
  }
}

/*
jarry@MacBook-Pro linked % javac CircularLinked.java 
jarry@MacBook-Pro linked % java CircularLinked
1 -> 2 -> 3 -> (back to head)
*/