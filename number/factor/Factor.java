
/**
 * @desc
 * 质因数分解Java语言示例
 */

import java.util.*;

class Factor {

  public static List<Integer> factorize(int num) {
    int i = 2;
    List<Integer> result = new ArrayList<>();
    while (num > i * i) {
      while (num % i == 0) {
        result.add(i);
        num /= i;
      }
      i++;
    }
    if (num > 1) {
      result.add(num);
    }
    return result;
  }

  public static void factorize2(int num) {
    int i = 2;
    while (num > 1) {
      while (num % i == 0) {
        System.out.print(i);
        if (num != i) {
          System.out.print(" * ");
        }
        num /= i;
      }
      i++;
    }
  }

  public static void main(String args[]) {
    int num = 20;
    
    long startTime;
    // test1
    System.out.println("start:" + num);
    startTime = System.currentTimeMillis();
    List<Integer> result = Factor.factorize(num);
    for (int i = 0; i < result.size(); i++) {
      System.out.print(result.get(i));
      if (i < result.size() - 1) {
        System.out.print(" * ");
      }
    }
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // test 2
    startTime = System.currentTimeMillis();
    Factor.factorize2(num);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
  }

}

/**
jarry@jarrys-MacBook-Pro factor % java --version
java 14.0.1
Java(TM) SE Runtime Environment (build 14.0.1+7)
Java HotSpot(TM) 64-Bit Server VM (build 14.0.1+7, mixed mode, sharing)
jarry@jarrys-MacBook-Pro factor % javac Factor.java
jarry@jarrys-MacBook-Pro factor % java Factor
start:20
2 * 2 * 5
time:0 ms.
2 * 2 * 5
time:1 ms.
*/