/**
 * Comprehensive Array Deduplication Class
 * Demonstrates 18 different methods for array deduplication in JavaScript
 * Each method showcases different optimization strategies and ECMAScript features
 */
class UniqueArray {
  constructor(arr) {
    this.originalArray = arr; // Preserve original array immutability
  }

  // Method 1: Double Nested Loop
  methodDoubleLoop() {
    console.time("DoubleLoop");
    const arr = this.originalArray.slice();
    const uniqueArr = [];
    
    // O(n²) time complexity - brute force comparison
    for (let i = 0; i < arr.length; i++) {
      let isUnique = true;
      for (let j = 0; j < uniqueArr.length; j++) {
        if (arr[i] === uniqueArr[j]) {
          isUnique = false;
          break;
        }
      }
      if (isUnique) uniqueArr.push(arr[i]);
    }
    
    console.log("Double Loop:", uniqueArr);
    console.timeEnd("DoubleLoop");
  }

  // Method 2: indexOf Check
  methodIndexOfCheck() {
    console.time("IndexOfCheck");
    const arr = this.originalArray.slice();
    const uniqueArr = [];
    
    // Leverage built-in indexOf for existence check
    arr.forEach(item => {
      if (uniqueArr.indexOf(item) === -1) {
        uniqueArr.push(item);
      }
    });
    
    console.log("indexOf Check:", uniqueArr);
    console.timeEnd("IndexOfCheck");
  }

  // Method 3: includes Check
  methodIncludesCheck() {
    console.time("IncludesCheck");
    const arr = this.originalArray.slice();
    const uniqueArr = [];
    
    // Modern alternative to indexOf with better readability
    arr.forEach(item => {
      if (!uniqueArr.includes(item)) {
        uniqueArr.push(item);
      }
    });
    
    console.log("Includes Check:", uniqueArr);
    console.timeEnd("IncludesCheck");
  }

  // Method 4: Reverse Splice (Right to Left)
  methodReverseSplice() {
    console.time("ReverseSplice");
    const arr = this.originalArray.slice();
    let length = arr.length;
    
    // Modify array in-place from end to start
    while (length--) {
      for (let i = 0; i < length; i++) {
        if (arr[length] === arr[i]) {
          arr.splice(length, 1);
          break;
        }
      }
    }
    
    console.log("Reverse Splice:", arr);
    console.timeEnd("ReverseSplice");
  }

  // Method 5: Nested Reverse Splice
  methodNestedReverseSplice() {
    console.time("NestedReverseSplice");
    const arr = this.originalArray.slice();
    let length = arr.length;
    
    // Optimized reverse comparison with nested while loops
    while (length--) {
      let i = length;
      while (i--) {
        if (arr[length] === arr[i]) {
          arr.splice(length, 1);
          break;
        }
      }
    }
    
    console.log("Nested Reverse Splice:", arr);
    console.timeEnd("NestedReverseSplice");
  }

  // Method 6: Forward Splice
  methodForwardSplice() {
    console.time("ForwardSplice");
    const arr = this.originalArray.slice();
    let length = arr.length;
    
    // In-place modification from start to end
    for (let i = 0; i < length; i++) {
      for (let j = i + 1; j < length; j++) {
        if (arr[i] === arr[j]) {
          arr.splice(j, 1);
          length--;
          j--;
        }
      }
    }
    
    console.log("Forward Splice:", arr);
    console.timeEnd("ForwardSplice");
  }

  // Method 7: indexOf Position Check
  methodIndexPosition() {
    console.time("IndexPosition");
    const arr = this.originalArray.slice();
    const uniqueArr = [];
    
    // Compare current index with first occurrence index
    arr.forEach((item, index) => {
      if (arr.indexOf(item) === index) {
        uniqueArr.push(item);
      }
    });
    
    console.log("Index Position:", uniqueArr);
    console.timeEnd("IndexPosition");
  }

  // Method 8: Filter with indexOf
  methodFilterIndex() {
    console.time("FilterIndex");
    const arr = this.originalArray.slice();
    
    // Concise functional programming approach
    const result = arr.filter((item, index) => arr.indexOf(item) === index);
    
    console.log("Filter + indexOf:", result);
    console.timeEnd("FilterIndex");
  }

  // Method 9: Object Property Map
  methodObjectMap() {
    console.time("ObjectMap");
    const arr = this.originalArray.slice();
    const objMap = {};
    
    // Using object properties for uniqueness check
    arr.forEach(item => objMap[item] = true);
    const result = Object.keys(objMap).map(Number);
    
    console.log("Object Map:", result);
    console.timeEnd("ObjectMap");
  }

  // Method 10: ES6 Map
  methodES6Map() {
    console.time("ES6Map");
    const arr = this.originalArray.slice();
    const map = new Map();
    
    // Preserve insertion order with Map
    arr.forEach(item => map.set(item, true));
    const result = Array.from(map.keys());
    
    console.log("ES6 Map:", result);
    console.timeEnd("ES6Map");
  }

  // Method 11: Set Conversion
  methodSetConversion() {
    console.time("SetConversion");
    // Most modern and efficient method
    const result = [...new Set(this.originalArray)];
    
    console.log("Set Conversion:", result);
    console.timeEnd("SetConversion");
  }

  // Method 12: Sort and Adjacent Check
  methodSortAdjacent() {
    console.time("SortAdjacent");
    const arr = this.originalArray.slice();
    
    // Sort-based approach modifies original order
    arr.sort();
    for (let i = arr.length - 1; i > 0; i--) {
      if (arr[i] === arr[i - 1]) {
        arr.splice(i, 1);
      }
    }
    
    console.log("Sort + Adjacent:", arr);
    console.timeEnd("SortAdjacent");
  }

  // Method 13: Custom Sort and Clean
  methodCustomSort() {
    console.time("CustomSort");
    const arr = this.originalArray.slice();
    
    // Custom sorting logic for type consistency
    arr.sort((a, b) => a.toString().localeCompare(b.toString()));
    for (let i = 0; i < arr.length - 1; i++) {
      if (arr[i] === arr[i + 1]) {
        arr.splice(i, 1);
        i--;
      }
    }
    
    console.log("Custom Sort:", arr);
    console.timeEnd("CustomSort");
  }

  // Method 14: Reduce Accumulator
  methodReduceAccumulator() {
    console.time("ReduceAccumulator");
    const arr = this.originalArray.slice();
    
    // Functional approach with reducer
    const result = arr.reduce((acc, item) => {
      return acc.includes(item) ? acc : [...acc, item];
    }, []);
    
    console.log("Reduce Accumulator:", result);
    console.timeEnd("ReduceAccumulator");
  }

  // Method 15: Optimized Push
  methodOptimizedPush() {
    console.time("OptimizedPush");
    const arr = this.originalArray.slice();
    const uniqueArr = [];
    
    // Optimized version of indexOf check
    arr.forEach(item => {
      uniqueArr.indexOf(item) === -1 && uniqueArr.push(item);
    });
    
    console.log("Optimized Push:", uniqueArr);
    console.timeEnd("OptimizedPush");
  }

  // Method 16: Type-safe Filter
  methodTypeSafeFilter() {
    console.time("TypeSafeFilter");
    const arr = this.originalArray.slice();
    const seen = {};
    
    // Prevent type coercion issues
    const result = arr.filter(item => {
      const key = typeof item + JSON.stringify(item);
      return seen[key] ? false : (seen[key] = true);
    });
    
    console.log("Type-safe Filter:", result);
    console.timeEnd("TypeSafeFilter");
  }

  // Method 17: Recursive Approach
  methodRecursiveDedupe(arr = this.originalArray.slice()) {
    console.time("RecursiveDedupe");
    // Base case for recursion
    if (arr.length <= 1) return arr;
    
    const [first, ...rest] = arr;
    const filtered = rest.filter(item => item !== first);
    
    // Recursively process remaining elements
    const result = [first, ...this.methodRecursiveDedupe(filtered)];
    
    console.timeEnd("RecursiveDedupe");
    return result;
  }

  // Method 18: Hash Table Optimization
  methodHashTable() {
    console.time("HashTable");
    const arr = this.originalArray.slice();
    const hash = {};
    const result = [];
    
    // Optimal O(n) time complexity solution
    for (let item of arr) {
      const key = typeof item + JSON.stringify(item);
      if (!hash[key]) {
        hash[key] = true;
        result.push(item);
      }
    }
    
    console.log("Hash Table:", result);
    console.timeEnd("HashTable");
  }
}

// Test Execution
(() => {
  const testArray = [1, 1, 3, -1, 1, 2, 2, 4, 2, 2, -1];
  const deduplicator = new UniqueArray(testArray);
  
  console.log("=== Array Deduplication Benchmark ===");
  
  // Execute all methods
  deduplicator.methodDoubleLoop();
  deduplicator.methodIndexOfCheck();
  deduplicator.methodIncludesCheck();
  deduplicator.methodReverseSplice();
  deduplicator.methodNestedReverseSplice();
  deduplicator.methodForwardSplice();
  deduplicator.methodIndexPosition();
  deduplicator.methodFilterIndex();
  deduplicator.methodObjectMap();
  deduplicator.methodES6Map();
  deduplicator.methodSetConversion();
  deduplicator.methodSortAdjacent();
  deduplicator.methodCustomSort();
  deduplicator.methodReduceAccumulator();
  deduplicator.methodOptimizedPush();
  deduplicator.methodTypeSafeFilter();
  console.log("Recursive:", deduplicator.methodRecursiveDedupe());
  deduplicator.methodHashTable();
})();
