class DoublyLinked {
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

    public DoublyLinked() {
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
        newNode.prev = last;
    }

    public void printList() {
        Node current = head;
        while (current != null) {
            System.out.print(current.data + " <-> ");
            current = current.next;
        }
        System.out.println("NULL");
    }

    public static void main(String[] args) {
        DoublyLinked list = new DoublyLinked();
        list.append(1);
        list.append(2);
        list.append(3);
        list.printList();  // 输出：1 <-> 2 <-> 3 <-> NULL
    }
}

/*
jarry@MacBook-Pro linked % javac DoublyLinked.java 
jarry@MacBook-Pro linked % java DoublyLinked
1 <-> 2 <-> 3 <-> NULL
*/