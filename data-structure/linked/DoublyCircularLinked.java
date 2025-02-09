class DoublyCircularLinked {
  static class Node {
      int data;
      Node next;
      Node prev;

      Node(int data) {
          this.data = data;
          this.next = null;
          this.prev = null;
      }
  }

  private Node head;

  public DoublyCircularLinked() {
      this.head = null;
  }

  public void append(int data) {
      Node newNode = new Node(data);
      if (head == null) {
          head = newNode;
          newNode.next = newNode;
          newNode.prev = newNode;
          return;
      }
      Node last = head;
      while (last.next != head) {
          last = last.next;
      }
      last.next = newNode;
      newNode.prev = last;
      head.prev = newNode;
      newNode.next = head;
  }

  public void printList() {
      if (head == null) {
          return;
      }
      Node current = head;
      do {
          System.out.print(current.data + " <-> ");
          current = current.next;
      } while (current != head);
      System.out.println("(back to head)");
  }

  public static void main(String[] args) {
    DoublyCircularLinked list = new DoublyCircularLinked();
      list.append(1);
      list.append(2);
      list.append(3);
      list.printList();  // 输出：1 <-> 2 <-> 3 <-> (back to head)
  }
}

/*
jarry@MacBook-Pro linked % javac DoublyCircularLinked.java 
jarry@MacBook-Pro linked % java DoublyCircularLinked
1 <-> 2 <-> 3 <-> (back to head)
*/