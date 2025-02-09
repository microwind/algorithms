class Node {
  constructor(data) {
    this.data = data;
    this.next = null;
    this.prev = null;
  }
}

class DoublyCircularLinkedList {
  constructor() {
    this.head = null;
  }

  append(data) {
    const newNode = new Node(data);
    if (this.head === null) {
      this.head = newNode;
      newNode.next = newNode;
      newNode.prev = newNode;
      return;
    }
    let last = this.head;
    while (last.next !== this.head) {
      last = last.next;
    }
    last.next = newNode;
    newNode.prev = last;
    this.head.prev = newNode;
    newNode.next = this.head;
  }

  printList() {
    if (this.head === null) return;
    let current = this.head;
    let result = '';
    do {
      result += current.data + ' <-> ';
      current = current.next;
    } while (current !== this.head);
    console.log(result + '(back to head)');
  }
}

const list = new DoublyCircularLinkedList();
list.append(1);
list.append(2);
list.append(3);
list.printList();  // 输出：1 <-> 2 <-> 3 <-> (back to head)

/*
jarry@MacBook-Pro linked % node doubly_circular_linked.js
1 <-> 2 <-> 3 <-> (back to head)
*/