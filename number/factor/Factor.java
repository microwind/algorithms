/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;


class Factor {

  public static void factor1(int num) {
    int i = 2;
    while (num > 1) {
      while (num % i == 0)  {
        System.out.print(i);
        if (num != i) {
          System.out.print(" * ");
        }
        num /= i;
      }
      i++;
    }
  }

  public static void factor2(int num) {
    int i = 2;
    while (num > i * i) {
      while (num % i == 0)  {
        System.out.print(i);
        if (num != i) {
          System.out.print(" * ");
        }
        num /= i;
      }
      i++;
    }
    if (num > 1) {
      System.out.print(num);
    }
  }

  public static void main(String args[]) {
    int num = 20;
    System.out.println("start:" + num);
    long startTime = System.currentTimeMillis();
    Factor.factor1(num);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    System.out.println("start:" + num);
    startTime = System.currentTimeMillis();
    Factor.factor2(num);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
  }

}
