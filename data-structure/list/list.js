class List {
  constructor() {
      this.capacity = 10;
      this.data = new Array(this.capacity);
      this.size = 0;
  }

  resize(newCapacity) {
      if (newCapacity > this.capacity) {
          let newData = new Array(newCapacity);
          for (let i = 0; i < this.size; i++) {
              newData[i] = this.data[i];
          }
          this.data = newData;
          this.capacity = newCapacity;
      }
  }

  add(value) {
      if (this.size === this.capacity) {
          this.resize(this.capacity * 2);
      }
      this.data[this.size++] = value;
  }

  remove() {
      if (this.size > 0) {
          this.size--;
      }
  }

  get(index) {
      if (index < 0 || index >= this.size) {
          throw new Error("Index out of range");
      }
      return this.data[index];
  }

  print() {
      console.log("List:", this.data.slice(0, this.size));
  }
}

const list = new List();
list.add(10);
list.add(20);
list.add(30);
list.print(); // List: [10, 20, 30]
console.log("Element at index 1:", list.get(1)); // 20
list.remove();
list.print(); // List: [10, 20]

/*
jarry@MacBook-Pro list % node list.js 
List: [ 10, 20, 30 ]
Element at index 1: 20
List: [ 10, 20 ]
*/