class Node {
  constructor(data) {
    this.data = data;
    this.next = null;
  }
}

class SinglyLinkedList {
  constructor() {
    this.head = null;
  }

  append(data) {
    const newNode = new Node(data);
    if (this.head === null) {
      this.head = newNode;
      return;
    }
    let last = this.head;
    while (last.next !== null) {
      last = last.next;
    }
    last.next = newNode;
  }

  printList() {
    let current = this.head;
    let result = '';
    while (current !== null) {
      result += current.data + ' -> ';
      current = current.next;
    }
    console.log(result + 'NULL');
  }
}

const list = new SinglyLinkedList();
list.append(1);
list.append(2);
list.append(3);
list.printList();  // 输出：1 -> 2 -> 3 -> NULL

/*
jarry@MacBook-Pro linked % node singly_linked.js
1 -> 2 -> 3 -> NULL
*/
