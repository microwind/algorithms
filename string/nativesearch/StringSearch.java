
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

public class StringSearch {

  /**
   * 朴素字符串搜索双循环
   */
  int find(String str, String text) {
    int strLen = str.length();
    int textLen = text.length();
    // 双循环，外循环为目标内容，内循环为查找字符串
    for (int i = 0; i < textLen; i++) {
      int j = 0;
      // 从目标内容的递增下标作为起始点，每次完整对比查找字符串
      for (; j < strLen; j++) {
        // 将查找字符串逐个与目标内容进行比较，匹配则继续。
        // 如果遇到不符合的字符则跳出比较，以目标内容里新的下标作为起始位置重新计算。
        if (str.charAt(j) != text.charAt(i + j)) {
          break;
        }
      }
      // 当查询字符串比较完成时，说明已经匹配成功，返回当前位置。
      if (j == strLen) {
        return i;
      }
    }
    return -1;
  }

  /**
   * 朴素字符串搜索for+while写法，算法与与双循环同
   */
  int find2(String str, String text) {
    int strLen = str.length();
    int textLen = text.length();
    int len = textLen - strLen + 1;
    // 从目标内容逐个开始对比
    for (int i = 0; i < len; i++) {
      // 每次以完整对比查找字符串与目标内容
      int j = 0;
      while (j < strLen) {
        // 当目标内容剩余长度不足时退出
        if (textLen - i < strLen - j) {
          return -1;
        }
        // 当遇到有不匹配的情况跳出循环，从目标内容的下一个位置开始重新计算
        if (str.charAt(j) != text.charAt(i + j)) {
          break;
        }
        j++;
      }
      // 当全部匹配后，则返回当前下标
      if (j == strLen) {
        return i;
      }
    }
    return -1;
  }

  public static void main(final String args[]) {
    StringSearch stringSearch = new StringSearch();
    String str1 = "ABC";
    String text1 = "AABABC";

    String str2 = "AAB";
    String text2 = "AAAABC";

    String str3 = "ABC";
    String text3 = "AABAC";

    int result = -1;
    long startTime;
    // find test
    startTime = System.currentTimeMillis();
    result = stringSearch.find(str1, text1);
    System.out.println("stringSearch.find(" + str1 + ", " + text1 + ")");
    System.out.println("result:" + result);

    result = stringSearch.find(str2, text2);
    System.out.println("stringSearch.find(" + str2 + ", " + text2 + ")");
    System.out.println("result:" + result);

    result = stringSearch.find(str3, text3);
    System.out.println("stringSearch.find(" + str3 + ", " + text3 + ")");
    System.out.println("result:" + result);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // find2 test
    startTime = System.currentTimeMillis();
    result = stringSearch.find2(str1, text1);
    System.out.println("stringSearch.find2(" + str1 + ", " + text1 + ")");

    System.out.println("result:" + result);
    result = stringSearch.find2(str2, text2);
    System.out.println("stringSearch.find2(" + str2 + ", " + text2 + ")");

    System.out.println("result:" + result);
    result = stringSearch.find2(str3, text3);
    System.out.println("stringSearch.find2(" + str3 + ", " + text3 + ")");
    System.out.println("result:" + result);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
  }
}

/*
 * jarry@jarrys-MacBook-Pro nativesearch % java -version
 * java version "14.0.1" 2020-04-14
 * Java(TM) SE Runtime Environment (build 14.0.1+7)
 * Java HotSpot(TM) 64-Bit Server VM (build 14.0.1+7, mixed mode, sharing)
 * jarry@jarrys-MacBook-Pro nativesearch % javac StringSearch.java
 * jarry@jarrys-MacBook-Pro nativesearch % java StringSearch
 * stringSearch.find(ABC, AABABC)
 * result:3
 * stringSearch.find(AAB, AAAABC)
 * result:2
 * stringSearch.find(ABC, AABAC)
 * result:-1
 * 
 * time:22 ms.
 * stringSearch.find2(ABC, AABABC)
 * result:3
 * stringSearch.find2(AAB, AAAABC)
 * result:2
 * stringSearch.find2(ABC, AABAC)
 * result:-1
 * 
 * time:2 ms.
 */